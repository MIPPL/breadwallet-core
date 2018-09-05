//
//  BREthereumBCSEvent.c
//  Core
//
//  Created by Ed Gamble on 5/24/18.
//  Copyright (c) 2018 breadwallet LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#include <stdlib.h>
#include "BREthereumBCSPrivate.h"

// ==============================================================================================
//
// Signal/Handle Transaction
//
typedef struct {
    BREvent base;
    BREthereumBCS bcs;
    BREthereumTransaction transaction;
} BREthereumHandleSubmitTransactionEvent;

static void
bcsHandleSubmitTransactionDispatcher (BREventHandler ignore,
                                      BREthereumHandleSubmitTransactionEvent *event) {
    bcsHandleSubmitTransaction(event->bcs,
                               event->transaction);
}

static BREventType handleSubmitTransactionEventType = {
    "BCS: Handle Submit Transaction Event",
    sizeof (BREthereumHandleSubmitTransactionEvent),
    (BREventDispatcher) bcsHandleSubmitTransactionDispatcher
};

extern void
bcsSignalSubmitTransaction (BREthereumBCS bcs,
                            BREthereumTransaction transaction) {
    BREthereumHandleSubmitTransactionEvent event =
    { { NULL, &handleSubmitTransactionEventType}, bcs, transaction };
    eventHandlerSignalEvent(bcs->handler, (BREvent *) &event);
}


// ==============================================================================================
//
// Signal/Handle Announce
//
typedef struct {
    BREvent base;
    BREthereumBCS bcs;
    BREthereumHash headHash;
    uint64_t headNumber;
    UInt256  headTotalDifficulty;
    uint64_t reorgDepth;
} BREthereumHandleAnnounceEvent;

static void
bcsHandleAnnounceDispatcher (BREventHandler ignore,
                             BREthereumHandleAnnounceEvent *event) {
    bcsHandleAnnounce(event->bcs,
                      event->headHash,
                      event->headNumber,
                      event->headTotalDifficulty,
                      event->reorgDepth);
}

static BREventType handleAnnounceEventType = {
    "BCS: Handle Announce Event",
    sizeof (BREthereumHandleAnnounceEvent),
    (BREventDispatcher) bcsHandleAnnounceDispatcher
};

extern void
bcsSignalAnnounce (BREthereumBCS bcs,
                   BREthereumHash headHash,
                   uint64_t headNumber,
                   UInt256 headTotalDifficulty,
                   uint64_t reorgDepth) {
    BREthereumHandleAnnounceEvent event =
    { { NULL, &handleAnnounceEventType}, bcs, headHash, headNumber, headTotalDifficulty, reorgDepth };
    eventHandlerSignalEvent(bcs->handler, (BREvent *) &event);
}

// ==============================================================================================
//
// Signal/Handle Status
//
typedef struct {
    BREvent base;
    BREthereumBCS bcs;
    BREthereumHash headHash;
    uint64_t headNumber;
} BREthereumHandleStatusEvent;

static void
bcsHandleStatusDispatcher (BREventHandler ignore,
                             BREthereumHandleStatusEvent *event) {
    bcsHandleStatus(event->bcs,
                      event->headHash,
                      event->headNumber);
}

static BREventType handleStatusEventType = {
    "BCS: Handle Status Event",
    sizeof (BREthereumHandleStatusEvent),
    (BREventDispatcher) bcsHandleStatusDispatcher
};

extern void
bcsSignalStatus (BREthereumBCS bcs,
                   BREthereumHash headHash,
                   uint64_t headNumber) {
    BREthereumHandleStatusEvent event =
    { { NULL, &handleStatusEventType}, bcs, headHash, headNumber };
    eventHandlerSignalEvent(bcs->handler, (BREvent *) &event);
}

// ==============================================================================================
//
// Signal/Handle Provision
//
typedef struct {
    BREvent base;
    BREthereumBCS bcs;
    BREthereumLES les;
    BREthereumLESNodeReference node;
    BREthereumProvisionResult result;
} BREthereumHandleProvisionEvent;

