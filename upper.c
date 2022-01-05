/* 3.1 Großbuchstaben (17%)
Implementieren Sie ein Programm, dass mittels scanf eine Zeichenfolge einliest, jeden Kleinbuchstaben darin durch den
 entsprechenden Großbuchstaben ersetzt und die veränderte Zeichenfolge ausgibt. Nur Kleinbuchstaben sollen verändert
 werden, andere Zeichen sollen beibehalten werden. Ihre Implementierung soll für alle Zeichenfolgen mit Länge kleiner
 als 50 funktionieren. Achten Sie in Ihrer Implementierung darauf, dass es auch bei längeren Zeichenfolgen zu keinem
 Buffer-Overflow kommt.

Achtung: Die Benutzung von Bibliotheksfunktionen zur Umwandlung Ihrer Zeichenkette ist nicht erlaubt. Außerdem ist die
 Eingabe von Daten via scanf in Jupyter-Notebook nicht möglich. Testen Sie Ihre Implementierung daher direkt in der
 Kommandozeile.

Author: Juergen Zangerl
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    int str_length = 0;
    char mystring[50];

    // printf("\nGeben Sie eine Zeichenkette mit maximal 50 Zeichen ein: ");
    scanf("%[^\n]50s",mystring);

    while (str_length < 50) {
        if (mystring[str_length] >= 'a' && mystring[str_length] <= 'z') {
            mystring[str_length] = mystring[str_length] - 32;
        }
        str_length++;
    }
    printf("\n%s\n",mystring);

    return EXIT_SUCCESS;
}
