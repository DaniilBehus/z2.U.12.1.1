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

// Funkcia na vytvorenie relacie s danou velkostou
NURELM *nurelm_create(unsigned int m, unsigned int n) {
    NURELM *rel = (NURELM *)malloc(sizeof(NURELM));
    if (rel == NULL) return NULL;
    rel->m = m;
    rel->n = n;
    rel->properties = 0;
    rel->matrix = (char *)calloc(m * n, sizeof(char));
    if (rel->matrix == NULL) {
        free(rel);
        return NULL;
    }
    return rel;
}

// Funkcia na vytvorenie prazdneho vztahu zo Z0 do Z0
NURELM *nurelm_create_Znot_to_Znot(void) {
    return nurelm_create(0, 0);
}

// Funkcia na vytvorenie a inicializaciu matice vztahu zo suboru
NURELM *nurelm_create_by_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return NULL;

    NURELM *rel = (NURELM *)malloc(sizeof(NURELM));
    if (rel == NULL) {
        fclose(file);
        return NULL;
    }

    fscanf(file, "N R 1\n");
    fscanf(file, "%u %u\n", &(rel->m), &(rel->n));

    rel->matrix = (char *)calloc(rel->m * rel->n, sizeof(char));
    if (rel->matrix == NULL) {
        free(rel);
        fclose(file);
        return NULL;
    }

    unsigned int i, j;
    for (i = 0; i < rel->m; ++i) {
        for (j = 0; j < rel->n; ++j) {
            int temp;
            fscanf(file, "%d", &temp);
            BIND(rel, i, j) = temp;
        }
    }

    fclose(file);
    return rel;
}

// Funkcia na ulozenie maticoveho zobrazenia vztahu do suboru
char nurelm_save(NURELM *rel, char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) return IMPOSSIBLE;

    fprintf(file, "N R 1\n");
    fprintf(file, "%u %u\n", rel->m, rel->n);

    unsigned int i, j;
    for (i = 0; i < rel->m; ++i) {
        for (j = 0; j < rel->n; ++j) {
            fprintf(file, "%d ", BIND(rel, i, j));
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return SUCCESS;
}

// Funkcia na spravne znicenie maticoveho zobrazenia vztahu v pamati
void nurelm_destroy(NURELM *to_destroy) {
    if (to_destroy != NULL) {
        free(to_destroy->matrix);
        free(to_destroy);
    }
}

// Funkcia na vypis maticoveho zobrazenia vztahu na obrazovku
void nurelm_print(NURELM *to_print) {
    unsigned int i, j;
    for (i = 0; i < to_print->m; ++i) {
        for (j = 0; j < to_print->n; ++j) {
            printf("%d ", BIND(to_print, i, j));
        }
        printf("\n");
    }
}

// Funkcia na zmenu zobrazenia vztahu *to_redef
char nurelm_set(NURELM *to_redef, unsigned int x, unsigned int y) {
    if (to_redef == NULL) {
        return IMPOSSIBLE;
    }
    if (x >= to_redef->m || y >= to_redef->n) {
        return IMPOSSIBLE;
    }

    BIND(to_redef, x, y) = 1;
    return SUCCESS;
}

int main() {
    unsigned int m, n, x, y;
    printf("Zadajte pocet riadkov matice: ");
    scanf("%u", &m);
    printf("Zadajte pocet stlpcov matice: ");
    scanf("%u", &n);

    NURELM *rel = nurelm_create(m, n);
    if (rel == NULL) {
        printf("Chyba: Nedostatok pamate\n");
        return 1;
    }

    int choice;
    do {
        printf("1. Nastavit hodnotu v matici\n");
        printf("2. Vytlacit maticu\n");
        printf("3. Ukoncit\n");
        printf("Vyberte moznost: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Zadajte riadok: ");
                scanf("%u", &x);
                printf("Zadajte stlpec: ");
                scanf("%u", &y);
                if (nurelm_set(rel, x, y) == SUCCESS) {
                    printf("Hodnota bola uspesne nastavena\n");
                } else {
                    printf("Nepodarilo sa nastavit hodnotu\n");
                }
                break;
            case 2:
                nurelm_print(rel);
                break;
            case 3:
                printf("Ukoncenie programu\n");
                break;
            default:
                printf("Neplatna volba\n");
                break;
        }
    } while (choice != 3);

    nurelm_destroy(rel);
    return 0;
}

