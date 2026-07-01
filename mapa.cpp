#include <iostream>
#include <iomanip>
#include "mapa.h"
#include <fstream>
#include <string>
#include <cmath> // pow()
#include <cstdlib> // rand() e srand()
#include <ctime> // time()

MapaAltitudes::MapaAltitudes(int n) {
    this->tamanho = pow(2, n) + 1;
    this->mapa = new float[tamanho*tamanho];

    for (int i = 0; i < this->tamanho * this->tamanho; i++) {
        mapa[i] = 0;
    }
}

MapaAltitudes::~MapaAltitudes() {
    delete[] this->mapa;
}

void MapaAltitudes::diamond(int linha, int coluna, int passo, float escala) {
    int metade = passo / 2;

    // 1. Índices dos 4 cantos usando a fórmula (lin * tamanho + col)
    int supEsquerdo = linha * this->tamanho + coluna;
    int supDireito  = linha * this->tamanho + (coluna + passo);
    int infEsquerdo = (linha + passo) * this->tamanho + coluna;
    int infDireito  = (linha + passo) * this->tamanho + (coluna + passo);

    // 2. Cálculo da média das altitudes dos cantos
    float media = (this->mapa[supEsquerdo] + this->mapa[supDireito] + this->mapa[infEsquerdo] + this->mapa[infDireito]) / 4.0f;

    // 3. Gerar o deslocamento aleatório (ruído) entre -1.0 e 1.0
    float deslocamento = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;

    // 4. Coordenadas e índice do ponto central (meio)
    int linhaMeio = linha + metade;
    int colunaMeio = coluna + metade;
    int indiceMeio = linhaMeio * this->tamanho + colunaMeio;

    // 5. Atribuição do valor final com o ruído escalado
    this->mapa[indiceMeio] = media + (deslocamento * escala);
}

void MapaAltitudes::square(int linha, int coluna, int passo, float escala) {
    int metade = passo / 2;
    
    float soma = 0.0f;
    int vizinhosValidos = 0;

    // 1. Identificar os 4 vizinhos ortogonais em relação ao ponto (linha, coluna)
    // O ponto recebido aqui é o centro de uma das arestas do quadrado.
    
    // Vizinho de Cima (linha - metade, coluna)
    if (linha - metade >= 0) {
        int cima = (linha - metade) * this->tamanho + coluna;
        soma += this->mapa[cima];
        vizinhosValidos++;
    }

    // Vizinho de Baixo (linha + metade, coluna)
    if (linha + metade < this->tamanho) {
        int baixo = (linha + metade) * this->tamanho + coluna;
        soma += this->mapa[baixo];
        vizinhosValidos++;
    }

    // Vizinho da Esquerda (linha, coluna - metade)
    if (coluna - metade >= 0) {
        int esquerda = linha * this->tamanho + (coluna - metade);
        soma += this->mapa[esquerda];
        vizinhosValidos++;
    }

    // Vizinho da Direita (linha, coluna + metade)
    if (coluna + metade < this->tamanho) {
        int direita = linha * this->tamanho + (coluna + metade);
        soma += this->mapa[direita];
        vizinhosValidos++;
    }

    // 2. Cálculo da média usando apenas os vizinhos que existem (3 ou 4)
    float media = soma / vizinhosValidos;

    // 3. Gerar o deslocamento aleatório (ruído) entre -1.0 e 1.0
    float deslocamento = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;

    // 4. Índice do ponto atual no array 1D
    int indiceAtual = linha * this->tamanho + coluna;

    // 5. Atribuição do valor final com o ruído escalado
    this->mapa[indiceAtual] = media + (deslocamento * escala);
}

float MapaAltitudes::obterAltitude(int lin, int col) {
    return this->mapa[lin * this->tamanho + col];
}

int MapaAltitudes::obterLinhas() {
    return this->tamanho;
}

int MapaAltitudes::obterColunas() {
    return this->tamanho;
}

void MapaAltitudes::gerarMapaAltitudes(unsigned int n, float rugosidade) {
    // 1. O tamanho já foi calculado no construtor como pow(2, n) + 1
    int passo = this->tamanho - 1;
    float escala = 1.0f;

    // 2. Inicializar os 4 cantos da matriz inteira com valores aleatórios entre 0.0 e 1.0
    this->mapa[0 * this->tamanho + 0] = static_cast<float>(rand()) / RAND_MAX;                 // Sup. Esquerdo
    this->mapa[0 * this->tamanho + passo] = static_cast<float>(rand()) / RAND_MAX;             // Sup. Direito
    this->mapa[passo * this->tamanho + 0] = static_cast<float>(rand()) / RAND_MAX;             // Inf. Esquerdo
    this->mapa[passo * this->tamanho + passo] = static_cast<float>(rand()) / RAND_MAX;         // Inf. Direito

    // 3. Loop principal do algoritmo Diamond-Square
    while (passo > 1) {
        int metade = passo / 2;

        // --- ETAPA DIAMOND ---
        // Aplica o método diamond no centro de cada subquadrado
        for (int i = 0; i < this->tamanho - 1; i += passo) {
            for (int j = 0; j < this->tamanho - 1; j += passo) {
                this->diamond(i, j, passo, escala);
            }
        }

        // --- ETAPA SQUARE ---
        // Aplica o método square nos pontos médios das arestas.
        // O mapeamento abaixo garante que passamos por todos os "diamantes" gerados.
        for (int i = 0; i < this->tamanho; i += metade) {
            // Se a linha for par, deslocamos a coluna inicial para pegar os pontos alternados
            int deslocamentoColuna = (i % passo == 0) ? metade : 0;
            
            for (int j = deslocamentoColuna; j < this->tamanho; j += passo) {
                this->square(i, j, passo, escala);
            }
        }

        // 4. Reduzir o passo e atualizar a escala com base na rugosidade para a próxima iteração
        passo /= 2;
        escala *= rugosidade;
    }
}

bool MapaAltitudes::salvarMapaAltitudes(std::string nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        arquivo << this->tamanho << std::endl;
        
        for (int i = 0; i < this->tamanho*this->tamanho; i++) {
            arquivo << this->mapa[i] << ' ';
        }

        return true;
    }

    return false;
}

bool MapaAltitudes::lerMapaAltitudes(std::string nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        std::string linha;
        int novaTamanho;

        arquivo >> novaTamanho;

        getline(arquivo, linha); // pula a primeira linha com o tamanho

        if (this->tamanho != novaTamanho) {
            delete[] this->mapa;

            this->tamanho = novaTamanho;

            float *novoMapa = new float[tamanho*tamanho];

            this->mapa = novoMapa;
        }

        for (int i = 0; i < this->tamanho*this->tamanho; i++) {
            arquivo >> this->mapa[i];
        }

        arquivo.close();

        return true;
    }

    return false;
}