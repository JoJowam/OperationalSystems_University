/*
 * Sistema: TP03 - BCC264 - Sistemas Operacionais.
 * Autor: Josué Villa Real
 *
 * Descrição: Este programa foi desenvolvido para a disciplina de Sistemas Operacionais
 * lecionada pelo professor Carlos Frederico na Universidade Federal de Ouro Preto. O
 * programa tem como principal objetivo a implementação de um sistema de produtores e
 * consumidores, onde os produtores são responsaveis por produzir itens e os consumidores
 * por consumir os mesmos. Para a implementação do programa foi utilizado a linguagem C++.
 *
 * Principais pontos: Para evitar a exclusão mútua entre os processos, utilizei a biblioteca
 * <mutex> que é responsavel por criar um mutex, que é uma variável que garante que apenas uma
 * Thread por vez acesse uma determinada região critica. Para realizar a sincronização entre
 * as threads, utilizei a biblioteca <condition_variable> que é responsavel por criar variaveis
 * de condição, que são variaveis que sinalizam quando uma determinada condição é verdadeira ou
 * falsa, e a partir disso, os processos podem ser sincronizados.
 *
 * No geral esse programa serve para mostrar conceitos de SO como race condition, exclusão mútua e
 * sincronização de threads.
 *
 * Uso: Para compilar esse programa, basta digitar dentro da pasta TP03:
 *          make
 * depois disso, digite:
 *          ./main
 * */

#include "produtor.h"
#include "consumidor.h"
#include "buffer.h"
#include <iostream>
#include <thread>
#include <typeinfo>

using std::cin;
using std::cout;
using std::endl;
using std::thread;
using std::exception;

int main() {
    Buffer buffer(100); //Tamanho do buffer: 100
    Produtor produtor(buffer); //Produtor do buffer
    Consumidor consumidor(buffer); //Consumidor do buffer

    try {

        //Solicita a quantidade de inteiros por segundo a serem gerados
        int producaoPorSegundo;
        cout << "Digite a quantidade de inteiros por segundo a serem produzidos: ";
        cin >> producaoPorSegundo;

        //Trata de erros de input
        if (producaoPorSegundo <= 0) {
            throw "A quantidade de inteiros por segundo a serem gerados deve ser maior que zero.";
        } else if (producaoPorSegundo > 100) {
            throw "A quantidade de inteiros por segundo a serem gerados deve ser menor ou igual a 100.";
        } else if (typeid(producaoPorSegundo) != typeid(int)) {
            throw "A quantidade de inteiros por segundo a serem gerados deve ser um número inteiro.";
        }

        produtor.setInteirosPorSegundo(producaoPorSegundo);

        //Solicita a quantidade de inteiros por segundo a serem consumidos
        int consumoPorSegundo;
        cout << "Digite a quantidade de inteiros por segundo a serem consumidos: ";
        cin >> consumoPorSegundo;

        //Trata de erros de input
        if (consumoPorSegundo <= 0) {
            throw "A quantidade de inteiros por segundo a serem consumidos deve ser maior que zero.";
        } else if (consumoPorSegundo > 100) {
            throw "A quantidade de inteiros por segundo a serem consumidos deve ser menor ou igual a 100.";
        } else if (typeid(consumoPorSegundo) != typeid(int)) {
            throw "A quantidade de inteiros por segundo a serem consumidos deve ser um número inteiro.";
        }

        consumidor.setInteirosPorSegundo(consumoPorSegundo);

    } catch (const char* exception) {
        cout << "ERRO: " << exception << endl;
        return 1;
    }

    //Cria as threads para o produtor e o consumidor.
    thread produtorThread(&Produtor::run, &produtor);
    thread consumidorThread(&Consumidor::run, &consumidor);

    //Aguarda o término das threads para encerrar o programa e retorna qualquer erro que possa acontecer durante.
    try {
        produtorThread.join();
        consumidorThread.join();
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
