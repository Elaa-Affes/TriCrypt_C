#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rsa.h"


int est_premier(long long n) {
    if (n < 2) return 0;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}


void generer_premiers(long long a, long long b, long long** liste, int* taille) {
    int count = 0;

    for (long long i = a; i <= b; i++) {
        if (est_premier(i)) count++;
    }

    if (count == 0) {
        *liste = NULL;
        *taille = 0;
        return;
    }


    *liste = (long long*)malloc(count * sizeof(long long));
    if (*liste == NULL) {
        *taille = 0;
        return;
    }

    *taille = count;
    int index = 0;

    for (long long i = a; i <= b; i++) {
        if (est_premier(i)) {
            (*liste)[index] = i;
            index++;
        }
    }
}


void choisir_p_q(long long a, long long b, long long* p, long long* q) {
    long long* mes_premiers = NULL;
    int taille = 0;

    generer_premiers(a, b, &mes_premiers, &taille);

    if (taille < 2) {
        *p = 0; *q = 0;
    } else {
        int idx1 = rand() % taille;
        int idx2 = rand() % taille;


        while (idx1 == idx2) {
            idx2 = rand() % taille;
        }

        *p = mes_premiers[idx1];
        *q = mes_premiers[idx2];
    }
    free(mes_premiers);
}


PublicKey generer_cle_publique(long long p, long long q) {
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long debut;


    if (p > q) debut = p + 1;
    else       debut = q + 1;


    long long fin = debut + 2000;
    if (fin > phi - 1) fin = phi - 1;

    long long* Le = NULL;
    int taille = 0;

    generer_premiers(debut, fin, &Le, &taille);

    long long e = 0;

    for (int i = 0; i < taille; i++) {
        if (phi % Le[i] != 0) {
            e = Le[i];
            break;
        }
    }


    if (e == 0) e = 65537;
    if (taille > 0) free(Le);

    PublicKey cle;
    cle.n = n;
    cle.e = e;

    return cle;
}

long long euclide_etendu(long long a, long long b, long long* u, long long* v) {
    long long r0 = a, r1 = b;
    long long u0 = 1, u1 = 0;
    long long v0 = 0, v1 = 1;

    while (r1 != 0) {
        long long q = r0 / r1;
        long long rs = r0 % r1;
        long long us = u0 - q * u1;
        long long vs = v0 - q * v1;

        r0 = r1; r1 = rs;
        u0 = u1; u1 = us;
        v0 = v1; v1 = vs;
    }

    *u = u0;
    *v = v0;

    return r0;
}

PrivateKey generer_cle_privee(long long p, long long q, long long e) {
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    long long u, v;
    euclide_etendu(e, phi, &u, &v);

    long long d = (u % phi + phi) % phi;

    PrivateKey cle;
    cle.n = n;
    cle.d = d;

    return cle;
}


long long mod_pow(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {

            res = (long long)((__int128)res * base % mod);
        }
        base = (long long)((__int128)base * base % mod);
        exp = exp / 2;
    }
    return res;
}

long long rsa_encrypt(long long message, PublicKey key) {
    return mod_pow(message, key.e, key.n);
}

long long rsa_decrypt(long long chiffre, PrivateKey key) {
    return mod_pow(chiffre, key.d, key.n);
}
