BotJs Core
==========

The BotJs base is contained in a tiny core. This core is just composed of a QApplication and a QJsEngine.

## Start up flow


## BotJs Modules

One main features of BotJs is to be extendable. The core provides a way to extends BotJs through a module system.

### Module properties


### Create custom module

## Core Module

Core is a module that is loaded at startup by BotJs. it provides every basic functionalities to manage and extend the BotJs. Core is directly linked to the BotJs core.

### Require function

This function provides a way to load a module through javascript. That is why core module is loaded at startup.

To load a module called 'modulename':

```js
core.require('modulename');
```

Require search for the module library (libmodulename.so) in directories indicated by the env variable: BOTJS\_MODULE_PATH.

### Exit function

This function stops the application

```js
core.exit();
```

