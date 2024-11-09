#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define maxNum 1001 // Maior numero do range + 1
#define numBaldes 100 // Numero de baldes
#define tam 100000000 // Quantidade de numeros a serem ordenados

typedef struct balde
{
    int* vet; //vetor com os números do balde
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
//organiza o heap
void heapify(int arr[], int n, int i) {

    // Inicializa o maior como sendo o pai i
    int largest = i;

    // nó filho da esquerda
    int l = 2 * i + 1;

    // nó filho da direita
    int r = 2 * i + 2;

    // se o filho da esquerda for maior que o pai
    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }

    // se o filho da direita for maior que o pai
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }

    // se o maior valor não é o pai
    if (largest != i) {
        //coloca o maior valor na posição do pai
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // recursivamente organiza em heap a sub-árvore afetada
        heapify(arr, n, largest);
    }
}
//função principal do heap sort
void heapSort(int arr[], int n) {

    // Constrói o heap reorganizando o array
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    //No heap, o maior valor fica na posição 0; para cada posição i, seu nó filho da esquerda está em 2i+1 e seu nó filho
    //da direita está em 2i+2

    // Extrai os elementos do heap e coloca em sua posição correta no array
    for (int i = n - 1; i > 0; i--) {

        // Move o maior valor atual para o final do array
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Reorganiza o array restante em um heap reduzido
        heapify(arr, i, 0);
    }
}
void selectionSort(int arr[]) {
    //percorre o array encontrando o menor valor entre i e tam-1 e colocando-o na posição i
    for (int i = 0; i < tam - 1; i++) {

        //assume que a posição atual tem o menor valor
        int min_idx = i;

        //itera pela parte não ordenada para encontrar o mínimo real
        for (int j = i + 1; j < tam; j++) {
            if (arr[j] < arr[min_idx]) {

                //atualiza o índice do mínimo se um valor menor for encontrado
                min_idx = j;
            }
        }

        //move o elemento mínimo para sua posição correta (i)
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}
//junta as duas metades do array
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // arrays temporários
    int leftArr[n1], rightArr[n2];

    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // junta os arrays temporários de volta em arr[left...right] do menor elemento para o maior
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    //copia os elementos restantes dos arrays temporários, se existirem
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}
//função principal do merge sort
void mergeSort(int arr[], int left, int right) {
    //divide o array em partes cada vez menores e as ordena para depois uni-las
    if (left < right) {
        //acha o meio
        int mid = left + (right - left) / 2;

        //ordena as metades
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        //junta as metades
        merge(arr, left, mid, right);
    }
}
void insertionfunc(int baldes[], int n){

    //percorre o vetor iterativamente comparando os elementos de dois em dois
    for(int i = 1;i < n; i++) {
        int j = i;

        while(j > 0 && baldes[j] < baldes[j-1]) {
            int temp = baldes[j];
            baldes[j] = baldes[j-1];
            baldes[j-1] = temp;
            j--;
        }
    }
}
//coloca os valores nos baldes
void inserir(Balde baldes[], int num)
{
    //encontra o intervalo ao qual o numero pertence de acordo com o numero de baldes e o número mais alto; divide igualmente de acordo com o numero de buckets
    int pos = ((num) * (numBaldes)/(maxNum)); //a posição é o valor * o numero total de baldes / pelo número mais alto + 1;
    baldes[pos].vet[baldes[pos].ultimo] = num; //o valor é guardado na próxima posição livre do vetor de valores do balde
    baldes[pos].ultimo++; //aumenta o índice do vetor de valores
}
//ordena cada balde de acordo com o algoritmo escolhido
void ordenaBalde(Balde *baldes, int tipo)
{
    if(tipo==1){ //quick sort
        for (int i = 0; i < numBaldes; i++){
            heapSort(baldes[i].vet, tam);
        }
    }
    else if(tipo ==2){ //selection sort
        for(int i = 0; i < numBaldes; i++){
            selectionSort(baldes[i].vet);
        }
    }
    else if(tipo == 3){ //merge sort
        for(int i= 0; i < numBaldes; i++){
            mergeSort(baldes[i].vet, 0, tam-1);
        }
    }
    else if(tipo == 4){ //insertion sort
        for (int i = 0; i < numBaldes; i++){
            insertionfunc(baldes[i].vet,tam);
        }
    }

}

int main(){
    const char file_name[99] = "output.txt";
    //o vetor de valores tem o tamanho especificado no comando da função
    int* valores = calloc(tam, sizeof(int));
    read_ints(file_name,  valores); //le os valores do arquivo

    int tipo;
    printf("Qual tipo de sort deseja utilizar?\n1)Heap sort\n2)Selection sort\n3)Merge sort\n4)Insertion sort\n");
    scanf("%d", &tipo);
    // alocacao dos baldes
    Balde* baldes = malloc(tam*sizeof(Balde)); //inicializados em 0

    for(int i = 0; i < numBaldes; i++)
    {
        baldes[i].vet = calloc(tam, sizeof (int));
        baldes[i].ultimo  = 0; //seta o último indice do vetor de valores do balde como 0
    }

    clock_t begin = clock(); //começa a contar o tempo

    // insercao de cada elemento do array valores no balde correto
    for (int i = 0; i < tam; i++) {
        inserir(baldes, valores[i]);
    }

    free(valores); // libera o vetor original de valores pois todos já estão nos baldes

    // ordenacao dos baldes
    ordenaBalde(baldes, tipo);

    clock_t end = clock(); //termina de contar o tempo

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; //tempo de execução

    // insercao dos elementos ordenados no vetor final

    int* vetFinal = calloc(tam, sizeof(int));

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

    printf("Tempo de execução:%f.\n", time_spent);

    free(vetFinal);
    for (int i =0; i< numBaldes; i++)
        free(baldes[i].vet);
    free(baldes);

    return 0;
}