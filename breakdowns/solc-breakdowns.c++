// 0x6080604052348015600e575f80fd5b5060a58061001b5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea264697066735822122063fb6121e5313b02ef53105a3444f83d87a65e93152c670ffe58b89ff008515764736f6c63430008140033

/////* 1.  Contract Creation    */////

/* Free memory pointer */
// PUSH1 0x80
// PUSH1 0x40
// MSTORE

/* Check msg.value */
// CALLVALUE            // [msg.value]
// DUP1                 // [msg.value, msg.value]
// ISZERO               // [1 or 0, msg.value]
// PUSH1 0x0e           // [0x0e, 1 or 0, msg.value]
// JUMPI                // [msg.value] :: Jump to 0x0e if msg.value == 0;

/* msg.value != 0 */
// PUSH0                // [0, msg.value]
// DUP1                 // [0, 0, msg.value]
// REVERT               // [msg.value] :: revert because constructor is non-payable

/* 0x0e JUMPDEST*/
/* Puts runtime code on-chain */
// JUMPDEST             // [msg.value]
// POP                  // []
// PUSH1 0xa5           // [165]
// DUP1                 // [165, 165]
// PUSH2 0x001b         // [27, 165, 165]
// PUSH0                // [0, 27, 165, 165]
// CODECOPY             // [165] :: Copy runtime code to memory at location 0, we only want the runtime code which starts from 27th byte and its of size 165 (rest fo bytecode)
// PUSH0                // [0, 165]
// RETURN               // []
// INVALID              // [] :: end of contract creation bytecode

/////* 2.    Runtime code       */////

// Free memory pointer
// PUSH1 0x80
// PUSH1 0x40
// MSTORE

// Check msg.value
// CALLVALUE            //  [msg.value]
// DUP1                 // [msg.value, msg.value]
// ISZERO               // [1 or 0, msg.value]
// PUSH1 0x0e           // [14, msg.value]
// JUMPI                // [msg.value]
// PUSH0                // [0, msg.value]
// DUP1                 // [0, 0, msg.value]
// REVERT               // [msg.value] :: revert if msg.value != 0

/* JUMPDEST location :: 14 */
/* Check if calldata contains function selector */
// JUMPDEST             // [msg.value]
// POP                  // []
// PUSH1 0x04           // [4] :: function selector is always 4 bytes big.
// CALLDATASIZE         // [calldata_size, 4]
// LT                   // [1 or 0] :: is calldata_siza < 4
// PUSH1 0x30           // [48, 1 or 0]
// JUMPI                // [] :: jump to PC 48 if true

/* Function dispatch */
// PUSH0                // [0]
// CALLDATALOAD         // [calldata, 0]    
// PUSH1 0xe0           // [224, calldata, 0]
// SHR                  // [function_selector, 0]
// DUP1                 // [function_selector, function_selector, 0]
// PUSH4 0xcdfead2e     // [0xcdfead2e, function_selector, function_selector, 0]
// EQ                   // [1 or 0, function_selector, 0]
// PUSH1 0x34           // [52, 1 or 0, function_selector, 0]
// JUMPI                // [function_selector, 0] :: jump to PC 52
// DUP1                 // [function_selector, function_selector, 0]
// PUSH4 0xe026c017     // [0xe026c017, function_selector, function_selector, 0]
// EQ                   // [1 or 0, function_selector, 0]
// PUSH1 0x45           // [69, 1 or 0, function_selector, 0]
// JUMPI                // [function_selector, 0] :: jump to PC 69

/* --> if no valid function selector, the next revert block will stop sequential execution <-- */

/* JUMPDEST PC :: 48 */
/* Solidity just blank reverts as no function selector supplied in calldata and no fallback function for calldata */
// JUMPDEST             // []
// PUSH0                // [0]
// DUP1                 // [0, 0]
// REVERT               // [] :: revert!

/* updateHorseNumber JUMPDEST 1 :: PC 52*/
/* Set up jumping PC in stack */
// JUMPDEST             // [function_selector]
// PUSH1 0x43           // [0x43, function_selector]
// PUSH1 0x3f           // [0x3f, 0x43, function_selector]
// CALLDATASIZE         // [calldata_size, 0x3f, 0x43, function_selector]
// PUSH1 0x04           // [0x04, calldata_size, 0x3f, 0x43, function_selector]
// PUSH1 0x59           // [0x59, 0x04, calldata_size, 0x3f, 0x43, function_selector]
// JUMP                 // [0x04, calldata_size, 0x3f, 0x43, function_selector]

