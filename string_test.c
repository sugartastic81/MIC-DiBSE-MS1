
#include <stdio.h>
#include <string.h>
#include "my_string.h"


void test_string_len(const char* str) {
    printf("string_len(\"%s\"): %d\n", str, string_len(str));
}


void test_string_cmp(const char* str1, const char* str2) {
    printf("string_cmp(\"%s\", \"%s\"): %d\n", str1, str2, string_cmp(str1, str2));
}

void test_string_rev(const char* str) {
    // First we need to copy the string into a memory region that is write-enabled
    char tmp[string_len(str) + 1];
    memcpy(tmp, str, sizeof(tmp));
    string_rev(tmp);
    printf("string_rev(\"%s\"): %s\n", str, tmp);
}

void test_string_chr(const char* str, const char c) {
    char* retval = string_chr(str, c);
    printf("string_chr(\"%s\", \'%c\'): %p", str, c, retval);
    if (retval != NULL) {
        printf(" (%c) %ld Bytes from start of string\n", *retval, (long)retval - (long)str);
    } else {
        printf("\n");
    }
}

int main() {
    
    test_string_len("");
    test_string_len("X");
    test_string_len("Hallo Welt!");
    
    printf("\n");
    
    test_string_cmp("", "");
    test_string_cmp("", "X");
    test_string_cmp("X", "");
    test_string_cmp("bla", "blabla");
    test_string_cmp("blabla", "bla");
    test_string_cmp("Hallo Welt!", "Hallo Welt!");
    test_string_cmp("12345", "12345");
    
    printf("\n");
    
    test_string_rev("");
    test_string_rev("Hallo Welt!");
    test_string_rev("X");
    test_string_rev("blabla");
    
    printf("\n");
    
    test_string_chr("Hallo Welt!", 'H');
    test_string_chr("Hallo Welt!", 'o');
    test_string_chr("Hallo Welt!", 'l');
    test_string_chr("Hallo Welt!", '!');
    test_string_chr("Hallo Welt!", 'X');
}

