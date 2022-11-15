/*
Nome: Bruno Hideki Amadeu Ogata
RA: 140884
Programação Concorrente e Distribuída
Atividade 2 - Exercício 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <omp.h>


int request = 0;
int respond = 0;
int SOMA = 0;
int controle = 0;


void secao_critica(int t) {
    int local = SOMA;
    Sleep(rand() % 2);
    SOMA = local + 1;

    printf("(%d) SOMA: %d\n", t, SOMA);
}


void cliente(int t) {
    while (1) {
        if (controle == 1) {        //entra no pré protocolo para controle de acesso à zona crítica
            while (respond != t)
                request = t;
        }
            

        secao_critica(t);

        respond = 0;                //pós protocolo 
    }
}

void servidor() {
    while (1) {
        while (request == 0);
        respond = request;

        while (respond != 0);
        request = 0;
    }
}

int main() {

    int N = 4;

    omp_set_num_threads(N + 1);

    printf("Threads: %d\n", N + 1);
    printf("Servidor  t: 0\n");
    printf("Cliente  t: 1");
    for (int i = 2; i <= N; i++) printf(", %d", i);
    printf("\n");


    printf("\n");

#pragma omp parallel
    {
        int t = omp_get_thread_num();

        if (t == 0) servidor();
        else cliente(t);
    }

    return 0;
}