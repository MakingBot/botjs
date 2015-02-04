Tutorial 00: Build environment
==============================

# Ubuntu

### Cmake installation

BotJs use cmake to generate compilation project.
To install cmake on ubuntu just use apt-get.

```bash
sudo apt-get install cmake
```

Minimum cmake version must be 2.8.11

```bash
# Just type cmake to check your cmake version
sudo apt-get install cmake
```

### Qt installation

BotJs use Qt as base library and will follow its evolution.

Current version: Qt5.4

**note** It is recommended to install Qt with the installer from the Qt web site.

### Cmake issues

For questions from users

### Compilation

The build process is entirely managed by a bash script. It builds and install the core and block of the project. Each block have it own cmake script to build it.

```bash
# Start BotJs build
cd path/to/botjs
./build.sh
```

Clean script is also available, it remove all build directories.

```bash
# Start BotJs clean
cd path/to/botjs
./clean.sh
```

### Binary folder link

By default, BotJs binary is installed in $HOME/opt/botjs/bin.

It is recommended to add this directory to your PATH.

```bash
export PATH=$PATH:$HOME/opt/botjs/bin
```

**note** Use the BotJs binary from the install directory, not the one from the build directory.

# Window

In creation...
