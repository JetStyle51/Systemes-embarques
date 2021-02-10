#define HWREG(x) (*((volatile unsigned int *)(x)));

a = a & ~(1<<n) met à 0 le nème bit de a.
a = a | (1<<n) met à 1 le nème bit de a.