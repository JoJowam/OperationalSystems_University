#include "produtor.h"
#include <chrono>
#include <random>

using std::cout;
using std::endl;
using std::mt19937;
using std::random_device;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;
using std::uniform_int_distribution;

Produtor::Produtor(Buffer& buffer) : buffer(buffer), inteirosPorSegundo(0) {}

void Produtor::setInteirosPorSegundo(int inteirosPorSegundo) {
    this->inteirosPorSegundo = inteirosPorSegundo;
}

void Produtor::run() {
    //Aqui eu crio um gerador de números aleatórios pra representar os items criados e mando ele pro pruduzir do buffer.
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);
    int itemsProduzidos = 0;

    while (true) {
        int item = dis(gen); //Item aleatório a ser produzido.

        //Adicionar item ao buffer.
        buffer.produzir(item);
        itemsProduzidos++;
        cout << "Total de items produzidos: " << itemsProduzidos << endl << endl;

        //Aguardar o tempo necessário para produzir a próxima sequência de itens.
        sleep_for(milliseconds(1000 / inteirosPorSegundo));
    }
}
