# Introduction à U-Boot

Les bootloader sont généralement à plusieurs étages (stages). Il y a généralement deux ou trois bootloader avant de rentrer dans le noyau du système.

![Bootloader Embedded](https://i.ytimg.com/vi/DV5S_ZSdK0s/maxresdefault.jpg)

![Bootloader](https://www.digikey.fr/-/media/Images/Article%20Library/TechZone%20Articles/2020/June/IoT%20Security%20Fundamentals%20Part%203%20Ensuring%20Secure%20Boot%20and%20Firmware%20Update/article-2020june-iot-security-fundamentals-part-3-fig2.jpg?la=en&ts=713be6fb-ec8a-43ad-8c1a-3a7ed2661016)



## First Stage Bootloader (FSB)

Premièrement on rentre dans le First Stage BootLoader (FSB) : 
Ce dernier :
- Stocke la table des vecteurs d'interruption.
- Peut être stocké sur le BootROM du Chip.
- Initialise l'hardware et charge le prochain étage (Chargement de U-Boot ou du noyau directement)

## Second Stage Bootloader (SSB)

### Secondary Program Loader SPL

- Construit à partir des mêmes sources que U-Boot.
- Taille du code significativement réduit et la listes des possibilités également.
- Utilisé pour faire l'init du système ou pour charger U-Boot ou Linux.

### U-Boot
U-Boot offre un shell interactif.
Permet de monitorer le boot.
De faire du debug (Tester de l'hardware).
Il permet de mettre à jour l'applicatif par exemple ou le boot lui même.

# U-Boot Shell

Il y a deux types de shell pour U-Boot :
- Le shell originel
- HUSH Shell (qui possèdes plus de possibilités) : + utilisé. (Viens de busybox)

Il permet en partie de faire du scripting, et de gérer des variables d'environement.
Pour obtenir de l'aide sur le shell de uboot il suffit de taper la commande `help`

## Information commands

```
bdinfo - print Board Info structure
coninfo - print console devices and information
flinfo - print FLASH memory information
help - print online help
```

### bdinfo
Obtenir des informations sur le système :
- Comme l'addresse de départ et la taille de la mémoire RAM présent sur le board.
- L'addresse ip du board
```
arch_number = 0x00000e05
boot_params = 0x80000100
DRAM bank   = 0x00000000
-> start    = 0x80000000
-> size     = 0x20000000
eth0name    = cpsw
ethaddr     = d0:03:eb:dc:ba:b1
eth1name    = usb_ether
eth1addr    = d0:03:eb:dc:ba:b3
current eth = cpsw
ip_addr     = 192.168.1.2
baudrate    = 115200 bps
TLB addr    = 0x9fff0000
relocaddr   = 0x9ff58000
reloc off   = 0x1f758000
irq_sp      = 0x9df37ea0
sp start    = 0x9df37e90
Early malloc usage: 410 / 1000
```

### coninfo

```
List of available devices:
ns16550_serial 00000007 IO stdin stdout stderr
serial   00000003 IO
```

## Memory commands

```
base - print or set address offset
crc32 - checksum calculation
cmp - memory compare
cp - memory copy
md - memory display
mm - memory modify (auto incrementing)
mtest - simple RAM test
mw - memory write (fill)
nm - memory modify (constant address)
loop - infinite loop on address range
```

### mw
Pour l'écriture en mémoire, on peut imaginer écrire dans des registres, des addresses mémoires bien spécificique etc ...

```
mw <addr> <value_to_write>
```

Exemple :
```
=> mw 0x80000000 1
=> md 0x80000000
80000000: 00000001                               ....
```


### md
Pour la lecture en mémoire,
Supporte l'accès au byte/mot/long/quad registres en utilisant les suffixes (.b,.w,.l,.q)
La longeur de la lecture par défaut est long : 32 bits (md=md.l)
Lit par défaut les 0x40 prochains bytes

Syntaxe :
```
md(.b,.w,.l,.q) <addr> <number_of_bytes_to_read>
```

Exemple :
```
=> md.l 0x80000000
80000000: 00000000 ffffffff 00000000 ffffffff    ................
80000010: 00000000 ffffffff 00000000 fffffffb    ................
80000020: 00000000 ffffffff 00080000 ffffffff    ................
80000030: 00100000 fffdffff 00000000 ffffffbf    ................
80000040: 00000004 ffffffff 00000001 ffffffff    ................
80000050: 00000000 fffeffff 00200000 ffffffff    .......... .....
80000060: 00000000 ffffffff 0080009a ffffffff    ................
80000070: 00200000 ffffffff 00400000 ffffffff    .. .......@.....
80000080: 00000020 ffefffff 00800000 ff7fffff     ...............
80000090: 00440000 ffffffff 00020000 ffffffff    ..D.............
800000a0: 00000000 ffffffff 00000000 ffffffff    ................
800000b0: 00100000 ffffffff 00840000 fffffff7    ................
800000c0: 00020001 ffffffff 00000084 fff7ffff    ................
800000d0: 00000080 ffffffff 00200000 fffffffd    .......... .....
800000e0: 00800080 fffaffff 00000021 ff7effff    ........!.....~.
800000f0: 00000000 ffffffff 00000000 fffffffd    ................
```

```
=> md.b 0x80000000
80000000: 00 00 00 00 ff ff ff ff 00 00 00 00 ff ff ff ff    ................
80000010: 00 00 00 00 ff ff ff ff 00 00 00 00 fb ff ff ff    ................
80000020: 00 00 00 00 ff ff ff ff 00 00 08 00 ff ff ff ff    ................
80000030: 00 00 10 00 ff ff fd ff 00 00 00 00 bf ff ff ff    ................
```

```
md.b 0x80000000 0x8
80000000: 00 00 00 00 ff ff ff ff                            ........
```

Tips : en appuyant sur entrer on obtient directement les prochains bytes :
```
=> md.b 0x80000000 0x8
80000000: 00 00 00 00 ff ff ff ff                            ........
=>
80000008: 00 00 00 00 ff ff ff ff
```

### mm
Modification de la mémoire.
Utile pour modifier la valeur des registres interactivement.
(Incrémente automatiquement les addresses)
Mêmes propriétés que md/mw

`q` pour quitter
`-` pour revenir à l'addresse précédente
`Enter` pour passer la valeur actuelle.

Exemple :
```
=> mm 0x80000000
80000000: 00000001 ? 2
80000004: ffffffff ? 1
80000008: 00000000 ?
8000000c: ffffffff ?
80000010: 00000000 ? 2
80000014: ffffffff ? 3
80000018: 00000000 ? 2
8000001c: fffffffb ? 1
80000020: 00000000 ? q
=> md 0x80000000
80000000: 00000002                               ....
=> md 0x80000000 0x10
80000000: 00000002 00000001 00000000 ffffffff    ................
80000010: 00000002 00000003 00000002 00000001    ................
80000020: 00000000 ffffffff 00080000 ffffffff    ................
80000030: 00100000 fffdffff 00000000 ffffffbf    ................
```

### nm
Modification de la mémoire.
Utile pour modifier la valeur des registres interactivement.
(Reste sur l'addresse courante)
Mêmes propriétés que md/mw

`q` pour quitter
`-` pour revenir à l'addresse précédente
`Enter` pour passer la valeur actuelle.

Exemple :
```
=> nm 0x80000000
80000000: 00000002 ? 1
80000000: 00000001 ? 2
80000000: 00000002 ? 3
80000000: 00000003 ? 1
80000000: 00000001 ? 2
80000000: 00000002 ? 1
80000000: 00000001 ? q
```

### cp
Pour copier la mémoire

Syntaxe :
```
cp <src> <dest> <size>
```

Exemple :
```
cp 0x81000000 0x80000000 0x8
```

### cmp
Pour comparer la mémoire

Syntaxe :
```
cmp <src> <dest> <size>
```

Exemple :
```
=> cmp 0x80000000 81000000 0x8
word at 0x80000000 (0x01) != word at 0x81000000 (0x00)
Total of 0 word(s) were the same
```

## Flash memory commands

```
cp - memory copy
flinfo - print FLASH memory information
erase - erase FLASH memory
protect - enable or disable FLASH write protection
```

## Image commands

```
iminfo - print header information for application image
imxtract - extract a part of a multi-image
```

## Execution control commands

```
autoscr - run script from memory
source - run script from memory
bootm - boot application image from memory
go - start application at address 'addr'
loop - infinite loop on address range
exit - exit script
```

## Download commands

```
bootp - boot image via network using BOOTP/TFTP protocol
dhcp - invoke DHCP client to obtain IP/boot params
loadb - load binary file over serial line (kermit mode)
loady - load binary file over serial line (ymodem mode)
loads - load S?Record file over serial line
rarpboot - boot image via network using RARP/TFTP protocol
tftpboot - boot image via network using TFTP protocol
nfs - boot image via network using NFS protocol
ping - send ICMP ECHO REQUEST to network host
```

## Environment variables commands

```
env - environment handling commands
editenv - edit environment variable
printenv - print environment variables
saveenv - save environment variables to persistent storage
setenv - set environment variables
run - run commands in an environment variable
bootd - boot default, i.e., run 'bootcmd'
boot - boot default, i.e., run 'bootcmd'
```

### printenv
Pour afficher les variables d'environnement.

Synthaxe :
```
print env
```

Exemple :
```
=> env print
arch=arm
args_mmc=run finduuid;setenv bootargs console=${console} ${cape_disable} ${cape_enable} ${cape_uboot} root=PARTUUID=${uuid} ro rootfstype=${mmcrootfstype} ${uboot_detected_capes} ${cmdline}
args_mmc_old=setenv bootargs console=${console} ${optargs} ${cape_disable} ${cape_enable} ${cape_uboot} root=${oldroot} ro rootfstype=${mmcrootfstype} ${uboot_detected_capes} ${cmdline}
(...)
```

```
=> env print arch
arch=arm
=> echo "$arch"
arm
```

#### Petit tour des variables d'environnement :
Certaines variables on des fonctionalités spécifique :
- ver : U-Boot version
- stdin,stdout,stderr : Redirection of STDIO. Mettre des valeurs ici ont un impact immediat. (Voir aussi coninfo)
- loadaddr : Addresse de chargement par défault
- filesize : Taille du fichier chargé.
- bootargs : Les arguments de boot donnée au Linux command line
- bootcmd : Les boot commands par défaut (voir commande boot et autoboot)
- preboot : Script executé avant l'autoboot
- ipaddr, netmask, serverip, gatewayip : Paramètres réseaux.
- ethaddr, eth1addr, ... : Ethernet Mac ADDR.

### setenv
Pour affecter/modifier des variables d'environnement

Synthaxe :
```
env set test=ok
```

Exemple :
```
=> env set foo bar
=> env print foo
foo=bar

=> env ask quux "Set quux to ?"
Set quux to? 1234
=> env print quux
quux=1234

=> env edit quux
edit: 24
=> env print quux
quux=24
```

### saveenv
Pour sauvegarder les variables d'environement de manière persistante.

Synthaxe :
```
saveenv
```

Exemple :
```
=> env set foo bar
=> env print foo
foo=bar

=> reset
=> env print foo
## Error: "foo" not defined

=> env set foo bar
=> saveenv
=> reset
=> env print foo
bar

```

### run
Pour faire tourner des scripts dans l'environnement
Le chainage des commandes est possible avec `;`, note: *ce dernier ignore la valeur de retour.*

Exemple :
```
=> env set foo `echo hello`
=> run foo
hello

=> env set foo `echo hello ; echo world`
=> run foo
hello
world
```


## File system support commands

```
fatinfo - print information about a FAT file system
fatload - load binary file from a FAT file system
fatls - list files in a FAT file system directory (default /)
ext2load - load binary file from a Ext2 filesystem
ext2ls - list files in a directory (default /)
fsinfo - print information about JFFS2 file system
fsload - load binary file from a JFFS2 file system image
ls - list files in a JFFS2 file system directory (default /)
```

## NAND flash support

```
nand - NAND sub-system control
nandecc - switch OMAP3 NAND ECC calculation algorithm
nboot - boot from NAND device
```

## EEPROM support

```
eeprom - EEPROM sub-system control
```

## Partition commands

```
mtdparts - define flash/nand partitions
chpart - change active partition
```

## FDT support

```
fdt - flattened device tree utility commands
```

## MMC support

```
mmc - MMC sub system
mmcinfo - display MMC information
```

## I2C support

```
i2c - I2C sub-system control
```

## USB support
```

usb - USB sub-system control
usbboot - boot from USB device
```

C## ache support
```

icache - enable or disable instruction cache
dcache - enable or disable data cache
```

## Bitmap support
```

bmp - manipulate BMP image data
```

## GPIO support

```
gpio - manipulate gpios
```

## Miscellaneous commands
```
echo - echo arguments to console
reset - Perform RESET of the CPU
sleep - delay execution for some time
version - print monitor version
test - minimal test, like /bin/bash
? - alias for help
showvar - print local hushshell variables
true - do nothing, successfully
false - do nothing, unsuccessfully
cls - clear screen
itest - return true/false on integer compare
```

### version
Affiche la version d'uboot et les informations de compilation :

Exemple :
```
=> version
U-Boot 2019.04-00002-g07d5700e21 (Mar 06 2020 - 11:24:55 -0600), Build: jenkins-github_Bootloader-Builder-137

arm-linux-gnueabihf-gcc (Linaro GCC 6.5-2018.12) 6.5.0
GNU ld (Linaro_Binutils-2018.12) 2.27.0.20161229
=> ver
U-Boot 2019.04-00002-g07d5700e21 (Mar 06 2020 - 11:24:55 -0600), Build: jenkins-github_Bootloader-Builder-137

arm-linux-gnueabihf-gcc (Linaro GCC 6.5-2018.12) 6.5.0
GNU ld (Linaro_Binutils-2018.12) 2.27.0.20161229
```

Pour avoir de l'aide sur une commande en particulier il suffit ensuite de taper `help usb` pour avoir plus d'informations.

## Les traces de démarrages

```
U-Boot SPL 2019.04-00002-g07d5700e21 (Mar 06 2020 - 11:24:55 -0600)
Trying to boot from MMC2
Loading Environment from EXT4... Card did not respond to voltage select!


U-Boot 2019.04-00002-g07d5700e21 (Mar 06 2020 - 11:24:55 -0600), Build: jenkins-github_Bootloader-Builder-137

CPU  : AM335X-GP rev 2.1
I2C:   ready
DRAM:  512 MiB
No match for driver 'omap_hsmmc'
No match for driver 'omap_hsmmc'
Some drivers were not found
Reset Source: Power-on reset has occurred.
RTC 32KCLK Source: External.
MMC:   OMAP SD/MMC: 0, OMAP SD/MMC: 1
Loading Environment from EXT4... Card did not respond to voltage select!
Board: BeagleBone Black
<ethaddr> not set. Validating first E-fuse MAC
BeagleBone Black:
Model: Element14 BeagleBone Black Industrial:
BeagleBone: cape eeprom: i2c_probe: 0x54:
BeagleBone: cape eeprom: i2c_probe: 0x55:
BeagleBone: cape eeprom: i2c_probe: 0x56:
BeagleBone: cape eeprom: i2c_probe: 0x57:
```


