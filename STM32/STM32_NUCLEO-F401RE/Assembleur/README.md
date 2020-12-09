##Présentation

![alt text](https://sc01.alicdn.com/kf/HTB1aBH4B5OYBuNjSsD4q6zSkFXa9.jpg_640x640.jpg)
![alt text](https://components101.com/sites/default/files/inline-images/STM32-Nucleo-F401RE.png)

![alt text](https://components101.com/sites/default/files/component_pin/STM32-Nucleo-F401RE-Pinout.png)

L’architecture du CPU est de type HARVARD avec un bus d’adresse de 32 bits vers la mémoire programme et un bus d’adresse de 32 bits entre la mémoire et les données. Le bus de données vers la mémoire programme est de 32 bits et vers la mémoire de données de 32 bits.  
 
Le CPU contient 18 registres tous de taille 32 bits :  o douze registres généraux (R0 à R12)  o un compteur ordinal PC (Program Counter),  o Un pointeur de pile SP (Stack Pointer) o Une registre de lien LR (Linked Register) 
 5
o un registre d'état PSR (Program Status Register),  o un pointeur de pile SP (16 bits). 
 
 
La mémoire présente est de type :  o Flash (256 Ko) pour la mémoire programme,  o RAM (80Ko), o EEPROM (16Ko). 
 
 
Les périphériques sont :  o ports d’entrées/sorties (PORT A, PORT B, PORT C, PORT D) avec un nombre de broches qui varient o Watchdog : IWDG (Independant Watchdog) et WWDG (Window Watchdog)  o Timers : timers basiques et avancés, 32 ou 16-bit o module de communication I2C  o module de communication SPI  o module de communication UART  o convertisseur analogique numérique o convertisseur numérique analogique o … 
 
L’accès aux périphériques se fait à travers différents bus : AHB, APB1 et APB2. Vous ferez attention de gérer l’horloge pour chaque périphérique. 

II. Clock System
STM32 has five clock sources: HSI, HSE, LSI, LSE, PLL.
- (1) HSI is a high-speed internal clock, RC oscillator, with a frequency of 8MHz and low accuracy.
- (2) HSE is a high-speed external clock, which can be connected with quartz/ceramic resonator or external clock source. Its frequency range is from 4MHz to 16MHz.
- (3) LSI is a low-speed internal clock, RC oscillator, with a frequency of 40 kHz, providing a low-power clock. 　
- (4) LSE is a low-speed external clock connected to 32.768 kHz quartz crystal.
- (5) PLL is the frequency doubling output of PLL, and its clock input source can be HSI/2, HSE or HSE/2. Frequency doubling can be chosen as 2 to 16 times, but the maximum output frequency should not exceed 72MHz.
The system clock SYSCLK can be derived from three clock sources:
- (1) HSI oscillator clock
- (2) HSE oscillator clock
- (3) PLL Clock
STM32 can choose a clock signal to output to MCO foot (PA8), and can choose 2-frequency, HSI, HSE, or system clock for PLL output.
Before any peripheral can be used, its corresponding clock must be enabled first.
 
L'utilisation des registres des périphériques est expliquée dans la documentation technique du µcontrôleur (reference Manual)

##Instructions assembleur du programme