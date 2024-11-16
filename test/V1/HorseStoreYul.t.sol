// SPDX-License-Identifier: MIT
pragma solidity 0.8.20;

import {HorseStoreYul} from "../../src/V1/HorseStoreYul.sol";
import {BaseTestV1} from "./BaseTestV1.t.sol";
import {HorseStore} from "../../src/V1/HorseStore.sol";
import {IHorseStore} from "../../src/V1/IHorseStore.sol";

contract HorseTestYul is BaseTestV1 {
    function setUp() public override {
        horseStore = new HorseStoreYul();
    }
}
