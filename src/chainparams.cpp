// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

// What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
	boost::assign::map_list_of
	(     10, uint256("0xa198c38a77555a9fbff0b147bf7ce0660416d6abdaa86adaa3a9be97092592ed"))
	(   1000, uint256("0x9d849e078deac30d58372db898318186cf5073a7f0b109b4776393b21b7b4e5a"))
	(   2000, uint256("0x4674c50137c1d9bf47d96dee5e8c38c41895d494a0bb71e243d1c8a6c805e1f7"))
	(   3000, uint256("0x0deff246b8dfc102ccdbc3a306649be82c441e1da0fba8ca1075cf6b5d7f3c01"))
	(   4000, uint256("0xad880a4c23d511f04311e98ee77f5163e54cd92f80433e9f3bd6bc2261d50592"))
	(   5000, uint256("0x3f673ef045f4a7d71fb841ce96ed190b20569182bd3dfe628527ec3a7934d08f"))
	(   6000, uint256("0x1222056e58dce70c0a6638e07415bd6190fa5ccdd6d5e7f6af68abb30ebd4eb8"))
	(   6150, uint256("0xe221b12cf8b0c264697e9bb3c9c9f0f7ada5f2736e054cbd53b94852908cdbd3"))
	(  10000, uint256("0x35d5f9cbd94c15771d5ebebf55ea4bfc649c473c0a868fe4d1832f5b45bd5d0c"))
	(  15000, uint256("0x87a8c4289e661720095f2ab6a077151bc84b9615a53c5e7207ba1c20418bd178"))
	(  20000, uint256("0x6a86a4cbbcea694027591ba416ae3831b4f3f9aa3cc6a0a1b5627f920dd765bb"))
	(  44878, uint256("0xd81a3724a81b78e762821d16bfe23565576905685b2c072ea9a3fa7d36dbad8b"))
	(  45189, uint256("0xd10b5da162b922d3cf09c44ea3d533a203c9ab1c442015d7e72f21062d20aeb4"))
	(  45239, uint256("0xe14dba7c7d1ed1a7566e23b0ca0989e3e26099b7beaa673d324001d1291223f7"))
	( 114834, uint256("0xdc5c776ca006c6d40e48c90aeeb43bf6493de589e28f779b486e64aa3403344a"))
	( 184000, uint256("0xe22e6b027cd49cd9aa2ba6df0e0c264c2eed5656b1fa39052c8235d52f2b04d6"))
	( 244999, uint256("0x0b7bb56edfae2f2f1e71ac39daab16614fccf1a1e02c58d4169521d76d880b42"))
	( 285319, uint256("0x4cc87e04718ecc7972f7639481002cd6f4c8f37846390cb50007eddccb64c73c"))
	( 325639, uint256("0x77a09ff950d4a25325395ca9b90b1bfb9b00a9b9eb7beb919c9bcbebe9ced05f"))
	( 365959, uint256("0xc54de093f57aed303a8cf23752a62f724f4e92605680a41be1d7bad71be69206"))
	( 406279, uint256("0x2fb13b9504d3e5817b12b2e7291256a1c5cbdc327ea4b232558142a96bc4cffd"))
	( 446599, uint256("0x7748fb2b7058c4001ef37a6bd8067f2314cb96acc4603fb2c35eb3d1595b3c78"))
	( 486919, uint256("0xf751a1cfe32c1cfddbd5db4d925a1f45f3a6ab680afcd82c8e37c5df4bcb5294"))
	( 527239, uint256("0x476aa826c0a4f61edc66684aa3be1d22e21363262710f944e1cb69052116841e"))
	( 567559, uint256("0x334db8b00ce5ae2202d02beaaca028d9082b0d3415ca29b3f4b164306d99d11f"))
	( 607879, uint256("0x1f97ac7d62896aef736c13918a8a63854c55c1b3b4aea668fa68a475a6ce5d1c"))
	( 648199, uint256("0xbc28b257140edd7823c3c68527d8f659c2cded7e72b9e2d8b1b451e2a583b71c"))
	( 688519, uint256("0x6be18349c18743418a2ae44d9e59fd7e44af0dd118836e3ac3997ceaca7fb06e"))
	( 728839, uint256("0xffde2f99b00291f5972215e196a3ed0f95f7993e692e5f189c0ac5b6dc48c21e"))
	( 769159, uint256("0xe30e85d460eafa3787bc46b91dca3795aa47196fa4e2a4294033dffb2e995605"))
	( 809479, uint256("0xfe410999f834c8ec50935789f98e0e8b91ae9ae6c6f2153f047e2763b7c2696f"))
	( 849799, uint256("0x59b8677a52fd5c487185c08bd7f7a2d957d7e407c2a1e3d1570f2c90e2a14740"))
	( 890119, uint256("0xa20cf4b103dc081f4e57fa17b3a7a3d42d973d2da070bff2c83b2cb9b17f67cb"))
	( 930439, uint256("0xb65e5bb7b7973ddc87db097833c5bb7ee563495702d21e3b92cdf4538e6313ea"))
	( 970759, uint256("0xfe377082ffa049df27761c55c54b3bae58d4b9b52f04a514164e21a2d71dad1a"))
	(1011079, uint256("0x2c667186705704e64d2acc7331e30f72d79b76f34d6c19ab59e8bec0317ae10b"))
	(1051399, uint256("0x94d1c7526079f885cc62a7a9c58a7b4ee1624c15a7352bddce092fb7cc3ca520"))
	(1091719, uint256("0x8456b8b6d1eef1ca71d176e49948b5125c38ac413797674c8fcf0691a2f875ca")) //use this checkpoint as start when calculating
	(1092493, uint256("0x84216243e68638814a7400367aef99716ec48d2b436c42417c0d147651b6a6b0")) //remove this check point for next batch
	;
