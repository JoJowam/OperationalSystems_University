# Sistemas Operacionais - UFOP

Este repositório foi criado com o objetivo de armazenar e compartilhar os trabalhos práticos (TPs) da disciplina de Sistemas Operacionais, ministrada na UFOP (Universidade Federal de Ouro Preto). Aqui você encontrará uma variedade de tarefas e projetos relacionados a sistemas operacionais, com o intuito de aprofundar meu conhecimento e aplicar os conceitos estudados ao longo do curso. Este repositório será atualizado regularmente, à medida que os TPs forem sendo distribuídos durante o semestre letivo!

A disciplina de Sistemas Operacionais tem como objetivo fornecer aos estudantes uma compreensão aprofundada dos princípios e conceitos fundamentais por trás dos sistemas operacionais modernos. Durante o curso, serão abordados tópicos como gerenciamento de processos, escalonamento, gerenciamento de memória, sistemas de arquivos, entrada/saída, entre outros. Os TPs são projetados para aplicar e aprofundar o conhecimento teórico adquirido em sala de aula.

Este README também será atualizado conforme a postagem de trabalhos, carregando informações de funcionamento dos diferentes códigos implementados!

___
___
___


# "Atualização - [Docker Learning](./DockerLearning)"

Nesta seção, explorarei o Docker como uma ferramenta fundamental para o desenvolvimento de sistemas operacionais. O uso do Docker será introduzido e aplicado em sala de aula para aprimorar o entendimento dessa plataforma.

## O que é Docker?

Docker é uma plataforma de código aberto que permite empacotar, distribuir e executar aplicativos em ambientes isolados, chamados de contêineres. Com o Docker, podemos criar contêineres leves e independentes que incluem tudo o que seu aplicativo precisa para ser executado, como bibliotecas, dependências e configurações. Essa abordagem oferece uma maneira consistente e reproduzível de implantar aplicativos, independentemente do ambiente em que estão sendo executados.

## Conteúdo do TP

O TP "Docker Learning" consistire em uma série de tarefas práticas que abordão os seguintes pontos:

1. Instalação do Docker;

2. Comandos básicos do Docker;

3. Criação de um contêiner personalizado;

4. Push de imagens contendo a implementação dos TPs;
 
Dentro da pasta do TP se encontram dois arquivos, um [DockerFile](./DockerLearning/Dockerfile) que usei para buildar minha imagem docker e um [Arquivo em C++](./DockerLearning/tp01.cpp) que executa alguns comandos básicos. O foco foi upa-los para o docker mesmo! 

Para compilar o programa digite no terminal:
```
 g++ tp01.cpp -o "nome preferivel do executavel"
 ./nome_do_executavel
```
Este TP foi desenvolvido para fins didáticos e de aprendizado dentro da disciplina de Sistemas Operacionais!

___
___
___

# "Atualização - [Forks and Threads](./ForksAndThreads)"

Nesta seção, exploraremos o uso de forks e threads para criar processos e realizar operações concorrentes em sistemas operacionais.

## O que são forks e threads?

Em sistemas operacionais, forks e threads são mecanismos fundamentais para a criação de processos e a execução concorrente de tarefas. Um fork é um mecanismo que permite criar um processo filho a partir de um processo pai, enquanto as threads são sequências de instruções que podem ser executadas simultaneamente dentro de um processo. Esses mecanismos fornecem uma abordagem eficiente para a execução de tarefas paralelas e a divisão de trabalho em um sistema operacional.

## Conteúdo do TP

O TP "Forks and Threads" abordará os seguintes tópicos:

1. Criação de processos usando forks;

2. Utilização de threads;

3. Implementação de exemplos práticos;
    
4. Diferenças entre Threads e Forks;
    
5. Race Condition;
 
