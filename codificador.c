#include <stdio.h>
#include <stdlib.h>
#include "criptografia.c"

int main () {
    char nomeImg[50], nomeImgResult[50], mensagem[200];
    char *destino;
    int p, q;
    //scanf("%s%s%s%d%d", nomeImg, mensagem, nomeImgResult, &p, &q);
    fgets(mensagem, 200 * sizeof(char), stdin);
    scanf("%d%d",&p, &q);
    destino = criptografaTexto(mensagem, p, q);
    printf("\n%s\n", destino);
    free(destino);
    return 0;
}
