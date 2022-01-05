//
// Created by Juergen Zangerl on 27.12.2021.
//
//

#include <stdio.h>
#include "my_string.h"

int string_cmp(const char* str1, const char* str2){
    int i;
    // prüft die Länge der beiden String. Bei Ungleichheit wird abgebrochen und 0 zurückgegeben.
    if(string_len(str1) != string_len(str2)){
        return 0;
    }
    // vergleicht Zeichen für Zeichen der beiden Strings. Bei Ungleichheit wird abgebrochen und 0 zurückgegeben.
    for(i=0; i<string_len(str1); i++) {
        if( str1[i]!=str2[i]){
            return 0;
        }
    }
    // kommt die Funktion bis an diesen Punkt, waren alle Gleichheitsprüfungen positiv, deshalb wird 1 zurückgegeben. (=Erfolg)
    return 1;
}

unsigned int string_len(const char* str){
    int i;
    //Endlosschleife, welche bis zum Stringterminator durchzählt
    for(i=0; str[i] != '\0'; i++);
    //gibt die Zeichenanzahl zurück
    return i;
}

void string_rev(unsigned char* str){
    int i;
    unsigned  var_length;
    unsigned char foo;
    var_length = string_len(str);
    // geht die 1. Hälfte des Strings durch
    for(i=0; i<(var_length/2); i++) {
        // Spiegeltausch mit Hilfsvariable foo
        // speichert das aktuelle Zeichen in der 1. Hälfte in der Hilfsvariable foo und tauscht das mit dem Zeichen der 2. Hälfte
        foo = str[i];
        str[i] = str[var_length-1-i];
        str[var_length-1-i] = foo;
    }
}

char *string_chr(const char* str, const char c){
    int i;
    for(i=0; i<string_len(str); i++) {
        if( str[i]== c){
            // gibt die Adresse zurück, an welcher das Zeichen gefunden wurde
            return (char*)str+i;
        }
    }
    return NULL;
}