Dentro da pasta do TP se encontram dois arquivos implementados em C: ([Arquivo Fork](./ForksAndThreads/tp2_fork.c), [Arquivo Threads](./ForksAndThreads/tp2_threads.c)), um que gera 3 "processos pesados" (forks) para realizar tarefas basicas de adicão, subtração e print, e outro que faz a mesma coisa, porem usando threads ao invez de forks. Dentro de cada arquivo tem uma breve descrição acerca do assunto.

Para compilar o programa digite no terminal:
```
  gcc -o "nome preferivel do executavel" tp2_fork.c
 ./nome_do_executavel
 
  gcc -o "nome preferivel do executavel" tp2_threads.c
  ./nome_do_executavel
```
Este TP foi desenvolvido para fins didáticos e de aprendizado dentro da disciplina de Sistemas Operacionais!

___
___
___

# "Atualização - [Producer and Consumer](./ProducerAndConsumer)"

O objetivo principal do programa é implementar um sistema de produtores e consumidores. Nesse sistema, os produtores são responsáveis por produzir itens e os consumidores por consumir esses itens. A implementação foi realizada utilizando a linguagem C++.

## Sobre o Problema do Produtor e Consumidor

O problema do produtor e consumidor é um clássico da computação concorrente, que envolve a coordenação entre processos ou threads que produzem itens e outros processos ou threads que consomem esses itens. O objetivo é garantir uma interação correta e segura entre os produtores e consumidores, evitando problemas como condições de corrida, inconsistência nos dados e bloqueios.

O cenário geral do problema envolve um buffer compartilhado entre os produtores e consumidores, onde os produtores colocam os itens produzidos e os consumidores retiram esses itens para processá-los ou utilizá-los. O desafio é garantir que os produtores só coloquem itens no buffer quando há espaço disponível, e que os consumidores só retirem itens quando há itens disponíveis para consumo.

Para solucionar esse problema, várias técnicas de sincronização e exclusão mútua são utilizadas. Uma abordagem comum é a utilização de semáforos, mutexes e variáveis de condição. O mutex garante a exclusão mútua, permitindo que apenas um processo ou thread acesse o buffer por vez. Os semáforos controlam a quantidade de espaços livres no buffer e a quantidade de itens disponíveis para consumo. As variáveis de condição são usadas para sinalizar quando uma determinada condição (como o buffer cheio ou vazio) é atendida, permitindo que os processos ou threads esperem ou sejam notificados sobre a disponibilidade de itens ou espaços no buffer.

## Conteúdo do TP

O TP "Producer and Consumer" irá abordar os seguintes tópicos:

1. Conceitos de sincronização e exclusão mútua;

2. Tratamento de condições de corrida e bloqueios;

3. Implementação do Buffer, Consumidor e Produtor em C++;

4. Sincronização entre produtores e consumidores;

Dentro da pasta do TP se encontra a pasta [src](./ProducerAndConsumer/src) que por sua vez contém os arquivos implementados em C++ onde serão explorados conceitos fundamentais de Sistemas Operacionais, como race condition, exclusão mútua e sincronização de threads. Para evitar a exclusão mútua entre os processos, foi utilizada a biblioteca <mutex>, que cria um mutex (mutual exclusion) responsável por garantir que apenas uma thread acesse uma determinada região crítica por vez. Para sincronizar as threads, foi utilizada a biblioteca <condition_variable>, que cria variáveis de condição. Essas variáveis sinalizam quando uma determinada condição é verdadeira ou falsa, permitindo a sincronização dos processos.

Para compilar o programa, é necessário ter o make instalado no sistema e se certificar que todas as dependências e bibliotecas necessárias estejam instaladas para que a compilação seja bem-sucedida. Caso contrário, podem ocorrer erros durante o processo de compilação. 

Digite: ```make``` no terminal para executar o programa. Seram solicitados dados referêntes á produção e consumo por segundo, após inseri-los corretamente é possivel acompanhar o funcionamento do programa pelo terminal.


Este TP foi desenvolvido para fins didáticos e de aprendizado dentro da disciplina de Sistemas Operacionais!

___
___
___


