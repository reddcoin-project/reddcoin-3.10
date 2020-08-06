// Copyright (c) 2012-2013 The PPCoin developers
// Copyright (c) 2014 The Reddcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef REDDCOIN_KERNEL_H
#define REDDCOIN_KERNEL_H

#include "main.h"

// MODIFIER_INTERVAL: time to elapse before new modifier is computed
extern unsigned int nModifierInterval;

// MODIFIER_INTERVAL_RATIO:
// ratio of group interval length between the last group and the first group
static const int MODIFIER_INTERVAL_RATIO = 3;

// Compute the hash modifier for proof-of-stake
bool ComputeNextStakeModifier(const CBlockIndex* pindexPrev, uint64_t& nStakeModifier, bool& fGeneratedStakeModifier);

// Check whether stake kernel meets hash target
// Sets hashProofOfStake on success return
bool CheckStakeKernelHash(unsigned int nBits, const CBlockHeader& blockFrom, unsigned int nTxPrevOffset, const CTransaction& txPrev, const COutPoint& prevout, unsigned int nTimeTx, uint256& hashProofOfStake, uint256& targetProofOfStake, bool fPrintProofOfStake = false);

// Check kernel hash target and coinstake signature
// Sets hashProofOfStake on success return
bool CheckProofOfStake(const CTransaction& tx, unsigned int nBits, uint256& hashProofOfStake, uint256& targetProofOfStake);

// Check whether the coinstake timestamp meets protocol
bool CheckCoinStakeTimestamp(int64_t nTimeBlock, int64_t nTimeTx);

// Get stake modifier checksum
unsigned int GetStakeModifierChecksum(const CBlockIndex* pindex);

// Check stake modifier hard checkpoints
bool CheckStakeModifierCheckpoints(int nHeight, uint64_t nStakeModifierChecksum);

// Get time weight using supplied timestamps
int64_t GetCoinAgeWeight(int64_t nIntervalBeginning, int64_t nIntervalEnd);

// Get transaction coin age
uint64_t GetCoinAge(const CTransaction& tx);

// Calculate total coin age spent in block
uint64_t GetCoinAge(const CBlock& block);

// Calculate the inflation rate for the current block
double GetInflation(const CBlockIndex* pindex);

// Calculate the adjustment to apply to coinstake to align with 5% growth
double GetInflationAdjustment(const CBlockIndex* pindex);

#endif // REDDCOIN_KERNEL_H
