#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define maxNum 1001 // Maior numero do range + 1
#define numBaldes 100 // Numero de baldes
#define tam 150000 // Quantidade de numeros a serem ordenados

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
void heapify(int arr[], int n, int i) {

    // Initialize largest as root
    int largest = i;

    // left index = 2*i + 1
    int l = 2 * i + 1;

    // right index = 2*i + 2
    int r = 2 * i + 2;

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }

    // If largest is not root
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main function to do heap sort
void heapSort(int arr[], int n) {

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {

        // Move current root to end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void selectionSort(int arr[]) {
    for (int i = 0; i < tam - 1; i++) {

        // Assume the current position holds
        // the minimum element
        int min_idx = i;

        // Iterate through the unsorted portion
        // to find the actual minimum
        for (int j = i + 1; j < tam; j++) {
            if (arr[j] < arr[min_idx]) {

                // Update min_idx if a smaller element is found
                min_idx = j;
            }
        }

        // Move minimum element to its
        // correct position
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}
// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int leftArr[n1], rightArr[n2];

    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
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

    // Copy the remaining elements of leftArr[], if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArr[], if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// The subarray to be sorted is in the index range [left-right]
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Calculate the midpoint
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

void insertionfunc(int baldes[], int n){

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

void inserir(Balde baldes[], int num)
{
    //encontra o intervalo ao qual o numero pertence de acordo com o numero de baldes e o número mais alto; divide igualmente de acordo com o numero de buckets
    int pos = ((num) * (numBaldes)/(maxNum)); //a posição é o valor * o numero total de baldes / pelo número mais alto + 1;
    baldes[pos].vet[baldes[pos].ultimo] = num; //o valor é guardado na próxima posição livre do vetor de valores do balde
    baldes[pos].ultimo++; //aumenta o índice do vetor de valores
}

void ordenaBalde(Balde *baldes, int tipo)
{
    if(tipo==1){ //quick sort
        for (int i = 0; i < numBaldes; i++){
//            initial_quick(baldes[i].vet, 0, tam-1);
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
    const char file_name[99] = "/home/evergreenis/Documentos/2024-2/pod/t1-pod/output.txt";
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

    free(valores);
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

    printf("\nVet Final:\n");

    for (int i = 0; i < tam; i++)
        printf("%d ", vetFinal[i]);
    printf("\n\n");

    printf("Tempo de execução:%f.\n", time_spent);

    free(vetFinal);
    for (int i =0; i< numBaldes; i++)
        free(baldes[i].vet);
    free(baldes);

    return 0;
}