static const Checkpoints::CCheckpointData data = {
	&mapCheckpoints,
	1457090077, // * UNIX timestamp of last checkpoint block
	3950973,    // * total number of transactions between genesis and last checkpoint
				//   (the tx=... number in the SetBestChain debug.log lines)
	8000.0      // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
	boost::assign::map_list_of
	//( 0, uint256("0xa12ac9bd4cd26262c53a6277aafc61fe9dfe1e2b05eaa1ca148a5be8b394e35a"))
	(      0, uint256("0xa12ac9bd4cd26262c53a6277aafc61fe9dfe1e2b05eaa1ca148a5be8b394e35a"))
	(  40320, uint256("0xd6455e345f00791a76ccb8159efa7bd92c24dc89183f2c8db46735b121af4abd"))
	(  80640, uint256("0xba509693115a82fc2f6282034dc587f28d4d160f87a477d78653fcf4ea7e8d48"))
	( 120960, uint256("0x419ad8a5f1797c338caf42306141baa82789e36bbc340d9a4a6bd91a7c24a7ad"))
	( 161280, uint256("0x0099cf9699e240d7426b4b8dc35a8cdab13e945d9108300fbb43772b3432a2b0"))
	;
static const Checkpoints::CCheckpointData dataTestnet = {
	&mapCheckpointsTestnet,
	1456668199, // * UNIX timestamp of last checkpoint block
	322625,     // * total number of transactions between genesis and last checkpoint
				//   (the tx=... number in the SetBestChain debug.log lines)
	2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
	boost::assign::map_list_of
	( 0, uint256("0x0472dc040de80ded8bd385a2b6bc6e4e05cb6432047efa07692724c6ccef40ac"))
	;
static const Checkpoints::CCheckpointData dataRegtest = {
	&mapCheckpointsRegtest,
	1401051600,
	1,
	10
};
class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xdb;
        vAlertPubKey = ParseHex("0437b4b0f5d356f205c17ffff6c46dc9ec4680ffb7f8a9a4e6eebcebd5f340d01df00ef304faea7779d97d8f1addbe1e87308ea237aae3ead96e0a736c7e9477a1");
        nDefaultPort = 45444;
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
        nTargetTimespan = 24 * 60 * 60; // 24 hours
        nTargetSpacing = 60; // 1 minute

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
        CMutableTransaction txNew;
        txNew.nTime = 1390280400;
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

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultCheckMemPool = false;
        fAllowMinDifficultyBlocks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return data;
    }
};
static CMainParams mainParams;

//
// Testnet (v3)
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfe;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0xb9;
        pchMessageStart[3] = 0xde;
        vAlertPubKey = ParseHex("048b75ab041ee9965f6f57ee299395c02daf5105f208fc49e908804aad3ace5a77c7f87b3aae74d6698124f20c3d1bea31c9fcdd350c9c61c0113fd988ecfb5c09");
        nDefaultPort = 55444;
        nEnforceBlockUpgradeMajority = 510;
        nRejectBlockOutdatedMajority = 750;
        nToCheckBlockUpgradeMajority = 1000;
        nEnforceBlockUpgradeMajority_4 = 510;
        nRejectBlockOutdatedMajority_4 = 750;
        nToCheckBlockUpgradeMajority_4 = 1000;
        nEnforceBlockUpgradeMajority_5 = 510;
        nRejectBlockOutdatedMajority_5 = 750;
        nToCheckBlockUpgradeMajority_5 = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 24 * 60 * 60; // 24 hours
        nTargetSpacing = 60; // 1 minute

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

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultCheckMemPool = false;
        fAllowMinDifficultyBlocks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
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
        nTargetTimespan = 24 * 60 * 60; // 24 hours
        nTargetSpacing = 60; // 1 minute
        bnProofOfWorkLimit = bnProofOfStakeLimit = CBigNum(~uint256(0) >> 1);
        nLastProofOfWorkHeight = 350 - 1;
        genesis.nTime = 1401051600;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 3;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 56444;
        assert(hashGenesisBlock == uint256("0x0472dc040de80ded8bd385a2b6bc6e4e05cb6432047efa07692724c6ccef40ac"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultCheckMemPool = true;
        fAllowMinDifficultyBlocks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

//
// Unit test
//
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18445;
        vFixedSeeds.clear();
        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultCheckMemPool = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    // Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultCheckMemPool(bool afDefaultCheckMemPool)  { fDefaultCheckMemPool=afDefaultCheckMemPool; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectBaseParams(network);
    SelectParams(network);
    return true;
}
