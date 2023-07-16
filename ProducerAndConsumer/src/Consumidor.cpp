#include "consumidor.h"
#include <chrono>

using std::cout;
using std::endl;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

Consumidor::Consumidor(Buffer& buffer) : buffer(buffer) {}

void Consumidor::setInteirosPorSegundo(int inteirosPorSegundo) {
    this->inteirosPorSegundo = inteirosPorSegundo;
}

void Consumidor::run() {
    //Aqui é a função onde faço o consumo dos itens do buffer. Nela apenas chamo o método consumir do buffer e imprimo.
    //o total de itens consumidos.
    int itemsConsumidos = 0;

    while (true) {
        //Remove item do buffer.
        buffer.consumir();

        itemsConsumidos++;
        cout << "Total de items consumidos: " << itemsConsumidos << endl << endl;

        //Aguardar um tempo para continuar consumindo itens.
        sleep_for(milliseconds(1000 / inteirosPorSegundo));
    }
}
