#ifndef MAPA_H
#define MAPA_H

#include <string>

/**
 * @brief Uma classe que representa um mapa de altitudes.
 */
class MapaAltitudes {
    private:
    float *mapa; ///< Ponteiro para alocação dinâmica das altitudes na matrix.
    int tamanho; ///< Atributo para as dimensões da matrix.

    public:
    /**
     * @brief Construtor padrão. Aloca e inicializa a matriz com valores default.
     */
    MapaAltitudes(int n);

    /**
     * @brief Destrutor.
     */
    ~MapaAltitudes();

    /**
     * @brief Método que consulta o valor de uma altitude dado a sua localização.
     * @param lin Linha onde está localizada a altitude. 
     * @param col Coluna onde está localizada a altitude.
     * @return A altitude localizada em (lin, col).
     */
    float obterAltitude(int lin, int col);

    /**
     * @brief Método para consultar a quantidade de linhas da matriz.
     * @return Quantidade de linhas da matriz.
     */
    int obterLinhas();

    /**
     * @brief Método para consultar a quantidade de colunas da matriz.
     * @return Quantidade de colunas da matriz.
     */
    int obterColunas();

    /**
     * @brief Gera aleatoriamente um mapa de altitudes seguindo o algoritmo Diamond-Square
     * @param n Parâmetro usado para calcular o tamanho da matriz, evitando matrizes de tamanhos inválidos.
     * @param rugosidade Parâmetro para o nível de detalhamento do terreno.
     */
    void gerarMapaAltitudes(unsigned int n, float rugosidade);

    /**
     * @brief Método para salvar a matriz de altitudes em um arquivo.
     * @param nomeArquivo Nome do arquivo onde será salvo.
     * @return true (se for bem sucedido) ou false (se for mal sucedido).
     */
    bool salvarMapaAltitudes(std::string nomeArquivo);

    /**
     * @brief Método para ler a matriz de altitude de um arquivo.
     * @param nomeArquivo Nome do arquivo a ser lido.
     * @return true (se for bem sucedido) ou false (se for mal sucedido).
     */
    bool lerMapaAltitudes(std::string nomeArquivo);
};

#endif