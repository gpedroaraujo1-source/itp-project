#ifndef IMAGEM_H
#define IMAGEM_H

#include <string>
#include "paleta.h"

/**
 * @brief Tipo para definir uma única Pixel no formato.
 */
struct Pixel {
    unsigned int r; ///< Componente vermelho (0 - 255)
    unsigned int g; ///< Componente verde (0 - 255)
    unsigned int b; ///< Componente azul (0 - 255)
};

/**
 * @brief Classe para representar uma imagem no formato PPM.
 */
class Imagem {
    private:
        int largura, altura; ///< Dimensões da matriz.
        Cor *pixels; ///< Ponteiro para a alocação dinâmica dos pixels/cores.
    
    public:
        Imagem();
    
        /**
         * @brief Construtor padrão.
         * @param largura Comprimento da Imagem.
         * @param altura Altura da Imagem.
         */
         Imagem(int largura, int altura);

        /**
         * @brief Destrutor.
         */
        ~Imagem();
        
        Cor& operator()(int linha, int coluna);

        /**
         * @brief Método para ler uma imagem a partir de um arquivo. Caso as dimensões sejam diferentes, o método redimensiona.
         * @param nomeArquivo Nome do arquivo a ser lido.
         */
        bool lerPPM(std::string nomeArquivo);

        /**
         * @brief Método para salvar uma imagem no formato PPM a partir de um arquivo.
         * @param nomeArquivo Nome do arquivo a ser salvo.
         */
        bool salvarPPM(std::string nomeArquivo);

        /**
         * @brief Método para consultar a largura da imagem.
         * @return Largura da imagem.
         */
        int obterLargura();

        /**
         * @brief Método para consultar a altura da imagem.
         * @return Altura da imagem.
         */
        int obterAltura();
};

#endif