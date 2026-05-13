#include "cesar.h"

char cesar_car(char c, int k) {
    char base;
    int modulo;

    if (c >= 'a' && c <= 'z') {
        base = 'a';
        modulo = 26;
    } else if (c >= 'A' && c <= 'Z') {
        base = 'A';
        modulo = 26;
    } else if (c >= '0' && c <= '9') {
        base = '0';
        modulo = 10;
    } else {
        return c;
    }

    int index = c - base;
    int nouvel_index = (index + k) % modulo;
    if (nouvel_index < 0) nouvel_index += modulo;

    return base + nouvel_index;
}

void cesar_crypte_mot(char *mot, int k) {
    for (int i = 0; mot[i] != '\0'; i++) {
        mot[i] = cesar_car(mot[i], k);
    }
}

void cesar_decrypte_mot(char *mot, int k) {
    cesar_crypte_mot(mot, -k);
}



