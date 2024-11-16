// SPDX-License-Identifier: MIT
pragma solidity 0.8.20;

import {BaseTestV2, HorseStoreV2} from "./BaseTestV2.t.sol";
import {HuffDeployer} from "foundry-huff/HuffDeployer.sol";

contract HorseStoreHuffV2 is BaseTestV2 {
    string public constant horseStoreLocation = "V2/HorseStoreV2Working";

    function setUp() public override {
        horseStore = HorseStoreV2(
            HuffDeployer.config().with_args(bytes.concat(abi.encode(NFT_NAME), abi.encode(NFT_SYMBOL))).deploy(
                horseStoreLocation
            )
        );
    }
}
