# Cheat Sheet - Embedded Systems


Accès en mémoire :
```
#define HWREG(x) (*((volatile unsigned int *)(x))) //Accès à la valeur de l'addresse 'x';
```

Masquage :
```
a = a & ~(1<<n) // met à 0 le nème bit de a.
a = a | (1<<n) // met à 1 le nème bit de a.
```