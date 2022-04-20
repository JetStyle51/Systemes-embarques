# Les registres des processeurs



## Les registres d'un processeur Intel 32 bits :


EAX : Extended Accumulator X


On voit que E*X (32 bits) est composé de *X (16 bits de poids faible) lui-même composé de *h (8 bits de poids fort) et *l (8 bits de poids faible).


![](https://flint.cs.yale.edu/cs421/papers/x86-asm/x86-registers.png)


| Registre| Dénomination          | Description |
| :--------------- |:---------------:| -----:|
| EAX| Accumulateur          | Utilisé pour les opérations arithmétiques et le stockage de la valeur de retour des appels systèmes. |
| EBX  |   Base            |  Utilisé comme pointeur de donnée (située dans DS en mode segmenté, segment par défaut) ou sert de base au calcul d'une adresse. |
| ECX | Compteur             |   Utilisé comme compteur par certaines intructions, permettant de répéter une série d'instructions un nombre de fois prédéterminé. |
| EDX   | Données          |    Utilisé pour les opérations arithmétiques et les opérations d'entrée/sortie. |
| EIP   | Instruction Pointer          |    |
| EDI   | Destination Index          |     |
| ESI   | Source Index          |  Pointeur source   |
| CS   | Code Segment          |     |
| SS   | Stack Segment          |     |
| ESP   | Stack Pointer          |  Pointeur de pile   |
| EBP   | Frame Base Pointer          |   Pointeur de base, utilisé dans le calcul d'adresse mémoire  |
| DS, ES, FS, GS   | Data Segment          |     |
| EFLAG   | Data Segment          |     |

## Les registres d'un processeur 64 bits

De même que pour 64 bits avec 32 bits supplémentaire 
![](https://1.bp.blogspot.com/-c1rrZSO90C0/WuYcnxMms2I/AAAAAAAAAQE/b0BuIyz1-bQnNBKQ8BT3KXFuC8AS9P83gCLcBGAs/s1600/register.png)

## Les registres d'un processeur ARM :