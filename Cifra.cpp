/* 
 ** UC: 21045 - Estruturas de Dados e Algoritmos Avançados
 ** e-fólio A 2017-18 (cbcm)
 ** 
 ** Aluno: 1301913 - José Póvoa
 */

#include <iostream>
#include "Cifra.h"

using namespace std;

//FUNÇÕES PÚBLICAS

Cifra::Cifra(const int* chaveInicial) {
    //copiar números octais da chave
    for (int i = 0; i < 8; i++) {
        chave[i] = chaveInicial[i];
    }
}

Cifra::Cifra(const Cifra& original) {
    caracter = original.caracter;
    //copiar números octais da chave
    for (int i = 0; i < 8; i++) {
        chave[i] = original.chave[i];
    }
}

Cifra::~Cifra() {
}

char Cifra::GetCaracter() const {
    return caracter;
}

void Cifra::SetCaracter(char caracterNovo) {
    caracter = caracterNovo;
}

const int* Cifra::GetChave() const {
    return chave;
}

void Cifra::SetChave(const int* chaveNova) {
    //copiar números octais da chave nova
    for (int i = 0; i < 8; i++) {
        chave[i] = chaveNova[i];
    }
}

char Cifra::Cifrar(char caracterAnterior) const {
    //obter byte correspondente ao caracter
    const int* byteCaracter = CaracterParaByte(caracter);
    //obter byte correspondente ao caracterAnterior
    const int* byteCaracterAnterior = CaracterParaByte(caracterAnterior);

    //realizar operação XOR entre os dois bytes caracteres
    const int* byteXOR = OperacaoXOR(byteCaracter, byteCaracterAnterior);
    //libertar memória reservada para o vetor byteCaracter
    delete byteCaracter;
    //libertar memória reservada para o vetor byteCaracterAnterior
    delete byteCaracterAnterior;

    //obter byte cifrado
    const int* byteCifrado = CascataPSP(byteXOR);
    //libertar memória reservada para o vetor byteCaracter
    delete byteXOR;

    //converter byte em número decimal
    int numero = 0;
    for (int i = 0; i < 8; i++) {
        numero += (byteCifrado[i] * PotenciaBase2(i));
    }
    //libertar memória reservada para o vetor byteCifrado
    delete byteCifrado;

    //converter para char
    char caracterCifrado = (char) numero;

    return caracterCifrado;
}

char Cifra::Decifrar(char caracterAnterior) const {
    //obter byte correspondente ao caracter
    const int* byteCaracter = CaracterParaByte(caracter);

    //obter byte decifrado
    const int* byteDecifrado = CascataPSP(byteCaracter);
    //libertar memória reservada para o vetor byteCaracter
    delete byteCaracter;

    //obter byte correspondente ao caracterAnterior
    const int* byteCaracterAnterior = CaracterParaByte(caracterAnterior);

    //realizar operação XOR entre os dois bytes caracteres
    const int* byteXOR = OperacaoXOR(byteDecifrado, byteCaracterAnterior);
    //libertar memória reservada para o vetor byteCaracterAnterior
    delete byteCaracterAnterior;
    //libertar memória reservada para o vetor byteDecifrado
    delete byteDecifrado;

    //converter byte em número decimal
    int numero = 0;
    for (int i = 0; i < 8; i++) {
        numero += (byteXOR[i] * PotenciaBase2(i));
    }
    //libertar memória reservada para o vetor byteXOR
    delete byteXOR;

    //converter para char
    char caracterDecifrado = (char) numero;

    return caracterDecifrado;
}

void Cifra::ChaveInversa() {
    int* chaveInv = new int[8]; //vetor para chave inversa
    //chave inversa corresponde, para cada numero octal, ao índice no vetor chave
    for (int i = 0; i < 8; i++) {
        chaveInv[i] = IndiceNaChave(chave, i);
    }
    //alterar chave para a chave inversa
    for (int i = 0; i < 8; i++) {
        chave[i] = chaveInv[i];
    }
    //libertar memória reservada para o vetor chaveInv
    delete chaveInv;
}

//FUNÇÕES PÚBLICAS STATIC

bool Cifra::ValidarChave(const int* chaveTeste) {
    for (int i = 0; i < 8; i++) {
        //procurar número octal i na chave de teste
        if (Cifra::IndiceNaChave(chaveTeste, i) == -1)
            return false;
    }
    return true;
}

//FUNÇÕES PRIVADAS

const int* Cifra::InteiroParaByte(unsigned int numero, int dim) const {
    const int SHIFT = dim - 1;
    const unsigned int MASCARA = 1 << SHIFT;
    int* byte = new int[dim];
    for (int i = 0; i < dim; i++) {
        //realizar operação AND com MASCARA
        byte[dim - 1 - i] = (numero & MASCARA ? 1 : 0);
        //realizar "shift" de um bit à direita
        numero <<= 1;
    }
    return byte;
}

