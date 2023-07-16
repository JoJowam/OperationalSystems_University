#include "buffer.h"

using std::cout;
using std::endl;

Buffer::Buffer(int tamanho) : tamanho(tamanho), proximaPosicao(0), proximoItem(0), inteirosConsumidosPorSegundo(0) {
    itens = new int[tamanho];
}

void Buffer::produzir(int item) {
    //Abaixo declaro a exclusão mútua para garantir que apenas uma thread por vez acesse o buffer.
    std::unique_lock<std::mutex> lock(mutex);

    //Abaixo chamo a função wait que é uma variavel condicional, ela vai suspender a thread atual até que a condição
    //passada como parâmetro seja verdadeira. No caso, a thread vai esperar até que a variável proximaPosicao seja menor
    //que o valor tamanho.
    bufferCheio.wait(lock, [this]() { return proximaPosicao < tamanho; });

    //Aqui adiciono o item no buffer.
    itens[proximaPosicao] = item;
    proximaPosicao++;

    cout << "Foi produzido o item: { " << item << " }"<< endl;
    cout << "Quantidade de items no Buffer: " << proximaPosicao << endl;

    //A notify_one é responsável por notificar uma das threads que estejam esperando na condição bufferVazio.wait()
    //para que elas continuem a execução. No caso vai avisar que tem items no buffer pro consumidor consumir.
    bufferVazio.notify_one();
}

int Buffer::consumir() {
    std::unique_lock<std::mutex> lock(mutex);

    //Aqui a thread vai esperar até que a variável proximaPosicao seja maior que 0.
    bufferVazio.wait(lock, [this]() { return proximaPosicao > 0; });

    int item = itens[proximoItem];
    proximoItem++;

    if (proximoItem == proximaPosicao) {
        proximoItem = 0;
        proximaPosicao = 0;
        inteirosConsumidosPorSegundo++;
    }

   cout << "Foi consumido o item: { " << item << " }" << endl;
   cout << "Quantidade de items no Buffer: " << proximaPosicao << endl;

    //Aqui notifico uma das threads que estejam esperando na condição bufferCheio.wait() para que elas continuem a
    //execução. No caso vai avisar que tem espaço no buffer pro produtor produzir.
    bufferCheio.notify_one();

    return item;
}

int Buffer::getInteirosConsumidosPorSegundo() {
    return inteirosConsumidosPorSegundo;
}
