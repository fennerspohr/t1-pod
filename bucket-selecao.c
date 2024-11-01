#include <stdlib.h>
#include <stdio.h>

void read_ints (const char* file_name, int* valores)
{
    FILE* file = fopen (file_name, "r");
    int i = 0;
    int in = 0;

    fscanf (file, "%d", &i);
    while (!feof (file))
    {
        valores[in] = i;
        fscanf (file, "%d", &i);
        in++;
    }
    fclose (file);
}

int main(int argc){

const char file_name[11] = "output.txt";
int valores[argc];

read_ints(file_name, (int *) &valores);

for(int i = 0; i <argc; i++){
    printf("%d\n", valores[i]);
}

return 0;
}