/* updateHorseNumber JUMPDEST 4 :: PC 63 */
/* SStore value */
// JUMPDEST             // [value, 0x43, function_selector]
// PUSH0                // [0, value, 0x43, function_selector]
// SSTORE               // [0x43, function_selector]            // storage: [0: value]
// JUMP                 // [function_selector] :: jump to PC 67

/* updateHorseNumber JUMPDEST 5 :: PC 67 */
// JUMPDEST             // [func_selector]
// STOP                 // stop sequential execution

/* readNumberOfHorses JUMPDEST :: PC 69 */
// JUMPDEST             // [function_selector, 0]
// PUSH0                // [0, function_selector, 0]
// SLOAD                // [numOHorses,function_selector, 0] :: load storage at key : 0
// PUSH1 0x40           // [0x40, numOHorses, function_selector, 0]
// MLOAD                // [0x80, numOHorses, function_selector, 0] :: load memory at free memory pointer into stack
// SWAP1                // [numOHorses, 0x80, function_selector, 0]
// DUP2                 // [0x80, numOHorses, 0x80, function_selector, 0]
// MSTORE               // [0x80, function_selector, 0] :: store numOfHorses in memory at 0x80
// PUSH1 0x20           // [0x20, 0x80, function_selector, 0]
// ADD                  // [0xa0, function_selector, 0] :: 0x20 + 0x80 = 0xa0 = 180
// PUSH1 0x40           // [0x40, 0xa0, function_selector, 0]
// MLOAD                // [0x80, 0xa0, function_selector, 0]
// DUP1                 // [0x80, 0x80, 0xa0, function_selector, 0]
// SWAP2                // [0xa0, 0x80, 0x80, function_selector, 0]
// SUB                  // [0xa0 - 0x80, 0x80, function_selector, 0]
// SWAP1                // [0x80, 0xa0 - 0x80, function_selector, 0]
// --> return a value of size 32 bytes (0xa0 - 0x80) that's located at 0x80 in memory
// RETURN               // [function_selector, 0]

/* updateHorseNumber JUMPDEST 2 :: PC 89 */
/* Check to see if number input within calldata */
// JUMPDEST             // [0x04, calldata_size, 0x3f, 0x43, function_selector]
// PUSH0                // [0, 0x04, calldata_size, 0x3f, 0x43, function_selector]
// PUSH1 0x20           // [0x20, 0, 0x04, calldata_size, 0x3f, 0x43, function_selector]
// DUP3                 // [0x04, 0x20, 0, 0x04, calldata_size, 0x3f, 0x43, function_selector]
// DUP5                 // [calldata_size, 0x04, 0x20, 0, 0x04, calldata_size, 0x3f, 0x43, function_selector]
// SUB                  // [calldata_size - 0x04, 0x20, 0, 0x04, calldata_size, 0x3f, 0x43, function_selector]
// SLT                  // [1 or 0, 0, 0x04, calldata_size, 0x3f, 0x43, function_selector] :: (calldata_size - 0x04) < 0x20 // Checking if there is more data than just the function selector. 1 = true = no
// ISZERO               // [1 or 0, 0, 0x04, calldata_size, 0x3f, 0x43, function_selector]
// PUSH1 0x68           // [0x68, 1 or 0, 0, 0x04, calldata_size, 0x3f, 0x43, function_selector]
// JUMPI                // [0, 0x04, calldata_size, 0x3f, 0x43, function_selector] :: jump to PC 104 if true

/* Revert block if updateHorseNumber called with no input */
// PUSH0                // [0, 0, 0x04, calldata_size, 0x3f, 0x43, function_selector]
// DUP1                 // [0, 0, 0, 0x04, calldata_size, 0x3f, 0x43, function_selector]
// REVERT               // [0, 0x04, calldata_size, 0x3f, 0x43, function_selector] :: revert!

/* updateHorseNumber JUMPDEST 3 :: PC 104 */
/* get value to updateHorseNumber */
// JUMPDEST             // [0, 0x04, calldata_size, 0x3f, 0x43, function_selector]
// POP                  // [0x04, calldata_size, 0x3f, 0x43, function_selector]
// CALLDATALOAD         // [value, calldata_size, 0x3f, 0x43, function_selector] :: calldata - selector = value
// SWAP2                // [0x3f, calldata_size, value, 0x43, function_selector]
// SWAP1                // [calldata_size, 0x3f, value, 0x43, function_selector]
// POP                  // [0x3f, value, 0x43, function_selector]
// JUMP                 // [value, 0x43, function_selector] :: jump to PC 63

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