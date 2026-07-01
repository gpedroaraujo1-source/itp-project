#include <iostream>
#include <fstream>
#include <string>
#include "imagem.h"

Imagem::Imagem() {
    this->largura = 0;
    this->altura = 0;
    this->pixels = nullptr;
}

Imagem::Imagem(int largura, int altura) {
    this->largura = largura;
    this->altura = altura;
    this->pixels = new Cor[altura*largura];

    for (int i = 0; i < altura*largura; i++) {
        pixels[i] = {0 , 0, 0};
    }
}

Imagem::~Imagem() {
    delete[] pixels;
}

Cor& Imagem::operator()(int coluna, int linha) {
    return pixels[linha * this->largura + coluna];
}

int Imagem::obterLargura() {
    return this->largura;
}

int Imagem::obterAltura() {
    return this->altura;
}

bool Imagem::lerPPM(std::string nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        std::string linha;
        int novaLargura, novaAltura;
        
        getline(arquivo, linha); //lê e ignora o "P3"
        
        arquivo >> novaLargura >> novaAltura;

        getline(arquivo, linha); //consome o resto da linha com as dimensões

        getline(arquivo, linha); //ignora o "255"

        if (this->altura != novaAltura || this->largura != novaLargura) {
            delete[] this->pixels;

            this->altura = novaAltura;
            this->largura = novaLargura;

            Cor *novoArray = new Cor[altura*largura];

            this->pixels = novoArray;
        }

        for (int i = 0; i < this->altura*this->largura; i++) {
            arquivo >> pixels[i].r >> pixels[i].g >> pixels[i].b;
        }

        arquivo.close();

        return true;
    }

    return false;
}

bool Imagem::salvarPPM(std::string nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        arquivo << "P3" << std::endl;
        arquivo << this->largura << ' ' << this->altura << std::endl;
        arquivo << 255 << std::endl;
        for (int i = 0; i < this->altura*this->largura; i++) {
            arquivo << pixels[i].r << ' ' << pixels[i].g << ' ' << pixels[i].b << std::endl;
        }

        arquivo.close();

        return true;
    }

    return false;
}