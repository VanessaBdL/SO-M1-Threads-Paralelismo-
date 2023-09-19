#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int tam = 3;
float matrizA[3][3];
float matrizB[3][3];
float matrizR[3][3] = {0};

void preenche_matriz(float matriz[3][3]){
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            matriz[i][j] = 0.0015;//(float)rand()/(float)rand();
        }
    }
}
void imprime_matriz(float matriz[3][3]){
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            printf("%.3f ", matriz[i][j]);
        }
        printf("\n");
    }
}

void multP1(void *param)
{
    for (int i = 0; i < tam; i++) {
        matrizR[0][i] = matrizA[0][i] * matrizB[0][i];
    }
}

void multP2(void *param)
{
    for (int i = 0; i < tam; i++) {
        matrizR[1][i] = matrizA[1][i] * matrizB[1][i];
    }
}

void multP3(void *param)
{
    for (int i = 0; i < tam; i++) {
        matrizR[2][i] = matrizA[2][i] * matrizB[2][i];
    }
}

void main(){
    srand(time(NULL));
    int modo = 1;
    double time_spent;
    clock_t begin, end;

    ///Preenchimento Aleatório das Matrizes com Float
    preenche_matriz(matrizA);
    preenche_matriz(matrizB);


    time_spent = 0.0;
    begin = clock();

    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            matrizR[j][i] = matrizA[j][i] * matrizB[j][i];
        }
    }
    sleep(1);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Tempo decorrido single thread %f segundos \n", time_spent-1);


    //Limpando a matriz para teste
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            matrizR[j][i] = 0;
        }
    }

    time_spent = 0.0;
    begin = clock();

    ///Criação das THREADS
    pthread_t tid_parte1, tid_parte2, tid_parte3;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_create(&tid_parte1,&attr,multP1,NULL);

    pthread_create(&tid_parte2,&attr,multP2,NULL);

    pthread_create(&tid_parte3,&attr,multP3,NULL);

    ///Espera terminar todas as THREADS para continuar o código
    pthread_join(tid_parte1, NULL);
    pthread_join(tid_parte2, NULL);
    pthread_join(tid_parte2, NULL);
    sleep(1);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Tempo decorrido multithread %f segundos \n", time_spent-1);


    //printf("Matriz A \n");
    //imprime_matriz(matrizA);
    //printf("\n Matriz B \n");
    //imprime_matriz(matrizB);
    //printf("\n Matriz R \n");
    //imprime_matriz(matrizR);

    return 0;
}
