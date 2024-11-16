// SPDX-License-Identifier: MIT
pragma solidity 0.8.20;

import {BaseTestV1} from "./BaseTestV1.t.sol";
import {HuffDeployer} from "foundry-huff/HuffDeployer.sol";
import {HorseStore} from "../../src/V1/HorseStore.sol";

contract HorseTestHuffc is BaseTestV1 {
    string public HORSE_STORE_HUFF_PATH = "V1/HorseStoreRaw";

    function setUp() public override {
        horseStore = HorseStore(HuffDeployer.config().deploy(HORSE_STORE_HUFF_PATH));
    }
}
