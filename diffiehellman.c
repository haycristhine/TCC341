#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <math.h>

uint64_t powmod(uint64_t g, uint64_t c, uint64_t p) { // g ^ c mod p
    uint64_t result = 1;

    while (c > 0)
    {
        if (c % 2 == 1)
            result = (result * g) % p;
        c = c >> 1;
        g = (g * g) % p;
    }
    return result;
}

int main() {

    uint64_t p, g, c;
    uint64_t a, b, Alice, Bob = 0;
    uint64_t segredoAlice, segredoBob;

    printf("Insira o valor de p : ");
    scanf("%"SCNu64, &p);
    printf("\n");

    printf("Insira o valor de g : ");
    scanf("%"SCNu64, &g);
    printf("\n");

    a = rand();
    b = rand();
    Alice = powmod(g, a, p);
    Bob = powmod(g, b, p);

    printf("Alice: ");
    printf("%" PRIu64 "\n", Alice);

    printf("Bob: ");
    printf("%" PRIu64 "\n", Bob);

    segredoAlice = powmod(Bob, a, p);
    segredoBob = powmod(Alice, b, p);

    printf("Segredo Alice: ");
    printf("%" PRIu64 "\n", segredoAlice);

    printf("Segredo Bob: ");
    printf("%" PRIu64 "\n", segredoBob);

    return 0;
}