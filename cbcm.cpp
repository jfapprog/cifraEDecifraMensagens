/* 
 ** UC: 21045 - Estruturas de Dados e Algoritmos Avançados
 ** e-fólio A 2017-18 (cbcm)
 ** 
 ** Aluno: 1301913 - José Póvoa
 */

#include <iostream>
#include "Cifra.h"

using namespace std;

int main(int argc, char** argv) {

    //verificar se o número de argumentos está correto
    if (argc != 2 && argc != 3) {
        cerr << "Sintaxe: cbcm <c|d> [chave]" << endl;
        return 0;
    }

    //verificar se a opção é válida
    if (argv[1][0] != 'c' && argv[1][0] != 'd') {
        cerr << "Opção inválida, opções válidas c - cifrar ou d - decifrar" << endl;
        return 0;
    }

    //chave por defeito
    int chave[8] = {1, 0, 5, 3, 7, 6, 4, 2};

    //extrair a chave introduzida pelo utilizador
    if (argc == 3) {
        //verificar se tamanho da chave é correto
        int comprimento = 0;
        while (argv[2][comprimento] != '\0')
            comprimento++;
        if (comprimento != 8) {
            cerr << "A chave tem que ter os 8 dígitos octais" << endl;
            return 0;
        }
        //transformar os caracteres em números octais
        for (int i = 0; i < 8; i++) {
            chave[i] = argv[2][i] - '0';
        }
    }

    //validar a chave - verificar se esta tem todos os dígitos octais
    if (!Cifra::ValidarChave(chave)) {
        cerr << "A chave tem que ter os 8 dígitos octais" << endl;
        return 0;
    }

    //criar objeto cifra
    Cifra* cifra = new Cifra(chave);

    //variáveis para os caracteres
    char caracterLido;
    char caracterCifrado;
    char caracterAnterior = (char) 0xA5;

    //cifrar
    if (argv[1][0] == 'c') {
        //ler os caracteres até ao fim do ficheiro
        while (cin.get(caracterLido)) {
            //alterar caracter a cifrar
            cifra->SetCaracter(caracterLido);
            //obter caracter cifrado
            caracterCifrado = cifra->Cifrar(caracterAnterior);
            //escrever caracter cifrado
            cout << caracterCifrado;
            //guardar caracter cifrado
            caracterAnterior = caracterCifrado;
        }
    }

    //decifrar
    if (argv[1][0] == 'd') {
        //inverter chave
        cifra->ChaveInversa();
        //ler os caracteres até ao fim do ficheiro
        while (cin.get(caracterLido)) {
            //alterar caracter a decifrar
            cifra->SetCaracter(caracterLido);
            //obter caracter decifrado
            caracterCifrado = cifra->Decifrar(caracterAnterior);
            //escrever caracter decifrado
            cout << caracterCifrado;
            //guardar caracter cifrado
            caracterAnterior = caracterLido;
        }
    }

    //libertar memória reservada para o objeto Cifra
    delete cifra;

    return 0;
}

