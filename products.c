
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct s_product {
    char product_name[32];
    char product_market[32];
    float product_weight;
    float product_price;
    float product_priceperentity;
};

#define FILE_NAME "products.txt"
#define SCAN_CORRECT_LINES_MAX 36

int readproductsoutoffile(char filename[50], struct s_product *productbasket) {
    char v_line[256];
    int n = 0;

    // Prduktfile öffnen
    FILE *productfile = fopen(filename, "r");
    fflush(productfile);
    if (productfile == NULL) {
        // perror gibt die übergebene Fehlermeldung auf stderr aus und hängt zusätzlich noch einen String dran, der die Fehlerursache beschreibt
        perror("Fehler: Konnte Datei nicht öffnen. Lesefehler.");
        return 1;
    }
    // liest nun bis Dateiende bzw. bis zu max_lines korrekte Zeilen ein und splittet die Tabellendaten auf die einzelnen Strukturvariablen auf
    while (fgets(v_line, 256, productfile) != NULL) {
        if (sscanf(v_line, "%31[^;];%31[^;];%f;%f", productbasket[n].product_name,productbasket[n].product_market, &productbasket[n].product_weight, &productbasket[n].product_price) == 4 ) {
            productbasket[n].product_priceperentity = productbasket[n].product_price / productbasket[n].product_weight;
            //printf("Zeile %i %s: %.2f EUR/kg, %s\n", n, productbasket[n].product_name, productbasket[n].product_price, productbasket[n].product_market);
            n++;
            if (n >= SCAN_CORRECT_LINES_MAX) break; // steigt nach max_lines Zeilen aus der Schleife aus
        } else {
            fprintf(stderr, "%s -> nicht korrekt lesbare Datenstruktur.\n", v_line);
            continue;
        }
    }
    fclose(productfile);
    return n;
}


int searchlowestprice(struct s_product *productbasket, int n, char* name, float* priceperentity, char** shop) {
    float lowest_priceperentity = -1;
    char* cheapestShop = NULL;
    for (int i = 0; i < n; i++) {
        if (strcmp(name, productbasket[i].product_name) == 0) {
            if (lowest_priceperentity < 0) {
                lowest_priceperentity = productbasket[i].product_priceperentity;
                cheapestShop = productbasket[i].product_market;
            } else if (lowest_priceperentity > productbasket[i].product_priceperentity) {
                lowest_priceperentity = productbasket[i].product_priceperentity;
                cheapestShop = productbasket[i].product_market;
            }
        }
    }
    if (lowest_priceperentity < 0) {
        return 0;
    } else {
        *priceperentity = lowest_priceperentity;
        *shop = cheapestShop;
        return 1;
    }
}


int main(int argc, char* argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Es wurden der Funktion keine Parameter (= Produkte) übergeben.\n");
        exit(1);
    }
    // Warenkorb mit bis zu 36 Proukten deklarieren
    struct s_product productbasket[SCAN_CORRECT_LINES_MAX];
    // Liest die Datei products.txt ein.
    int n = readproductsoutoffile(FILE_NAME, productbasket);

    for (int i = 1; i < argc; i++) {
        float price;
        char* shop;
        if (searchlowestprice(productbasket, n, argv[i], &price, &shop)) {
            printf("%s: %.2f EUR/kg, %s\n", argv[i], price, shop);
        } else {
            printf("Produkt '%s' nicht gefunden\n", argv[i]);
        }
    }

}

