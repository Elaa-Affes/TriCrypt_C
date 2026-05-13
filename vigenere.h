#ifndef VIGENERE_H
#define VIGENERE_H

char cesar_car_alphanum(char c, int k);
int key_shift(char c);
char* viginer_crypt_mot(char *mot, char *cle);
char* viginer_decrypt_mot(char *mot, char *cle);

#endif