static void
bcsHandleProvisionDispatcher (BREventHandler ignore,
                                BREthereumHandleProvisionEvent *event) {
    bcsHandleProvision(event->bcs, event->les, event->node, event->result);
}

static void
bcsHandleProvisionDestroyer (BREthereumHandleProvisionEvent *event) {
    // provisionResultRelease(event->result);
}

static BREventType handleProvisionEventType = {
    "BCS: Handle Provision Event",
    sizeof (BREthereumHandleProvisionEvent),
    (BREventDispatcher) bcsHandleProvisionDispatcher,
    (BREventDestroyer) bcsHandleProvisionDestroyer
};

extern void
bcsSignalProvision (BREthereumBCS bcs,
                    BREthereumLES les,
                    BREthereumLESNodeReference node,
                    BREthereumProvisionResult result) {
    BREthereumHandleProvisionEvent event =
    { { NULL, &handleProvisionEventType}, bcs, les, node, result };
    eventHandlerSignalEvent(bcs->handler, (BREvent *) &event);
}


// ==============================================================================================
//
// Signal/Handle Block Header
//
typedef struct {
    BREvent base;
    BREthereumBCS bcs;
    BREthereumBlockHeader header;
} BREthereumHandleBlockHeaderEvent;

static void
bcsHandleBlockHeaderDispatcher (BREventHandler ignore,
                                BREthereumHandleBlockHeaderEvent *event) {
    bcsHandleBlockHeader(event->bcs, event->header);
}

static void
bcsHandleBlockHeaderDestroyer (BREthereumHandleBlockHeaderEvent *event) {
    blockHeaderRelease(event->header);
}

static BREventType handleBlockHeaderEventType = {
    "BCS: Handle Block Header Event",
    sizeof (BREthereumHandleBlockHeaderEvent),
    (BREventDispatcher) bcsHandleBlockHeaderDispatcher,
    (BREventDestroyer) bcsHandleBlockHeaderDestroyer
};

extern void
bcsSignalBlockHeader (BREthereumBCS bcs,
                      BREthereumBlockHeader header) {
    BREthereumHandleBlockHeaderEvent event =
    { { NULL, &handleBlockHeaderEventType}, bcs, header };
    eventHandlerSignalEvent(bcs->handler, (BREvent *) &event);
}

// ==============================================================================================
//
// Signal/Handle Block Bodies
//
typedef struct {
    BREvent base;
    BREthereumBCS bcs;
    BREthereumHash blockHash;
    BREthereumTransaction *transactions;
    BREthereumBlockHeader *ommers;
} BREthereumHandleBlockBodiesEvent;

static void
bcsHandleBlockBodiesDispatcher (BREventHandler ignore,
                                BREthereumHandleBlockBodiesEvent *event) {
    bcsHandleBlockBodies(event->bcs,
                         event->blockHash,
                         event->transactions,
                         event->ommers);
}

static void
bcsHandleBlockBodiesDestroyer (BREthereumHandleBlockBodiesEvent *event) {
    if (NULL != event->transactions) {
        for (size_t index = 0; index < array_count(event->transactions); index++)
            transactionRelease(event->transactions[index]);
        array_free(event->transactions);
    }

    if (NULL != event->ommers) {
        for (size_t index = 0; index < array_count(event->ommers); index++)
            blockHeaderRelease(event->ommers[index]);
        array_free (event->ommers);
    }
}

static BREventType handleBlockBodiesEventType = {
    "BCS: Handle Block Bodies Event",
    sizeof (BREthereumHandleBlockBodiesEvent),
    (BREventDispatcher) bcsHandleBlockBodiesDispatcher,
    (BREventDestroyer) bcsHandleBlockBodiesDestroyer
};

extern void
bcsSignalBlockBodies (BREthereumBCS bcs,
                      BREthereumHash blockHash,
                      BREthereumTransaction transactions[],
                      BREthereumBlockHeader ommers[]) {
    BREthereumHandleBlockBodiesEvent event =
    { { NULL, &handleBlockBodiesEventType}, bcs, blockHash, transactions, ommers };
    eventHandlerSignalEvent(bcs->handler, (BREvent *) &event);
}

