BotJs
=====

BotJs is a modular C++ application scriptable and composable through JavaScript. The aim is to create a system adaptable to any robot and host system.

## Build

### Qt

BotJs use QT5.4 with cmake configuration. It has to be installed and configured before the build.

### Build on Ubuntu

The build process is entirely managed by a bash script. It builds and install the core and modules of the project. Each module have it own cmake script to build it.

```bash
# Start BotJs build
cd botjs
./build
```

Clean is also possible, it remove all build directories

```bash
# Start BotJs clean
cd botjs
./clean
```


## Usage

```bash
# Start BotJs in console mode
botjs
```

```bash
# Start BotJs with the user configuration script
botjs script.js
```

See the tutorial section for more information about the use of BotJs.
