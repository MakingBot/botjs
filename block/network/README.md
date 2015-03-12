Network Block
=============




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
|    String   |   Core Tag   |       N      |

##### NET_TEST

This message require a TCP connection

- Dev Core: Send 1022 bytes data to the bot core and wait for the return of every data.
- Bot Core: Send back the message to the emitter.

|     Type    |     Value    | Size (bytes) |
|:-----------:|:------------:|:------------:|
| MessageType |   NET_TEST   |       2      |
|    String   |     Data     |     1022     |

##### NET_BLOCK_CREATE

This message require a TCP connection. It request a block creation in the receiver core. The father of the new block must be already created.

|     Type    |     Value        | Size (bytes) |
|:-----------:|:----------------:|:------------:|
| MessageType | NET_BLOCK_CREATE |       2      |
|    String   |     Block Type   |       N      |
|    String   |     Id Chain     |       N      |

##### NET_BLOCK_UPDATE

This message require a TCP connection. It request a block update in the receiver core. The block must be already created.

|     Type    |       Value      | Size (bytes) |
|:-----------:|:----------------:|:------------:|
| MessageType | NET_BLOCK_UPDATE |       2      |
| Data Stream |   Block Config   |       N      |

##### NET_BLOCK_UPDATE_I_PROPERTY

This message require a TCP connection.

|     Type    |       Value      | Size (bytes) |
|:-----------:|:----------------:|:------------:|
| MessageType | NET_BLOCK_UPDATE_I_PROPERTY |       2      |
|  uint32   |   Id Nb Block    |       4      |
|  uint8   |   Id Property    |       4      |
|  uint32   |   Value    |       N      |
... List
|  uint32   |   Id Nb Block    |       4      |
|  uint8   |   Id Property    |       4      |
|  uint32   |   Value    |       N      |



##### NET_BLOCK_CONNECT

This message require a TCP connection. It request a block connection in the receiver core. Blocks must be already created.

|     Type    |        Value      | Size (bytes) |
|:-----------:|:-----------------:|:------------:|
| MessageType | NET_BLOCK_CONNECT |       2      |
|    uint32   |   Id Nb Block 1   |       4      |
|    uint32   |   Id Nb Block 2   |       4      |

##### NET_BLOCK_DISCONNECT

This message require a TCP connection. It request a block disconnection in the receiver core. Blocks must be already created.

|     Type    |         Value        | Size (bytes) |
|:-----------:|:--------------------:|:------------:|
| MessageType | NET_BLOCK_DISCONNECT |       2      |
|    uint32   |   Id Nb Block 1      |       4      |
|    uint32   |   Id Nb Block 2      |       4      |

##### NET_BLOCK_DESTROY

This message require a TCP connection. It request a block destruction in the receiver core. Block must be already created.

|     Type    |     Value         | Size (bytes) |
|:-----------:|:-----------------:|:------------:|
| MessageType | NET_BLOCK_DESTROY |       2      |
|    uint32   |   Id Nb Block     |       4      |

