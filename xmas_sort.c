/* 3.5 Sortieren von Geschenken (17%)
Author: Juergen Zangerl
*/

#include <stdio.h>

void xmas_sort(int* array, const int n) {
    int position=0;
    while(position < n-1) {
        if (array[position] > array[position + 1]) {
            int var_dump;
            var_dump = array[position + 1];
            array[position + 1] = array[position];
            array[position] = var_dump;
            if(position > 0) position--;
        } else {
            position++;
        }
    }
}