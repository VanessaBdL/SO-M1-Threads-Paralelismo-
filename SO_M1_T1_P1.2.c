#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int tam = 3;
float matrizA[3][3];
float matrizB[3][3];
float matrizS[3][3];
float matrizM[3][3];


///Função de Preenchimento
void preenche_matriz(float matriz[3][3]){
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            matriz[i][j] = (float)rand()/(float)rand();
        }
    }
}

///Função de Impressão
void imprime_matriz(float matriz[3][3]){
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            printf("%.3f ", matriz[i][j]);
        }
        printf("\n");
    }
}

///Thread 1
void *matricial_t1(void *param){
    int linha = 0;
    for (int i = 0; i < tam; i++){
        matrizM[linha][i] = 0;
        for (int j = 0; j < tam; j++)
            matrizM[linha][i] += matrizA[linha][j]*matrizB[j][i];
    }
    pthread_exit(0);
}

// Thread 2
void *matricial_t2(void *param){
    int linha = 1;
    for (int i = 0; i < tam; i++){
        matrizM[linha][i] = 0;
        for (int j = 0; j < tam; j++)
            matrizM[linha][i] += matrizA[linha][j]*matrizB[j][i];
    }
    pthread_exit(0);
}

//thread 3
void *matricial_t3(void *param){
    int linha = 2;
    for (int i = 0; i < tam; i++){
        matrizM[linha][i] = 0;
        for (int j = 0; j < tam; j++)
            matrizM[linha][i] += matrizA[linha][j]*matrizB[j][i];
    }
    pthread_exit(0);
}

///Função Single Thread
void matricial_S(int tam){
    for (int row = 0; row < tam; row++){
        for (int i = 0; i < tam; i++){
            matrizS[row][i] = 0;
            for (int j = 0; j < tam; j++){
                matrizS[row][i] += matrizA[row][j]*matrizB[j][i];
            }
        }
    }
}

int main(){
    /// Seed aleatória e Declaração de Variáveis
    srand(time(NULL));
    clock_t begin, end;
    double time_spent;

    //preencher matrizes:
    preenche_matriz(matrizA);
    preenche_matriz(matrizB);

    printf("Matriz A: \n");
    imprime_matriz(matrizA);
    printf("\nmatriz B: \n");
    imprime_matriz(matrizB);

    /// Depuração Multiplicação Single-Thread
    begin = clock();
    matricial_S(tam);
    sleep(1);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\nMatriz Single-Thread: \n");
    imprime_matriz(matrizS);
    printf("Tempo decorrido single-thread %f segundos \n", time_spent - 1);

    /// Depuração Multiplicação Multi-Thread
    begin = clock();

    // Criação das THREADS
    pthread_t tid_parte1, tid_parte2, tid_parte3;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&tid_parte1,&attr,matricial_t1,NULL);
    pthread_create(&tid_parte2,&attr,matricial_t2,NULL);
    pthread_create(&tid_parte3,&attr,matricial_t3,NULL);

    pthread_join(tid_parte1, NULL);
    pthread_join(tid_parte2, NULL);
    pthread_join(tid_parte3, NULL);

    sleep(1);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\nMatriz Multi-Thread: \n");
    imprime_matriz(matrizM);
    printf("Tempo decorrido multi-thread %f segundos \n", time_spent - 1);

    return 0;
}
