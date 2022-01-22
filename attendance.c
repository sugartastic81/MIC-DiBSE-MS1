
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCAN_CORRECT_LINES_MAX 30
#define STRINGMAX 32
#define SCAN_LINE_MAXLENGTH 256

struct s_students {
    char student_name[STRINGMAX];
    char student_surname[STRINGMAX];
    char student_studypaths[4][STRINGMAX];
} studentlist[SCAN_CORRECT_LINES_MAX];

struct s_participiants {
    char part_name[STRINGMAX];
    char part_surname[STRINGMAX];
    int part_login;
    int part_logout;
} webinarparticipants[SCAN_CORRECT_LINES_MAX];


int readparticipantssoutoffile(char filename[STRINGMAX]) {
    char v_line[SCAN_LINE_MAXLENGTH];
    int n = 0;

    // Datei öffnen
    FILE *file = fopen(filename, "r");
    fflush(file);
    if (file == NULL) {
        // perror gibt die übergebene Fehlermeldung auf stderr aus und hängt zusätzlich noch einen String dran, der die Fehlerursache beschreibt
        perror("Fehler: Konnte Datei nicht öffnen. Lesefehler.");
        return 1;
    }
    // liest nun bis Dateiende bzw. bis zu max_lines korrekte Zeilen ein und splittet die Tabellendaten auf die einzelnen Strukturvariablen auf
    while (fgets(v_line, SCAN_LINE_MAXLENGTH, file) != NULL) {
        if (sscanf(v_line, "%31[^:]:%31[^:]:%d:%d[^,\r\n ]", webinarparticipants[n].part_name, webinarparticipants[n].part_surname, &webinarparticipants[n].part_login, &webinarparticipants[n].part_logout) > 3 ) {
            //printf("__%s__%s__%li__%li__\n", webinarparticipants[n].part_name, webinarparticipants[n].part_surname, webinarparticipants[n].part_login, webinarparticipants[n].part_logout);
            n++;
            if (n >= SCAN_CORRECT_LINES_MAX) break; // steigt nach max_lines Zeilen aus der Schleife aus
        } else {
            fprintf(stderr, "%s -> nicht korrekt lesbare Datenstruktur.\n", v_line);
            continue;
        }
    }
    fclose(file);
    return n;
}

int readstudentssoutoffile(char filename[STRINGMAX]) {
    char v_line[SCAN_LINE_MAXLENGTH];
    int n = 0;

    // Datei öffnen
    FILE *studentsfile = fopen(filename, "r");
    fflush(studentsfile);
    if (studentsfile == NULL) {
        // perror gibt die übergebene Fehlermeldung auf stderr aus und hängt zusätzlich noch einen String dran, der die Fehlerursache beschreibt
        perror("Fehler: Konnte Datei nicht öffnen. Lesefehler.");
        return 1;
    }
    // liest nun bis Dateiende bzw. bis zu max_lines korrekte Zeilen ein und splittet die Tabellendaten auf die einzelnen Strukturvariablen auf
    while (fgets(v_line, SCAN_LINE_MAXLENGTH, studentsfile) != NULL) {
        if (sscanf(v_line, "%31[^;];%31[^;];%31[^,\r\n],%31[^,\r\n],%31[^,\r\n],%31[^,\r\n],", studentlist[n].student_name,studentlist[n].student_surname, studentlist[n].student_studypaths[0], studentlist[n].student_studypaths[1],studentlist[n].student_studypaths[2],studentlist[n].student_studypaths[3]) >= 3 ) {
            //printf("__%s__%s__%s__%s__%s__%s__\n", studentlist[n].student_name,studentlist[n].student_surname,studentlist[n].student_studypaths[0],studentlist[n].student_studypaths[1],studentlist[n].student_studypaths[2],studentlist[n].student_studypaths[3]);
            n++;
            if (n >= SCAN_CORRECT_LINES_MAX) break; // steigt nach max_lines Zeilen aus der Schleife aus
        } else {
            fprintf(stderr, "%s -> nicht korrekt lesbare Datenstruktur.\n", v_line);
            continue;
        }
    }
    fclose(studentsfile);
    return n;
}

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        fprintf(stderr, "Es wurden der Funktion nicht genügend Parameter (Studiengang und Webinardauer) übergeben.\n");
        exit(1);
    }

    int webinar_length;
    webinar_length = atoi(argv[2]);

    // Prüft, ob berechenbare Webinardauer angegeben wurde.
    if( webinar_length > 0 ) {
        // liest die Studenten in die Struktur ein
        int m = readparticipantssoutoffile("webinar.txt");
        int n = readstudentssoutoffile("students.txt");
        for (int i = 0; i < n; i++) { // Studentenschleife
            int j;
            for (int k = 0; k < 4; k++) {
                if( strcmp(studentlist[i].student_studypaths[k],argv[1]) == 0 ) { // Student ist im Kurs registriert
                    int student_found = 0;
                    for (j = 0; j < m; j++) { // Durchläuft Webinardaten auf der Suche nach dem Student
                        if( strcmp(studentlist[i].student_name,webinarparticipants[j].part_name) == 0 && strcmp(studentlist[i].student_surname,webinarparticipants[j].part_surname) == 0) {
                            student_found = 1;
                            break;
                        }
                    }
                    if ( student_found == 1 ) {
                        //printf("__%s__%s__%s__\n__%s__%s__%li__%li__\n\n", studentlist[i].student_name,studentlist[i].student_surname,studentlist[i].student_studypaths[k],webinarparticipants[j].part_name, webinarparticipants[j].part_surname, webinarparticipants[j].part_login, webinarparticipants[j].part_logout);
                        if( (webinarparticipants[j].part_logout - webinarparticipants[j].part_login)/60 < (0.75 * webinar_length) ) { // prüft ob der Teilnehmer weniger als 75% der Zeit anwesend war
                            printf("%s %s: %li Minuten\n", studentlist[i].student_name, studentlist[i].student_surname, ( (long) (webinarparticipants[j].part_logout - webinarparticipants[j].part_login)/60 ));
                        }
                    }else{
                        printf("%s %s: nicht anwesend\n", studentlist[i].student_name, studentlist[i].student_surname);
                    }

                }
            }
        }
    }else{
        fprintf(stderr, "Es wurden der Funktion keine berechenbare Webinarlänge übergeben. (2. Argument)\n");
        exit(1);
    }
}

