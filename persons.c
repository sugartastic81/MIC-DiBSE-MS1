// author: jürgen zangerl
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINEMAXLENGHT 254
#define STRINGMAX 64
#define MAXLINES 120
#define MAXHOBBIES 5

struct Personinfo {
    char s_vorname[STRINGMAX];
    char s_nachname[STRINGMAX];
    int s_alter;
    struct {
        char s_hobby[STRINGMAX];
    } hobbies[MAXHOBBIES];
} person[MAXLINES];

int main() {
    // Datei öffnen
    FILE *datei = fopen("persons_input.txt", "r");
    fflush(datei);
    if (datei == NULL) {
        // perror gibt die übergebene Fehlermeldung auf stderr aus und hängt zusätzlich noch einen String dran, der die Fehlerursache beschreibt
        perror("Fehler: Konnte Datei nicht öffnen.");
        return 1;
    }

    // Folgender Code liest bis zu MXLINES Zeilen aus der Textdatei
    int n=0, i, ret_scan;

    // Liest bis zur Ende der Datei bzw. < MAXLINES Zeile für Zeile aus der Datei
    char v_zeile[LINEMAXLENGHT];
    while ( fgets(v_zeile, LINEMAXLENGHT, datei) && n < MAXLINES ) {
        fflush(stdout);
        ret_scan = sscanf(v_zeile, "%63[^;];%63[^;];%i;%63[^,\n],%63[^,\n],%63[^,\n],%63[^,\n],%63[^,\n]", person[n].s_vorname, person[n].s_nachname, &person[n].s_alter,person[n].hobbies[0].s_hobby, person[n].hobbies[1].s_hobby, person[n].hobbies[2].s_hobby,person[n].hobbies[3].s_hobby, person[n].hobbies[4].s_hobby);
        if(ret_scan >= 4) {
            n++;
        }
    }
    // Datei ist fertig ausgelesen und wird geschlossen
    fclose(datei);

    // Ausgeben der Nachnamen der Personen zwischen 20 und inklusive 30 und Hobby Tanzen
    for (n=0; n < MAXLINES; n++) {
        if ( person[n].s_alter > 20 && person[n].s_alter <= 30 ){
            for (i = 0; i < MAXHOBBIES; i++) {
                if(strcmp(person[n].hobbies[i].s_hobby, "Tanzen") == 0) {
                    printf("%s\n", person[n].s_nachname);
                }
            }
        }
    }
    return 0;
}
