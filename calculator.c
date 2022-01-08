// author: jürgen zangerl
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRINGMAX 30

int f_get_integer(long int *number) {
    int ret_scan;
    char v_input[STRINGMAX];
    // Einlesen eines String
    fgets(v_input, STRINGMAX, stdin);
    fflush(stdin);
    if(strcmp(v_input, "exit\n") == 0) {
        // 1 -> Abbruch / Exit
        return 1;
    }
    // Auslesen eines Integer aus dem gepufferten Sting
    ret_scan = sscanf(v_input, "%li[^\n]", number);
    if( ret_scan == 1 ){
        // es war eine Zahl
        return 0;

    }else{
        // es war KEINE Zahl
        return 2;
    }
}

int f_get_operator(char *operation) {
    char v_input[STRINGMAX];
    // Einlesen eines String
    fgets(v_input, STRINGMAX, stdin);
    fflush(stdin);
    if(strcmp(v_input, "exit\n") == 0) {
        // 1 -> Abbruch / Exit
        return 1;
    }
    // Check auf gültige Rechenoperation
    if( v_input[0] == '+' || v_input[0] == '-' || v_input[0] == '/' || v_input[0] == '*' ) {
        *operation =  v_input[0];
        // 0 -> es war eine gültige Eingabe
        return 0;
    }
    // 2 -> es war KEINE gültige Eingabe
    return 2;
}

int main() {
    int v_errorcode;
    long int num1, num2;
    char operator;
    while (1) {
        fprintf(stdout, "> Geben Sie Zahl 1 ein:\n");
        v_errorcode = f_get_integer(&num1);
        if( v_errorcode == 1 ) break;
        if( v_errorcode == 2 ) {
            fprintf(stderr, "> Falsche Eingabe!\n");
        } else {
            fprintf(stdout, "> Geben Sie die Operation ein:\n");
            v_errorcode = f_get_operator(&operator);
            if( v_errorcode == 1 ) break;
            if( v_errorcode == 2 ) {
                fprintf(stderr, "> Falsche Eingabe!\n");
            } else {
                fprintf(stdout, "> Geben Sie Zahl 2 ein:\n");
                v_errorcode = f_get_integer(&num2);
                if( v_errorcode == 1 ) break;
                if( v_errorcode == 2 ) {
                    fprintf(stderr, "> Falsche Eingabe!\n");
                }
            }
        }
        // Wurde alles korrekt eingeben, wird die Rechenoperation durchgeführt
        if( v_errorcode != 2 ) {
            if(operator == '+') {
                fprintf(stdout, "> Ergebnis: %li\n", (num1+num2));
            }else if(operator == '-') {
                fprintf(stdout, "> Ergebnis: %li\n", (num1-num2));
            }else if(operator == '/') {
                fprintf(stdout, "> Ergebnis: %.1f\n", ((float) num1/ (float) num2));
            }else if(operator == '*') {
                fprintf(stdout, "> Ergebnis: %li\n", (num1*num2));
            }else{
                fprintf(stderr, "> Unerwarteter Fehler! Rechenoperation nicht erkannt.\n");
            }
        }
    }
    fprintf(stdout, "> Rechner wird geschlossen\n");
    return 0;
}
