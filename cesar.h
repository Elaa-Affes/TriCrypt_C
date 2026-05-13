#ifndef CESAR_H
#define CESAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// --- Prototypes des fonctions ---
// (C'est la liste de ce que votre "librairie" sait faire)

// Crypte ou décrypte un seul caractère
char cesar_car(char c, int k);

// Crypte toute une phrase (modifie la chaine directement)
void cesar_crypte_mot(char *mot, int k);

// Décrypte toute une phrase
void cesar_decrypte_mot(char *mot, int k);

#endif
