# Systèmes-embarqués

Ce dépôt regroupe des outils / documentation / tutoriel et codes qui peuvent être utiles pour un système embarqué.

## Introdudction aux systèmes embarqués :

Un système embarqué est un ensemble électronique et/ou informatique intégré comme composant d'un environnement plus important.
Un système embarqué se définit surtout par les contraintes auxquelles il est soumis


# Généralités sur les systèmes embarqués

## Microcontroleur / microprocesseur / et System on Chip (S.O.C)

Il est important de comprendre la différence qu'il existe entre un microcontroleur et un microprocesseur.

![alt text](micro.png)

|  Microcontrôleur| Microprocesseur|
| ------------------------- | -------------------------------------------------- |
| Généralement pas de système d'exploitation (ou minimal). | Optimisé pour l'utilisation d'un système d'exploitation |
| Mise en œuvre électronique simple. | Mise en œuvre électronique beaucoup plus complexe |
| Déterminisme et fiabilité de fonctionnement. | Entrées-sorties réalisées par des contrôleurs externes au processeur |

Quelques exemples de microcontrôleurs :
• Atmel : AT91 (AT91SAM9xx, AT91SAM7xx), AVR (TinyAVR, MegaAVR…) 
• Freescale : 68HC05, 68HC08, 68HC11
• Hitachi / Renesas : H8 (H8/300, H8/500…), SuperH (SH-1, SH-2, SH-3...)
• Intel : 8051, 8052, 8085
• Microchip : PIC (PIC-10F, PIC-12F, PIC-16F, PIC-24F)
• STMicroelectronics : ST6, STM8, STM32
• Texas Instruments : MSP430, TMS320, TM4C

Quelques exemples de microprocesseurs :
• Famille Arm : ARM7 (Arm 720T), ARM9 (Arm 926) ARM11 (Arm 1176jzf), Cortex-A
(Cortex-A7, Cortex-A8, Cortex-A9, Cortex-A15),
• Famille x86 : Intel (Atom, Core 2, Core i5, Core i7), AMD (Opteron, Phenom), Via
(Nano)
• Famille M68k : Motorola 680x0, Coldfire (MCF5xxx), Dragonball.
• Famille PowerPC : Apple (G5), IBM (Power 6, Power 7, Power 8, Cell, Xenon)

Un *System on Chip* regroupe un microprocesseur et des périphériques sur le même boitier.

| SoC |
| -------- |
| Contrôleurs d'entrées-sorties déjà incorporés
Intégration électronique encore assez complexe
Souvent peu d'entrées-sorties industrielles (CAN) ou analogiques (ADC/DAC, PWM) |

![alt text](soc.png)

Quelques systems-on-chip Arm :
• Allwinner : A13, A20, A80
• Broadcom : BCM2835, BCM2836
• Freescale : i.MX21, i.MX23, i.MX6
• Marvell : 88SE6, 88SE9
• Rockchip : RK30, RK31
• Texas Instruments : OMAP, DaVinci

## Le language C en embarqué ?

On se demande pourquoi le language est particulièrement adapté à l'embarqué? La réponse est que le besoin de l'embarqué est de se retrouver très proche de la machine.
Le language le plus proche de la machine est le langage assembleur, cependant écrire un programme en assembleur est pénible et long à faire. Le langage C permet de rajouter une couche, afin de programmer plus rapidement mais en restant proche du hardware.
Ce dernier est réutilisable facilement et très bien strusturé pour nos applications.

## Un programme en embarqué c'est quoi ?

Un programme est une suite d'instruction lancé au démarrage du processeur. Celui ci ne doit jamais se terminer.
Ainsi ce dernier doit se trouver dans une boucle infini pour ne jamais s'arrêter.
Cependant l'application de l'embarqué nous contraint d'optimiser la consommation de courant, la taille du programme et le temps d'exécution.
Ainsi un programme functionnant sous interruption est préféré à un programme qui marche sous scrutation (polling).

## La compilation

La compilation se fait la plupart du temps en embarqué sous la forme de cross-compilation.
La machine de développement est en effet en général un ordinateur commum et non pas la cible embarqué directement.
Ainsi le programme est écris sur une machine Intel,AMD,etc ... et l'architecture cible est un processeur du type ARM, etc ...

