#ifndef PALETA_H
#define PALETA_H

#include <string>

/**
 * @brief Tipo para definir uma única cor no formato RGB.
 */
struct Cor {
    unsigned int r; ///< Componente vermelho (0 - 255)
    unsigned int g; ///< Componente verde (0 - 255)
    unsigned int b; ///< Componente azul (0 - 255)
};

/**
 * @brief Tipo para definir um conjunto de cores, de forma que cada cor esteja associada a um índice.
 */
class Paleta {
    private:
        Cor *cores; ///< Ponteiro para alocação dinâmica das cores.
        int n_cores; ///< Variável com a quantidade de cores no array.
    
    public:
        
        /**
         * @brief Construtor padrão. Inicializa a paleta vazia.
         */
        Paleta();

        /**
         * @brief Construtor que lê as cores contidas em um arquivo.
         * @param nomeArquivo Nome do arquivo a ser lido.
         */
        Paleta(std::string nomeArquivo);

        /**
         * @brief Função para adicionar uma cor ao conjunto de cores no último índice.
         * @param c A cor a ser adicionada.
         * @return true se a adição for bem sucedida, false se não for possível.
         */
        void adicionarCor(Cor c); 

        /**
         * @brief Função para consultar a quantidade de cores.
         * @return Retorna a quantidade de cores no array.
         */
        int getNumeroCores();

        /**
         * @brief Função para consultar a cor de um índice determinado.
         * @param indice Índice da cor.
         * @return Retorna a cor do respectivo índice.
         */
        Cor getCorIndice(int indice);

        /**
         * @brief Destrutor. Libera a memória alocada.
         */
        ~Paleta();
};

#endif