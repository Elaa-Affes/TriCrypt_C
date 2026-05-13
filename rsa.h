#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED
typedef struct {
    long long n;
    long long e;
} PublicKey;

typedef struct {
    long long n;
    long long d;
} PrivateKey;

int est_premier(long long n);
long long euclide_etendu(long long a, long long b, long long* u, long long* v);


void generer_premiers(long long a, long long b, long long** liste, int* taille);
void choisir_p_q(long long a, long long b, long long* p, long long* q);


PublicKey generer_cle_publique(long long p, long long q);
PrivateKey generer_cle_privee(long long p, long long q, long long e);
long long rsa_encrypt(long long message, PublicKey key);
long long rsa_decrypt(long long chiffre, PrivateKey key);


long long mod_pow(long long base, long long exp, long long mod);

#endif






