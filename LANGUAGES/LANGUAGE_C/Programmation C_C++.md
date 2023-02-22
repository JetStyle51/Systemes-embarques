
# Langage C

- [Langage C](#langage-c)
  - [Conditions et boucles](#conditions-et-boucles)
    - [Boucles infinies](#boucles-infinies)
    - [Arrêts et continuation de boucles](#arrêts-et-continuation-de-boucles)
    - [Expression conditionnelle](#expression-conditionnelle)
    - [Saut inconditionnel](#saut-inconditionnel)
  - [Pointeurs](#pointeurs)
    - [Déclarer un pointeur](#déclarer-un-pointeur)
    - [Stocker une adresse](#stocker-une-adresse)
    - [Déclarer un pointeur en `restrict`](#déclarer-un-pointeur-en-restrict)
    - [Allocation dynamique](#allocation-dynamique)
  - [Tableaux, énumérations](#tableaux-énumérations)
    - [Tableaux](#tableaux)
    - [Enumérations](#enumérations)
  - [Structures](#structures)
  - [Fonctions](#fonctions)
    - [Évaluation des arguments](#évaluation-des-arguments)
    - [Fonctions `inline`](#fonctions-inline)
    - [`return` d'une fonction](#return-dune-fonction)
  - [Listes chainées](#listes-chainées)
  - [Arbres binaires](#arbres-binaires)
  - [TypeCasting](#typecasting)
  - [Threads](#threads)
    - [Créer des threads](#créer-des-threads)
    - [Les mutex](#les-mutex)
  - [Low Level](#low-level)
    - [What does \& 0xFF do?](#what-does--0xff-do)
    - [What does double underscore ( \_\_const) mean in C?](#what-does-double-underscore--__const-mean-in-c)
    - [Double underscore un macro](#double-underscore-un-macro)
    - [Déclaration d'une variable en `volatile`](#déclaration-dune-variable-en-volatile)
    - [Déclaration d'une variable en `const`](#déclaration-dune-variable-en-const)
    - [Utilisation d'une variable avec `extern`](#utilisation-dune-variable-avec-extern)
    - [Déclaration d'une variable avec `register`](#déclaration-dune-variable-avec-register)
    - [Déclaration d'une variable en `static`](#déclaration-dune-variable-en-static)
    - [Déclaration d'une variable en `auto`](#déclaration-dune-variable-en-auto)
    - [@ in C](#-in-c)
  - [Preprocessor](#preprocessor)
    - [pragma pack](#pragma-pack)
    - [Conditions](#conditions)
    - [Utiliser du code C parmi du C++](#utiliser-du-code-c-parmi-du-c)
    - [Eviter l'inclusion multiple ou récursivité des librairies](#eviter-linclusion-multiple-ou-récursivité-des-librairies)
    - [Générer des erreurs](#générer-des-erreurs)
    - [La directive #pragma](#la-directive-pragma)
      - [pragma pack](#pragma-pack-1)
- [Langage C++](#langage-c-1)
  - [Introduction: ce qui change](#introduction-ce-qui-change)
    - [Allocation dynamique](#allocation-dynamique-1)
  - [Namespace et flux](#namespace-et-flux)
    - [Namespace](#namespace)
    - [Flux](#flux)
  - [Classes](#classes)
  - [Bonnes pratiques](#bonnes-pratiques)
- [Compilation](#compilation)
  - [Compilation croisée ou "cross compilation"](#compilation-croisée-ou-cross-compilation)

--------

## Conditions et boucles

### Boucles infinies

```c
for (; true; ) {
    //code
}
```
```c
for (; 1 == 1; ) {
    //code
}
```
```c
for (;;) {
    //code
}
```
```c
while(1);
```

### Arrêts et continuation de boucles

Il arrive fréquemment qu'en évaluant un test à l'intérieur d'une boucle, on aimerait arrêter brutalement la boucle ou alors « sauter » certains cas non significatifs. C'est le rôle des instructions `break` et `continue`.

`break` permet de sortir immédiatement d'une boucle `for`, `while` ou `do-while`. À noter que si la boucle se trouve elle-même dans une autre boucle, seule la boucle où l'instruction break se trouvait est stoppée.
continue permet de recommencer la boucle depuis le début du bloc. Dans le cas de la boucle for, le bloc lié à l'incrémentation sera exécuté, puis dans tous les cas, la condition sera testée.

### Expression conditionnelle

```c
condition ? expression_si_vrai : expression_si_faux ;
```

### Saut inconditionnel

Cette instruction permet de continuer l'exécution du programme à un autre endroit, dans la même fonction. On l'utilise de la manière suivante :
```c
goto label;
```
```c
label:
```



## Pointeurs

### Déclarer un pointeur
```c
double *pointeurA;
//Un pointeur qui peut contenir l'adresse d'un nombre à virgule

unsigned int *pointeurB;
//Un pointeur qui peut contenir l'adresse d'un nombre entier positif

string *pointeurC;
//Un pointeur qui peut contenir l'adresse d'une chaîne de caractères

vector<int> *pointeurD;
//Un pointeur qui peut contenir l'adresse d'un tableau dynamique de nombres entiers

int const *pointeurE;
//Un pointeur qui peut contenir l'adresse d'un nombre entier constant

int *pointeur(0);
//Déclarer un pointeur à une adresse libre
```

### Stocker une adresse
```c
int main()
{
    int ageUtilisateur(16);
    //Une variable de type int
    int *ptr(0);
    //Un pointeur pouvant contenir l'adresse d'un nombre entier

    ptr = &ageUtilisateur;
    //On met l'adresse de 'ageUtilisateur' dans le pointeur 'ptr'

    return 0;
}
```

### Déclarer un pointeur en `restrict`

Introduit par C99, ce mot-clé s'applique aux déclarations de pointeurs uniquement. Avec restrict, le programmeur certifie au compilateur que le pointeur déclaré sera le seul à pointer sur une zone mémoire. Cela permettra au compilateur d'effectuer des optimisations qu'il n'aurait pas pu deviner autrement. Le programmeur ne doit pas mentir sous peine de problèmes...

```cpp
int* restrict pZone;
```
### Allocation dynamique
- Pointeur `void *`

Ce pointeur est un cas particulier. Il permet de pointer sur un type quelconque. Il est notamment utilisé dans la fonction malloc():
```c
void * malloc(int n);
```
En pratique, il faut penser à transformer ce pointeur pour qu'il devienne utilisable, même si certains compilateurs acceptent de l'utiliser directement:
```c
// Allocation avec conversion
int * p; // Pointeur p sur le type int
p = (int *) malloc(sizeof(int) * 10); // Allocation de 10 int, soit 20 octets
*p = 4; // Modification

// Allocation sans conversion
int * p; // Pointeur p sur le type int
p = malloc(sizeof(int) * 10); // Allocation de 10 int, soit 20 octets
*p = 4; // Modification
```
- Arithmétique avec effet de bord

C'est sans doute ce qui a donné des sueurs froides à des générations de programmeurs découvrant le C : un usage « optimisé » de la priorité des opérateurs, le tout imbriqué dans des expressions à rallonge. Par exemple 'while( *d++ = *s++ );', pour copier une chaine de caractères.

En fait, en décomposant l'instruction, c'est nettement plus simple qu'il ne parait. Par exemple :
```c
int i;
int * entier;

/* ... */

i = *entier++; /* i = *(entier++); */
```
Dans ce cas de figure, l'opérateur d'incrémentation ayant priorité sur celui de déréférencement, c'est celui-ci qui sera appliqué en premier. Comme il est postfixé, l'opérateur ne prendra effet qu'à la fin de l'expression (donc de l'affectation). La variable i sera donc tout simplement affectée de la valeur pointée par entier et après cela le pointeur sera incrémenté. Voici les différents effets suivant les combinaisons de ces deux opérateurs :
```c
i = *++entier; /* Incrémente d'abord le pointeur, puis déréférence la nouvelle adresse pointée */
i = ++*entier; /* Incrémente la valeur pointée par "entier", puis affecte le résultat à "i" */
i = (*entier)++; /* Affecte la valeur pointée par "entier" et incrémente cette valeur */
```
On peut évidemment complexifier les expressions à outrance, mais privilégier la compacité au détriment de la clarté et de la simplicité dans un hypothétique espoir d'optimisation est une erreur de débutant à éviter.

[Plus sur les pointeurs]

## Tableaux, énumérations

### Tableaux
- Utilisation des tableaux unidimensionnels
```c
int tab[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int tableau[] = { 1 , 5 , 45 , 3 , 9 };
int tableau[512] = {0};

int case_0 = tab(0);
```

Les tableaux commencent à la case 0.
- Utilisation des tableaux pluridimensionnels
```c 
int matrice[10][5];
int matrice[2][3] = { { 1 , 2 , 3 } , { 4 , 5 , 6 } };
int matrice[2][3] = { 1 , 2 , 3 , 4 , 5 , 6 };
```
```c
matrice[0][0] = 5;
int identite[][3] = { { 1 } , { 0 , 1 } , { 0 , 0 , 1 } }
```
Avec le type VLA (Variable Length Array), introduit par C99, il est possible de définir un tableau à plusieurs dimensions dont les bornes ne sont connues qu'à l'exécution et non à la compilation :
```c
static void vlaDemo(int taille1, int taille2)
{
	// Declaration du tableau VLA
	int table[taille1][taille2];

	// ...
}
```
- Les tableaux et les pointeurs
```c
int tab[10];
int *p, *q;
p = tab; 
q = &(tab[0]);
```

[Plus sur les tableaux]

 ### Enumérations

 ```c
enum {HAUT, BAS, DROITE, GAUCHE}
```
## Structures

Les structures permettent de créer de nouveaux types de types connus par le langage C.
Définition d'une structure :
```c
typedef struct
{
    int age;
    string nom[100];
    string ville[100];

    int nb_habitants;
    int * pointeur;
}Nom_struct
```
Utilisation d'une structure :
```c
struct Nom_struct Nom1;

Nom1.age = 10;
Nom1->pointeur = 0xFF
(*Nom1).pointeur = 0xFF
```
## Fonctions

### Évaluation des arguments

La norme du langage ne spécifie pas l'ordre d'évaluation des arguments. Il faut donc faire particulièrement attention aux effets de bords.

Ex d'erreur :
```c
#include <stdio.h>
int fonction(int, int);
int g(void);
int h(void);

int test(void)
{
    return fonction(g(), h());
}
```
Dans cet autre exemple, les expressions g() et h() pouvant être évaluées dans n'importe quel ordre, on ne peut pas savoir laquelle des fonctions g et h sera appelée en premier. Si l'appel de ces fonctions provoque des effets de bord (affichage de messages, modification de variables globales...), alors le comportement du programme est imprévisible.

Ex de solution :
```c
#include <stdio.h>
int fonction(int, int);
int g(void);
int h(void);

int test(void)
{
    int a,b;
    a = g();
    b = h();
    return fonction(a, b);
}
```

### Fonctions `inline`

### `return` d'une fonction

Le `return` d'une fonction permet de donner un résultat de valeur au type de la fonction. On ne peut pas retourner un `void`. S'il y a plusieurs paramètres à retourner, on ne peut pas utiliser plusieurs `return` il faut dans ce cas utiliser les pointeurs.

```c
int max(int a, int b)
{
    return (a > b) ? a : b;
}
```
## Listes chainées

```c
//Dans le fichier .h

#ifndef __LIST
#define __LIST

typedef struct
{
    int data;
    struct List *next
}List;

#endif;
```

## Arbres binaires

C'est commes les listes chainées sauf que chaque case vise vers 2 pointeurs.

```c
// Dans le fichier .h

#ifndef __BINTREE__
#define __BINTREE__

typedef struct Node
{
    int data;
    struct Node * left;
    strcut Node * right;
}BinTree, Node;

BinTree *empty_bintree(void);
BinTree *insert(BinTree *, int);

#endif;
```
```c
// Dans le fichier bintree.c

BinTree *empty_bintree(void)
{
    return NULL;
}

static Node *createNode(int);
static Node *createNode(int date)
{
    Node *node = malloc(sizeof(Node));
    if(!node)
        return NULL;
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

BinTree *insert(BinTree *bt, int data)
{
    BinTree * prec;
    BinTree * head = bt;
    if(!bt)
    (
        return create_node(data);
    )

}

[Youtube arbres binaires]

## Récursivité

La récursivité est quand une fonction s'appelle elle-même dans le bloc.
Voici un exemple de récursivité, seulement ce code génère une erreur de sémentation.
```c
unsigned fact(int n)
{
    return n * fact(n-1);
}

int main()
{
    printf("%u\n", fact(5));
}
```
Ici le problème est que le programme entraine un `stack overflow`. En effet une fonction libère sa mémoire après le `return` sauf que dans le cas ci-dessus une nouvelle fonction demande de la mémoire dans la stack et ainsi de suite. On a donc finalement un débordement de la pile mémoire.

La solution a ce problème pourrait par exemple :
```c
unsigned fact(int n)
{
    if (n == 1 || n == 0)
        return 1;
    return n * fact(n-1);
}

int main()
{
    printf("%u\n", fact(5));
}
```
On a identifié le problème récursif : la factorielle vaut toujours 1 pour 1 et 0.
Ainsi une fois que fact(n-1) arrive à 0 la dernière fonction dépile et termine le contexte qui va terminer celui d'avant jusqu'au premier.

Ainsi pour utiliser une récursivité il faut toujours identifié le problème récursif du cas de base (le dernier contexte) afin d'arrêter la récursivité et de remonter les contexte jusqu'à terminer le premier contexte.

## TypeCasting

The typecasting is to convert from one type to another explicitly. The type conversion changes from one data type to another implicitly.

## Threads

Un thread est un programme qui a été démarré par un autre programme et qui va s'exécuter en même temps. Ils seront liés sauf en mémoire.

### Créer des threads

```c
#include <pthread.h>

void *func1(void *arg)
{
    for (int i = 0; i < 10; i ++)
    {
        fprintf(stderr, "thread 1: %d\n", (char*)arg)); 
        // On utilise la sortie d'erreur de printf afin qu'il n'attende pas que son buffer soit plein pour afficher la sortie.
    }
    pthread_exit(arg);
}

void *func2(void *arg)
{
    for (int i = 0; i < 10; i ++)
    {
        fprintf(stderr, "thread 2: %d\n", (char*)arg);
    }
    pthread_exit(arg);
}

int main(void)
{
    pthread_t t1;
    pthread_t t2;

    pthread_create(&t1, NULL, func1, "Hello 1");
    pthread_create(&t1, NULL, func2, "Hello 2");

    char *s1, *s2;
    pthread_join(t1, (**void)&s1);
    pthread_join(t2, (**void)&s2);

    return 0;
}
```

`pthread_create(pointeur, NULL, func, argument)` crée un thread et le démarre.

`pthread_exit()` termine un thread en retournant la valeur de l'argument.

`pthread_join()` attend le retour de `pthread_exit()` pour terminer le thread.

### Les mutex

Les mutex permettent de bloquer un thread pour protéger l'exécution.

```c
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *hello1(void *data)
{
    char str[] = "Hello world";
    int i = 0;

    pthread_mutex_lock(&mutex);
    while(i < 12)
    {
        fprintf(stderr, "%c", str[i]);
        usleep(10000);
        i++;
    }
    fprintf(stderr, "\n");
    pthread_mutex_unlock(&mutex);
}

void *hello2(void *data)
{
    char str[] = "Good bye";
    int i = 0;

    pthread_mutex_lock(&mutex);
    while(i < 12)
    {
        fprintf(stderr, "%c", str[i]);
        usleep(10000);
        i++;
    }
    fprintf(stderr, "\n");
    pthread_mutex_unlock(&mutex);
}

int main (void)
{
    pthread_t t1;
    pthread_t t2;

    pthread_create(&t1, NULL, func1, NULL);
    pthread_create(&t1, NULL, func2, NULL);
    pthread_mutex_destroy(&mutex);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
```
> La variable globale est pour l'exemple mais n'est pas à utiliser ! Il faut créer une structure avec les données et le passer dans l'argument des fonctions et des `pthread_join(t1, struct_name);`

Il existe une façon de bloquer un thread tant qu'un autre thread n'est pas fini.
```c
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *hello1(void *data)
{
    char str[] = "Hello world";
    int i = 0;

    pthread_cond_wait(&cond, &mutex);
    while(i < 12)
    {
        fprintf(stderr, "%c", str[i]);
        usleep(10000);
        i++;
    }
    fprintf(stderr, "\n");
}

void *hello2(void *data)
{
    char str[] = "Good bye";
    int i = 0;

    while(i < 12)
    {
        fprintf(stderr, "%c", str[i]);
        usleep(10000);
        i++;
    }
    fprintf(stderr, "\n");
    pthread_cond_signal(&cond);
}

int main (void)
{
    pthread_t t1;
    pthread_t t2;

    pthread_create(&t1, NULL, func1, NULL);
    pthread_create(&t1, NULL, func2, NULL);
    pthread_mutex_destroy(&mutex);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
```
Bien evidemment c'est cumulable avec les mutex.

Autres fonctions :

`int pthread_equal(pthread_t thread1,pthread_t thread2)` : renvoie si les thread sont égaux
`pthread_t pthread_self(void)` : renvoie le thread courant

## Low Level

### What does & 0xFF do?

```c++
void DYIRDaikin::checksum()
{
	uint8_t sum = 0;
	uint8_t i;


	for(i = 0; i <= 6; i++){
		sum += daikin[i];
	}

        daikin[7] = sum &0xFF;

        sum=0;
	for(i = 8; i <= 25; i++){
		sum += daikin[i];
        }

        daikin[26] = sum &0xFF;
}
```

Cela permet de faire un masque sur le type précédant & 0xFF (ici c'est un type uint8_t donc cela ne sert à rien puisque les bits supérieurs sont déjà à 0. Mais c'est une sécurité au cas quelqu'un change le type de `sum`) . On récupère donc le LSB (Least Significant Byte) du type le précédent.
Ex:
```c++
    0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
 &  0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1
    -------------------------------
    0 0 0 0 0 0 0 0 0 1 0 1 0 1 0 1
```
[What does &0xff do?]

### What does double underscore ( __const) mean in C?

```c
extern int ether_hostton (__const char *__hostname, struct ether_addr *__addr)
 __THROW;
```
[Ce que signifie (__const)]

### Double underscore un macro
```c
#define rdtscll(val)__asm__ __volatile__(...)
```
In this case `__asm__` and `__volatile__` are compiler extensions for embedding assembly statements into a C file. The two leading underscores are to prevent clashes with identifiers in user code, and the trailing are pure choice. `__volatile__` is just an "anti-optimization" directive.

[double underscore in c macro]

### Déclaration d'une variable en `volatile`

One popular use of the volatile keyword for a variable is in writing code to end a loop or terminate a thread. A programmer can write a simple function that will take in the volatile variable value and end the loop based on a given value. The volatile keyword ensures that the program gets a current value for a Boolean or other variable, instead of an obsolete one.

En qualifiant par volatile le type d'une variable, le programmeur prévient le compilateur que cette variable peut être modifiée par un moyen extérieur au programme. Ceci se produit lorsqu'on interagit avec des parties matérielles de la machine : coupleurs d'entrées-sorties généralement. Lorsqu'une variable est de type volatile le compilateur ne doit pas procéder aux optimisations qu'il réalise sur les variables normales.
Les qualificatifs de type deviennent pénibles en conjonction avec les pointeurs car on a les trois possibilités :

- l'objet pointé est qualifié ;
- le pointeur lui-même est qualifié ;
- le pointeur et l'objet pointé sont qualifiés.

Une variable volatile est une variable sur laquelle aucune optimisation de compilation n'est appliquée.

Ex1:
```c++
bool usb_interface_flag = 0;
while(usb_interface_flag == 0)
{
// execute logic for the scenario where the USB isn't connected 
}
```
À partir du code ci-dessus, le compilateur peut penser que `usb_interface_flag` est défini sur `0`, et que dans la boucle `while`, il sera nul pour toujours. Après l'optimisation, le compilateur le traitera comme `while(true)` tout le temps, résultant en une boucle infinie.

Pour éviter ce genre de scénarios, nous déclarons le drapeau `volatile`, nous disons au compilateur que cette valeur peut être changée par une interface externe ou un autre module de programme, c'est à dire, ne l'optimisez pas. C'est le cas d'utilisation de volatile.

Ex2:

Demander au compilateur de ne pas optimiser pour faire des benchmarks.

### Déclaration d'une variable en `const`

Une variable dont le type est qualifié par `const` ne peut pas être modifiée. Le programmeur entend ainsi se protéger contre une erreur de programmation. Ceci n'est utile que pour les paramètres d'une fonction, lorsqu'on désire protéger les paramètres effectifs de la fonction en les mettant en << lecture seulement >> pour la fonction.

```c
const char c;   //caractère constant
const char *p;  //pointeur vers caractère constant
char * const p; //pointeur constant vers caractère
const char * const p;   //pointeur constant vers caractère constant
```
### Utilisation d'une variable avec `extern`

Une variable ou fonction dont le type est qualifié par `extern` n'a pas de mémoire allouée au moment de la compilation. La variable est déclarée sans la définir.

C'est utile pour la compilation séparée, pour définir une variable ou une fonction dans un fichier, en permettant à des fonctions contenues dans d'autres fichiers d'y accéder.

Toutes les variables globales et fonctions qui ne sont pas déclarées (ou définies) `static` sont externes par défaut.
  
### Déclaration d'une variable avec `register`

L'usage de ce mot clé est utile dans un contexte de logiciel embarqué. Indique que la variable devrait être stockée dans un registre du processeur. Cela permet de gagner en performance par rapport à des variables qui seraient stockées dans un espace mémoire beaucoup moins rapide, comme une pile placée en mémoire vive.

* Les registres du processeur sont limités. Leur nombre peut varier en fonction du processeur. Sur un PC (d'architecture AMD64?), ils sont au nombre de 13, dont seulement 4 servent au stockage (EAX,EBX,ECX,EDX). Il est donc inutile de déclarer une structure entière ou un tableau avec le mot clé register.

* Qui plus est, les variables placées dans des registres sont forcément locales à des fonctions ; on ne peut pas définir une variable globale en tant que registre.

Aujourd'hui, ce mot-clé est déconseillé sauf pour des cas particuliers, les compilateurs modernes sachant généralement mieux que le programmeur comment optimiser et quelles variables placer dans les registres.

```c
#include <stdio.h>

int main(void)
{
    register short i, j;
    for (i = 1; i < 1000; ++i)
    {
        for(j = 1; j < 1000; ++j)
        {
            printf("\n %d %d", i, j);
        }
    }
    return 0;
}
```
[Classe register]

### Déclaration d'une variable en `static`

Une variable dont le type est qualifié par `static` n'a pas sa valeur libérée de la mémoire à la fin de l'exécution de la fonction dans laquelle elle se trouve; contrairement à une variable déclarée en locale (ou auto variable). Par contre elle fonctionne de la même façon qu'une variable locale en terme de scope.

Quand une variable `static` est déclarée en dehors de toute fonction ou bloc {}, le scope (étendue) de la variable est uniquement dans le fichier.

Déclarer une fonction en `static` est utile pour éviter les conflits avec d'autres fichiers ou d'autres programme qui font appel à celui-ci puisqu'il permet de limiter le scope au fichier seulement.

[Static function in C]

### Déclaration d'une variable en `auto`

Cette classe est un héritage du langage B. En C, ce mot-clé sert pour les variables locales à une fonction non-statiques, dites aussi automatiques. Mais une variable déclarée localement à une fonction sans qualificateur static étant implicitement automatique, ce mot-clé est inutile en C.

[Class auto en C]

### @ in C

The **@** can be used to specify the absolute address of a variable on embedded systems.
```c
unsigned char buf[128]@0x2000; //example from StackOverflow

/*! Example from Sliceio
 * \var const uint32_t FsblVersion @ MFW_FSBL_VERSION_NOR_OFFSET  
 * \brief FSBL version 
 *
 * Must always be at the same location in NOR => MFW_FSBL_VERSION_NOR_OFFSET must never change
 * (in order for Main FW to retrieve it)
 */
const uint32_t FsblVersion @ MFW_FSBL_VERSION_NOR_OFFSET = MFW_FSBL_VALID_TAG_VERSION | (PRODUCT_FSBL_MAJOR_FW_VERSION << 8) | PRODUCT_FSBL_MINOR_FW_VERSION;
```

Note this is a non-standard compiler extension.

[@ discussions]

## Preprocessor

### pragma pack

### Conditions

```c
#ifdef (ou #if defined)
#else
#endif
```

### Utiliser du code C parmi du C++

Pour le cas où du code C est intégré dans du code en C++. Pour éviter que le compilateur C++ traite du code en C comme étant du C++, il convient de délimiter la portion de code en C comme ceci :

```c++
#ifdef __cplusplus
extern "C" {
#endif
 
// Portion de code en C
 
#ifdef __cplusplus
}
#endif
``` 

### Eviter l'inclusion multiple ou récursivité des librairies

 La technique généralement utilisée est de définir dans chaque fichier .h une macro propre à ce fichier – généralement à partir du nom du fichier – en prenant soin de vérifier au préalable que cette macro n’a pas déjà été définie.

```c++
#ifndef FICHIER_COMMUN_H
#define FICHIER_COMMUN_H 
// Tout ce qui est compris ici ne sera activé que si la macro FICHIER_COMMUN_H vient d'être définie
#endif /* FICHIER_COMMUN_H */
```
Ainsi, quand le préprocesseur inclura ce fichier, cette portion de code ne sera inclue que la première fois.

### Générer des erreurs

 Si un programme utilise la norme C99, il faut d'abord vérifier sa compatibilité.

 ```c
 #if __STDC_VERSION__ 199901L
#error Ce programme n'est pas supporté par les normes du C antérieures à C99
#endif
```
Le seul moyen d’écrire un message sur plusieurs lignes est de terminer une ligne par un antislash (\) pour indiquer que la ligne courante se poursuit sur la ligne suivante.

Si vous préférez plutôt avertir l’utilisateur d’un risque sans interrompre la compilation, vous pouvez utiliser la directive **#warning** pour générer un avertissement plutôt qu’une erreur.
```c
#warning Ce programme est susceptible de ne pas fonctionner correctement sur cette plateforme
```

### La directive #pragma

La directive préprocesseur `#pragma` est très puissante mais complexe.
C'est une extension du compilateur.

#### pragma pack
Permet d'indiquer au compilateur de ne pas ajouter de padding entre les membres d'une structure afin que sa taille soit exactement egale à la somme des tailles de ces membres
```c
#pragma pack(1)
typedef struct
{    
    char ProductName[PRODUCT_NAME_MAX_LEN];   /* Called "ProductCode" in data model: it is the commercial reference */
    unsigned short HwRev;
    char SerialNumber[SERIAL_NUMBER_MAX_LEN]; /* Unique code number added by Manufacturing with this format: PPYYWWDLLLNNNNN */
}
#pragma pack()
```
[pragma pack thread](https://devblogs.microsoft.com/oldnewthing/20200103-00/?p=103290#comments)

[IBM pragma](https://www.ibm.com/docs/en/zos/2.3.0?topic=descriptions-pragma-pack)

```

### Defined (The C Preprocessor)

The special operator defined is used in ‘#if’ and ‘#elif’ expressions to test whether a certain name is defined as a macro. defined name and defined (name) are both expressions whose value is 1 if name is defined as a macro at the current point in the program, and 0 otherwise. Thus, #if defined MACRO is precisely equivalent to #ifdef MACRO.

defined is useful when you wish to test more than one macro for existence at once. For example,

`#if defined (__vax__) || defined (__ns16000__)`
would succeed if either of the names __vax__ or __ns16000__ is defined as a macro.

Conditionals written like this:

`#if defined BUFSIZE && BUFSIZE >= 1024`
can generally be simplified to just #if BUFSIZE >= 1024, since if BUFSIZE is not defined, it will be interpreted as having the value zero.

If the defined operator appears as a result of a macro expansion, the C standard says the behavior is undefined. GNU cpp treats it as a genuine defined operator and evaluates it normally. It will warn wherever your code uses this feature if you use the command-line option -Wpedantic, since other compilers may handle it differently. The warning is also enabled by -Wextra, and can also be enabled individually with -Wexpansion-to-defined.

```c
#elif defined(__AVR_AT90USB162__)
#define IR_USE_TIMER1     // tx = pin 17
```

[Plus sur le préprocesseur]

# Langage C++
## Introduction: ce qui change

### Allocation dynamique

En C

```c
int *a = NULL;
a = (int *)malloc(sizeof(int));

free(a);
```

Ex:
```c
int main(int argc, char *argv[])
{
    int* memoireAllouee = NULL;

    memoireAllouee = malloc(sizeof(int)); // Allocation de la mémoire
    if (memoireAllouee == NULL)
    {
        exit(0);
    }

    // Utilisation de la mémoire
    printf("Quel age avez-vous ? ");
    scanf("%d", memoireAllouee);
    printf("Vous avez %d ans\n", *memoireAllouee);

    free(memoireAllouee); // Libération de mémoire

    return 0;
}
```

En C++
```c++
    int *a = new int;

    delete a;
```
## Namespace et flux

### Namespace
Les `namespace` fournissent une méthode qui préviennent des conflicts de noms dans les gros proejts.
On peut encapsuler des constantes, variables, des classes, des fonctions

```cpp
//Déclaration :

namespace exemple
{
    int var1 = 5;
    long var2 = 23.89;

    void print()
    {
        printf("Hello world");
    }
    void print1();
}


//Utilisation :

using namespace std;

exemple::print1()
{
    printf("hello print1");
}

int main()
{
    exemple::var1 = 67; //sans l'utilisation de using namespace exemple;
    cout << exemple::var2 << endl; //avec l'utilisation de using namespace std;
    exemple::print();
    exemple::print1();
}
```

### Flux
Les flux sont 

## Classes

Les `variables` sont appelées `attributs`. Les `fonctions` sont appelées `méthodes`.

>Encapsulation : Tous les attributs doivent être déclarés en privé !

- Constructeur 
>Un constructeur par défaut est automatiquement créé par le compilateur. C'est un constructeur vide, qui ne fait rien de particulier.
On a cependant très souvent besoin de créer soi-même un constructeur qui remplace ce constructeur vide par défaut.


Le rôle principal du constructeur est d'initialiser les attributs.

```c++
class Personnage
{
    public:

    Personnne();
    //Methodes
    private:
    //Attributs
};
```

```c++
Personnage::Personnage()
{
    m_vie = 100;
    m_mana = 100;
    m_nomArme = "Épée rouillée";
    m_degatsArme = 10;
}
```
```c++
Personnage::Personnage() : m_vie(100), m_mana(100), m_nomArme("Épée rouillée"), m_degatsArme(10)
{
    //Rien à mettre dans le corps du constructeur, tout a déjà été fait !
}
````
- Surcharger un constructeur (ou une méthode), une fonction

Dans le .h :
```c++
Personnage();   //Constructeur sans surcharge

Personnage(std::string nomArme, int degatsArme);    //Constructeur surchargé par nomArme et degatsArme
```
Dans le .cpp
```c++
Personnage::Personnage(string nomArme, int degatsArme) : m_vie(100), m_mana(100),m_nomArme(nomArme), m_degatsArme(degatsArme)
{
 
}
```

Dans le main :
```c++
Personnage david, goliath("Épée aiguisée", 20);
```

- Copie du constructeur

Par défaut le compilateur crée une copie du constructeur. C'est une surcharge du constructeur qui initialise notre objet en copiant les valeurs des attributs de l'autre objet.
On peut créer une copie de `goliath` :
```c++
Personnage david(goliath);                //On crée david en copiant tous les attributs de goliath
```
Et si on veut changer le comportement du constructeur de copie, il faut simplement le déclarer dans votre classe de la manière suivante :
```c++
//Dans le .h
Personnage(Personnage const& autre);

//Et dans le .cpp
Personnage::Personnage(Personnage const& autre): m_vie(autre.m_vie), m_mana(autre.m_mana), m_nomArme(autre.m_nomArme), m_degatsArme(autre.m_degatsArme)
{
}
```
- Destructeur

Le destructeur est une méthode appelée lorsque l'objet est supprimé de la mémoire. Son principal rôle est de désallouer la mémoire (via des `delete`) qui a été allouée dynamiquement.
```c++
Personnage::~Personnage()
{
    /* Rien à mettre ici car on ne fait pas d'allocation dynamique
    dans la classe Personnage. Le destructeur est donc inutile mais
    je le mets pour montrer à quoi cela ressemble.
    En temps normal, un destructeur fait souvent des delete et quelques
    autres vérifications si nécessaire avant la destruction de l'objet. */
}
```
- Méthodes constantes

Les méthodes constantes sont des méthodes de « lecture seule ». Elles possèdent le mot-clé `const`à la fin de leur prototype et de leur déclaration.

Une méthode constante ne modifie pas l'objet, c'est-à-dire qu'elle ne modifie la valeur d'aucun de ses attributs.
Cela permet :
<!-- -->
De savoir que la méthode ne modifie rien;
<!-- -->
D'informer que la méthode ne modifie rien;
<!-- -->
Le compilateur crée du meilleur code, mieux optimiser


```c
//Prototype de la méthode (dans le .h) :
void maMethode(int parametre) const;
 
 
//Déclaration de la méthode (dans le .cpp) :
void MaClasse::maMethode(int parametre) const
{
 return m_vie > 0; //Vérifie la vie de quelque chose par exemple
}
```

Ex de classe:
```c++
class DYIRDaikinSend
{
public:
    DYIRDaikinSend() {}
    void begin();
    void begin(int IRsendPin);
    void sendRaw(unsigned int buf[], int len, int hz);
    void sendDaikin(unsigned char buf[], int len,int start);
    void sendDaikinWake();
    // private:
    void enableIROut(int khz);
    void mark(int usec);
    void space(int usec);
    void delayMicrosecondsEnhance(uint32_t usec);
private:
	void sendIRWarm();
    int halfPeriodicTimeHigh;
    int halfPeriodicTimeLow;
    int IRpin;
};
```

- Associer des classes entre elles

Ajouter un attribut de la nouvelle classe en le déclarant comme un type dans la classe qui va l'utiliser.
```c++
class Personnage
{
    public:
    //méthodes

    private:
    //attributs
    Nom_classe m_attribut; //Notre Personnage possède une Arme
};
```
Pour utiliser un objet dans un objet il faut généralement créer un accesseur qui va modifier indirectement l'attribut puisqu'il est privé!
```c++
int Arme::getDegats() const
{
    return m_degats;
}
```
Il faut rajouter le mot-clé `const`aux accesseurs pour en faire des méthodes constantes, puisqu'elles ne modifient pas l'objet.
```c++
void Personnage::attaquer(Personnage &cible)
{
    cible.recevoirDegats(m_arme.getDegats());
}
```
```c++
void Personnage::changerArme(string nomNouvelleArme, int degatsNouvelleArme)
{
    m_arme.changer(nomNouvelleArme, degatsNouvelleArme);
}
```

![Exemple de schéma d'un code en C++](https://user.oc-static.com/files/85001_86000/85453.png)

- Opérations sur des objets

```c++
bool operator==(Objet const& a, Objet const& b);
```
> Ceci n'est pas une méthode. C'est une fonction normale située à l'extérieur de toute classe.
On utilise le mot clé `const`car les valeurs a et b récupérées par référence ne doivent pas être modifiées.

## Bonnes pratiques
`using namespace std;` ne se place pas dans les `.h` il faut utiliser `std::` devant la déclaration.

Ex:
```c++
Personnage(std::string nomArme, int degatsArme);
```

Ne pas supprimer ou modifier le nom des méthodes déjà existantes dans un programme, encore moins dans une bibliothèque. Cela empêcherait la compatibilité avec le reste du programme et plus rien ne fonctionnerait. Dans le cas d'une bibliothèque les utilisateurs ne pourrait plus s'en servir.
Les attributs sont encapsuler donc pas de risques.

# Compilation

## Compilation croisée ou "cross compilation"

La « cross compilation » ou compilation croisée est le fait de compiler un programme sur une architecture qui n’est pas celle de l’architecture cible.

Exemple : vous êtes sur un PC avec un processeur de type Intel en 64bits (architecture LittleEndian) et vous souhaitez compiler pour un RaspberryPi ou une BeagleBoneBlack qui utilise une architecture 32 bits de type ARM (architecture BigEndian).


[//]: <Liens> 

[Comments in markdown]: https://stackoverflow.com/questions/4823468/comments-in-markdown

[What does &0xff do?]: <https://stackoverflow.com/questions/14713102/what-does-and-0xff-do>


[Static function in C]: <https://www.cprogrammingbasics.com/static-function-in-c/> 
[Classe register]: <https://fr.wikibooks.org/wiki/Programmation_C/Classe_de_stockage#Classe_'register'>
[Class auto en C]: <https://fr.wikibooks.org/wiki/Programmation_C/Classe_de_stockage#Classe_'register'>
[Plus sur le préprocesseur]: <https://fr.wikibooks.org/wiki/Programmation_C/Préprocesseur>
[Plus sur les tableaux]: <https://fr.wikibooks.org/wiki/Programmation_C/Tableaux>
[Plus sur les pointeurs]: <https://fr.wikibooks.org/wiki/Programmation_C/Pointeurs#Tableaux_dynamiques>
[Ce que signifie (__const)]: <https://stackoverflow.com/questions/1449181/what-does-double-underscore-const-mean-in-c>
[double underscore in c macro]: <https://stackoverflow.com/questions/26652288/unclear-c-code-double-underscore-in-c-macro>
[Youtube arbres binaires]: <https://www.youtube.com/watch?v=1M66CUV877s>
[@ discussions]: <https://stackoverflow.com/questions/33324076/what-is-absolute-symbol-and-how-to-define-it-in-c/33324663#33324663>