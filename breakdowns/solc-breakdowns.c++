// 0x6080604052348015600e575f80fd5b5060a58061001b5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea264697066735822122063fb6121e5313b02ef53105a3444f83d87a65e93152c670ffe58b89ff008515764736f6c63430008140033

/////* 1.  Contract Creation    */////

/* Free memory pointer */
// PUSH1 0x80
// PUSH1 0x40
// MSTORE

/* Check msg.value */
// CALLVALUE    // [msg.value]
// DUP1         // [msg.value, msg.value]
// ISZERO       // [1 or 0, msg.value]
// PUSH1 0x0e   // [0x0e, 1 or 0, msg.value]
// JUMPI        // [msg.value] :: Jump to 0x0e if msg.value == 0;

/* msg.value != 0 */
// PUSH0        // [0, msg.value]
// DUP1         // [0, 0, msg.value]
// REVERT       // [msg.value] :: revert because constructor is non-payable

/* 0x0e JUMPDEST*/
/* Puts runtime code on-chain */
// JUMPDEST     // [msg.value]
// POP          // []
// PUSH1 0xa5   // [165]
// DUP1         // [165, 165]
// PUSH2 0x001b // [27, 165, 165]
// PUSH0        // [0, 27, 165, 165]
// CODECOPY     // [165] :: Copy runtime code to memory at location 0, we only want the runtime code which starts from 27th byte and its of size 165 (rest fo bytecode)
// PUSH0        // [0, 165]
// RETURN       // []
// INVALID      // [] :: end of contract creation bytecode

/////* 2.    Runtime code       */////

// PUSH1 0x80
// PUSH1 0x40
// MSTORE
// CALLVALUE
// DUP1
// ISZERO
// PUSH1 0x0e
// JUMPI
// PUSH0
// DUP1
// REVERT
// JUMPDEST
// POP
// PUSH1 0x04
// CALLDATASIZE
// LT
// PUSH1 0x30
// JUMPI
// PUSH0
// CALLDATALOAD
// PUSH1 0xe0
// SHR
// DUP1
// PUSH4 0xcdfead2e
// EQ
// PUSH1 0x34
// JUMPI
// DUP1
// PUSH4 0xe026c017
// EQ
// PUSH1 0x45
// JUMPI
// JUMPDEST
// PUSH0
// DUP1
// REVERT
// JUMPDEST
// PUSH1 0x43
// PUSH1 0x3f
// CALLDATASIZE
// PUSH1 0x04
// PUSH1 0x59
// JUMP
// JUMPDEST
// PUSH0
// SSTORE
// JUMP
// JUMPDEST
// STOP
// JUMPDEST
// PUSH0
// SLOAD
// PUSH1 0x40
// MLOAD
// SWAP1
// DUP2
// MSTORE
// PUSH1 0x20
// ADD
// PUSH1 0x40
// MLOAD
// DUP1
// SWAP2
// SUB
// SWAP1
// RETURN
// JUMPDEST
// PUSH0
// PUSH1 0x20
// DUP3
// DUP5
// SUB
// SLT
// ISZERO
// PUSH1 0x68
// JUMPI
// PUSH0
// DUP1
// REVERT
// JUMPDEST
// POP
// CALLDATALOAD
// SWAP2
// SWAP1
// POP
// JUMP
// INVALID
// LOG2
// PUSH5 0x6970667358
// INVALID
// SLT
// KECCAK256
// PUSH4 0xfb6121e5
// BALANCE
// EXTCODESIZE
// MUL
// INVALID
// MSTORE8
// LT
// GAS
// CALLVALUE
// PREVRANDAO
// INVALID
// RETURNDATASIZE
// DUP8
// INVALID
// MCOPY
// SWAP4
// ISZERO
// INVALID
// PUSH8 0x0ffe58b89ff00851
// JUMPI
// PUSH5 0x736f6c6343
// STOP
// ADDMOD
// EQ
// STOP
// CALLER