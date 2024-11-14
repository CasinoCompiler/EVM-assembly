// SPDX-License-Identifier: MIT
pragma solidity 0.8.20;

import {HorseStore} from "../../src/V1/HorseStore.sol";
import {Test, console} from "forge-std/Test.sol";

// Make mandatory base tests abstract so they must inherit
abstract contract BaseTestV1 is Test{
    HorseStore public horseStore;
    
    function setUp() public virtual {
        horseStore = new HorseStore();
    }

    function test_UpdateHorseNumber(uint256 expectedUpdatedNumber) public virtual{
        horseStore.updateHorseNumber(expectedUpdatedNumber);
        assertEq(horseStore.readNumberOfHorses(), expectedUpdatedNumber);
    }

    function test_ReadNumberOfHorses() public virtual{
        uint256 expectedInitial = 0;
        assertEq(horseStore.readNumberOfHorses(), expectedInitial);
    }
}