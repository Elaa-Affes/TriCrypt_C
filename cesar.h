#ifndef CESAR_H
#define CESAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char cesar_car(char c, int k);

void cesar_crypte_mot(char *mot, int k);

void cesar_decrypte_mot(char *mot, int k);

#endif
