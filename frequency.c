/* 3.4 Häufigkeitsberechnung mit Pointerarithmetik (17%)
Author: Juergen Zangerl
*/

#include <stdio.h>

int main(int argc, char **argv) {
    int i, n;
    int str_length, counter;
    int mystring[51];
    if (argc > 1) {
        //da leerzeichen als mehrere Parameter zählen, werden die einzelnen Parameter zu einer Zeichenkette zusammengebaut
        str_length = 0;
        for(int i=1; i < argc; i++) {
            n=0;
            if(i>1) {
                mystring[str_length] = ' ';
                str_length++;
            }
            while( *(argv[i]+n) != '\0' ) {
                mystring[str_length] = *(argv[i]+n);
                n++;
                str_length++;
            }
        }

        //bubblesort der Zeichenkette
        char var_dump;
        for(n=0; n < str_length-1; n++){
            for(i=0; i < str_length-1-n; i++) {
                if ( *(mystring+i) > *(mystring+i+1)) {
                    var_dump = *(mystring+i);
                    *(mystring+i) = *(mystring+i+1);
                    *(mystring+i+1) = var_dump;
                }
            }
        }
        i = 0;
        while(i < str_length){
            counter = 1;
            // iteriert bis ans ende und überprüft, ob zählt gleiche zeichen in der variable counter
            for(n = 1; n < str_length-i; n++){
                if(*(mystring+i) == *(mystring+i+n)) counter++;
            }
            printf("\n> Zeichen: '%c' - Haeufigkeit: %d",mystring[i],counter);
            i = i + counter;
        }
    } else {
        printf("\nFehler! Es wurde keine Zeichenkette für die Häufigkeitsberechnung als Kommandozeilenparameter übergeben.\n");
        return 1;
    }
    printf("\n");

    return 0;
}