// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2019 The SucreCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x00000333fbaacf8b1c30da72491e893a2a1e92703a0765f14bb3ba44921b3b0e"))
    (482906, uint256("0x3b04e322705806a846d42c234fb6d700a3e2e291dcc373286176d82ec2d5f919"))
    (482898, uint256("0x59f7e8b5f59554d8ff8cf68e65e012366286449e0dbb98e341ad6b1ce4db1158"))
    (482885, uint256("0x2fe8009ec6012788cc2a3cb12a7674f4c375d8cc68ffac37edebba54e8ef2fe3"))
    (482864, uint256("0xaeb7df994d1182d9ed53b43ba1dbf879281aaee0acde781b89f79d2fe32b69db"))
    (482830, uint256("0x9c4ef64b9e81e607202fa5a9c404a0189c8736a70b0253f1bad108b2f4887c63"))
    (482775, uint256("0x87dbc2dee7cd83d8da8a2404d326c8271832dcba52e7e482782a0e0871f4fe50"))
    (482686, uint256("0xc197f9257cba2a15af05f0afd620e3f295cd8384d5708e994567c85adf64cf79"))
    (482542, uint256("0x10665a3950e536b7aa3cbbc23fd97fe4bf1c14646aaa9c29770fbcdea466945a"))
    (482309, uint256("0xdd10d7a1b81c25931a22eda9d4501630e3e9501f226075d03ffde3280f38294e"))
    (481932, uint256("0x3d1cea47c9b129612e26f2c7483542834774fd1ea0add60be2f9fd51dd49492a"))
    (481322, uint256("0x2ac9ad1d79b305b1c84e3df1cf72849b40934ea163592cd120460a9d2bcfbde3"))
    (480335, uint256("0x7ad9e1be5d2e1c508e528b7c768d2c4d2fe8f03f8fc25a037155ea5d43e502e2"))
    (478738, uint256("0xca5c25040b38b735c1f3e5ee2a65f85324e6ada089b1306f8f7ef6241321a995"))
    (476154, uint256("0xf14daf18f07f43c17cd07e4c8e18341831e1b96a702aacfb357d004304697d17"))
    (471973, uint256("0xda900f8db93e90410f87af6e5cba6660936a047009e5c9ed1770a931fd9cc280"))
    (465208, uint256("0x3199e35ced51acd5d0815644c255dadccecb990b9e8d59ad3d50acf6d47d648b"))
    (454262, uint256("0x6c3e814ec13261bd6f5bbf862dfb2e2a0d95093c9fb7860fda091ff0a6761988"))
    (436551, uint256("0xbf07c2ca9d88e3d03786a3f9131b20a8308020c14c44ec3bf2f1d3240c5853f8"))
    (407894, uint256("0xf2a4a70f7601c65fb1616547829e52a4692efcfc1f9651fc0332cce736adc185"))
    (361526, uint256("0x4af62690ef0e90ebc545dfe6cbe2ec258bdd75eec304c461b7772d05c505a276"))
    (286501, uint256("0x6f432853b9627af8a8740b5b132c7dc79e4afce6041edeaedce9c5ea4ab3b0ba"))
    (165108, uint256("0x44283fa440ac261bff2857e6ed34cd74d787f383fdc8cb05d664ecdc133c1f1b"))
    ;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1587807440, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1570470324,
    0,
    250
};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1570470444,
    0,
    100
};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x01;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0xfd;
        pchMessageStart[3] = 0x1a;
        vAlertPubKey = ParseHex("04931651bdaf8a51875470d48429af836dca915fc4d002698120c8d365f26cef2111405c702ec887a12915f3bad08c2eb2260c280664a743446d36bf3ee523f86e");
        nDefaultPort = 2108;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // XSR starting difficulty is 1 / 2^12
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // XSR: 1 day
        nTargetSpacing = 1 * 60;  // XSR: 1 minute
        nMaturity = 80;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 21000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 1000;
        nModifierUpdateBlock = 100;
        nEnforceNewSporkKey = 1587807440;
        nRejectOldSporkKey = 1587807440;

        const char* pszTimestamp = "Bitcoin_627544_000000000000000000045a465b959072a715f47047141108ef14db64e2ee9049";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 250 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0466f8e042492f7e1be50f8fa84bc2d39d0cea242704d219bc6d9cd7d1e20c4abc105e45b0510396978c22a7e9f35d21d6fb10005fc27febc2851ba4f051411865") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1587807440;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1167247;

        hashGenesisBlock = genesis.GetHash();


        assert(hashGenesisBlock == uint256("0x00000333fbaacf8b1c30da72491e893a2a1e92703a0765f14bb3ba44921b3b0e"));
        assert(genesis.hashMerkleRoot == uint256("0x6f62f2fde05b54e306ec25e3f0512d230652b88f0a90b9161238c56dd6067ad1"));

        vFixedSeeds.clear();

        vSeeds.push_back(CDNSSeedData("ecuador", "ecuador.sucrecoin.org"));
        vSeeds.push_back(CDNSSeedData("colombia", "colombia.sucrecoin.org"));
        vSeeds.push_back(CDNSSeedData("costarica", "costarica.sucrecoin.org"));
        vSeeds.push_back(CDNSSeedData("dev", "dev.sucrecoin.org")); 
        vSeeds.push_back(CDNSSeedData("node1", "node1.sucrecoin.org"));
        vSeeds.push_back(CDNSSeedData("node", "node.sucrecoin.org"));
        vSeeds.push_back(CDNSSeedData("pos", "pos.sucrecoin.org")); 
        vSeeds.push_back(CDNSSeedData("lik", "lik.sucrecoin.org")); 
        vSeeds.push_back(CDNSSeedData("explorer", "explorer.sucrecoin.org"));
        vSeeds.push_back(CDNSSeedData("master", "master.sucrecoin.org")); 
        // temp nodes
        vSeeds.push_back(CDNSSeedData("seed1", "217.61.122.125"));
        vSeeds.push_back(CDNSSeedData("seed2", "217.61.124.183"));
        vSeeds.push_back(CDNSSeedData("seed3", "217.61.121.60"));
        vSeeds.push_back(CDNSSeedData("seed4", "77.81.234.124"));
        vSeeds.push_back(CDNSSeedData("seed5", "80.211.57.114"));
        vSeeds.push_back(CDNSSeedData("seed6", "80.211.168.220"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 75);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 122);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 128);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true; // Default true
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false; // Default false
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04e613f9bcba88c7eb2be545da7b861930486522bbe2f4a73e553df93ebe29d4639069c577967f4400ca75585b60e6d06c88bda6bbf712af8c4e792c050fa176a3";
        strSporkKeyOld = "0418ce69724beb3bf3532a063d8424aacdddf84f286eacdd52893cfa5d31c90a3ac5f9c43f64b9aa602a0929d640df38bb6e55c0d1d4f7ec3050b78af3ac27d2e9";
        strObfuscationPoolDummyAddress = "XQf9JD2j2QwfuHiTGFauXf84Xjj3Jbky1f";
        nStartMasternodePayments = 1587807440;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xd0;
        pchMessageStart[1] = 0xcd;
        pchMessageStart[2] = 0xa9;
        pchMessageStart[3] = 0x96;
        vAlertPubKey = ParseHex("047702b6eb08ee32cfbd0cec8197e7287bc46aa3b9b855f268378a8e217eb1f7232dbca8f4e3459758ac2fd476a41266d8ce4ee19e3cacd5169802a9715bf572d1");
        nDefaultPort = 31244;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // XSR: 1 day
        nTargetSpacing = 1 * 60;  // XSR: 1 minute
        nLastPOWBlock = 100;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 101; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nEnforceNewSporkKey = 1521604800; //!> Sporks signed after Wednesday, March 21, 2018 4:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1522454400; //!> Reject old spork key after Saturday, March 31, 2018 12:00:00 AM GMT

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1570470324;
        genesis.nNonce = 1248594;

        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x0000031593b789b24efaa72a802fcc582f973d1d8871fb888dad1a951d0f1d57"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet sucrecoin addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet sucrecoin script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet sucrecoin BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet sucrecoin BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet sucrecoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04A8B319388C0F8588D238B9941DC26B26D3F9465266B368A051C5C100F79306A557780101FE2192FE170D7E6DEFDCBEE4C8D533396389C0DAFFDBC842B002243C";
        strSporkKeyOld = "04348C2F50F90267E64FACC65BFDC9D0EB147D090872FB97ABAE92E9A36E6CA60983E28E741F8E7277B11A7479B626AC115BA31463AC48178A5075C5A9319D4A38";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x93;
        pchMessageStart[1] = 0x9f;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xd8;
        nSubsidyHalvingInterval = 150;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // XSR: 1 day
        nTargetSpacing = 1 * 60;        // XSR: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;

        genesis.nTime = 1570470444;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 1;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 31246;
        //assert(hashGenesisBlock == uint256("0x55db4c46c531d7399537de526d10fddf1a36fbd7b270c721f0cd1a5e99743881"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
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

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 31248;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
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

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
