#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "cesar.h"
#include "rsa.h"
#include "vigenere.h"


void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void session_cesar() {
    char phrase[1024];
    int k, sous_choix;

    printf("\n==================================\n");
    printf("   MODE CESAR (Cryptage de Texte)   \n");
    printf("==================================\n");
    printf("1. Crypter une phrase\n");
    printf("2. Decrypter une phrase\n");
    printf("Votre choix : ");
    scanf("%d", &sous_choix);
    viderBuffer();

    if (sous_choix == 1) {
        printf(">> Entrez le decalage (cle k) : ");
        scanf("%d", &k);
        viderBuffer();
        printf(">> Entrez la phrase a crypter : ");
        if (fgets(phrase, sizeof(phrase), stdin) != NULL) {
            phrase[strcspn(phrase, "\n")] = 0;
            cesar_crypte_mot(phrase, k);
            printf("\n[RESULTAT CRYPTE] : %s\n", phrase);
        }
    }
    else if (sous_choix == 2) {
        printf(">> Entrez le decalage (cle k) : ");
        scanf("%d", &k);
        viderBuffer();
        printf(">> Entrez la phrase a decrypter : ");
        if (fgets(phrase, sizeof(phrase), stdin) != NULL) {
            phrase[strcspn(phrase, "\n")] = 0;
            cesar_decrypte_mot(phrase, k);
            printf("\n[RESULTAT DECRYPTE] : %s\n", phrase);
        }
    }
}


void session_rsa() {
    int niveau;
    long long a, b, ecart = 2000;
    long long p, q;

    printf("\n===================================\n");
    printf("   MODE RSA (Texte -> Nombres)      \n");
    printf("===================================\n");
    printf("Choisissez la puissance de securite :\n");
    printf("1. Faible (Nombres ~ 100) \n");
    printf("2. Moyen  (Nombres ~ 5 000) \n");
    printf("3. Fort   (Nombres ~ 50 000)\n");
    printf("Votre choix (1-3) : ");
    scanf("%d", &niveau);


    if (niveau == 1) a = 50;
    else if (niveau == 2) a = 5000;
    else if (niveau == 3) a = 50000;
    else { a = 100; printf("Choix incorrect, niveau par defaut (1).\n"); }

    b = a + ecart;

    printf("\nGeneration des cles RSA en cours...\n");
    choisir_p_q(a, b, &p, &q);

    if (p == 0 || q == 0) {
        printf("Erreur critique : Impossible de trouver des nombres premiers.\n");
        return;
    }

    PublicKey cle_pub = generer_cle_publique(p, q);
    PrivateKey cle_priv = generer_cle_privee(p, q, cle_pub.e);

    printf("\n--- CLES RSA GENEREES ---\n");
    printf("Module n (Public)      = %lld\n", cle_pub.n);
    printf("Exposant e (Public)    = %lld\n", cle_pub.e);
    printf("Exposant d (Prive)     = %lld\n", cle_priv.d);
    printf("-------------------------\n");

    int continuer_rsa = 1;
    viderBuffer();

    while (continuer_rsa) {
        char choix_action[50];

        printf("\nAction a effectuer ? (cryptage / decryptage / quitter) : ");
        if (scanf("%s", choix_action) != 1) break;
        viderBuffer();


        for(int i = 0; choix_action[i]; i++) choix_action[i] = tolower(choix_action[i]);


        if (strcmp(choix_action, "cryptage") == 0) {
            char message[1024];
            printf(">> Entrez la PHRASE a crypter : ");
            if (fgets(message, sizeof(message), stdin) != NULL) {
                message[strcspn(message, "\n")] = 0;
                printf("\n[RESULTAT CRYPTE] (Copiez ces nombres pour le decryptage) :\n");
                printf("-------------------------------------------------------\n");


                for (int i = 0; i < strlen(message); i++) {
                    long long caractere_ascii = (long long)message[i];
                    long long chiffre = rsa_encrypt(caractere_ascii, cle_pub);
                    printf("%lld ", chiffre);
                }
                printf("\n-------------------------------------------------------\n");
            }
        }

        else if (strcmp(choix_action, "decryptage") == 0) {
            printf(">> Entrez les nombres cryptes separes par des espaces.\n");



            long long val;
            printf("\n[RESULTAT DECRYPTE] : ");


            while (scanf("%lld", &val) && val != -1) {
                long long dechiffre = rsa_decrypt(val, cle_priv);
                printf("%c", (char)dechiffre);
            }
            printf("\n");
            viderBuffer();
        }
        else if (strcmp(choix_action, "quitter") == 0) {
            continuer_rsa = 0;
        }
        else {
            printf("Commande inconnue.\n");
        }
    }
}


void session_vigenere() {
    char texte[200];
    char cle[100];
    char reponse[20];
    char *resultat = NULL;

    printf("\n===================================\n");
    printf("   MODE VIGENERE (Cle Polyalphabetique) \n");
    printf("===================================\n");

    do {
        printf("Voulez-vous 'cryptage' ou 'decryptage' ? : ");
        if (fgets(reponse, 20, stdin) != NULL) {
            reponse[strcspn(reponse, "\n")] = '\0';
        }
    } while (strcmp(reponse, "cryptage") != 0 && strcmp(reponse, "decryptage") != 0);

    printf(">> Entrer le texte : ");
    if (fgets(texte, 200, stdin) != NULL) {
        texte[strcspn(texte, "\n")] = '\0';
    }

    printf(">> Entrer la cle (mot cle) : ");
    if (fgets(cle, 100, stdin) != NULL) {
        cle[strcspn(cle, "\n")] = '\0';
    }

    if (strcmp(reponse, "cryptage") == 0) {
        resultat = viginer_crypt_mot(texte, cle);
        if (resultat) printf("\n[RESULTAT CRYPTE] : %s\n", resultat);
    } else {
        resultat = viginer_decrypt_mot(texte, cle);
        if (resultat) printf("\n[RESULTAT DECRYPTE] : %s\n", resultat);
    }

    if (resultat != NULL) {
        free(resultat);
        resultat = NULL;
    }
}


int main() {
    srand(time(NULL));
    int choix_principal;
    int execution = 1;

    while (execution) {
        printf("\n######################################\n");
        printf("#      MENU GLOBAL DE SECURITE        #\n");
        printf("######################################\n");
        printf("Quel algorithme voulez-vous utiliser ?\n");
        printf("1. CESAR    (Texte - Decalage simple)\n");
        printf("2. RSA      (Texte - Cle Publique/Privee)\n");
        printf("3. VIGENERE (Texte - Cle mot de passe)\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix_principal) != 1) {
            viderBuffer(); continue;
        }
        viderBuffer();
        switch (choix_principal) {
            case 0:
                printf("Fermeture du programme. Au revoir !\n");
                execution = 0;
                break;
            case 1:
                session_cesar();
                break;
            case 2:
                session_rsa();
                break;
            case 3:
                session_vigenere();
                break;
            default:
                printf("Choix invalide.\n");
        }
    }
    return 0;
}