// ==============================================================================================
//
// Handle Transaction Status
//
typedef struct {
    BREvent base;
    BREthereumBCS bcs;
    BREthereumHash transactionHash;
    BREthereumTransactionStatus status;
} BREthereumHandleTransactionStatusEvent;

static void
bcsHandleTransactionStatusDispatcher(BREventHandler ignore,
                                     BREthereumHandleTransactionStatusEvent *event) {
    bcsHandleTransactionStatus(event->bcs, event->transactionHash, event->status);
}

static BREventType handleTransactionStatusEventType = {
    "BCS: Handle TransactionStatus Event",
    sizeof (BREthereumHandleTransactionStatusEvent),
    (BREventDispatcher) bcsHandleTransactionStatusDispatcher
};

extern void
bcsSignalTransactionStatus (BREthereumBCS bcs,
                            BREthereumHash transactionHash,
                            BREthereumTransactionStatus status) {
    BREthereumHandleTransactionStatusEvent event =
    { { NULL, &handleTransactionStatusEventType }, bcs, transactionHash, status };
    eventHandlerSignalEvent(bcs->handler, (BREvent*) &event);
}


// ==============================================================================================
//
// Handle Transaction Receipt
//
typedef struct {
    BREvent base;
    BREthereumBCS bcs;
    BREthereumHash blockHash;
    BREthereumTransactionReceipt *receipts;
} BREthereumHandleTransactionReceiptEvent;

static void
bcsHandleTransactionReceiptsDispatcher(BREventHandler ignore,
                                       BREthereumHandleTransactionReceiptEvent *event) {
    bcsHandleTransactionReceipts(event->bcs, event->blockHash, event->receipts);
}

static void
bcsHandleTransactionReceiptsDestroyer (BREthereumHandleTransactionReceiptEvent *event) {
    if (NULL != event->receipts) {
        for (size_t index = 0; index < array_count(event->receipts); index++)
            transactionReceiptRelease(event->receipts[index]);
        array_free(event->receipts);
    }
}

static BREventType handleTransactionReceiptEventType = {
    "BCS: Handle TransactionReceipt Event",
    sizeof (BREthereumHandleTransactionReceiptEvent),
    (BREventDispatcher) bcsHandleTransactionReceiptsDispatcher,
    (BREventDestroyer) bcsHandleTransactionReceiptsDestroyer
};

extern void
bcsSignalTransactionReceipts (BREthereumBCS bcs,
                              BREthereumHash blockHash,
                              BREthereumTransactionReceipt *receipts) {
    BREthereumHandleTransactionReceiptEvent event =
    { { NULL, &handleTransactionReceiptEventType }, bcs, blockHash, receipts };
    eventHandlerSignalEvent(bcs->handler, (BREvent*) &event);
}

// ==============================================================================================
//
// Handle Account State
//
typedef struct {
    BREvent base;
    BREthereumBCS bcs;
    BREthereumAddress address;
    BREthereumHash blockHash;
    BREthereumAccountState state;
} BREthereumHandleAccountStateEvent;

static void
bcsHandleAccountStateDispatcher(BREventHandler ignore,
                                BREthereumHandleAccountStateEvent *event) {
    bcsHandleAccountState(event->bcs, event->address, event->blockHash, event->state);
}

static BREventType handleAccountStateEventType = {
    "BCS: Handle AccountState Event",
    sizeof (BREthereumHandleAccountStateEvent),
    (BREventDispatcher) bcsHandleAccountStateDispatcher
};

extern void
bcsSignalAccountState (BREthereumBCS bcs,
                       BREthereumAddress address,
                       BREthereumHash blockHash,
                       BREthereumAccountState state) {
    BREthereumHandleAccountStateEvent event =
    { { NULL, &handleAccountStateEventType }, bcs, address, blockHash, state };
    eventHandlerSignalEvent(bcs->handler, (BREvent*) &event);
}


