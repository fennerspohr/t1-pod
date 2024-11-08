gerar arquivo com números aleatórios:\
`gcc -o geraN geraN.c`\
`./geraN {quantos números} {valor máximo dos números} > output.txt`

dica: dá pra gerar um arquivo com o número máximo de valores que vão ser ordenados e só mudar o tam no bucket.c pra ordenar arrays menores

rodar o programa\
!!IMPORTANTE!!
define tam -> quantos números vao ser lidos (tem que ser igual ao tamanho do geraN)\
define maxNum -> {valor máximo dos números} +1\

opções de sort dos buckets:\
1 - quick sort
2 - selection sort
3 - merge sort

`gcc -o bucket bucket.c quicksort.c`\
`./bucket`\

