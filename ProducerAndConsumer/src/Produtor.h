#ifndef PRODUTOR_H
#define PRODUTOR_H

#include "buffer.h"
#include <thread>

//Classe que representa um produtor de itens
class Produtor {
public:
    //Construtor
    Produtor(Buffer& buffer);
    //Define a quantidade de itens que serão produzidos por segundo
    void setInteirosPorSegundo(int inteirosPorSegundo);
    //Produz itens
    void run();

private:
    Buffer& buffer;
    int inteirosPorSegundo;
};

#endif // PRODUTOR_H
