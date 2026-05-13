<div align="center">

# 🔐 TriCrypt

**A cryptography project in C — César · Vigenère · RSA**

![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen?style=for-the-badge)
![School](https://img.shields.io/badge/School-SUP'COM-purple?style=for-the-badge)
![Year](https://img.shields.io/badge/Year-2025%2F2026-orange?style=for-the-badge)

*Réalisé par **Elaa Affes** — École Supérieure des Communications de Tunis*

</div>

---

## 📌 Table des matières

1. [Description](#-description)
2. [Structure du projet](#-structure-du-projet)
3. [Lancer le projet sur VS Code](#-lancer-le-projet-sur-vs-code)
4. [Algorithme de César](#1️⃣-algorithme-de-césar)
5. [Algorithme de Vigenère](#2️⃣-algorithme-de-vigenère)
6. [Algorithme RSA](#3️⃣-algorithme-rsa)
7. [Menu principal](#-menu-principal)
8. [.gitignore recommandé](#-gitignore-recommandé)

---

## 📖 Description

**TriCrypt** est une application console en langage **C** qui permet de **chiffrer** et **déchiffrer** des messages en utilisant trois algorithmes cryptographiques classiques :

| Algorithme | Type | Clé |
|---|---|---|
| **César** | Symétrique — substitution mono-alphabétique | Nombre entier `k` |
| **Vigenère** | Symétrique — substitution poly-alphabétique | Mot de passe |
| **RSA** | Asymétrique — clé publique / clé privée | Générée automatiquement |

Chaque algorithme supporte les **lettres majuscules et minuscules**, les **chiffres**, et laisse les **espaces / caractères spéciaux** intacts.

---

## 📁 Structure du projet

```
TriCrypt/
│
├── main.c          → Menu principal + fonctions de session
├── cesar.c         → Implémentation du chiffrement César
├── cesar.h         → Déclarations César
├── vigenere.c      → Implémentation du chiffrement Vigenère
├── vigenere.h      → Déclarations Vigenère
├── rsa.c           → Implémentation du chiffrement RSA
└── rsa.h           → Déclarations RSA
```

---

## 💻 Lancer le projet sur VS Code

### Étape 1 — Prérequis

Installe les outils nécessaires selon ton système :

**Windows :**
- Télécharge et installe [MinGW-w64](https://www.mingw-w64.org/) (inclut `gcc`)
- Ajoute `C:\MinGW\bin` à la variable d'environnement `PATH`
- Vérifie l'installation :
  ```bash
  gcc --version
  ```

**Linux / macOS :**
```bash
# Linux (Ubuntu/Debian)
sudo apt install gcc

# macOS
xcode-select --install
```

### Étape 2 — Extensions VS Code recommandées

Dans VS Code, installe ces extensions (`Ctrl+Shift+X`) :

| Extension | Utilité |
|---|---|
| `C/C++` par Microsoft | Coloration syntaxique + IntelliSense |
| `Code Runner` | Exécuter le code directement depuis VS Code |

### Étape 3 — Ouvrir le projet

```bash
# Ouvre le dossier du projet dans VS Code
code .
```

### Étape 4 — Compiler le projet

Ouvre le **Terminal intégré** (`Ctrl+ù` ou `View → Terminal`) et tape :

```bash
gcc main.c cesar.c vigenere.c rsa.c -o tricrypt
```

> ⚠️ Tous les fichiers `.c` doivent être compilés ensemble dans la même commande.

### Étape 5 — Exécuter

```bash
# Linux / macOS
./tricrypt

# Windows
tricrypt.exe
```

### 🔧 Optionnel — Compiler en un clic avec `tasks.json`

Crée le fichier `.vscode/tasks.json` dans ton projet :

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Build TriCrypt",
      "type": "shell",
      "command": "gcc",
      "args": [
        "main.c", "cesar.c", "vigenere.c", "rsa.c",
        "-o", "tricrypt",
        "-Wall"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": ["$gcc"]
    }
  ]
}
```

Ensuite utilise `Ctrl+Shift+B` pour compiler directement ✅

---

## 1️⃣ Algorithme de César

### Principe

Chaque caractère du message est **décalé d'une valeur fixe `k`** dans l'alphabet.
Pour déchiffrer, on applique le décalage inverse.

```
Chiffrement   →  C = (P + k) mod N
Déchiffrement →  P = (C - k + N) mod N

  N = 26  pour les lettres  (A→Z en boucle)
  N = 10  pour les chiffres (0→9 en boucle)
```

### Code source — `cesar.c`

```c
char cesar_car(char c, int k) {
    char base;
    int modulo;

    if (c >= 'a' && c <= 'z')      { base = 'a'; modulo = 26; }
    else if (c >= 'A' && c <= 'Z') { base = 'A'; modulo = 26; }
    else if (c >= '0' && c <= '9') { base = '0'; modulo = 10; }
    else return c; // espaces et ponctuations → inchangés

    int index        = c - base;
    int nouvel_index = (index + k) % modulo;
    if (nouvel_index < 0) nouvel_index += modulo;

    return base + nouvel_index;
}
```

### Exemple — k = 3

| Caractère | Calcul | Résultat |
|---|---|---|
| `P` | (15 + 3) mod 26 | `S` |
| `A` | (0 + 3) mod 26 | `D` |
| `S` | (18 + 3) mod 26 | `V` |
| `S` | (18 + 3) mod 26 | `V` |
| ` ` | espace → inchangé | ` ` |
| `8` | (8 + 3) mod 10 | `1` |

```
Message original  :  PASS 8
Message chiffré   :  SDVV 1
```

**Déchiffrement (k = 3) :**
```
Message chiffré   :  SDVV 1
Message original  :  PASS 8  ✅
```

### Démo terminal

```
==================================
   MODE CESAR (Cryptage de Texte)
==================================
1. Crypter une phrase
2. Decrypter une phrase
Votre choix : 1

>> Entrez le decalage (cle k) : 3
>> Entrez la phrase a crypter : Bonjour 2025

[RESULTAT CRYPTE] : Erqmrxu 5358
```

---

## 2️⃣ Algorithme de Vigenère

### Principe

Vigenère est une **version améliorée de César** : le décalage n'est pas fixe, il **change à chaque caractère** selon la lettre correspondante d'un **mot-clé**. Si le message est plus long que la clé, la clé se **répète**.

```
Chiffrement   →  C = (P + K) mod 26
Déchiffrement →  P = (C - K + 26) mod 26

  K = position de la lettre de clé (a=0, b=1, ..., z=25)
```

### Code source — `vigenere.c`

```c
char* viginer_crypt_mot(char *mot, char *cle) {
    int len_mot = strlen(mot);
    int len_cle = strlen(cle);
    char *motC  = malloc((len_mot + 1) * sizeof(char));

    int j = 0;
    for (int i = 0; i < len_mot; i++) {
        if (isalnum(mot[i])) {
            int k   = key_shift(cle[j % len_cle]); // clé cyclique
            motC[i] = cesar_car_alphanum(mot[i], k);
            j++;  // avancer dans la clé seulement si on chiffre un caractère
        } else {
            motC[i] = mot[i]; // espaces et ponctuations préservés
        }
    }
    motC[len_mot] = '\0';
    return motC;
}
```

### Exemple — clé = `python`

**Valeurs numériques de la clé :**

| `p` | `y` | `t` | `h` | `o` | `n` |
|---|---|---|---|---|---|
| 15 | 24 | 19 | 7 | 14 | 13 |

**Chiffrement de `concours2025` :**

| Car. | Clé | Décalage | Calcul | Résultat |
|---|---|---|---|---|
| `c` | `p` | 15 | (2+15) mod 26 | `r` |
| `o` | `y` | 24 | (14+24) mod 26 | `m` |
| `n` | `t` | 19 | (13+19) mod 26 | `g` |
| `c` | `h` | 7 | (2+7) mod 26 | `j` |
| `o` | `o` | 14 | (14+14) mod 26 | `c` |
| `u` | `n` | 13 | (20+13) mod 26 | `h` |
| `r` | `p` | 15 | (17+15) mod 26 | `g` |
| `s` | `y` | 24 | (18+24) mod 26 | `q` |
| `2` | `t` | 19 | (2+19) mod 10 | `1` |
| `0` | `h` | 7 | (0+7) mod 10 | `7` |
| `2` | `o` | 14 | (2+14) mod 10 | `6` |
| `5` | `n` | 13 | (5+13) mod 10 | `8` |

```
Message original  :  concours2025
Clé               :  python
Message chiffré   :  rmgjchgq1768
```

### Démo terminal

```
=====================================
   MODE VIGENERE (Cle mot de passe)
=====================================
1. Crypter une phrase
2. Decrypter une phrase
Votre choix : 1

>> Entrez la cle     : python
>> Entrez le message : concours2025

[RESULTAT CRYPTE] : rmgjchgq1768
```

---

## 3️⃣ Algorithme RSA

### Principe

RSA est un algorithme **asymétrique** qui utilise deux clés différentes :

- 🔑 **Clé publique `(n, e)`** → pour **chiffrer** (partagée librement)
- 🗝️ **Clé privée `(n, d)`** → pour **déchiffrer** (gardée secrète)

La sécurité repose sur la **difficulté de factoriser** de très grands entiers.

### Génération des clés

```
1. Choisir p, q     →  deux grands nombres premiers distincts
2. Calculer n       →  n = p × q                    (module public)
3. Calculer φ       →  φ = (p-1) × (q-1)
4. Choisir e        →  e premier avec φ              → clé publique (n, e)
5. Calculer d       →  e × d ≡ 1 (mod φ)            → clé privée  (n, d)
```

### Chiffrement et déchiffrement

```
Chiffrement   →  C = M^e mod n
Déchiffrement →  M = C^d mod n
```

### Code source — `rsa.c`

```c
// Exponentiation modulaire rapide (évite l'overflow avec __int128)
long long mod_pow(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (long long)((__int128)res * base % mod);
        base = (long long)((__int128)base * base % mod);
        exp  = exp / 2;
    }
    return res;
}

long long rsa_encrypt(long long message, PublicKey key) {
    return mod_pow(message, key.e, key.n);
}

long long rsa_decrypt(long long chiffre, PrivateKey key) {
    return mod_pow(chiffre, key.d, key.n);
}
```

> 💡 Le type `__int128` est utilisé pour stocker temporairement les multiplications intermédiaires sur 128 bits et ainsi éviter tout **dépassement de capacité (overflow)**.

### Exemple — message = `123`

| Étape | Calcul | Valeur |
|---|---|---|
| Nombres premiers | choix aléatoire | `p = 11`, `q = 13` |
| Module | `n = 11 × 13` | `n = 143` |
| Phi | `(11-1) × (13-1)` | `φ = 120` |
| Clé publique | `e` premier avec 120 | `e = 7` |
| Clé privée | `7 × d ≡ 1 (mod 120)` | `d = 103` |
| Chiffrement | `123^7 mod 143` | `C = 7` |
| Déchiffrement | `7^103 mod 143` | `M = 123` ✅ |

### Démo terminal

```
===================================
   MODE RSA (Texte -> Nombres)
===================================
Choisissez la puissance de securite :
1. Faible  (Nombres ~   100)
2. Moyen   (Nombres ~ 5 000)
3. Fort    (Nombres ~ 50 000)
Votre choix (1-3) : 1

Generation des cles RSA en cours...

[CLE PUBLIQUE]  n = 143  |  e = 7
[CLE PRIVEE]    n = 143  |  d = 103

>> Entrez le message a chiffrer : 123

[CHIFFRE]    C = 7
[DECHIFFRE]  M = 123  ✅
```

---

## 🖥️ Menu principal

Au lancement du programme :

```
######################################
#      MENU GLOBAL DE SECURITE       #
######################################

Quel algorithme voulez-vous utiliser ?

  1. CESAR    (Texte - Decalage simple)
  2. RSA      (Nombres - Cle Publique/Privee)
  3. VIGENERE (Texte - Cle mot de passe)
  0. Quitter

Votre choix :
```

Le programme **boucle** jusqu'à ce que tu entres `0`.

---

## 🚫 .gitignore recommandé

```gitignore
# Fichiers compilés
*.o
*.exe
*.out
*.a

# Dossiers de build
bin/
obj/
Debug/
Release/

# IDE
*.cbp
*.depend
*.layout
.vscode/
.idea/
```

---

<div align="center">

---

Réalisé par **Elaa Affes**
SUP'COM — École Supérieure des Communications de Tunis | 2025/2026

</div>
