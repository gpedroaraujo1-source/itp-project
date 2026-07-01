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