// ==============================================================================================
//
// Signal/Handle Transaction
//
typedef struct {
    BREvent base;
    BREthereumBCS bcs;
    BREthereumTransaction transaction;
} BREthereumHandleTransactionEvent;

static void
bcsHandleTransactionDispatcher (BREventHandler ignore,
                                BREthereumHandleTransactionEvent *event) {
    bcsHandleTransaction(event->bcs, event->transaction);
}

static BREventType handleTransactionEventType = {
    "BCS: Handle Transaction Event",
    sizeof (BREthereumHandleTransactionEvent),
    (BREventDispatcher) bcsHandleTransactionDispatcher
};

extern void
bcsSignalTransaction (BREthereumBCS bcs,
                      BREthereumTransaction transaction) {
    BREthereumHandleTransactionEvent event =
    { { NULL, &handleTransactionEventType}, bcs, transaction };
    eventHandlerSignalEvent(bcs->handler, (BREvent *) &event);
}

// ==============================================================================================
//
// Signal/Handle Log
//
typedef struct {
    BREvent base;
    BREthereumBCS bcs;
    BREthereumLog log;
} BREthereumHandleLogEvent;

static void
bcsHandleLogDispatcher (BREventHandler ignore,
                        BREthereumHandleLogEvent *event) {
    bcsHandleLog(event->bcs,
                 event->log);
}

static BREventType handleLogEventType = {
    "BCS: Handle Log Event",
    sizeof (BREthereumHandleLogEvent),
    (BREventDispatcher) bcsHandleLogDispatcher
};

extern void
bcsSignalLog (BREthereumBCS bcs,
              BREthereumLog log) {
    BREthereumHandleLogEvent event =
    { { NULL, &handleLogEventType}, bcs, log };
    eventHandlerSignalEvent(bcs->handler, (BREvent *) &event);
}

// ==============================================================================================
//
// Signal/Handle Peers
//
typedef struct {
    BREvent base;
    BREthereumBCS bcs;
    BRArrayOf(BREthereumLESNodeConfig) nodes;
} BREthereumHandleNodesEvent;

static void
bcsHandleNodesDispatcher (BREventHandler ignore,
                          BREthereumHandleNodesEvent *event) {
    bcsHandleNodes(event->bcs, event->nodes);
}

static void
bcsHandleNodesDestroyer (BREthereumHandleNodesEvent *event) {
    if (NULL != event->nodes) {
        for (size_t index = 0; index < array_count(event->nodes); index++)
            lesNodeConfigRelease(event->nodes[index]);
        array_free(event->nodes);
    }
}

static BREventType handleNodesEventType = {
    "BCS: Handle Nodes Event",
    sizeof (BREthereumHandleNodesEvent),
    (BREventDispatcher) bcsHandleNodesDispatcher,
    (BREventDestroyer) bcsHandleNodesDestroyer
};

extern void
bcsSignalNodes (BREthereumBCS bcs,
                BRArrayOf(BREthereumLESNodeConfig) nodes) {
    BREthereumHandleNodesEvent event =
    { { NULL, &handleNodesEventType}, bcs, nodes};
    eventHandlerSignalEvent (bcs->handler, (BREvent *) &event);
}

//
// MARK: - SyncProgress
//
// ==============================================================================================
//
// Sync Signal/Handle Block Header
//
typedef struct {
    BREvent base;
    BREthereumBCSSyncRange range;
    BREthereumBlockHeader header;
} BREthereumBCSSyncHandleBlockHeaderEvent;

static void
bcsSyncHandleBlockHeaderDispatcher (BREventHandler ignore,
                                    BREthereumBCSSyncHandleBlockHeaderEvent *event) {
    bcsSyncHandleBlockHeader(event->range, event->header);
}

static void
bcsSyncHandleBlockHeaderDestroyer (BREthereumBCSSyncHandleBlockHeaderEvent *event) {
//    blockHeaderRelease(event->header);
}

static BREventType handleSyncBlockHeaderEventType = {
    "BCS: Sync Handle Block Header Event",
    sizeof (BREthereumBCSSyncHandleBlockHeaderEvent),
    (BREventDispatcher) bcsSyncHandleBlockHeaderDispatcher,
    (BREventDestroyer) bcsSyncHandleBlockHeaderDestroyer
};