La compilation est le processus qui se déroule en plusieurs phases pour créer les fichiers nécéssaire à l'execution du programme par la machine.
Elle permet de traduire un programme C en langage machine que pourras executer cette dernière.
Elle se déroule en plusieurs phases :

- La phase de préprocessing : Le code source est analysé par le program appelée preprocesseur qui se charge d'enlever les commentaires, de remplacer les defines dans le code etc ...
- La phase d'assemblage ou de compilation : Les fichiers générés par le preprocesseur sont traduit en assembleur, ensuite vers un language machine (celle de la machine cible).
- La phase de Link : Permet de rejoindre les fichiers entres eux (un programme C est parfois divisé en plusieurs sous fichiers).
- La phase de boot : placé avant le main qui permet d'initilialiser la pile et son pointeurs ainsi que diverses variables.

## Processus de démarrage

Suivant le type de processeur et la complexité du matériel, le temps de boot du noyau dure de
deux à cinq secondes environ.
Le démarrage du processus init, les tâches administratives (montage systèmes de fichiers,
configuration paramètres de /proc (sous linux) , etc.) prennent une à deux secondes supplémentaires.
Le lancement de tous les services (réseau, authentification, environnement graphique, etc.)
peut demander une dizaine de secondes.

![alt text](boot.png)

## La MMU (Memory Managment Unit) au niveau du CPU :

Un processus voit un espace de mémoire virtuelle, au sein du quel il peut accéder à n'importe quelle adresse de 0x000000 à 0xFFFFFFFF (sur processeur 32 bits).
Cet espace est découpé en pages, et la MMU – Memory Managment Unit (un composant intégré dans le processeur) –  associe une page de mémoire virtuelle avec une page de mémoire physique en effectuant la modification d'adresse lors de l'accès à la mémoire. 

Certaines pages de mémoire virtuelle n'ont pas de correspondance en mémoire physique : une tentative d'accès déclenche une interruption « faute de page ».
Chaque processus dispose d'une configuration personnelle de la MMU. Cette dernière est programmée à chaque commutation entre deux processus.

Un processus ne voit que les pages de mémoire physique qui lui ont été attribué par le noyau ; 
les pages des autres processus ne sont projetées à aucun emplacement de sa mémoire virtuelle.

![alt text](mmu.png)

## Les types de mémoires

