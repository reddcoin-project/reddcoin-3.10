// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "pow.h"

#include "bignum.h"
#include "chain.h"
#include "chainparams.h"
#include "primitives/block.h"
#include "main.h"
#include "uint256.h"
#include "util.h"

unsigned int static KimotoGravityWell(const CBlockIndex* pindexLast, const CBlockHeader *pblock, uint64_t TargetBlocksSpacingSeconds, uint64_t PastBlocksMin, uint64_t PastBlocksMax)
{
    const CBlockIndex  *BlockLastSolved = pindexLast;
    const CBlockIndex  *BlockReading    = pindexLast;

    uint64_t  PastBlocksMass        = 0;
    int64_t   PastRateActualSeconds = 0;
    int64_t   PastRateTargetSeconds = 0;
    double  PastRateAdjustmentRatio = double(1);
    CBigNum PastDifficultyAverage;
    CBigNum PastDifficultyAveragePrev;
    CBigNum bnProofOfWorkLimit = Params().ProofOfWorkLimit();
    CBigNum bnProofOfStakeLimit = Params().ProofOfStakeLimit();
    CBigNum bnProofOfStakeReset = Params().ProofOfStakeReset();

    double EventHorizonDeviation;
    double EventHorizonDeviationFast;
    double EventHorizonDeviationSlow;

    bool fProofOfStake = false;
    if (pindexLast && pindexLast->nHeight >= Params().LastProofOfWorkHeight())
        fProofOfStake = true;

    if (BlockLastSolved == NULL || BlockLastSolved->nHeight == 0 || (uint64_t)BlockLastSolved->nHeight < PastBlocksMin)
    {
        return bnProofOfWorkLimit.GetCompact();
    }
    else if (fProofOfStake && (uint64_t)(BlockLastSolved->nHeight - Params().LastProofOfWorkHeight()) < PastBlocksMin)
    {
        // difficulty is reset at the first PoSV blocks
        if (Params().AllowMinDifficultyBlocks())
            return bnProofOfStakeLimit.GetCompact();
        else
            return bnProofOfStakeReset.GetCompact();
    }

    for (unsigned int i = 1; BlockReading && BlockReading->nHeight > (fProofOfStake ? Params().LastProofOfWorkHeight() : 0); i++)
    {
        if (PastBlocksMax > 0 && i > PastBlocksMax)
            break;

        PastBlocksMass++;

        if (i == 1)
        {
            PastDifficultyAverage.SetCompact(BlockReading->nBits);
        }
        else
        {
            PastDifficultyAverage = ((CBigNum().SetCompact(BlockReading->nBits) - PastDifficultyAveragePrev) / i) + PastDifficultyAveragePrev;
        }
        PastDifficultyAveragePrev = PastDifficultyAverage;

        PastRateActualSeconds = BlockLastSolved->GetBlockTime() - BlockReading->GetBlockTime();
        PastRateTargetSeconds = TargetBlocksSpacingSeconds * PastBlocksMass;
        PastRateAdjustmentRatio = double(1);

        if (PastRateActualSeconds < 0)
            PastRateActualSeconds = 0;

        if (PastRateActualSeconds != 0 && PastRateTargetSeconds != 0)
            PastRateAdjustmentRatio = double(PastRateTargetSeconds) / double(PastRateActualSeconds);

        EventHorizonDeviation = 1 + (0.7084 * pow((double(PastBlocksMass)/double(144)), -1.228));
        EventHorizonDeviationFast = EventHorizonDeviation;
        EventHorizonDeviationSlow = 1 / EventHorizonDeviation;

        if (PastBlocksMass >= PastBlocksMin)
        {
            if ((PastRateAdjustmentRatio <= EventHorizonDeviationSlow) || (PastRateAdjustmentRatio >= EventHorizonDeviationFast))
            {
                assert(BlockReading);
                break;
            }
        }

        if (BlockReading->pprev == NULL)
        {
            assert(BlockReading);
            break;
        }

        BlockReading = BlockReading->pprev;

    }

    CBigNum bnNew(PastDifficultyAverage);

    if (PastRateActualSeconds != 0 && PastRateTargetSeconds != 0)
    {
        bnNew *= PastRateActualSeconds;
        bnNew /= PastRateTargetSeconds;
    }

    if (!fProofOfStake && bnNew > bnProofOfWorkLimit)
    {
        bnNew = bnProofOfWorkLimit;
    }
    else if (fProofOfStake && bnNew > bnProofOfStakeLimit)
    {
        bnNew = bnProofOfStakeLimit;
    }

     /// debug print
    if (fDebug)
    {
        LogPrintf("Difficulty Retarget - Kimoto Gravity Well\n");
        LogPrintf("PastRateAdjustmentRatio = %g\n", PastRateAdjustmentRatio);
        LogPrintf("Before: %08x  %s\n", BlockLastSolved->nBits, CBigNum().SetCompact(BlockLastSolved->nBits).getuint256().ToString().c_str());
        LogPrintf("After:  %08x  %s\n", bnNew.GetCompact(), bnNew.getuint256().ToString().c_str());
    }

     return bnNew.GetCompact();
}

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock)
{
    // always mine PoW blocks at the lowest diff on testnet
    if (Params().AllowMinDifficultyBlocks() && pindexLast->nHeight < Params().LastProofOfWorkHeight())
        return Params().ProofOfWorkLimit().GetCompact();

    static const int64_t BlocksTargetSpacing = 1 * 60; // 1 Minute
    unsigned int TimeDaySeconds = 60 * 60 * 24;

    int64_t PastSecondsMin = TimeDaySeconds * 0.25;
    int64_t PastSecondsMax = TimeDaySeconds * 7;

    if (pindexLast->nHeight < 6000)
    {
        PastSecondsMin = TimeDaySeconds * 0.01;
        PastSecondsMax = TimeDaySeconds * 0.14;
    }

    uint64_t PastBlocksMin = PastSecondsMin / BlocksTargetSpacing;
    uint64_t PastBlocksMax = PastSecondsMax / BlocksTargetSpacing;

    if (fDebug)
    	LogPrintf("%s : Height = %s (%s) PastBlocksMin = %s, PastBlocksMax = %s \n", __func__, pindexLast->nHeight, pindexLast->GetBlockHash().ToString(), PastBlocksMin, PastBlocksMax);

    return KimotoGravityWell(pindexLast, pblock, BlocksTargetSpacing, PastBlocksMin, PastBlocksMax);
}

bool CheckProofOfWork(uint256 hash, unsigned int nBits)
{
    CBigNum bnTarget;

    if (Params().SkipProofOfWorkCheck())
       return true;

    bnTarget.SetCompact(nBits);

    // Check range
    if (bnTarget <= 0 || bnTarget > Params().ProofOfWorkLimit())
        return error("CheckProofOfWork() : nBits below minimum work");

    // Check proof of work matches claimed amount
    if (hash > bnTarget.getuint256())
        return error("CheckProofOfWork() : hash doesn't match nBits");

    return true;
}

uint256 GetBlockProof(const CBlockIndex& block)
{
    uint256 bnTarget;
    bool fNegative;
    bool fOverflow;
    bnTarget.SetCompact(block.nBits, &fNegative, &fOverflow);
    if (fNegative || fOverflow || bnTarget == 0)
        return 0;
    // We need to compute 2**256 / (bnTarget+1), but we can't represent 2**256
    // as it's too large for a uint256. However, as 2**256 is at least as large
    // as bnTarget+1, it is equal to ((2**256 - bnTarget - 1) / (bnTarget+1)) + 1,
    // or ~bnTarget / (nTarget+1) + 1.
    return (~bnTarget / (bnTarget + 1)) + 1;
}
