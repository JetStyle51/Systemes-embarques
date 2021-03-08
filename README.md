# Systèmes-embarqués

Ce dépôt regroupe des outils / documentation / tutoriel et codes qui peuvent être utiles pour un système embarqué.

## Introdudction aux systèmes embarqués :

Un système embarqué est un ensemble électronique et/ou informatique intégré comme composant d'un environnement plus important.
Un système embarqué se définit surtout par les contraintes auxquelles il est soumis


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

## Processus de démarrage

Suivant le type de processeur et la complexité du matériel, le temps de boot du noyau dure de
deux à cinq secondes environ.
Le démarrage du processus init, les tâches administratives (montage systèmes de fichiers,
configuration paramètres de /proc (sous linx) , etc.) prennent une à deux secondes supplémentaires.
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
