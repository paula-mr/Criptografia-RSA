#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int getRandomPrimeNumber();

int main() {
    int p, q;
    srand(time(NULL));
    p = getRandomPrimeNumber();
    q = getRandomPrimeNumber();
    while (p == q) {
        q = getRandomPrimeNumber();
    }

    printf("p=%d,q=%d", p, q);

}

int getRandomPrimeNumber() {
    int r = rand(), cont =0, prime;
    while (cont < r) {
        for (int i=2; i < 10000 && cont < r; i++) {
            int dividers = 0;
            for (int j=2; j<i && dividers == 0; j++) {
                if (i%j == 0) {
                    dividers++;
                }
            }
            if (dividers == 0) {
                prime = i;
                cont ++;
            }
        }
    }
    return prime;
}
