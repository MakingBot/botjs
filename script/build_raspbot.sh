# Based on the Qt tutorial
# http://qt-project.org/wiki/RaspberryPi_Beginners_guide

# ==================
# === PARAMETERS ===

# Define qt prefix in raspbot image
qt_prefix="/opt/qt5pi"

# Define the build directory
build_directory="$HOME/opt/botjs/raspbot"

# Define the mount directory
mount_directory="/mnt/rpi-rootfs"

# Define raspbian image link
raspbian_img_link="http://downloads.raspberrypi.org/raspbian/images/raspbian-2015-02-17/2015-02-16-raspbian-wheezy.zip"

# Define the toolchain link
# rpi_toolchain_link="http://de.sourceforge.jp/projects/sfnet_rfidmonitor/downloads/crosscompilation-resources/gcc-4.7-linaro-rpi-gnueabihf.tbz"
rpi_toolchain_link="https://github.com/raspberrypi/tools.git"

# Define the qt tools link
qt_toolchain_link="https://gitorious.org/cross-compile-tools/cross-compile-tools.git"

# Define the qt source link
qt_source_link="https://gitorious.org/qt/qt5.git"

# =================
# === FUNCTIONS ===

# ---
function title() {
    echo ""
    echo "-- $1"
}


# ==========================
# === MOUNT RASPBIAN IMG ===

# Create the build directory
title "Create directory: $build_directory" 
mkdir $build_directory

# Download the raspbian img
cd $build_directory
title "Download raspbian image"
wget $raspbian_img_link

# Unzip it
raspbian_zip=$(basename $raspbian_img_link)
title "Unzip: $raspbian_zip"
unzip $raspbian_zip

# The toolchain
title "Download cross toolchain"
git clone $rpi_toolchain_link

# Mount the img
raspbian_img="${raspbian_zip%.*}.img"
title "Mount $raspbian_img -> $mount_directory"
sudo mkdir $mount_directory
sudo mount -o loop,offset=62914560 $raspbian_img $mount_directory

# It is a 32-bit build so if you are running on a 64-bit machine (you probably are) you need to install ia32-libs:
# sudo apt-get install ia32-libs
# sudo -i
# cd /etc/apt/sources.list.d
# echo "deb http://old-releases.ubuntu.com/ubuntu/ raring main restricted universe multiverse" >ia32-libs-raring.list
# apt-get update
# apt-get install ia32-libs

# On Ubuntu 14.04 do the following first to get the ia32-lib
# if [ `lsb_release -ds` -eq "Ubuntu 14.04 LTS" ]
# then
#   sudo apt-get install lib32z1 lib32ncurses5 lib32bz2-1.0 lib32stdc++6
# fi

# Clone the cross-compile-tools repository:
title "Clone git qt toolchain"
git clone $qt_toolchain_link

# Clone and init the Qt5 repository:
git clone $qt_source_link
git checkout 5.4
cd qt5
./init-repository

cross_compile_prefixe=$build_directory/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-
cross_compile_gcc=$(echo "$cross_compile_prefixe"gcc)

# Now the we have all the resources needed to compile qt5 for raspberry, we need to execute a script to fix symlinks and lib paths:
title "Patch tools with $mount_directory and $cross_compile_gcc"
cd $build_directory/cross-compile-tools
sudo ./fixQualifiedLibraryPaths $mount_directory $cross_compile_gcc

# Configure and make
cd $build_directory/qt5/qtbase
./configure -opengl es2 -device linux-rasp-pi-g++ -device-option CROSS_COMPILE=$cross_compile_prefixe -sysroot $mount_directory -opensource -confirm-license -optimized-qmake -reduce-exports -release -make libs -prefix $qt_prefix
make -j 16
sudo make install
cd ..

for MODULE in qtserialport qtdeclarative
do
    cd $MODULE
    $qt_prefix/bin/qmake .
    make -j16
    sudo make install
    cd ..
done

sync
sudo umount $mount_directory
