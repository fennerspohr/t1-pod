#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "quicksort.h"
#define maxNum 1001 // Maior numero do range + 1
#define numBaldes 10 // Numero de baldes
#define tam 1000 // Quantidade de numeros a serem ordenados

typedef struct balde
{
    int vet[tam]; //vetor com os números do balde
    int ultimo; //indice livre do vetor
} Balde;

//leitura do arquivo
void read_ints (const char* file_name, int valores[])
{
    FILE* file = fopen (file_name, "r");
    int i = 0;
    int in = 0;

    fscanf (file, "%d", &i);
    while (in < tam)
    {
        fscanf (file, "%d", &i);
        valores[in] = i;
        in++;
    }
    fclose (file);
}

void inserir(Balde baldes[], int num)
{
    //encontra o intervalo ao qual o numero pertence de acordo com o numero de baldes e o número mais alto; divide igualmente de acordo com o numero de buckets
    int pos = ((num) * (numBaldes)/(maxNum)); //a posição é o valor * o numero total de baldes / pelo número mais alto + 1;
    baldes[pos].vet[baldes[pos].ultimo] = num; //o valor é guardado na próxima posição livre do vetor de valores do balde
    baldes[pos].ultimo++; //aumenta o índice do vetor de valores
}

// Funcao para a odenacao dos baldes com quick sort
int compare(const void * a, const void * b)
{
    if ( *(int*)a <  *(int*)b ) return -1; //elemento a vai antes de b
    if ( *(int*)a == *(int*)b ) return 0; // elemento a e b são iguais
    if ( *(int*)a >  *(int*)b ) return 1; // elemento a vai depois de b
}

void ordenaBalde(Balde *baldes, int tipo)
{
    if(tipo==1){ //quick sort
        for (int i = 0; i < numBaldes; i++){
            initial_quick(baldes[i].vet, 0, tam-1);
        }
    }

}


int main(){
    const char file_name[99] = "/home/evergreenis/Documentos/2024-2/pod/t1-pod/output.txt";
    //o vetor de valores tem o tamanho especificado no comando da função
    int valores[tam];
    read_ints(file_name,  valores); //le os valores do arquivo
    for(int i = 0; i <tam; i++){ //imprime os valores aleatórios
        printf("%d ,", valores[i]);
    }

    int tipo;
    printf("Qual tipo de sort deseja utilizar?\n1)Quick sort\n");
    scanf("%d", &tipo);
    // alocacao dos baldes
    Balde baldes[numBaldes] = {0}; //inicializados em 0

    for(int i = 0; i < numBaldes; i++)
    {
        baldes[i].ultimo  = 0; //seta o último indice do vetor de valores do balde como 0
    }

    clock_t begin = clock(); //começa a contar o tempo

    // insercao de cada elemento do array valores no balde correto
    for (int i = 0; i < tam; i++) {
        inserir(baldes, valores[i]);
    }
    // ordenacao dos baldes
    ordenaBalde(baldes, tipo);

    clock_t end = clock(); //termina de contar o tempo

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; //tempo de execução

    // insercao dos elementos ordenados no vetor final

    int vetFinal[tam] = {0};

    int k = 0;
    for (int i = 0; i < numBaldes; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if (baldes[i].vet[j] != 0) //o array de números aleatórios não possui nenhum 0, portanto todos os 0 que estiverem no vetor dos baldes são espaços vazios
            {
                vetFinal[k] = baldes[i].vet[j];
                k++;
            }

        }
    }

    printf("\nVet Final:\n");

    for (int i = 0; i < tam; i++)
        printf("%d ", vetFinal[i]);
    printf("\n\n");

    printf("Tempo de execução:%f.\n", time_spent);

    return 0;
}