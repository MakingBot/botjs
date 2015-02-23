Block Interface
===============

BotBlock is the master interface for all components of BotJs.

## Block basic information

Basic information is a group of elements that provide basic block identification. Those parameters are constant and use the Qt metaobject system.

- The version: Decimal number that indicate the evolution state of the block.
- The role: String that define what type of job the block perform.
- The type name: The block class name.
- The name: The name of the variable choosen by the user to identify the block.

## Block pointer management

BotJs architecture is based on a dynamic and flexible block composition. Therefore pointers are massively used and to make sure that it does not end in a huge memory mess some rules are imposed.

- Shared pointers are used to store new blocks.
- Only the father block can store the shared pointer.
- Other blocks must use weak pointer and transform them in shared pointer localy.

A block hold a weak pointer on itself, this pointer is initialized at creation time just after the constructor. Functions to cast block pointers are provided.

## Father and sons

A father block hold a shared pointer on every block it has created, those blocks are called its sons.

The father of all blocks is the core block. Therefore BotJs has a pyramidal architecture and every block can be identified by its unique block chain.

Sons are stored as a map to make more effecient block chain manipulation.

## Connection

A Block can be connected to all other existing block. However if those block have affinities, they create a block synergy and they can perform action much more interresting.

To connect a block1 to a block2 use connect block1.connect(block2). Be carefull the direction may be important. block1.connect(block2) may be slightly different than block2.connect(block1).

When connected a weak pointer of the connected block is keept in the internal connection map.


![connection_process](doc/connection_process.png "connection_process")


## The Js engine


## Interactive properties



## Log and talk


