/*
 * Sistema: TP02 - Questão 1 de BCC264 - Sistemas Operacionais.
 * Autor: Josué Villa Real.
 *
 * Descrição: Este programa foi desenvolvido para a disciplina de Sistemas Operacionais
 * lecionada pelo professor Carlos Frederico na Universidade Federal de Ouro Preto. O
 * programa tem como principal objetivo a impressão de um sistema de forks e pipes que
 * visam mostrar como são feitos processos pesados e como eles podem se comunicar.
 *
 * Principais pontos: Para realizar o IPC ("Inter process comunication") utilizei um dos
 * modelos que foi solicitado no enunciado do trabalho, o "pipe". Atravez dele é possivel
 * armazenar e ler informações de um determinado dado atraves das suas reespectivas posições
 * em um vetor, em minha imprementação utilizei de um define para ilustrar melhor qual operação
 * esta sendo feita (READ ou WRITE), Para a leitura e escrita dos dados no pipe!
 * 
 * Para estar criando os processos utilizei a função fork() que é responsavel por criar um "filho"
 * de um processo pai, e a partir disso, o filho pode executar uma determinada tarefa, no caso do
 * programa, o filho é responsavel por realizar as operações de adição e subtração, e o pai é responsavel
 * por realizar a impressão do saldo. Utilizei o processo de print como pai para ilustrar melhor o funcionamento
 * dos processos em um SO.
 * 
 * No geral esse programa serve para mostrar mais a criação de processos pesados e o uso de IPC nos mesmos.
 *
 * Uso: Para compilar esse programa, basta digitar:
 *          gcc -o "nome preferivel do executavel" tp2_fork.c
 * depois disso, digite:
 *          ./nome_do_executavel
 * 
 * */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

/*Definindo as opções de escrita e leitura
que usaremos para manipular as informações
no pipe!*/
#define READ  0
#define WRITE 1

/*Defines para ajudar na leitura do codigo.*/
#define ADD_OPERATION '+'
#define EXIT_OPERATION 'k'
#define PRINT_OPERATION 's'
#define SUBTRACT_OPERATION '-'

/*Estrutura de dados referente aos dados a serem
manipulados pelo pipe, sendo eles saldo e opção
reespectivamente.*/
typedef struct {
    int balance;
    int option;
} IPCData;

//Função de Escrita no pipe.
void writeDataToPipe(int pipefd, IPCData data);
//Função de Leitura no pipe.
IPCData readDataFromPipe(int pipefd);
//Função para fechar os pipes.
void closePipeEnds(int pipefd[2]);


