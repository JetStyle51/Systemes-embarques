# Emuler un environnement Raspberry Pi avec Buildroot :

Prérequis : 

```
sudo apt-get install qemu-system
sudo apt-get install gcc-aarch64-linux-gnu
```

# Compiler le Noyau Linux Virtuel

Il vous faut dans un premier temps cloner le repos buildroot :
```
git clone https://github.com/buildroot/buildroot.git
```

Si ce n'est pas déjà fait.

Faire le ménage pour commencer :
```
make clean
```

Dans le dossier buildroot, générer une configuration virtuelle :
```
make qemu_aarch64_virt_defconfig -j$(nproc)
```

Puis fabriquer le noyau :
```
make -j$(nproc)
```

La commande make lance la génération du système, c'est-à-dire : 
- la génération de la chaîne de cross-compilation pour l'architecture demandée ;
- la compilation, via la chaîne de cross-compilation, des applications/services afin de générer le système ;
- la compilation du noyau ;
- la génération du rootfs en créant une image disque (rootfs.ext4), et en recopiant le système cross-compilé.

Lorsque votre système est complètement généré, vous obtenez ceci :

![alt text](https://user.oc-static.com/upload/2019/01/14/15474782896388_compil-64.png)

À l'issue de la génération, vous obtenez 2 fichiers dans le dossier output/Images/. Le noyau correspond à l'Image et le système racine au fichier rootfs.ext4 (qui est un lien vers rootfs.ext2).

# Tester l'image

Testons maintenant cette nouvelle image avec QEMU. Utilisez pour cela la commande qemu-system-aarch64 afin d'émuler un système ARM 64 bits avec un processeur Cortex A57 monocœur et une carte réseau Ethernet. Vous démarrez sur le noyau et l'image disque que vous venez d'obtenir.

```
qemu-system-aarch64 -M virt \
                    -cpu cortex-a57 \
                    -nographic \
                    -smp 1 \
                    -kernel output/images/Image \
                    -append "root=/dev/vda console=ttyAMA0" \
                    -netdev user,id=eth0 -device virtio-net-device,netdev=eth0 \
                    -drive file=output/images/rootfs.ext4,if=none,format=raw,id=hd0 \
                    -device virtio-blk-device,drive=hd0
```

À la fin du démarrage, vous obtenez le message "Welcome to Buildroot" qui vous indique que votre image est fonctionnelle.
![alt text](https://user.oc-static.com/upload/2019/01/14/15474789812044_demarrage-64.png)

Vous pouvez maintenant comparer le temps nécessaire pour démarrer une image classique Raspbian et une version allégée Buildroot, et remarquer que cette nouvelle image démarre en quelques secondes.

Vous pouvez désormais vous authentifier en tant qu'utilisateur root et sans mot de passe.

Regardons rapidement les empreintes mémoire et disque de cette image. La commande free -m permet d'afficher l'occupation de la RAM, et la commande df -h celle du disque. Ainsi, notre Linux utilise 15 Mo de RAM, et même si nous avons généré un disque de 60 Mo, il n'utilise réellement que 2,9 Mo.  

![alt text](https://user.oc-static.com/upload/2019/01/14/1547479763568_connect-64.png)

Faites le même test sur la Raspbian et comparez.

```
pi@raspberrypi:~ $ df -h
Filesystem      Size  Used Avail Use% Mounted on
/dev/root        59G   12G   44G  22% /
devtmpfs        1.8G     0  1.8G   0% /dev
tmpfs           1.9G     0  1.9G   0% /dev/shm
tmpfs           1.9G  8.9M  1.9G   1% /run
tmpfs           5.0M  4.0K  5.0M   1% /run/lock
tmpfs           1.9G     0  1.9G   0% /sys/fs/cgroup
tmpfs           256M     0  256M   0% /tmp/jeedom
/dev/mmcblk0p1  253M   46M  207M  18% /boot
tmpfs           378M     0  378M   0% /run/user/114
tmpfs           378M     0  378M   0% /run/user/1000
```