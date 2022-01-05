// author: jürgen zangerl
#include <stdio.h>

int main() {
    // neue Datei anlegen
    FILE *datei = fopen("integers_output.txt", "w");
    // Prüfung, ob die Datei auch wirklich angelegt wurde
    if (datei == NULL) {
        // perror gibt die übergebene Fehlermeldung auf stderr aus und hängt zusätzlich noch einen String dran, der die Fehlerursache beschreibt
        perror("Fehler: Konnte Datei nicht anlegen");
        return 1;
    }

    int c=0,counter, last_letter=-1;
    fprintf(stdout, "> Geben Sie Ihren Text ein:\n");
    do {
        counter = 0;
        // liest solange immer ein Zeichen ein, bis ein Zeilenumbruch erfolgt
        while((c=getchar()) != '\n') {
            counter++;
            // falls das letzte Zeichen eine Zahl war und das aktuelle Zeichen keine Zahl mehr, dann wird ein Leerzeichen in die Datei geschrieben
            if ( (c < '0' || c > '9') && (last_letter >= '0' && last_letter <= '9') ) {
                putc(' ',datei);
            }
            // falls das aktuelle Zeichen eine Zahl ist, wird diese in die Datei geschrieben
            if (c >= '0' && c <= '9') {
                putc(c,datei);
            }
            last_letter = c;
        }
        // Zeilenumbruch, wenn nicht Ende
        if( counter > 0 ) {
            putc('\n',datei);
        }
        last_letter=-1;
        // Pufferlöschung
        fflush(datei);
    // Schleife wird abgebrochen, wenn das 1. Zeichen ein Zeilenumbruch ist, da der Counter dann nicht inkrementiert wurde
    } while (counter > 0);

    // Datei wird geschlossen
    fclose(datei);
    fprintf(stdout, "> Ende der Eingabe erreicht.\n");
    return 0;
}