const int* Cifra::CaracterParaByte(char caracterEntrada) const {
    unsigned int numero = (unsigned int) caracterEntrada; //inteiro correspondente ao caracter
    const int* byte = InteiroParaByte(numero, 8); //vetor para o byte correspondente ao caracter
    return byte;
}

const int* Cifra::OperacaoXOR(const int* vetorByte1, const int* vetorByte2) const {
    int* vetorXOR = new int[8];
    //percorrer vetores
    for (int i = 0; i < 8; i++) {
        if (vetorByte1[i] == 1) {
            if (vetorByte2[i] == 0)
                vetorXOR[i] = 1; //1 XOR 0 = 1
            else
                vetorXOR[i] = 0; //1 XOR 1 = 0
        } else {
            if (vetorByte2[i] == 1)
                vetorXOR[i] = 1; //0 XOR 1 = 1 
            else
                vetorXOR[i] = 0; //0 XOR 0 = 0
        }
    }
    return vetorXOR;
}

const int* Cifra::CaixaP(const int* palavraEntrada) const {
    int* palavraSaida = new int[8]; //vetor para byte permutado
    for (int i = 0; i < 8; i++) {
        //obter na chave ordem do bit a copiar
        int ordemBit = chave[i];
        //copiar bit
        palavraSaida[i] = palavraEntrada[ordemBit];
    }
    return palavraSaida;
}

const int* Cifra::ChaveHexadecimal() const {
    int* chaveHexa = new int[16];
    //copiar os 8 dígitos da chave octal
    for (int i = 0; i < 8; i++) {
        chaveHexa[i] = chave[i];
    }
    //adicionar os 8 dígitos da chave octal adicionados de 8
    for (int i = 0; i < 8; i++) {
        chaveHexa[i + 8] = chave[i] + 8;
    }
    return chaveHexa;
}

int Cifra::PotenciaBase2(int expoente) const {
    int resultado = 1;
    for (int i = 0; i < expoente; i++) {
        resultado *= 2;
    }
    return resultado;
}

const int* Cifra::CaixaS(const int* palavraEntrada, int bitInicial, int bitFinal) const {
    int numHexaEntrada = 0; //numero hexadecimal (0-15) correspondente aos 4 bits
    //converter palavra de 4 bits em número hexadecimal
    for (int i = bitInicial; i <= bitFinal; i++) {
        numHexaEntrada += (palavraEntrada[i] * PotenciaBase2(i - bitInicial));
    }
    //obter chave hexadecimal
    const int* chaveHexadecimal = ChaveHexadecimal();
    //obter numero hexadecimal que substitui
    int numHexaSaida = chaveHexadecimal[numHexaEntrada];
    //converter numero hexadecimal que sustitui para binário de 4 bits
    const int* palavraSaida = InteiroParaByte(numHexaSaida, 4);
    //libertar memória reservada para o vetor chaveHexadecimal
    delete chaveHexadecimal;
    return palavraSaida;
}

const int*Cifra::CascataPSP(const int* palavraEntrada) const {
    //Caixa P
    //obter byte permutado
    const int* bytePermutado1 = CaixaP(palavraEntrada);

    //Caixas S
    //obter primeira parte do byte substituído
    const int* byteSubs1 = CaixaS(bytePermutado1, 0, 3);
    //obter segunda parte do byte substituído
    const int* byteSubs2 = CaixaS(bytePermutado1, 4, 7);
    //libertar memória reservada para o byte permutado
    delete bytePermutado1;

    //juntar primeira parte e segunda parte
    int* byteSubs = new int[8];
    for (int i = 0; i < 4; i++) {
        byteSubs[i] = byteSubs1[i];
    }
    for (int i = 0; i < 4; i++) {
        byteSubs[i + 4] = byteSubs2[i];
    }
    //libertar memória reservada para as duas partes do byte substituído
    delete byteSubs1;
    delete byteSubs2;

    //Caixa P
    //obter byte permutado
    const int* bytePermutado2 = CaixaP(byteSubs);
    //libertar memória reservada para o vetor byteSubs
    delete byteSubs;
    return bytePermutado2;
}

//FUNÇÕES PRIVADAS STATIC

int Cifra::IndiceNaChave(const int* chaveProcura, int numero) {
    //percorrer chave até encontrar número
    for (int i = 0; i < 8; i++) {
        if (chaveProcura[i] == numero)
            return i;
    }
    //retornar -1 se não encontrar
    return -1;
}
