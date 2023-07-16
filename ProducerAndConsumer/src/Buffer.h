#ifndef BUFFER_H
#define BUFFER_H

#include <mutex>
#include <condition_variable>
#include <iostream>

using std::mutex;
using std::condition_variable;

class Buffer {
//Classe que representa um buffer de itens.
private:
    int* itens;
    int tamanho;
    int proximaPosicao;
    int proximoItem;
    int inteirosConsumidosPorSegundo;

//Aqui crio um mutex e duas variáveis de condição. O mutex é usado para garantir que apenas uma thread por vez acesse o
//buffer e as variáveis de condição são usadas para sinalizar quando o buffer está cheio ou vazio.
    mutex mutex;
    condition_variable bufferCheio;
    condition_variable bufferVazio;

public:
    Buffer(int tamanho);
    void produzir(int item);
    int consumir();
    int getInteirosConsumidosPorSegundo();
    int getTamanho();


};

#endif // BUFFER_H
