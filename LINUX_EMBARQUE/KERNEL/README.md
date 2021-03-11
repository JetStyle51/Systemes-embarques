# Le Noyau Linux

Linux : https://github.com/torvalds/linux

Linux BeagleBoard : https://github.com/beagleboard/linux

Linux RaspberryPi : https://github.com/raspberrypi/linux


## Compiler et déployer le Noyau Linux pour Debian (Cible Embarquée)

Prérequis :
Avoir déjà un Debian GNU/Linux qui tourne sur la cible embarquée.

Mettez un coup de propre avant de commencer dans le noyau Linux
```
make CROSS_COMPILE=arm-linux-gnueabihf- distclean
```

Aller chercher la configuration pour Beaglebone Black (ou autre) avec la commande :
```
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- bb.org_defconfig
```

La façon la plus simple de compiler le noyau Linux pour Debian est d'utiliser dpkg.
(Adapter le compilateur et l'architecture si besoin)
Avec la commande :

```
sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- deb-pkg -j$(nproc)
```

Cette dernière commande créer différents packets dans le repertoire précédent le dossier du noyau
```
linux-4.19.94+_4.19.94+-5_armhf.buildinfo // Contient quelques informations concernant le build du noyau
linux-4.19.94+_4.19.94+-5_armhf.changes // Contient les checksums et descriptions des différents packets
linux-4.19.94+_4.19.94+-5.diff.gz
linux-4.19.94+_4.19.94+-5.dsc
linux-4.19.94+_4.19.94+.orig.tar.gz //Linux kernel, version 4.19.94+
linux-headers-4.19.94+_4.19.94+-5_armhf.deb //Linux kernel headers for 4.19.94+ on armhf
linux-image-4.19.94+_4.19.94+-5_armhf.deb //Packet d'installation du noyau
linux-libc-dev_4.19.94+-5_armhf.deb //Linux support headers for userspace development
```

Il convient alors de transférer les packets vers la cible (soit par carte SD en transférant directement les fichiers vers un répertoire particulier)
Soit par la commande scp : qui permet de faire du transfert par SSH.

Pour commencer mettre tout les fichiers dans un même dossier puis aller dans ce dossier et démarrer le transfert :
(adapter les champs)

Syntaxe : scp <local_files> user@ip:/repertory/destination/oncible

```
cd mon_dossier
scp * debian@192.168.1.144:/home/debian/
```

Une fois les fichiers transférés il faut les installers :
Se connecter à la cible.

Vérifions d'abord la version du kernel Linux avec la commande
```
uname -r
```
Pour mon cas je suis en version :
```
4.19.94-ti-r42
```

Se rendre dans le repertoire de destination puis faire un :
```
dpkg -i *.deb
```

Attendre la fin de l'installation. Puis faire un reboot :
```
reboot
```

Au redémarrage du Kernel : en étant connecté directement à l'UART du processeur via la liaison série on peut voir ce que fait le boot du Kernel.
```
U-Boot SPL 2019.04-00002-g07d5700e21 (Mar 06 2020 - 11:24:55 -0600)
Trying to boot from MMC2
Loading Environment from EXT4... ** File not found /boot/uboot.env **

** Unable to read "/boot/uboot.env" from mmc0:1 **


U-Boot 2019.04-00002-g07d5700e21 (Mar 06 2020 - 11:24:55 -0600), Build: jenkins-github_Bootloader-Builder-137

CPU  : AM335X-GP rev 2.1
I2C:   ready
DRAM:  512 MiB
No match for driver 'omap_hsmmc'
No match for driver 'omap_hsmmc'
Some drivers were not found
Reset Source: Global warm SW reset has occurred.
Reset Source: Power-on reset has occurred.
RTC 32KCLK Source: External.
MMC:   OMAP SD/MMC: 0, OMAP SD/MMC: 1
Loading Environment from EXT4... ** File not found /boot/uboot.env **

** Unable to read "/boot/uboot.env" from mmc0:1 **
Board: BeagleBone Black
<ethaddr> not set. Validating first E-fuse MAC
BeagleBone Black:
Model: Element14 BeagleBone Black Industrial:
BeagleBone: cape eeprom: i2c_probe: 0x54:
BeagleBone: cape eeprom: i2c_probe: 0x55:
BeagleBone: cape eeprom: i2c_probe: 0x56:
BeagleBone: cape eeprom: i2c_probe: 0x57:
Net:   eth0: MII MODE
cpsw, usb_ether
Press SPACE to abort autoboot in 0 seconds
board_name=[A335BNLT] ...
board_rev=[EIA0] ...
switch to partitions #0, OK
mmc0 is current device
SD/MMC found on device 0
switch to partitions #0, OK
mmc0 is current device
Scanning mmc 0:1...
gpio: pin 56 (gpio 56) value is 0
gpio: pin 55 (gpio 55) value is 0
gpio: pin 54 (gpio 54) value is 0
gpio: pin 53 (gpio 53) value is 1
switch to partitions #0, OK
mmc0 is current device
gpio: pin 54 (gpio 54) value is 1
Checking for: /uEnv.txt ...
Checking for: /boot.scr ...
Checking for: /boot/boot.scr ...
Checking for: /boot/uEnv.txt ...
gpio: pin 55 (gpio 55) value is 1
2056 bytes read in 26 ms (77.1 KiB/s)
Loaded environment from /boot/uEnv.txt
Checking if uname_r is set in /boot/uEnv.txt...
gpio: pin 56 (gpio 56) value is 1
Running uname_boot ...
loading /boot/vmlinuz-4.19.94+ ...
10123472 bytes read in 667 ms (14.5 MiB/s)
debug: [enable_uboot_overlays=1] ...
debug: [enable_uboot_cape_universal=1] ...
debug: [uboot_base_dtb_univ=am335x-boneblack-uboot-univ.dtb] ...
uboot_overlays: [uboot_base_dtb=am335x-boneblack-uboot-univ.dtb] ...
uboot_overlays: Switching too: dtb=am335x-boneblack-uboot-univ.dtb ...
loading /boot/dtbs/4.19.94+/am335x-boneblack-uboot-univ.dtb ...
162266 bytes read in 88 ms (1.8 MiB/s)
uboot_overlays: [fdt_buffer=0x60000] ...
uboot_overlays: loading /lib/firmware/BB-ADC-00A0.dtbo ...
867 bytes read in 154 ms (4.9 KiB/s)
uboot_overlays: loading /lib/firmware/BB-BONE-eMMC1-01-00A0.dtbo ...
1584 bytes read in 1365 ms (1000 Bytes/s)
uboot_overlays: loading /lib/firmware/BB-HDMI-TDA998x-00A0.dtbo ...
4915 bytes read in 1334 ms (2.9 KiB/s)
uboot_overlays: loading /lib/firmware/AM335X-PRU-RPROC-4-19-TI-00A0.dtbo ...
3801 bytes read in 1232 ms (2.9 KiB/s)
loading /boot/initrd.img-4.19.94+ ...
5023648 bytes read in 348 ms (13.8 MiB/s)
debug: [console=ttyO0,115200n8 bone_capemgr.uboot_capemgr_enabled=1 root=/dev/mmcblk0p1 ro rootfstype=ext4 rootwait coherent_pool=1M net.ifnames=0 lpj=1990656 rng_core.default_quality=100 quiet] ...
debug: [bootz 0x82000000 0x88080000:4ca7a0 88000000] ...
## Flattened Device Tree blob at 88000000
   Booting using the fdt blob at 0x88000000
   Loading Ramdisk to 8fb35000, end 8ffff7a0 ... OK
   Loading Device Tree to 8faa9000, end 8fb34fff ... OK

Starting kernel ...

[    0.002183] timer_probe: no matching timers found
[    0.200351] l4_wkup_cm:clk:0010:0: failed to disable
[    1.238923] DEBUG: Passed omap_sham_probe 2210
[    1.337091] omap_voltage_late_init: Voltage driver support not added
rootfs: clean, 113099/944384 files, 697839/3888384 blocks

Debian GNU/Linux 10 beaglebone ttyS0

BeagleBoard.org Debian Buster IoT Image 2020-04-06

Support: http://elinux.org/Beagleboard:BeagleBoneBlack_Debian

default username:password is [debian:temppwd]

beaglebone login:
```

Cette fois ci si on se connecte et si on refait un uname -r on obtient un kernel mise à jour :
```
uname -r
4.19.94+
```