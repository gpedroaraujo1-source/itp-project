#include <iostream>
#include <ctime>
#include <algorithm> // Para std::min e std::max
#include "mapa.h"
#include "paleta.h"
#include "imagem.h"

// Função de integração da Etapa 4
Imagem renderizarTerreno(MapaAltitudes& mapa, Paleta& paleta) {
    int dimen = mapa.obterLinhas();
    // Cria a imagem com as mesmas dimensões do mapa de altitudes
    Imagem img(dimen, dimen);

    // 1. Encontrar a altitude mínima e máxima para normalização
    float altMin = mapa.obterAltitude(0, 0);
    float altMax = mapa.obterAltitude(0, 0);

    for (int i = 0; i < dimen; ++i) {
        for (int j = 0; j < dimen; ++j) {
            float alt = mapa.obterAltitude(i, j);
            if (alt < altMin) altMin = alt;
            if (alt > altMax) altMax = alt;
        }
    }

    float delta = altMax - altMin;
    // Evita divisão por zero caso o mapa seja completamente plano
    if (delta == 0.0f) delta = 1.0f; 

    int nCores = paleta.obterTamanho();

    // 2. Mapear cada altitude para uma cor da paleta
    for (int i = 0; i < dimen; ++i) {
        for (int j = 0; j < dimen; ++j) {
            float alt = mapa.obterAltitude(i, j);
            
            // Normaliza a altitude para o intervalo [0.0, 1.0]
            float altNormalizada = (alt - altMin) / delta;

            // Calcula o índice correspondente na paleta
            int indiceCor = static_cast<int>(altNormalizada * (nCores - 1));
            
            // Garante que o índice está dentro dos limites da paleta
            indiceCor = std::max(0, std::min(indiceCor, nCores - 1));

            // Obtém a cor correspondente e atribui ao pixel da imagem
            Cor corPixel = paleta.obterCor(indiceCor);
            img(i, j) = corPixel;
        }
    }

    return img;
}

int main() {
    // 1. Inicializa a semente aleatória baseada no tempo atual
    srand(time(0));

    // 2. Configura os parâmetros do gerador procedural
    // n = 8 gera um mapa de (2^8) + 1 = 257x257 pixels.
    unsigned int n = 8; 
    float rugosidade = 0.55f;

    std::cout << "--> Gerando mapa de altitudes via Diamond-Square..." << std::endl;
    MapaAltitudes mapa(n);
    mapa.gerarMapaAltitudes(n, rugosidade);

    // 3. Carrega a sua paleta de 30 cores
    std::cout << "--> Carregando paleta de cores (cores.hex)..." << std::endl;
    Paleta paleta("cores.hex"); 

    // 4. Renderiza o terreno cruzando as altitudes com as cores
    std::cout << "--> Colorindo os pixels do terreno..." << std::endl;
    Imagem imagemFinal = renderizarTerreno(mapa, paleta);

    // 5. Salva o resultado no formato PPM (P3)
    std::cout << "--> Salvando arquivo final (terreno.ppm)..." << std::endl;
    if (imagemFinal.salvarPPM("terreno.ppm")) {
        std::cout << "\n[SUCESSO] O arquivo 'terreno.ppm' foi gerado com sucesso!" << std::endl;
        std::cout << "Abra a imagem para visualizar o seu terreno procedural." << std::endl;
    } else {
        std::cerr << "\n[ERRO] Falha ao tentar salvar o arquivo PPM." << std::endl;
    }

    return 0;
}