extern void
bcsSyncSignalBlockHeader (BREthereumBCSSyncRange range,
                          BREthereumBlockHeader header) {
    BREthereumBCSSyncHandleBlockHeaderEvent event =
    { { NULL, &handleSyncBlockHeaderEventType}, range, header };
    eventHandlerSignalEvent (bcsSyncRangeGetHandler(range), (BREvent *) &event);
}

// ==============================================================================================
//
// Sync Handle Account State
//
typedef struct {
    BREvent base;
    BREthereumBCSSyncRange range;
    BREthereumAddress address;
    BREthereumHash blockHash;
    BREthereumAccountState account;
} BREthereumBCSSyncHandleAccountStateEvent;

static void
bcsSyncHandleAccountStateDispatcher(BREventHandler ignore,
                                    BREthereumBCSSyncHandleAccountStateEvent *event) {
    bcsSyncHandleAccountState(event->range, event->address, event->blockHash, event->account);
}

static BREventType handleSyncAccountStateEventType = {
    "BCS: Sync Handle AccountState Event",
    sizeof (BREthereumBCSSyncHandleAccountStateEvent),
    (BREventDispatcher) bcsSyncHandleAccountStateDispatcher
};

extern void
bcsSyncSignalAccountState (BREthereumBCSSyncRange range,
                           BREthereumAddress address,
                           BREthereumHash blockHash,
                           BREthereumAccountState account) {
    BREthereumBCSSyncHandleAccountStateEvent event =
    { { NULL, &handleSyncAccountStateEventType }, range, address, blockHash, account };
    eventHandlerSignalEvent (bcsSyncRangeGetHandler(range), (BREvent*) &event);
}


// ==============================================================================================
//
// Suync Signal/Handle Provision
//
typedef struct {
    BREvent base;
    BREthereumBCSSyncRange range;
    BREthereumLES les;
    BREthereumLESNodeReference node;
    BREthereumProvisionResult result;
} BREthereumBCSSyncHandleProvisionEvent;

static void
bcsSyncHandleProvisionDispatcher (BREventHandler ignore,
                                  BREthereumBCSSyncHandleProvisionEvent *event) {
    bcsSyncHandleProvision(event->range, event->les, event->node, event->result);
}

static void
bcsSyncHandleProvisionDestroyer (BREthereumHandleProvisionEvent *event) {
    // provisionResultRelease(event->result);
}

static BREventType handleSyncProvisionEventType = {
    "BCS: Sync Handle Provision Event",
    sizeof (BREthereumBCSSyncHandleProvisionEvent),
    (BREventDispatcher) bcsSyncHandleProvisionDispatcher,
    (BREventDestroyer) bcsSyncHandleProvisionDestroyer
};

extern void
bcsSyncSignalProvision (BREthereumBCSSyncRange range,
                    BREthereumLES les,
                    BREthereumLESNodeReference node,
                    BREthereumProvisionResult result) {
    BREthereumBCSSyncHandleProvisionEvent event =
    { { NULL, &handleSyncProvisionEventType }, range, les, node, result };
    eventHandlerSignalEvent(bcsSyncRangeGetHandler(range), (BREvent *) &event);
}

// ==============================================================================================
//
// BCS Event Types
//
const BREventType *
bcsEventTypes[] = {
    &handleSubmitTransactionEventType,
    &handleAnnounceEventType,
    &handleStatusEventType,
    &handleProvisionEventType,
    &handleBlockHeaderEventType,
    &handleBlockBodiesEventType,
    &handleTransactionStatusEventType,
    &handleTransactionReceiptEventType,
    &handleAccountStateEventType,
    &handleTransactionEventType,
    &handleLogEventType,
    &handleNodesEventType,
    &handleSyncBlockHeaderEventType,
    &handleSyncAccountStateEventType,
    &handleSyncProvisionEventType
};

const unsigned int
bcsEventTypesCount = (sizeof (bcsEventTypes) / sizeof(BREventType*)); //  11
