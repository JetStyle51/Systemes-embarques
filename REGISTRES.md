# Systèmes-embarqués

Ce dépôt regroupe des outils / documentation / tutoriel et codes qui peuvent être utiles pour un système embarqué.

## Les registres d'un processeur Intel 32 bits :

Tableau 2-1. Découpage d'un registre de travail

On voit que e*x (32 bits) est composé de *x (16 bits de poids faible) lui-même composé de *h (8 bits de poids fort) et *l (8 bits de poids faible).

Registre(s)	Taille
eax	32 bits
ax	16 bits
ah	al	8 bits chacun

| :--------------- |:---------------:| -----:|
| EAX  | Accumulateur          | Le registre %ebx (base index) utilisé comme pointeur sur les données |
| EBX  |   Base            |  Le registre ECX utilisé comme compteur |
| ECX | Compteur             |   Le registre ECX utilisé comme compteur |
| EDX   | Données          |    Le registre EDX utilisé pour les entrées/sorties |

Le registre EIP (Instruction Pointer)
Le registre EDI (Destination Index) et le registre ESI (Source Index)
Le registre CS (Code Segment)
Le registre SS (Stack Segment)
Le registre ESP (Stack Pointer)
Le registre EBP (Frame Base Pointer)
Les registres DS, ES, FS, GS (Data Segment)
Le registre EFLAG
