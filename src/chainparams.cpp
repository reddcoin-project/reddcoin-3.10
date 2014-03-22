// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0xc6c74b0a, 0x6baafdeb, 0xa2f3d1bc, 0xbce287b5, 0xbce287b8, 0x688361e5, 0xb23e116a, 0x80c789bb,
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xdb;
        vAlertPubKey = ParseHex("0437b4b0f5d356f205c17ffff6c46dc9ec4680ffb7f8a9a4e6eebcebd5f340d01df00ef304faea7779d97d8f1addbe1e87308ea237aae3ead96e0a736c7e9477a1");
        nDefaultPort = 45444;
        nRPCPort = 45443;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 210000;
        nEnforceBlockUpgradeMajority = 9500;
        nRejectBlockOutdatedMajority = 9500;
        nToCheckBlockUpgradeMajority = 10000;
        nEnforceBlockUpgradeMajority_4 = 6120;
        nRejectBlockOutdatedMajority_4 = 6120;
        nToCheckBlockUpgradeMajority_4 = 7200;
        nEnforceBlockUpgradeMajority_5 = 9000;
        nRejectBlockOutdatedMajority_5 = 9000;
        nToCheckBlockUpgradeMajority_5 = 10000;
        nMinerThreads = 0;

        // PoSV
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeReset = CBigNum(~uint256(0) >> 32); // 1
        nLastProofOfWorkHeight = 260800 - 1;
        vDevPubKey = ParseHex("03c8fc5c87f00bcc32b5ce5c036957f8befeff05bf4d88d2dcde720249f78d9313");
        nStakeMinAge = 8 * 60 * 60; // 8 hours
        nStakeMaxAge = 45 * 24 *  60 * 60; // 45 days

        // Genesis Block:
        // CBlock(hash=12a765e31ffd4059bada, PoW=0000050c34a64b415b6b, ver=1, hashPrevBlock=00000000000000000000, hashMerkleRoot=97ddfbbae6, nTime=1317972665, nBits=1e0ffff0, nNonce=2084524493, vtx=1)
        //   CTransaction(hash=97ddfbbae6, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //     CTxIn(COutPoint(0000000000, -1), coinbase 04ffff001d0104404e592054696d65732030352f4f63742f32303131205374657665204a6f62732c204170706c65e280997320566973696f6e6172792c2044696573206174203536)
        //     CTxOut(nValue=50.00000000, scriptPubKey=040184710fa689ad5023690c80f3a4)
        //   vMerkleTree: 97ddfbbae6
        const char* pszTimestamp = "January 21st 2014 was such a nice day...";
        CTransaction txNew(1390280400);
        txNew.nVersion = 1;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 10000 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1390280400;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 222583475;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xb868e0d95a3c3c0e0dadc67ee587aaf9dc8acbf99e3b4b3110fad4eb74c1decc"));
        assert(genesis.hashMerkleRoot == uint256("0xb502bc1dc42b07092b9187e92f70e32f9a53247feae16d821bebffa916af79ff"));

        vSeeds.push_back(CDNSSeedData("reddcoin.com", "seed.reddcoin.com"));
        vSeeds.push_back(CDNSSeedData("dnsseed01.redd.ink", "dnsseed01.redd.ink"));
        vSeeds.push_back(CDNSSeedData("dnsseed02.redd.ink", "dnsseed02.redd.ink"));
        vSeeds.push_back(CDNSSeedData("dnsseed03.redd.ink", "dnsseed03.redd.ink"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,61);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,189);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfe;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0xb9;
        pchMessageStart[3] = 0xde;
        vAlertPubKey = ParseHex("048b75ab041ee9965f6f57ee299395c02daf5105f208fc49e908804aad3ace5a77c7f87b3aae74d6698124f20c3d1bea31c9fcdd350c9c61c0113fd988ecfb5c09");
        nDefaultPort = 55444;
        nRPCPort = 55443;
        nEnforceBlockUpgradeMajority = 510;
        nRejectBlockOutdatedMajority = 750;
        nToCheckBlockUpgradeMajority = 1000;
        nEnforceBlockUpgradeMajority_4 = 510;
        nRejectBlockOutdatedMajority_4 = 750;
        nToCheckBlockUpgradeMajority_4 = 1000;
        nEnforceBlockUpgradeMajority_5 = 510;
        nRejectBlockOutdatedMajority_5 = 750;
        nToCheckBlockUpgradeMajority_5 = 1000;
        strDataDir = "testnet3";
        nLastProofOfWorkHeight = 350 - 1; // Last POW block
        vDevPubKey = ParseHex("03081542439583f7632ce9ff7c8851b0e9f56d0a6db9a13645ce102a8809287d4f");

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        // CTransaction txGenesis = genesis.vtx[0];
        genesis.nTime = 1446002303;
        // genesis.vtx[0] = txGenesis;
        genesis.nNonce = 2108003;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xa12ac9bd4cd26262c53a6277aafc61fe9dfe1e2b05eaa1ca148a5be8b394e35a"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("reddcoin.com", "testnet-seed.reddcoin.com"));
        vSeeds.push_back(CDNSSeedData("redd.ink", "testnet-dnsseed.redd.ink"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
    }

    virtual bool AllowMinDifficultyBlocks() const { return true; }
    virtual bool RequireStandard() const { return false; }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xff;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0xba;
        pchMessageStart[3] = 0xdf;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 510;
        nRejectBlockOutdatedMajority = 750;
        nToCheckBlockUpgradeMajority = 1000;
        nEnforceBlockUpgradeMajority_4 = 510;
        nRejectBlockOutdatedMajority_4 = 750;
        nToCheckBlockUpgradeMajority_4 = 1000;
        nEnforceBlockUpgradeMajority_5 = 510;
        nRejectBlockOutdatedMajority_5 = 750;
        nToCheckBlockUpgradeMajority_5 = 1000;
        nMinerThreads = 1;
        bnProofOfWorkLimit = bnProofOfStakeLimit = CBigNum(~uint256(0) >> 1);
        nLastProofOfWorkHeight = 350 - 1;
        genesis.nTime = 1401051600;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 3;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 56444;
        strDataDir = "regtest";
        assert(hashGenesisBlock == uint256("0x0472dc040de80ded8bd385a2b6bc6e4e05cb6432047efa07692724c6ccef40ac"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual bool MiningRequiresPeers() const { return false; }
    virtual bool MineBlocksOnDemand() const { return true; }
    virtual bool DefaultCheckMemPool() const { return true; }
    virtual bool RequireStandard() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
