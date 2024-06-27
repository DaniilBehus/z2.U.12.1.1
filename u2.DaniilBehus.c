#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define IMPOSSIBLE 1

// Struktura pre reprezentaciu relacie
typedef struct {
    unsigned int **relation; // Dvojrozmerne pole pre reprezentaciu relacie
    unsigned int size;       // Velkost matice
} NURELM;

// Funkcia na vytvorenie novej struktury NURELM
NURELM *create_nurelm(unsigned int size) {
    NURELM *new_nurelm = (NURELM *)malloc(sizeof(NURELM)); // Alokacia pamate pre strukturu NURELM
    new_nurelm->size = size; // Nastavenie velkosti matice
    new_nurelm->relation = (unsigned int **)malloc(size * sizeof(unsigned int *)); // Alokacia pamate pre riadky matice
    unsigned int i; // Deklaracia premennej mimo cyklu
    for (i = 0; i < size; i++) {
        new_nurelm->relation[i] = (unsigned int *)calloc(size, sizeof(unsigned int)); // Alokacia pamate pre stlpce a inicializacia na 0
    }
    return new_nurelm; // Vratenie ukazovatela na novu strukturu
}

// Funkcia na uvolnenie pamate struktury NURELM
void free_nurelm(NURELM *nurelm) {
    unsigned int i; // Deklaracia premennej mimo cyklu
    for (i = 0; i < nurelm->size; i++) {
        free(nurelm->relation[i]); // Uvolnenie pamate pre kazdy riadok
    }
    free(nurelm->relation); // Uvolnenie pamate pre ukazovatele na riadky
    free(nurelm); // Uvolnenie pamate pre samotnu strukturu
}

// Funkcia na nastavenie relacie (x, y) v strukture NURELM
char nurelm_set(NURELM *to_redef, unsigned int x, unsigned int y) {
    if (x >= to_redef->size || y >= to_redef->size) {
        return IMPOSSIBLE; // Ak su suradnice mimo rozsahu matice, vrati IMPOSSIBLE
    }
    to_redef->relation[x][y] = 1; // Nastavenie relacie (x, y) na 1
    return SUCCESS; // Vratenie SUCCESS, ak operacia prebehla uspesne
}

int main() {
    unsigned int size;
    printf("Zadajte velkost matice: ");
    scanf("%u", &size); // Nacitanie velkosti matice od pouzivatela

    NURELM *nurelm = create_nurelm(size); // Vytvorenie novej struktury NURELM s danou velkostou

    unsigned int x, y;
    char choice;
    do {
        printf("Zadajte suradnice (x, y) na nastavenie relacie: ");
        scanf("%u %u", &x, &y); // Nacitanie suradnic (x, y) od pouzivatela

        if (nurelm_set(nurelm, x, y) == SUCCESS) {
            printf("Relacia (%u, %u) bola uspesne pridana.\n", x, y); // Ak operacia prebehla uspesne
        } else {
            printf("Nie je mozne pridat relaciu (%u, %u).\n", x, y); // Ak operacia neprebehla uspesne
        }

        printf("Chcete zadat dalsie suradnice? (y/n): ");
        scanf(" %c", &choice); // Nacitanie volby pouzivatela, ci chce pokracovat v zadavani dalsich suradnic
    } while (choice == 'y' || choice == 'Y'); // Pokracovanie, ak pouzivatel zadal 'y' alebo 'Y'

    // Vypis matice na overenie
    printf("Matica relacii:\n");
    unsigned int i, j; // Deklaracia premennych mimo cyklu
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("%u ", nurelm->relation[i][j]); // Vypis kazdeho prvku matice
        }
        printf("\n"); // Novy riadok po vypise kazdeho riadku matice
    }

    free_nurelm(nurelm); // Uvolnenie pamate struktury NURELM

    return 0;
}

