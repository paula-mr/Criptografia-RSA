#include <stdio.h>
#include <stdlib.h>
#include "criptografia.c"

int main () {
    char mensagem[200], *texto;
    scanf("%s", mensagem);
    texto = descriptografaTexto(mensagem);
    printf("%s", texto);
    return 0;
}
