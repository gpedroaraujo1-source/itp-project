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
    std::srand(std::time(0));

    int supEsquerda = 0;
    int supDireito = this->tamanho - 1;
    int infEsquerdo = (this->tamanho - 1) * this->tamanho + 0;
    int infDireito = (this->tamanho - 1) * this->tamanho + (this->tamanho - 1);

    this->mapa[supEsquerda] = (float)rand() / RAND_MAX; // canto superior esquerdo
    this->mapa[supDireito] = (float)rand() / RAND_MAX; // canto superior direito
    this->mapa[infEsquerdo] = (float)rand() / RAND_MAX; // canto inferior esquerdo
    this->mapa[infDireito] = (float)rand() / RAND_MAX; // canto inferior direito

    
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