#ifndef CONSUMIDOR_H
#define CONSUMIDOR_H

#include "buffer.h"
#include <thread>
#include <iostream>

class Consumidor {
    //Classe que representa um consumidor de itens.
private:
    Buffer& buffer;
    int inteirosPorSegundo;

public:
    //Construtor.
    Consumidor(Buffer& buffer);
    //Define a quantidade de itens que serão consumidos por segundo.
    void setInteirosPorSegundo(int inteirosPorSegundo);
    //Consumir itens.
    void run();
};

#endif // CONSUMIDOR_H
