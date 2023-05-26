/*
 * Sistema: TP01 de BCC264 - Sistemas Operacionais.
 * Autor: Josué Villa Real.
 *
 * Descrição: Este programa foi desenvolvido para a disciplina de Sistemas Operacionais
 * lecionada pelo professor Carlos Frederico na Universidade Federal de Ouro Preto. O
 * programa tem como principal objetivo a impressão de informações na tela, como por
 * exemplo: Meus dados e dados de minha distro Linux. O intuito desse exercicio é
 * principalmente fixar conceitos do programa Docker, que será usado durante a disciplina.
 *
 * Principais pontos: Foi pedido no enunciado que fosse impresso o arquivo onde fica contido
 * algumas informações do Linux, pesquisei sobre e chegei ate o "os-release". Salvei o caminho
 * do mesmo na variavel OS_RELEASE_FILE_PATH para melhor vizualização. O menu conta também
 * com a impressão do arquivo txt contendo minhas informações que pode ser encontrado dentro
 * da pasta TP01, e por fim, implementei também opções que dizem respeito aos comandos de sistema,
 * solicitados no enunciado. Utilizei o complemento --help nos comandos relacionados ao fechamento
 * de processos com o intuito de exibir mais informações de uso sobre os mesmos!
 *
 * Uso: Para compilar esse programa, basta digitar:
 *          g++ tp01.cpp -o "nome preferivel do executavel"
 * depois disso, digite:
 *          ./nome_do_executavel
 * */



#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <unistd.h>

using std::ifstream;
using std::string;
using std::cout;
using std::cerr;
using std::cin;

using std::getline;
using std::system;
using std::endl;

//Criando constantes para melhor vizualização do código.
const string OS_RELEASE_FILE_PATH = "/etc/os-release";
const string STUDENT_FILE_PATH = "Josue_Vila_Real.txt";
const string FILE_ERROR_MSG = "Erro ao abrir o arquivo.";
const string INVALID_OPTION_MSG = "Opção inválida. Tente novamente.";


void PrintFile(const string& file_name) {
    //Função para imprimir o arquivo de texto.
    ifstream file_stream(file_name);

    if (!file_stream) {
        cerr << FILE_ERROR_MSG << endl;
        return;
    }

    string line;
    while (getline(file_stream, line)) {
        cout << line << endl;
    }

    file_stream.close();
}

void PrintLinuxOSRelease() {
    //Metodo para imprimir o arquivo /etc/os-release do Linux.
    PrintFile(OS_RELEASE_FILE_PATH);
}

void ShowMenu() {
    //Metodo que representa o Main Menu de meu codigo.
    system("clear");
    cout << "Menu Inicial" << endl;
    cout << "1. Imprimir arquivo de texto" << endl;
    cout << "2. Imprimir arquivo /etc/os-release do Linux" << endl;
    cout << "3. Executar comando 'top'" << endl;
    cout << "4. Executar comando 'ps'" << endl;
    cout << "5. Executar comando 'kill'" << endl;
    cout << "6. Executar comando 'killall'" << endl;
    cout << "7. Executar comando 'pkill'" << endl;
    cout << "8. Executar comando 'renice'" << endl;
    cout << "0. Sair" << endl;
}

int GetOption() {
    //Metodo para pegar a opção do usuario e validar a mesma para evitar erros de input.
    int menu_option;
    cout << "Escolha uma opção: ";

    while (!(cin >> menu_option) || (menu_option < 0 || menu_option > 8)) {
        cout << INVALID_OPTION_MSG << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    cout << endl;
    return menu_option;
}

void HandleOption(int selected_option) {
    //Metodo que lida com o input do usuario e executa a opção escolhida.
    //Optei por usar os comandos --help para exibir informações sobre os comandos.
    system("clear");
    switch (selected_option) {
        case 1:
            PrintFile(STUDENT_FILE_PATH);
            break;
        case 2:
            PrintLinuxOSRelease();
            break;
        case 3:
            system("top");
            break;
        case 4:
            system("ps");
            break;
        case 5:
             execl("/bin/kill", "kill", "--help", NULL);            
	     break;
        case 6:
            system("killall --help");
            break;
        case 7:
            system("pkill --help");
            break;
        case 8:
            system("renice --help");
            break;
        case 0:
            cout << "Saindo..." << endl;
            return;
    }
    cout << "Pressione qualquer tecla para voltar ao menu principal." << endl;
    cin.ignore();
    cin.get();
}

int main() {
    int selected_option;

    do {
        ShowMenu();
        selected_option = GetOption();
        HandleOption(selected_option);
    } while (selected_option != 0);

    return 0;
}
