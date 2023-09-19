#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

int arr[2000] = {0};
int n = 2000;
int n1 = 500;
int n2 = 1000;
int n3 = 1500;
int i;

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSortP1(void *param)
{
    int i, j;
    bool pronto;
    for (i = 0; i < n1 - 1; i++) {
        pronto = false;
        for (j = 0; j < n1 - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                pronto = true;
            }
        }
        if (pronto == false)
            break;
    }
}

void bubbleSortP2(void *param)
{
    int i, j;
    bool pronto;
    for (i = n1; i < n2 - 1; i++) {
        pronto = false;
        for (j = n1; j < n2 - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                pronto = true;
            }
        }
        if (pronto == false)
            break;
    }
}

void bubbleSortP3(void *param)
{
    int i, j;
    bool pronto;
    for (i = n2; i < n3 - 1; i++) {
        pronto = false;
        for (j = n2; j < n3 - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                pronto = true;
            }
        }
        if (pronto == false)
            break;
    }
}

void bubbleSortP4(void *param)
{
    int i, j;
    bool pronto;
    for (i = n3; i < n - 1; i++) {
        pronto = false;
        for (j = n3; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                pronto = true;
            }
        }
        if (pronto == false)
            break;
    }
}


void bubbleSort()
{
    int i, j;
    bool pronto;
    for (i = 0; i < n - 1; i++) {
        pronto = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                pronto = true;
            }
        }
        if (pronto == false)
            break;
    }
}

// Function to print an array
void printArray()
{

    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
}


void main(){
    int cont;
    double time_spent;
    clock_t begin, end;

    cont = 20000;
    for (i = 0; i < n; i++){
        arr[i] = cont;
        cont--;
    };

    time_spent = 0.0;
    begin = clock();
    bubbleSort();
    sleep(1);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Tempo decorrido single thread %f segundos \n", time_spent-1);


    cont = 20000;
    for (i = 0; i < n; i++){
        arr[i] = cont;
        cont--;
    };

    time_spent = 0.0;
    begin = clock();

    pthread_t tid_parte1, tid_parte2, tid_parte3, tid_parte4;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&tid_parte1,&attr,bubbleSortP1,NULL);
    pthread_create(&tid_parte2,&attr,bubbleSortP2,NULL);
    pthread_create(&tid_parte3,&attr,bubbleSortP3,NULL);
    pthread_create(&tid_parte4,&attr,bubbleSortP4,NULL);

    pthread_join(tid_parte1, NULL);
    pthread_join(tid_parte2, NULL);
    pthread_join(tid_parte2, NULL);
    pthread_join(tid_parte2, NULL);

    bubbleSort();
    sleep(1);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Tempo decorrido single thread %f segundos \n", time_spent-1);

    //printArray();
} 