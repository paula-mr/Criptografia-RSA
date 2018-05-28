#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* criptografaTexto(char *mensagem, int p, int q);
char* toString(int numero);
int encontraCoPrimo(int numero);
int codificaBloco(int numero, int e, int n);

int main () {
    char caminhoImg[50], nomeImg[50], nomeImgResult[50], mensagem[200];
    char *destino;
    int p, q;
    //scanf("%s%s%s%s%d%d", caminhoImg, nomeImg, mensagem, nomeImgResult, &p, &q);
    scanf("%s%d%d", mensagem, &p, &q);
    destino = criptografaTexto(mensagem, p, q);
    printf("\n%s\n", destino);
    free(destino);
    return 0;
}

char* criptografaTexto(char *mensagem, int p, int q) {
    char *string, *aux, *valor, *textoCriptografado;
    int ehPrimeiroValor = 1, oN, n, e;
    oN = (p-1)*(q-1);
    n = p*q;
    e = encontraCoPrimo(oN);

    textoCriptografado = (char*) malloc(1*sizeof(char));
    textoCriptografado[0] ='\n';

    string = (char*) malloc(0 * sizeof(char));

    for (int i=0; i<strlen(mensagem); i++) {
        int valorAsc, j=0;
        valorAsc = mensagem[i];
        valor = toString(valorAsc);
        aux = string;
        string = (char*) malloc((strlen(aux) + strlen(valor) +1) * sizeof(char));
        if (!ehPrimeiroValor) {
            for (j=0; j<strlen(aux); j++) {
                string[j] = aux[j];
            }
        }
        else {
            ehPrimeiroValor = 0;
        }
        for (int k=0; k<strlen(valor); k++, j++) {
            string[j] = valor[k];
        }
        string[j] = '\0';
        free(valor);
        free(aux);
    }

    ehPrimeiroValor = 1;
    textoCriptografado = (char*) malloc(0*sizeof(char));

    for (int i=0; i<strlen(string); i++) {
        int valor = 0, valorAnterior, j=0;
        char *valorString;
        while (valor < oN && valor > -1) {
            valorAnterior = valor;
            int vl = string[i] - '0';
            valor *= 10;
            valor += vl;
            i++;
        }
        i-=2;
        valor = codificaBloco(valorAnterior, e, n);
        valorString = toString(valor);
        aux = textoCriptografado;
        free(textoCriptografado);
        textoCriptografado = (char*) malloc((strlen(aux) + strlen(valorString))*sizeof(char));
        for (j; j<strlen(aux); j++) {
           textoCriptografado[j] = aux[j];
        }
        for (int k=0; k<strlen(valorString); j++,k++) {
           textoCriptografado[j] = valorString[k];
        }
        textoCriptografado[j] = '\0';
        free(aux);
    }
    return textoCriptografado;
}

char* toString(int numero) {
    char *string, *aux;
    int cont = 0, resto;
    string = (char*) malloc(0 * sizeof(char));
    while (numero > 0) {
        aux = string;
        string = (char*) malloc(cont+1 * sizeof(char));
        resto = numero%10;
        string[0] = resto + '0';
        numero -= resto;
        numero /= 10;
        for (int i=0; i<cont; i++) {
            string[i+1] = aux[i];
        }
        cont++;
        free(aux);
    }
    string[cont] = '\0';
    return string;
}

int encontraCoPrimo(int numero) {
    int divisoresNumero[numero/2], contDivisoresNumero = 0, contDivisoresIguais = 0;
    for (int i=1; i<(numero+1); i++) {
        if ((numero % i) == 0) {
            divisoresNumero[contDivisoresNumero] = i;
            contDivisoresNumero++;
        }
    }
    for (int i=2; i<(numero*10); i++) {
        for (int j=1; j<(i+1) && contDivisoresIguais < 2; j++) {
            if (i % j == 0) {
                for (int k=0; k<contDivisoresNumero && contDivisoresIguais < 2; k++) {
                    if (j == divisoresNumero[k]) {
                        contDivisoresIguais ++;
                    }
                }
            }
        }
        if (contDivisoresIguais < 2) {
            return i;
        }
        else {
            contDivisoresIguais = 0;
        }
    }
    return 0;
}

int codificaBloco(int numero, int e, int n) {
    int resultado = (numero*numero)%n;
    for (int i=2; i<e; i++) {
        resultado *= numero;
        resultado %= n;
    }
    return resultado;
}