On distingue deux types de mémoires:
- Les mémoires volatiles (ce sont des mémoires qui s'éfface lorsque le dispositif est hors tension) :
	- SRAM : Static Random Access Memory (Granularité à l'octet en écriture et en lecture | Accès rapide en R/W | Basse consommation en courant | Toujours utilisé dans les microcontroleurs)
	- DRAM : Dynamic Random Access Memory (Granularité à l'octet, Ecriture rapide en écriture et en lecture | Haute consommation en courant | Non utilisé dans les microcontroleurs)
- Les mémoires non volatiles (Des mémoires qui restent intacte lorsque le dispositif est mise hors tension)
	- ROM : Read Only Memory (Granularité à l'octet R/W) | Accès rapide à la lecture | Impossible à écrire)
	- EEPROM : Electrically Erasable Programmable Read Only Memory (Granularité à l'octet R/W | Accès lent écriture R/W)
	- Flash (Nor) (Granularité d'un octet : doit être écris en pages (block d'octets) | Accès très lent en mode écriture | Toujours utilisé dans les microcontroleurs)

Dans un microcontoleur : 
La mémoire Flash est utilisé pour stocker le programme en mémoire, 
La mémoire EEPROM pour stocker les paramètres et les valeurs.
La mémoire SRAM pour la pile (stack).

## L'endianness

En mode Big Endian, le most significant bit(MSB) est à l'addresse la plus basse.
En mode Little Endian, le less significant bit(LSB) est à l'addresse la plus basse.

![endianess](endianess.png)
Durant les transmissions en little endian le LSB est transmis en premier.
En big endian, c'est le bit le plus haut est est transmis en premier.

![endianess_communication](endianess_communication.png)

## La Stack(Pile) & le Heap(Tas)

La zone mémoire ou sont conservés les varibales dépend ou est déclaré la variable dans le programme prenons l'exemple de ce programme :
```
uint32_t myvarOutMain; //Saved int the data section of the RAM

int main(void)
{
	uint32_t myvarInMain = 0xDEADBEEF; //Saved in the stack
	return 0;
}
```
Dans le premier cas pour la variables `myvarOutMain` cette dernière est conservée dans le "heap", et pour la variables `myvarInMain` cette dernière est conservée dans la pile.


## Bootloader ou bootstrap
Un chargeur d'amorçage (ou bootloader) est un logiciel permettant de lancer un ou plusieurs systèmes d'exploitation (multiboot), 
c'est-à-dire qu'il permet d'utiliser plusieurs systèmes, à des moments différents, sur la même machine. En ce qui nous concerne: un petit programme qui charge un grand
programme et qui lui donne le contrôle.

Sous Windows ou Linux le plus répendu est "GNU GRUB"
<img src="https://upload.wikimedia.org/wikipedia/commons/8/81/Grub_logo_large.png" height="250">

<img src="https://i2.wp.com/itsfoss.com/wp-content/uploads/2019/12/grub_screen.png?fit=800%2C450&ssl=1" height="250">

### Sur une plateforme embarqué.

Sur une plateforme embarqué on utilise plutôt un de ces bootloaders :
- U-Boot (https://github.com/u-boot/u-boot)
- RedBoot
- Micro Monitor


<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/9e/U-Boot_Logo.svg/langfr-440px-U-Boot_Logo.svg.png" height="250">

Ce programme réside dans une zone spéciale de la mémoire flash et fournit un moyen pour :
- Effectuer les tests d’initialisation du matériel
- Charger une image du noyau et l’exécuter

## Les Clocks.

Tout les périphériques doivent être sous horloge pour fonctionner.
Mais attentions tout les périphériques ne sont pas sous la même horloge ils sont cadencés par leur bus propre.

## Les GPIOs

GPIO signifie General Purpose Input/Output : ils font partis des périphériques. C'est le périphérique qui permet de contrôler les pins et qui permet de communiquer avec le monde extérieur.
La connexion entre les pins et le CPU est effectuée à travers un PORT.

![gpio](gpio.png)

La DataSheet du composant donne le diagramme du pinout du composant sur lequel on travaille et indique sur quel port est relié quelle pin : Prenoms par exemple le pinout du raspberry pi :
![rasp_pinout](https://www.raspberrypi-spy.co.uk/wp-content/uploads/2012/06/Raspberry-Pi-GPIO-Header-with-Photo.png)

On prendra garde que plusieurs pin ont des fonctions multiples et parfois uniquement disponible sur ces broches. (Timer, I2C, UART, etc ...)
Les pins d'alimentations sont repérées par l'inscription : 5V,3.3V ou encore VDD et VSS(ou GND), VDDIO etc ...

On trouve les fonctions alternative des gpios dans la datasheet de notre composant :
![gpio_alt](gpio_alt.png)

On observe ainsi l'état de base de la sortie en Pull-up ou Pull-Down pour notre exemple ci dessous la GPIO0 est en pull up et possède 5 fonctions alternatives.

Ainsi chaques proches est connecté à un port. Un port peut être connecté au maximum à 16 broches. Le port est repéré par une lettre et un nombre qui correspond au numéro du pin. Ainsi par exemple PC2 signifie : Entrée/Sortie 2 du port C.

Chaques ports à au moins 10 registres de configurations :
```
MODER: Mode Register (input; output, alternate function, analog)
OTYPER: Output Type Register (Output Speed Register)
PUPDR: Pullup / Pull-down Register (if pin configured as open drain)
ODR: Output Data Register
IDR: Input Data Register
BSSR: Bit Set / Reset Register
AFRL/H: Alternate Function Register (connect pin to timers, bus, event)
BRR: Bit Reset Register (reset ODR registers)
LCKR: Lock Register
```

Pour plus d'informations chercher les informations dans le Reference Manual du processeur.

## Les Timers

Tout les timers dans tout les micro-contrôleur ont :
- Une horloge.
- Un Prescaler pour diviser la fréquence de l'horloge.
- Un compteur pour stocker la valeur du nombre de ticks. (TIMx_CNT)
- Un registre d'auto-reload pour interrargir avec le compteur. (Comparaison, reload ...) (TIMx_PSC)
Par exemple si l'autoreload register est égale à 36, lorsque le compteur dépasse 36 il revient à 0.

![timer](timer.png)

Ce dernier se sert du presclaer et de l'horloge pour s'incrémenter : l'autoreload permet de remettre la valeur à 0 comme le montre l'exemple ci dessous :

![timer2](timer2.png)



## Les interruptions

Pour un système embarqué les interruptions sont déclarés dans la table des vecteurs et présent dans le fichier de startup :
Le gestionnaire d'interruption doit avoir le nom écrit dans la table de vecteur
Ce nom est normalisé par ARM pour la compatibilité entre plates-formes et fournisseurs.

![interrupt](interrupt.png)

# OS et code BareMetal
## BareMetal

La programmation BareMetal consiste à écrire du code pour faire tourner directement le hardware (ou via des library) sans aucunes autre abstraction comme un système d'exploitation.
Au minimum la programmation BareMetal doit avoir un minibootloader pour initialiser le processeur, les horloges, la mémoire (etc ...) et saute au programme principal.


## Linux embarqué

![alt text](baremetal_linux_embarque.png)

Sur un système à micro-contrôleur, le code métier(BareMetal Code) est le seul maître à bord, il accède à volonté aux périphériques, à la mémoire, etc. 

Au contraire, dans un système à micro-processeur, le code métier n'est qu'une petite partie de l'ensemble du logiciel. Il est soumis à l'ordonnancement et au sous-système de gestion mémoire du noyau. Il s'appuie sur des bibliothèques et des utilitaires externes.


## Outils de développement pour les systèmes embarqués :

```
Virtualisation
Eclipse
Code Composer Studio
IAR Embedded Workbench
Keil
Quartus (FPGA Altera)
Vivado (FPGA Xilinx)
```

## Glossaire aux systèmes embarqués

```
Bootloader	Secteur d'amorçage (Permet de charger un noyau depuis un système de fichier ext2 ou
ext3/4)
GPIO 	General Purpose Input/Output
GRUB	GRand Unified Bootloader
CAN 	Control Area Network (Bus de données)
SoC		System On Chip
ASICs	Application-specific integrated circuit
I2C		Inter-Integrated Circuit (Communication Série)
SPI		Serial Periphical Interface (Communication Série)
UART	Universal Asynchronous Transmitter Receiver (Communication Série)
USB		Universal Serial Bus (Communication Série)
BSP		Board Support Package (Logiciel bas niveau de support de cartes-mères, c'est-à-dire entre l'OS et la carte mère)
DRIVER	Pilote (Permet de faire le lien entre le matériel et le logiciel)
GPP		General Purpose Memory Controller
FPGA	Field Programmable Gate Array
QNET	Quadnet Pile d'execution
RTOS	Real Time Operating System (Linux RT, FreeRTOS, VxWorks, Unix, OS/2 , Symbian, QNX , RTXC Quadros... )
RSTP	Rapid Spanning Tree Protocol
Modbus	TCP Modbus Protocol (Port 502)
SNMP	Simple Network Management Protocol
SNTP	Simple Network Time Protocol
LLDP	Link Layer Discovery Protocol
HPC	Host Proxy Component
EIP	EtherNet Industrial Protocol
TFTP	Trivial File Transfer Protocol
RTC	Real Time Clock
DMA	Direct Memory Access
DSP	Digital Signal Processor
ΔΣ	ADC Analog to Digital Converter
TPM	Trusted Plateform Module	 
SPL	Secondary Prgram Loader 
NOR Flash	Mémoire non volatile
PMIC	Power management integrated circuit
SDRAM	Mémoire RAM volatile
IOC	 	Input Output Controler
NVIC	Nested Vectored Interrupt Controller
PBS	Product Breakdown Structure
```

## Références :
http://syst.univ-brest.fr/boukhobza/images/stories/Documents/Teachings/OSM/Cours/OSM_7_Boukhobza.pdf
