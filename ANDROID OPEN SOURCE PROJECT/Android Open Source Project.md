# Android Open Source Project

## General Concept
### About AOSP
Android is an open source operating system for mobile devices and a corresponding open source project led by Google.
![AOSP Architecture](https://source.android.com/images/android_stack_1440.png)

#### What do you need to run Android?
- Hardware from one of the supported Architecture: ARM, x86 or MIPS in 32 or 64bits variety
- Running a recent version of Linux kernel (v4.4 or later)
- At least 512  MiB RAM
- Minimum of 1 GiB flash storage (eMMC, SD Card)
- A display
- A GPU with OpenGL ES 2.0 librairies

### Get Sources
Create an empty directory to hold your working files. Give it any name you like:
```bash
mkdir WORKING_DIRECTORY
cd WORKING_DIRECTORY
```
Run repo init to get the latest version of Repo with its most recent bug fixes. You must specify a URL for the manifest, which specifies where the various repositories included in the Android source are placed within your working directory.
```bash
repo init -u https://android.googlesource.com/platform/manifest
```
To check out the master branch:
```bash
repo init -u https://android.googlesource.com/platform/manifest -b master
```
To check out a branch other than master, specify it with -b. For a list of branches, see ![Source code tags and build](https://source.android.com/docs/setup/about/build-numbers#source-code-tags-and-builds)
To download the Android source tree to your working directory from the repositories as specified in the default manifest, run:
```bash
repo sync
```

### Linux Kernel
As seen in ![AOSP Architecture Diagram](#about-aosp) the lower level is Linux Kernel. This kernel is usually provided by the silicon manufacturer.


#### Troubleshooting network issues
When downloading from behind a proxy (which is common in some corporate environments), you might need to to explicitly specify the proxy for Repo to use:
```bash
export HTTP_PROXY=http://<proxy_user_id>:<proxy_password>@<proxy_server>:<proxy_port>
export HTTPS_PROXY=http://<proxy_user_id>:<proxy_password>@<proxy_server>:<proxy_port>
```


### ADB (Android Debug Bridge)
Android Debug Bridge (adb) is a versatile command-line tool that lets you communicate with a device. The adb command facilitates a variety of device actions, such as installing and debugging apps, and it provides access to a Unix shell that you can use to run a variety of commands on a device. It is a client-server program that includes three components:

- A client, which sends commands. The client runs on your development machine. You can invoke a client from a command-line terminal by issuing an adb command.
- A daemon (adbd), which runs commands on a device. The daemon runs as a background process on each device.
- A server, which manages communication between the client and the daemon. The server runs as a background process on your development machine.

## Build a AOSP on a Raspberry
### Introduction
#### What do you need ?
- A copy of AOSP
- A linux kernel with Android Extensions

### Existing projects
- Android RPi
- LineageOS
- RTAndroid: Real Time Android OS
- emteria.os
- Android Things (no longer maintained)

### Get AOSP
![AOSP Sources](#get-sources)

### Customizing AOSP
POrting Android to new hardware means creating a new Board Support Package

#### Device configuration
Device specific configuration is in `device/[organisation]/[product]`

Select the one you want with the command `lunch`
```bash
$ source build/envsetup.sh
$ lunch rpi3-eng
```
#### Selecting the base product
Base product is selected in device configuration by `device.mk`
```bash
$ (call inherit-product, $(SRC_TARGET_DIR)/product/aosp_base.mk)
```
Products in AOSP:

 product | Target |
 ------------ | -------------- |
 aosp_base.mk | Android tablet |
 aosp_base_telephony.mk | Android phone |
 atv_base.mk | Android TV |
 car.mk | Android Automotive |

#### Building
Just type `m`
```bash
$ m
```
This will take a couple of hours depending on your system performance.

Finally the images will be in `out/target/product/[product_name]/*.img`

Write these to SD card for Raspberry

Or use **Fastboot** to flash them

#### Linux kernel for Raspberry Pi
As seen in ![Linux kernel](#linux-kernel) a customized kernel need to be built.
For Raspberry Pi Leanage developed a specific kernel.
TO BE TESTED:
```bash
$ git clone https://github.com/lineage-rpi/android_kernel_brcm_rpi.git rpi4
$ cd rpi4
$ make lineageos_rpi4_defconfig
$ make -j $(nproc) zImage
$ make dtbs
```

### ADB (Android Debug Bridge)
ADB cannot be directly used with a Raspberry 3b+ board as it holds only USB Host ports but ADB needs a USB Peripheral port.

>Explaination: The host initiates all communication on the bus, the device only responds when asked by the host. For Details see the specs on ![usb.org](https://www.usb.org/documents)

ADB is usually provided by a dual mode USB "**On The Go**" (OTG) port. 
- Rasp3b doesn't have one. 

To pass over this, we can use OTG via Ethernet instead
```bash
$ adb connect Android.local
connected to Android.local:5555
```
- Rasp 4b: USB2 OTG port is inside the USB-C connector.

### OS started
All standard AOSP apps are installed.
If you want Play Store and more, install ![**Gapps**](https://opengapps.org) 
> Note: This does not come with Google License (~10k$ for this typical platform)







