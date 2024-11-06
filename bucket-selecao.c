#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define maxNum 1001 // Maior numero do range
#define numBaldes 10 // Numero de baldes
#define tam 1000 // Quantidade de numeros a serem ordenados


/* E estrutura do balde e formada por:
*  vetor que tem os numeros do balde
*  a ultima posicao que foi inserido o elemento
*/
typedef struct balde
{
    int vet[tam];
    int ultimo;
} Balde;

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
    //encontra o intervalo ao qual o numero pertence de acordo com o numero de baldes e o número mais alto; divide igualemente de acordo com o numero de buckets
    int pos = ((num) * (numBaldes)/(maxNum)); //a posição é o valor * o numero total de baldes / pelo número mais alto;
    baldes[pos].vet[baldes[pos].ultimo] = num; //o valor é guardado na próxima posição livre do vetor de valores do balde
    baldes[pos].ultimo++; //aumenta o índice do vetor de valores
}
// Funcao para a odenacao dos baldes
int compare(const void * a, const void * b)
{
    if ( *(int*)a <  *(int*)b ) return -1; //elemento a vai antes de b
    if ( *(int*)a == *(int*)b ) return 0; // elemento a e b são iguais
    if ( *(int*)a >  *(int*)b ) return 1; // elemento a vai depois de b
}

void ordenaBalde(Balde *baldes)
{
    for (int i = 0; i < numBaldes; i++)
        qsort(baldes[i].vet, tam, sizeof(int), compare);
}


int main(){

    const char file_name[11] = "output.txt";
//o vetor de valores tem o tamanho especificado no comando da função
    int valores[tam];
    read_ints(file_name,  valores); //le os valores do arquivo

    for(int i = 0; i <tam; i++){
        printf("%d ,", valores[i]);
    }

    // alocacao dos baldes
    Balde baldes[numBaldes] = {0};

    for(int i = 0; i < numBaldes; i++)
    {
        baldes[i].ultimo  = 0; //seta o último indice do vetor de valores do balde como 0
    }

    clock_t begin = clock();
    // insercao de cada elemento do array arr no balde correto
    for (int i = 0; i < tam; i++) {
        inserir(baldes, valores[i]);
    }
    // ordenacao dos baldes
    ordenaBalde(baldes);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    // insercao dos elementos ordenados no vetor final

    int vetFinal[tam] = {0};

    int k = 0;
    for (int i = 0; i < numBaldes; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if (baldes[i].vet[j] != 0)
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