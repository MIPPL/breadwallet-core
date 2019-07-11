/*
 * Created by Michael Carrara <michael.carrara@breadwallet.com> on 5/31/18.
 * Copyright (c) 2018 Breadwinner AG.  All right reserved.
 *
 * See the LICENSE file at the project root for license information.
 * See the CONTRIBUTORS file at the project root for a list of contributors.
 */
package com.breadwallet.corenative.crypto;

import com.breadwallet.corenative.CryptoLibrary;
import com.google.common.base.Optional;

public interface CoreBRCryptoAddress {

    static Optional<CoreBRCryptoAddress> createFromStringAsBtc(String address) {
        return Optional.fromNullable(CryptoLibrary.INSTANCE.cryptoAddressCreateFromStringAsBTC(address)).transform(OwnedBRCryptoAddress::new);
    }

    static Optional<CoreBRCryptoAddress> createFromStringAsEth(String address) {
        return Optional.fromNullable(CryptoLibrary.INSTANCE.cryptoAddressCreateFromStringAsETH(address)).transform(OwnedBRCryptoAddress::new);
    }

    boolean isIdentical(CoreBRCryptoAddress address);

    String toString();

    BRCryptoAddress asBRCryptoAddress();
}
