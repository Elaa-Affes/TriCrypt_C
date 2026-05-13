#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "vigenere.h"



char cesar_car_alphanum(char c, int k) {

    if (isalpha(c)) {
        char base = islower(c) ? 'a' : 'A';
        int index = c - base;
        int nouvel_index = (index + k) % 26;
        if (nouvel_index < 0) nouvel_index += 26;
        return base + nouvel_index;
    }

    else if (isdigit(c)) {
        int index = c - '0';
        int nouvel_index = (index + k) % 10;
        if (nouvel_index < 0) nouvel_index += 10;
        return '0' + nouvel_index;
    }

    return c;
}

int key_shift(char c) {
    if (isalpha(c)) return tolower(c) - 'a';
    if (isdigit(c)) return c - '0';
    return 0;
}

char* viginer_crypt_mot(char *mot, char *cle) {
    int len_mot = strlen(mot);
    int len_cle = strlen(cle);
    char *motC = malloc((len_mot + 1) * sizeof(char));
    if (motC == NULL || len_cle == 0) return NULL;

    int j = 0;
    for (int i = 0; i < len_mot; i++) {

        if (isalnum(mot[i])) {
            int k = key_shift(cle[j % len_cle]);
            motC[i] = cesar_car_alphanum(mot[i], k);
            j++;
        } else {
            motC[i] = mot[i];
        }
    }
    motC[len_mot] = '\0';
    return motC;
}


char* viginer_decrypt_mot(char *mot, char *cle) {
    int len_mot = strlen(mot);
    int len_cle = strlen(cle);
    char *motD = malloc((len_mot + 1) * sizeof(char));
    if (motD == NULL || len_cle == 0) return NULL;

    int j = 0;
    for (int i = 0; i < len_mot; i++) {
        if (isalnum(mot[i])) {
            int k = key_shift(cle[j % len_cle]);
            motD[i] = cesar_car_alphanum(mot[i], -k);
            j++;
        } else {
            motD[i] = mot[i];
        }
    }
    motD[len_mot] = '\0';
    return motD;
}
