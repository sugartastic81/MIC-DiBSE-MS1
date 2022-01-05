// author: jürgen zangerl
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRINGMAX 30
#define MAXPERSONS 20
#define MAXHOBBIES 5

struct Personinfo {
    char p_vorname[STRINGMAX];
    char p_nachname[STRINGMAX];
    unsigned int p_alter;
    struct {
        char p_hobby[STRINGMAX];
    } hobbies[MAXHOBBIES];
} person[MAXPERSONS];

int main() {
    // Datei öffnen
    FILE *datei = fopen("persons_input.txt", "r");
    if (datei == NULL) {
        // perror gibt die übergebene Fehlermeldung auf stderr aus und hängt zusätzlich noch einen String dran, der die Fehlerursache beschreibt
        perror("Fehler: Konnte Datei nicht öffnen.");
        return 1;
    }

    // Folgender Code liest bis zu 20 Zeilen aus der Textdatei
    int n=0, i=0, c, var_item=0;
    char var_string[100];
    while (n < MAXPERSONS) {
        c = fgetc(datei);
        if(c != '\n' && c != ';' && c != ',' && c != EOF) {
            // fügt die Buchstaben zu einem Wort zusammen
            var_string[i] = c;
            i++;
        }else{
            // falls ein Wort, eine Zeile oder die Datei abgeschlossen ist, wird dieser Teil ausgeführt
            i = 0;
            switch (var_item) {
                case 0:
                    strcpy(person[n].p_vorname, var_string);
                    break;
                case 1:
                    strcpy(person[n].p_nachname, var_string);
                    break;
                case 2:
                    person[n].p_alter = atoi(var_string);
                    break;
                case 3:
                    strcpy(person[n].hobbies[0].p_hobby, var_string);
                    break;
                case 4:
                    strcpy(person[n].hobbies[1].p_hobby, var_string);
                    break;
                case 5:
                    strcpy(person[n].hobbies[2].p_hobby, var_string);
                    break;
                case 6:
                    strcpy(person[n].hobbies[3].p_hobby, var_string);
                    break;
                case 7:
                    strcpy(person[n].hobbies[4].p_hobby, var_string);
                    break;
                default:
                    break;
            }
            memset(var_string, 0, 100);
            if( c == ';' || c == ',' ) {
                var_item++;
            }
            if( c == '\n' || c == EOF ) {
                n++;
                var_item = 0;
            }
        }
        if(i > 255) {
            perror("Fehler beim Einlesen einer Zeile. Vermutlich inkorrekte Datenstruktur.");
            return 1;
        }
        if(c == EOF) break;
    }
    // Datei ist fertig ausgelesen und wird geschlossen
    fclose(datei);
    
    // Ausgeben der Nachnamen der Personen zwischen 20 und inklusive 30 und Hobby Tanzen
    for (i=0; i < MAXPERSONS; i++) {
        if ( person[i].p_alter > 20 && person[i].p_alter <= 30 ){
            for (n = 0; n < MAXHOBBIES; n++) {
                if(strcmp(person[i].hobbies[n].p_hobby, "Tanzen") == 0) {
                    printf("%s\n", person[i].p_nachname);
                }
            }
        }
    }
    return 0;
}
