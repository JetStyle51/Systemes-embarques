# Cheat Sheet - Embedded Systems

# Language C

## Les mots clées 

- `volatile`
Mot-clé qui est un qualificatif indiquant au compilateur que la valeur du variable peut changer à tout moment sans qu'aucune action ne soit entreprise par le code. Ceci peut être le cas pour une varibale globale modifiée par une ISR, une variable globale qui est accessible par du multi-tâche., ou encore les périphériques qui sont mappé directement sur la mémoire.

## Les pointeurs

Pour un programmateur C, la mémoire de l'ordinateur est une succession de cellules mémoires. Avec chacunes son addresse unique.
Quand une variable est déclarée , la mémoire a besoin de stocker la valeur dans une zone spécifique mémoire.

Ainsi prenons l'exemple :
```
uint32_t myvar = 0xDEADBEEF;
uint32_t *pointer_myvar;
pointer_myvar = &myvar;
*pointer_myvar = 0x12345678;
```
- myvar est déclarée en tant qu'entier unsigned 32-bit
- pointer_myvar est déclarée en tant que pointeur sur entier 32 bits.
- point_myvar est remplis avec la valeur de l'addresse de myvar
- La valeur à l'addresse mémoire peut être ensuite modifiée avec *.

## Les structures
Elles sont particulièrement utile pour mapper des données en mémoires sur des choses répétitives.
Par exemple ci dessous la structure matches avec le hardware du STM32L152.
Je prend l'exemple des structures pour GPIO dont la structure se répète :
Ainsi ceci s'écrirait :
```
typedef struct
{	
	uint32_t MODER;				/*!< GPIO port mode register,					Address offset : 0x00	*/
	uint32_t OTYPER;			/*!< GPIO port output type register,			Address offset : 0x04	*/
	uint32_t OSPEEDR;			/*!< GPIO port output speed register,			Address offset : 0x08	*/
	uint32_t PUPDR;				/*!< GPIO port pull-up/pull-down register,		Address offset : 0x0C	*/
	uint32_t IDR;				/*!< GPIO port input data register,				Address offset : 0x10	*/
	uint32_t ODR;				/*!< GPIO port output data register,			Address offset : 0x14	*/
	uint32_t BSRR;				/*!< GPIO port bit set/reset register,			Address offset : 0x18	*/
	uint32_t LCKR;				/*!< GPIO port configuration lock register,		Address offset : 0x1C	*/
	uint32_t AFR[2];			/*!< GPIO alternate function register,			Address offset : 0x20-0x24	*/
	uint32_t BRR;				/*!< GPIO bit reset register,					Address offset : 0x28	*/
} GPIO_struct;
```

Afin de meppaer la structure au bon port (par exemple le port B) on écrit alors :
```
GPIO_struct *GPIO_portB;
GPIO_portB = (GPIO_struct *) 0x40020400;
(* GPIO_portB).MODER = 0xFFFFFFFF;
```

Le tout peut être factorisé en :
```
GPIO_struct * GPIO_portB = (GPIO_struct *) 0x40020400;
GPIO_portB->MODER = 0xFFFFFFFF;
```

## Bit Shifting

Décallage à gauche de 1 de la variable a : (multiplication par 2)
```
a = a << 1;
```

Décallage à droite de 1 de la variable a : (division par 2)
```
a = a >> 1;
```

## DEFINES
En langage de programmation C, la directive #define permet les définitions de macros dans le code. Ces définitions de macros permettent de déclarer des valeurs constantes pour
utiliser tout au long du code Les définitions de macros ne sont pas des variables et ne peuvent pas être modifiées par le programme comme variables. 
Il est utilisé lors de la création de constantes qui représentent des nombres, des chaînes ou expressions et sont remplacés lors de la phases de compilation par le préprocesseur.

```
#define CNAME (expression) (called Macros)
```

## Accès en mémoire :

Exemple d'une macro pour accéder en mémoire sur 32 bits (unsigned int)
```
#define HWREG(x) (*((volatile unsigned int *)(x))) //Accès à la valeur de l'addresse 'x';
```

## Masquages des bits :
```
a &=~(1<<n) // met à 0 le nème bit de a.
a |= (1<<n) // met à 1 le nème bit de a.
var = (a & (1<<12)) >> 12; // Query value of bit 12 of value called a
a ^= (1<<4| 1<<3); // Basculler le bit 4 et 3 de a à 1.
```