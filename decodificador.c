#include <stdio.h>
#include <stdlib.h>
#include "criptografia.c"

int main () {
    char mensagem[200], *texto;
    fgets(mensagem, 200 * sizeof(char), stdin);
    texto = descriptografaTexto(mensagem);
    printf("%s", texto);
    free(texto);
    return 0;
}
