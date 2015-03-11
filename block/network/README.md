Network Block
=============

## Configuration

- Master: Master interface on Host computer dev
- Slave: Interface mode for the code embeded in the robot

## Start Up mode

A master interface have 2 startup mode

- Manual: NetworkBlock create a spy on it and user have to configure and start the network interface.
- Auto: NetworkBlock start scan and connect to the first that respond

A slave interface just wait for a connection

## Message Types

##### NET_PING

This message is sent by a dev core. It is used to scan the network searching for a robot. It is usually broadcasted in UDP.

|     Type    |   Value  | Size (bytes) |
|:-----------:|:--------:|:------------:|
| MessageType | NET_PING |       2      |

##### NET_PING_ACK

This message is sent by a bot core. It is used to answer to a network ping.

|     Type    |     Value    | Size (bytes) |
|:-----------:|:------------:|:------------:|
| MessageType | NET_PING_ACK |       2      |
|    String   |   Core Tag   |       5      |

##### NET_TEST

This message required a TCP connection

- Dev Core: Send 1022 bytes data to the bot core and wait for the return of every data.
- Bot Core: Send back the message to the emitter.

|     Type    |     Value    | Size (bytes) |
|:-----------:|:------------:|:------------:|
| MessageType |   NET_TEST   |       2      |
|    String   |     Data     |     1022     |

##### NET_BLOCK_CREATE

This message required a TCP connection. It request a block creation in the receiver core. The father of the new block must be already created.

|     Type    |     Value    | Size (bytes) |
|:-----------:|:------------:|:------------:|
| MessageType |   NET_BLOCK_CREATE   |       2      |
|    String   |     Block Type   |     N     |
|    String   |     Id Chain     |     N     |

##### NET_BLOCK_UPDATE

|     Type    |     Value    | Size (bytes) |
|:-----------:|:------------:|:------------:|
| MessageType |   NET_BLOCK_UPDATE   |       2      |
| Data Stream | Block Config  |     N     |

##### NET_BLOCK_CONNECT

##### NET_BLOCK_DISCONNECT

##### NET_BLOCK_DESTROY



