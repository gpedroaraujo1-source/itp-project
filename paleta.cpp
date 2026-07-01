#include <iostream>
#include <fstream>
#include <string>
#include "paleta.h"

Paleta::Paleta() {
    this->n_cores = 0;
    this->cores = nullptr;
}

Paleta::Paleta(std::string nomeArquivo) {
    this->n_cores = 0;
    this->cores = nullptr;

    std::ifstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        std::string linha;
        while (std::getline(arquivo, linha)) {
            Cor c;
            c.r = stoi(linha.substr(1, 2), nullptr, 16);
            c.g = stoi(linha.substr(3, 2), nullptr, 16);
            c.b = stoi(linha.substr(5, 2), nullptr, 16);

            Paleta::adicionarCor(c);
        }

        arquivo.close();
    } else {
        std::cerr << "Erro: Arquivo não encontrado" << std::endl;
    }
}

void Paleta::adicionarCor(Cor c) {
    Cor *novoArray = new Cor[n_cores+1];

    for (int i = 0; i < this->n_cores; i++) {
        novoArray[i] = this->cores[i]; 
    }

    novoArray[this->n_cores] = c;

    delete[] this->cores;

    this->cores = novoArray;

    this->n_cores++;
}

int Paleta::obterTamanho() {
    return this->n_cores;
}

Cor Paleta::obterCor(int indice) {
    if (indice >= 0 && indice < this->n_cores) {
        return this->cores[indice];
    } else {
        return Cor{0, 0, 0};
    }
}

Paleta::~Paleta() {
    delete[] this->cores;
}