int main() {

    printf("\nPress %c to add 1000 UD\n", ADD_OPERATION);
    printf("Press %c to subtract 1000 UD\n", SUBTRACT_OPERATION);
    printf("Press %c to print the balance value\n", PRINT_OPERATION);
    printf("Press %c to exit the program\n", EXIT_OPERATION);
    printf("Initial balance value: 0\n");

    //Criando pipes para saldo e opção.
    int balancePipe[2], optionPipe[2];
    int failure = 0;

    /*Criando nossos processos pesados*/
    pid_t parentPid, incrementProcessPid, decrementProcessPid;


    /*A Variavel failre armazena os valores 0 ou -1. 0 = Pipe criado,
    -1 = Erro na criação do pipe */

    failure = pipe(balancePipe);
    if (failure < 0) {
        printf("Failed to create pipe.\n");
        exit(1);
    }

    failure = pipe(optionPipe);
    if (failure < 0) {
        printf("Failed to create pipe.\n");
        exit(1);
    }

    //Setando os valores iniciais do saldo e da opção.
    IPCData initialData;
    initialData.balance = 0;
    initialData.option = 0;

    //Escrevendo-os no pipe.
    writeDataToPipe(balancePipe[WRITE], initialData);

    //Armazenando o processo atual como pai e criando um processo filho.
    parentPid = getpid();
    incrementProcessPid = fork();

    if (incrementProcessPid < 0) {
        printf("Error creating fork.\n");
        exit(1);
    }

    /*Se o processo atual for o pai, criamos um novo processo filho. E tomamos cuidado
    Para que os processos filhos não criem mais filhos.*/
    if (getpid() == parentPid) {
        decrementProcessPid = fork();
        if (decrementProcessPid < 0) {
            printf("Error creating fork.\n");
            exit(1);
        }
        if (decrementProcessPid == 0) {
            incrementProcessPid = -1;
        }
    }

    //If que lida com a opção de impressão do saldo. Primeiro checamos se estamos no processo correto.
    if (getpid() == parentPid) {
        IPCData data;
        int character = 0;

        //While principal da opção de impressão do saldo.
        while (character != EXIT_OPERATION && tolower(character) != EXIT_OPERATION) {

            do {
                character = (int)getchar();
            } while (character != ADD_OPERATION && character != PRINT_OPERATION &&
                     character != SUBTRACT_OPERATION && tolower(character) != EXIT_OPERATION);
            //Lemos o saldo do pipe e o imprimimos.
            if (character == PRINT_OPERATION) {
                data = readDataFromPipe(balancePipe[READ]);
                printf("\n");
                printf("Print process PID: %d\n", getpid());
                printf("Balance: %d\n", data.balance);
                printf("\n");
                writeDataToPipe(balancePipe[WRITE], data);
            } else {
                //Se não for a opção de impressão, retornamos com a informação para a origem (ilustrativo).
                data.option = character;
                writeDataToPipe(optionPipe[WRITE], data);
            }

            if (tolower(character) == EXIT_OPERATION) {
                printf("Killing procees\n");
                kill(incrementProcessPid, SIGKILL);
                kill(decrementProcessPid, SIGKILL);
                kill(getpid(), SIGKILL);
                exit(0);
            }

        }
        //if que lida com o processo de incrementação do saldo. Primeiro checamos se estamos no processo correto.
    } else if (incrementProcessPid == 0) {
        IPCData data;

        do {
            data = readDataFromPipe(optionPipe[READ]);

            //Se a opção for de incrementação, lemos o saldo do pipe e o incrementamos.
            if (data.option == ADD_OPERATION) {

                printf("\n");
                printf("Addition process PID: %d\n", getpid());
                printf("\n");
                data = readDataFromPipe(balancePipe[READ]);
                data.balance += 1000;
                writeDataToPipe(balancePipe[WRITE], data);

            } else {
                //Se não for a opção de incrementação, retornamos com a informação para a origem (ilustrativo).
                writeDataToPipe(optionPipe[WRITE], data);
            }

        } while (data.option != EXIT_OPERATION && tolower(data.option) != EXIT_OPERATION);

    // if que lida com o processo de decrementação do saldo. Primeiro checamos se estamos no processo correto.
    } else if (decrementProcessPid == 0) {
        IPCData data;

        do {
            data = readDataFromPipe(optionPipe[READ]);

            //Se a opção for de decrementação, lemos o saldo do pipe e o decrementamos.
            if (data.option == SUBTRACT_OPERATION) {

                printf("\n");
                printf("Subtraction process PID: %d\n", getpid());
                printf("\n");
                data = readDataFromPipe(balancePipe[READ]);
                data.balance -= 1000;
                writeDataToPipe(balancePipe[WRITE], data);

            } else {
                //Se não for a opção de decrementação, retornamos com a informação para a origem (ilustrativo).
                writeDataToPipe(optionPipe[WRITE], data);
            }

        } while (data.option != EXIT_OPERATION && tolower(data.option) != EXIT_OPERATION);
    }

    //Fechando os pipes.
    closePipeEnds(balancePipe);
    closePipeEnds(optionPipe);

    return 0;
}

void writeDataToPipe(int pipefd, IPCData data) {
    // Mandando para o pipe o endereço de memória do dado a ser armazenado.
    write(pipefd, &data, sizeof(IPCData));
}

IPCData readDataFromPipe(int pipefd) {
    IPCData data;
    // Lendo os dados do pipe
    read(pipefd, &data, sizeof(IPCData));
    return data;
}

void closePipeEnds(int pipefd[2]) {
    close(pipefd[READ]);
    close(pipefd[WRITE]);
}
