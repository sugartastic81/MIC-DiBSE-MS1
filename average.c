/* 3.2 Mittelwert und Varianz (17%)
Author: Juergen Zangerl
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calc_average_variance(int array[], int quantity, float *erg_average, float *erg_variance) {
    *erg_average = 0;
    *erg_variance = 0;
    int summe = 0, i;
    for (i = 0; i < quantity; i++) {
        summe += array[i];
    }
    *erg_average = summe / quantity;
    for (i = 0; i < quantity; i++) {
        *erg_variance += (array[i]-*erg_average)*(array[i]-*erg_average);
    }
    *erg_variance = *erg_variance / quantity;
}


int main() {
    int quantity;

    printf("> Geben Sie die Anzahl der Elemente Ihres Arrays an:\n");
    scanf("%i", &quantity);

    int i;
    int array[quantity];

    for(i = 0; i < quantity; i++) {
        printf("> Element #%d:\n", i+1);
        scanf("%i", &array[i]);
    }

    float erg_average=0, erg_variance=0;

    calc_average_variance(array, quantity, &erg_average, &erg_variance);

    printf("\nDurchschnitt = %f.1 \tVarianz = %.1f", erg_average, erg_variance);

    return EXIT_SUCCESS;
}
