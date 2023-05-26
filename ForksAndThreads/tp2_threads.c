/*
 * Sistema: TP02 - Questão 2 de BCC264 - Sistemas Operacionais.
 * Autor: Josué Villa Real
 *
 * Descrição: Este programa foi desenvolvido para a disciplina de Sistemas Operacionais
 * lecionada pelo professor Carlos Frederico na Universidade Federal de Ouro Preto. O
 * programa tem como principal objetivo a impressão de um sistema de threads que
 * visam mostrar como são feitos threads em um sistema fechado e como manupular os dados
 * entre elas.
 *
 * Principais pontos: Foi solicitado no enunciado do trabalho que explicassemos alguns pontos, vou explica-los
 * tanto aqui quanto em meu video para não deixar nada passar.
 * 
 * 1 - Race Condition: O meu codigo apresenta sim race condition pois a a variável compartilhada balance é 
 * acessada e modificada pelas threads de incremento e decremento sem qualquer mecanismo de sincronização, 
 * o que pode levar a resultados inconsistentes. Para resolver isso eu precisaria usar um mecanismo de 
 * mutex ou semaphoros que foram apresentados em aula, com mutex trancaria a variavel balance para 
 * "protege-la" das demais threads do sistema, assim evitando que uma thread acesse a variavel enquanto
 * outra esta modificando a mesma. Como acho que o intuito desse trabalho era só mostrar a criação de threads
 * e como elas funcionam, não implementei nenhum mecanismo de sincronização.
 * 
 * 2 - Principais diferenças entre threads e processos: Notei durante a implentação do trabalho o porque
 * de os forks levarem o nome de processos "pesados", notei logo apos de implementar as threads, pois as
 * mesmas são uma forma mais "leve" de implementar o paralelismo. Falando muito por cima, as threads são
 * diferentes em relação aos forks pois elas compartilham o mesmo espaço de endereçamento, enquanto que
 * os forks tem um espaço de endereçamento diferente, tornando mais dificil a comunicação entre as 
 * "entidades" do programa. O custo de criação das threads também é menor pois exige menos recursos do sistema
 * mas no caso dos forks é necessario duplicar todo o processo, o que exige mais recursos do sistema. 
 * No mais, notei que ao criar uma thread, são criadas entidades que compartilham do mesmo processo, então
 * o compartilhamento de memoria é mais independente (por isso não implementei o pipe aqui), enquanto que 
 * no fork, são criados tres processos diferentes que são cópias independentes, então a troca de informações 
 * entre eles é mais dificil.
 * 
 * Acho que os forks são mais utilizados em sistemas que precisam de mais segurança, pois como os processos
 * não se comunicam, é mais dificil de um processo "roubar" informações de outro, enquanto que as threads
 * são mais utilizadas em sistemas que precisam de mais velocidade, pois como elas compartilham o mesmo
 * espaço de endereçamento, a troca de informações é mais rapida. Isso se remete a escalabilidade, onde
 * as threads podem ser escalonadas em sistemas com suporte de multthreading, possibilitando extrair mais
 * desempenho do sistema. E os forks são mais visados em sistemas fechados que trabalham com processos
 * independentes e isolados.
 * 
 * 3 - Diferenças entre pthread_join e pthread_kill e pthread_exit: A pthread_join é utilizada para esperar
 * que uma thread termine sua execução, enquanto que a pthread_kill é utilizada para enviar um sinal para
 * uma thread, geralmente se usa o sinal SIGKILL para matar uma thread. Já a pthread_exit é utilizada para
 * terminar a execução de uma thread, ela é mais utilizada quando a thread termina sua execução de forma
 * inesperada, como por exemplo, quando ocorre um erro de segmentação ou só para finalizar a thread mesmo.
 * 
 * No geral esse programa serve para mostrar mais a criação de threads.
 *
 * Uso: Para compilar esse programa, basta digitar:
 *          gcc -o "nome preferivel do executavel" tp2_threads.c
 * depois disso, digite:
 *          ./nome_do_executavel
 * 
 * */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/syscall.h>

#define ADD_OPERATION '+'
#define SUBTRACT_OPERATION '-'
#define PRINT_OPERATION 's'
#define EXIT_OPERATION 'k'
#define RESTART_OPERATION 'r'

int balance = 0;
char operation;

struct thread_data {
    pthread_t thread;
};

void main_menu();

/* Funções para cada operação de cada thread*/
void *increment_function(void *arg);
void *decrement_function(void *arg);
void *print_function(void *arg);
void *restart_function(void *arg);

