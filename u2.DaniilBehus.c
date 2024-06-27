#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define IMPOSSIBLE 0
// Makro pre pristup k prvkom matice
#define BIND(r, i, j) ((r)->matrix[(i) * ((r)->n) + (j)])
// Struktura NURELM
typedef struct {
    unsigned int m;
    unsigned int n;
    char properties;
    char *matrix;
} NURELM;

// Makro pre prístup k prvkom matice
#define BIND(r, i, j) ((r)->matrix[(i) * ((r)->n) + (j)])

// Funkcia pre nastavenie prvku v matici
char nurelm_set(NURELM *to_redef, unsigned int x, unsigned int y) {
    // Kontrola na NULL ukazovatel
    if (to_redef == NULL) {
        printf("Error: NULL pointer provided.\n");
        return IMPOSSIBLE;
    }
    
    // Kontrola, ci su x a y v pripustnych medziach
    if (x >= to_redef->m || y >= to_redef->n) {
        printf("Error: Indices out of bounds.\n");
        return IMPOSSIBLE;
    }
    
    // Nastavenie prvku v matici
    BIND(to_redef, x, y) = 1;
    
    return SUCCESS;
}

// Priklad pouzitia funkcie
int main() {
    // Zadanie velkosti matice pouzivatelom
    unsigned int m, n;
    printf("Zadajte velkost matice (m n): ");
    scanf("%u %u", &m, &n);

    // Vytvorenie prikladu struktury NURELM
    NURELM example;
    example.m = m;
    example.n = n;
    example.properties = 0;
    example.matrix = (char *)calloc(example.m * example.n, sizeof(char));
    if (example.matrix == NULL) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }
    
    while (1) {
        unsigned int x, y;
        printf("Zadajte suradnice (x, y) pre nastavenie prvku v matici (velkost %ux%u) alebo zaporne cisla pre ukoncenie:\n", example.m, example.n);
        scanf("%u %u", &x, &y);
        
        // Kontrola na ukoncenie
        if (x == -1 || y == -1) {
            break;
        }

        // Nastavenie prvku v matici podla zadanych suradnic
        char result = nurelm_set(&example, x, y);
        if (result == SUCCESS) {
            printf("Prvok bol úspešne nastavený.\n");
        } else {
            printf("Nepodarilo sa nastavit prvok.\n");
        }
    }
    
    // Vytlacenie matice pre kontrolu
    unsigned int i, j;  // Deklarujeme premenne cyklu mimo cyklu
    for (i = 0; i < example.m; ++i) {
        for (j = 0; j < example.n; ++j) {
            printf("%d ", BIND(&example, i, j));
        }
        printf("\n");
    }
    
    // Uvolnenie alokovanej pamate
    free(example.matrix);
    
    return 0;
}

