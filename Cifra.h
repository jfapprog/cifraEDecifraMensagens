/* 
 ** UC: 21045 - Estruturas de Dados e Algoritmos Avançados
 ** e-fólio A 2017-18 (cbcm)
 ** 
 ** Aluno: 1301913 - José Póvoa
 */

#ifndef CIFRA_H
#define CIFRA_H

class Cifra {
private:
    char caracter; //caracter a cifrar
    int chave[8]; //chave para a caixa P

public:
    //construtor com um único parâmetro
    explicit Cifra(const int* chaveInicial);
    //construtor cópia
    Cifra(const Cifra& original);
    //destrutor
    virtual ~Cifra();
    //retorna o caracter
    char GetCaracter() const;
    //modifica o caracter
    void SetCaracter(char caracterNovo);
    //retorna a chave
    const int* GetChave() const;
    //modifica a chave
    void SetChave(const int* chaveNova);
    //retorna o caracter cifrado
    char Cifrar(char caracterAnterior) const;
    //retorna o caracter decifrado
    char Decifrar(char caracterAnterior) const;
    //modifica para a chave inversa (para decifrar)
    void ChaveInversa();
    //retorna true se uma chave é válida
    static bool ValidarChave(const int* chaveTeste);

private:
    //retorna vetor que representa o byte correspondente a um inteiro
    const int* InteiroParaByte(unsigned int numero, int dim) const;
    //retorna vetor que representa o byte correspondente ao caracter
    const int* CaracterParaByte(char caracterEntrada) const;
    //retorna o vetor (byte) resultante do XOR dos dois vetores (bytes)
    const int* OperacaoXOR(const int* vetorByte1, const int* vetorByte2) const;
    //retorna vetor que representa o byte após permutação - caixa P
    const int* CaixaP(const int* palavraEntrada) const;
    //retorna chave hexadecimal de 16 dígitos
    const int* ChaveHexadecimal() const;
    //retorna a potência de base 2 dado o expoente
    int PotenciaBase2(int expoente) const;
    //retorna o vetor que representa parte do byte após substituição - caixa S
    const int* CaixaS(const int* palavraEntrada, int bitInicial, int bitFinal) const;
    //retorna vetor alterado pela cifra de produto PSP
    const int* CascataPSP(const int* palavraEntrada) const;
    //retorna o indice do numero no vetor
    static int IndiceNaChave(const int* chaveProcura, int numero);

};

#endif /* CIFRA_H */
