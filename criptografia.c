#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* leChave();
int toInt(char* string);
char* toString(int numero);
void salvaChave(int n, int d);
int encontraCoPrimo(int numero);
int inversoModular(int a, int b);
char* descriptografaTexto(char *mensagem);
int codificaBloco(int numero, int e, int n);
char* criptografaTexto(char *mensagem, int p, int q);

char* descriptografaTexto(char *mensagem) {
    int *vetor, d, n, k=0;
    char *textoDescriptografado, *stringAsc;
    vetor = leChave();
    n = vetor[0];
    d = vetor[1];
    free(vetor);

    textoDescriptografado = (char*) malloc(0*sizeof(char));

    for (int i=0; i<strlen(mensagem); i++) {
        int valor = 0, valorAnterior, j=0, vl;
        char *valorString, *aux;
        while (valor < n && valor > -1 && vl > -1) {
            valorAnterior = valor;
            vl = mensagem[i] - '0';
            valor *= 10;
            valor += vl;
            i++;
        }
        i-=2;
        valor = codificaBloco(valorAnterior, d, n);
        valorString = toString(valor);
        aux = textoDescriptografado;
        free(textoDescriptografado);
        textoDescriptografado = (char*) malloc((strlen(aux) + strlen(valorString))*sizeof(char));
        for (j; j<strlen(aux); j++) {
           textoDescriptografado[j] = aux[j];
        }
        for (k=0; k<strlen(valorString); j++,k++) {
           textoDescriptografado[j] = valorString[k];
        }
        textoDescriptografado[j] = '\0';
        free(aux);
    }

    stringAsc = (char*) malloc((strlen(textoDescriptografado)/2) * sizeof(char));

    for (int i=0, k=0; i<strlen(textoDescriptografado); i+=2, k++) {
        int valor;
        valor = textoDescriptografado[i] - '0';
        valor *= 10;
        valor += textoDescriptografado[i+1] - '0';
        stringAsc[k] = valor;
    }
    if (strlen(textoDescriptografado) % 2 != 0) {
        k++;
    }
    stringAsc[k] ='\0';

    free(textoDescriptografado);

    return stringAsc;
}

int toInt(char* string) {
    int valor = 0;
    for (int i=0; i<strlen(string); i++) {
        valor *= 10;
        valor += string[i] - '0';
    }
    return valor;
}

void salvaChave(int n, int d) {
    char *nString = toString(n), *dString = toString(d);
    FILE *file;
    file = fopen("private.txt", "w");
    fputs(nString, file);
    fputs("\n", file);
    fputs(dString, file);
    fclose(file);
}

int* leChave() {
    char nString[10], dString[10];
    int *vetor;
    vetor = (int*) malloc(2 * sizeof(int));

    FILE *file;
    file = fopen("private.txt", "r");
    fscanf(file, "%s", nString);
    fscanf(file, "%s", dString);
    fclose(file);

    vetor[0] = toInt(nString);
    vetor[1] = toInt(dString);

    return vetor;
}

char* criptografaTexto(char *mensagem, int p, int q) {
    char *string, *aux, *textoCriptografado;
    int ehPrimeiroValor = 1, oN, n, e, d;
    oN = (p-1)*(q-1);
    n = p*q;
    e = encontraCoPrimo(oN);
    d = inversoModular(e, oN);

    string = (char*) malloc(0 * sizeof(char));

    for (int i=0; i<strlen(mensagem); i++) {
        int valorAsc, j=0;
        char *valor;
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
    salvaChave(n, d);

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

int inversoModular(int a, int b) {
	int b0 = b, t, q;
	int x0 = 0, x1 = 1;
	if (b == 1) {
        return 1;
	}

	while (a > 1) {
		q = a / b;
		t = b;
		b = a % b;
		a = t;
		t = x0;
		x0 = x1 - q * x0;
		x1 = t;
	}

	if (x1 < 0){
        x1 += b0;
    }

	return x1;
}

int codificaBloco(int numero, int e, int n) {
    int resultado;
    if (e > 1) {
        resultado = (numero*numero)%n;
        for (int i=2; i<e; i++) {
            resultado *= numero;
            resultado %= n;
        }
    }
    else {
      resultado = inversoModular(numero, n);
    }
    return resultado;
}
