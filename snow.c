
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_MAX 8
#define STRINGMAX 32
#define SCAN_LINE_MAXLENGTH 256

// Funktion übernimmt ein Int-Array, in welches die Schneefallmengen der DATA_MAX Tage geschrieben werden
int collectsnowydaysinfile(int *snowydays, char *village) {
    char filename[50];
    int villageisindata = 1;
    for(int i=0; i < DATA_MAX; i++) {
        sprintf(filename, "snow_data/%d.txt", i+1);
        FILE *file = fopen(filename, "r");
        fflush(file);
        if (file == NULL) {
            fprintf(stderr, "Lesefehler -> konnte Datei nicht öffnen.");
            exit(1);
        }
        int v_snowfall;
        char v_village[STRINGMAX];
        char v_line[SCAN_LINE_MAXLENGTH];
        while (fgets(v_line, SCAN_LINE_MAXLENGTH, file) != NULL) {
            if (sscanf(v_line, "%31[^;];%d[^,\r\n ]", v_village, &v_snowfall) > 1 ) {
                if(strcmp(v_village, village) == 0) {
                    villageisindata = 0;
                    snowydays[i] = v_snowfall;
                    //printf("Tag %i: %i\n", i+1, snowydays[i]);
                }
            } else {
                fprintf(stderr, "%s -> nicht korrekt einlesbare Datenstruktur.\n", v_line);
                continue;
            }
        }
        fclose(file);
    }
    return villageisindata;
 }


int main(void) {
    char foo;
    int snowydays[DATA_MAX];
    char days[10];
    char village[64];
    printf("> Geben Sie einen Ort an:\n");
    fflush(stdout);
    fgets(village, 64, stdin);

    if (village[0] == '\n' || village[0] == '\r') {
        fprintf(stderr, "Eingabefehler -> die Eingabe hat keine Zeichen enthalten.\n");
        return 1;
    }else{
        sscanf(village, "%63[^\r\n]", village);
        int sum=0, i, till_day=0;
        if( collectsnowydaysinfile(snowydays,village) == 0 ) {
            printf("> Geben Sie einen Tag an:\n");
            fflush(stdout);
            fgets(days, 10, stdin);
            if ( days[0] == '\n' || days[0] == '\r' || (sscanf(days, " %d %c", &till_day, &foo) != 1) ) {
                fprintf(stderr, "Eingabefehler -> die Eingabe hat keine Zahl enthalten.\n");
                return 1;
            }else{
                if ( till_day >= 1 && till_day <= 8 ) {
                    char filename[100];
                    sprintf(filename, "snow_data/%s_%d.txt", village, till_day);
                    // neue Datei anlegen
                    FILE *datei = fopen(filename, "w");
                    // Prüfung, ob die Datei auch wirklich angelegt wurde
                    if (datei == NULL) {
                        fprintf(stderr, "Schreibfehler -> die Datei konnte nicht geöffnet werden.\n");
                        return 1;
                    }
                    for(i=0; i < till_day; i++) {
                        fprintf(datei, "Tag %i: %i\n", i+1, snowydays[i]);
                        sum += snowydays[i];
                    }
                    fprintf(datei, "Summe: %i", sum);
                    fclose(datei);
                }else{
                    fprintf(stderr, "Eingabefehler -> die Eingabe muss eine Zahl von 1 bis 8 sein.\n");
                    return 1;
                }

            }
        }else{
            fprintf(stderr, "Eingabefehler -> der Ort ist nicht in den Daten enthalten.\n");
            return 1;
        }
    }
    return EXIT_SUCCESS;

}

