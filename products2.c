// 6.2 Klausur von 2020 - Einkaufsplaner

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct s_product {
    char product_name[32];
    char product_market[32];
    float product_priceperentity;
};

#define FILE_NAME "products.txt"
#define SCAN_CORRECT_LINES_MAX 36

int getcheapestpriceoutoffile(char filename[50], struct s_product *productbasket, int numofproducts) {
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
    char product_name[32];
    char product_market[32];
    float product_weight;
    float product_price;
    float product_priceperentity;
    // liest nun bis Dateiende bzw. bis zu max_lines korrekte Zeilen ein und splittet die Tabellendaten auf die einzelnen Strukturvariablen auf
    while (fgets(v_line, 256, productfile) != NULL) {
        if (sscanf(v_line, "%31[^;];%31[^;];%f;%f", product_name,product_market, &product_weight, &product_price) == 4 ) {
            product_priceperentity = product_price/product_weight;
            for( int i = 0; i < numofproducts; i++ ) {
                if( strcmp(productbasket[i].product_name, product_name) == 0  && (productbasket[i].product_priceperentity > product_priceperentity || strlen(productbasket[i].product_market) < 2) ) {
                    strcpy(productbasket[i].product_name, product_name);
                    strcpy(productbasket[i].product_market, product_market);
                    productbasket[i].product_priceperentity = product_price/product_weight;
                }
            }
            n++;
            if (n >= SCAN_CORRECT_LINES_MAX) break; // steigt nach max_lines eingelesenen Zeilen aus der Schleife aus
        } else {
            fprintf(stderr, "%s -> nicht korrekt lesbare Datenstruktur.\n", v_line);
            continue;
        }
    }
    fclose(productfile);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Es wurden der Funktion keine Parameter (= Produkte) übergeben.\n");
        exit(1);
    }
    // Baut einen Warenkorb aus den übergebenen Produkten
    struct s_product productbasket[argc-1];
    for (int i = 1; i < argc; i++) {
        strcpy(productbasket[i-1].product_name, argv[i]);
        strcpy(productbasket[i-1].product_market, "");
        productbasket[i-1].product_priceperentity = 0;
    }

    // Liest die Datei products.txt ein, gleicht diese mit dem Warenkorb ab und
    getcheapestpriceoutoffile(FILE_NAME, productbasket, argc-1);

    for (int i = 0; i < argc-1; i++) {
        if( strlen(productbasket[i].product_market) < 2 ) {
            printf("Produkt '%s' nicht gefunden\n", productbasket[i].product_name);
        } else {
            printf("%s: %.2f EUR/kg, %s\n", productbasket[i].product_name, productbasket[i].product_priceperentity, productbasket[i].product_market);
        }
    }

    return 0;

}