int main() {

    main_menu();
    
    pthread_t increment_thread;
    pthread_t decrement_thread;
    pthread_t print_thread;
    pthread_t restart_thread;

    // Criando as structs para cada thread.
    struct thread_data *thread_of_print  = (struct thread_data *) malloc(sizeof(struct thread_data));
    struct thread_data *thread_of_increment    = (struct thread_data *) malloc(sizeof(struct thread_data));
    struct thread_data *thread_of_decrement = (struct thread_data *) malloc(sizeof(struct thread_data));

    // Atribuindo as threads para cada struct.
    thread_of_print->thread  = print_thread;
    thread_of_increment->thread    = increment_thread;
    thread_of_decrement->thread = decrement_thread;

    // Criando as threads.
    pthread_create(&print_thread, NULL, print_function, (void *) thread_of_print);
    pthread_create(&increment_thread, NULL, increment_function, (void *) thread_of_increment);
    pthread_create(&decrement_thread, NULL, decrement_function, (void *) thread_of_decrement);

    do {
        //Lendo qual a operação a ser realizada.
        scanf(" %c", &operation);

        //Discartando caracteres "extras" do buffer.
        while (getchar() != '\n') {}

        //Se for a opção de sair, mata as threads.
        if (operation == EXIT_OPERATION) {

            pthread_kill(increment_thread, 0);
            pthread_kill(decrement_thread, 0);
            pthread_kill(print_thread, 0);

            printf("\n");
            printf("==============================================\n");
            printf("Terminating Threads...\n");
            printf("\n");
        }

        //Se for a opção de reiniciar o sistema, mata as threads e cria novas.
        else if (operation == RESTART_OPERATION) {

            pthread_join(increment_thread, NULL);
            pthread_kill(increment_thread, 0);
            pthread_join(decrement_thread, NULL);
            pthread_kill(decrement_thread, 0);
            pthread_join(print_thread, NULL);
            pthread_kill(print_thread, 0);

            pthread_create(&restart_thread, NULL, restart_function, NULL);
            pthread_create(&print_thread, NULL, print_function, (void *) thread_of_print);
            pthread_create(&increment_thread, NULL, increment_function, (void *) thread_of_increment);
            pthread_create(&decrement_thread, NULL, decrement_function, (void *) thread_of_decrement);

            pthread_join(restart_thread, NULL);
            main_menu();
        }

    } while (operation != EXIT_OPERATION);

    return 0;
}
// Menu main_menu
void main_menu() {
    printf("\n");
    printf("Press %c to add 1000 UD\n", ADD_OPERATION);
    printf("Press %c to subtract 1000 UD\n", SUBTRACT_OPERATION);
    printf("Press %c to print the balance value\n", PRINT_OPERATION);
    printf("Press %c to exit the program\n", EXIT_OPERATION);
    printf("Press %c to restart all operations\n", RESTART_OPERATION);
    printf("\n");
}

//Função de icremento.
void *increment_function(void *arg) {

    //Loop infinito para a thread ficar sempre ativa, esperando a operação ser chamada.
    do {

        if (operation == ADD_OPERATION) {
            printf("==============================================\n");
            printf("\nAddition thread TID: %ld\n", syscall(__NR_gettid));
            printf("\n");
            balance += 1000;
            operation = 0;
        }

        //Se a operação for de saída ou reiniciar, a thread é finalizada.
        else if (operation == EXIT_OPERATION || operation == RESTART_OPERATION) {
            pthread_exit(0);
        }

    } while (1);
}

// Função de decremento.
void *decrement_function(void *arg) {
    // Loop infinito para a thread ficar sempre ativa, esperando a operação ser chamada.
    do {

        if (operation == SUBTRACT_OPERATION) {
            printf("==============================================\n");
            printf("\nSubtraction thread TID: %ld\n", syscall(__NR_gettid));
            printf("\n");
            balance -= 1000;
            operation = 0;
        }

        //Se a operação for de saída ou reiniciar, a thread é finalizada.
        else if (operation == EXIT_OPERATION || operation == RESTART_OPERATION) {
            pthread_exit(0);
        }

    } while (1);
}

// Função de impressão.
void *print_function(void *arg) {
    // Loop infinito para a thread ficar sempre ativa, esperando a operação ser chamada.
    do {
        if (operation == PRINT_OPERATION) {
            printf("\n");
            printf("==============================================\n");
            printf("Print process TID: %ld\n", syscall(__NR_gettid));
            printf("Balance: %d units\n", balance);
            printf("\n");
            operation = 0;
        }

        //Se a operação for de saída ou reiniciar, a thread é finalizada.
        else if (operation == EXIT_OPERATION || operation == RESTART_OPERATION) {
            pthread_exit(0);
        }

    } while (1);
}

// Função de reiniciar o sistema.
void *restart_function(void *arg) {
    //Zera os valores de saldo e operação, limpa a tela e finaliza a thread.
    balance = 0;
    operation = 0;
    system("clear");
    pthread_exit(0);
}
