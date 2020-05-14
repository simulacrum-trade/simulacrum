// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2019 The PIVX developers
// Copyright (c) 2020 The Simulacrum developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "consensus/merkle.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>
#include <limits>


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
    (0, uint256("0x00000210aeb11eeabaaa6c8eae21191c35583b1276ba915f3fadbab5970fd167"))/* 
    (424998, uint256("f31e381eedb0ed3ed65fcc98cc71f36012bee32e8efd017c4f9fb0620fd35f6b"))
    (616764, uint256("29dd0bd1c59484f290896687b4ffb6a49afa5c498caf61967c69a541f8191557")) //first block to use modifierV2
    (623933, uint256("c7aafa648a0f1450157dc93bd4d7448913a85b7448f803b4ab970d91fc2a7da7"))
    (791150, uint256("8e76f462e4e82d1bd21cb72e1ce1567d4ddda2390f26074ffd1f5d9c270e5e50"))
    (795000, uint256("4423cceeb9fd574137a18733416275a70fdf95283cc79ad976ca399aa424a443"))
    (863787, uint256("5b2482eca24caf2a46bb22e0545db7b7037282733faa3a42ec20542509999a64"))
    (863795, uint256("2ad866818c4866e0d555181daccc628056216c0db431f88a825e84ed4f469067"))
    (863805, uint256("a755bd9a22b63c70d3db474f4b2b61a1f86c835b290a081bb3ec1ba2103eb4cb"))
    (867733, uint256("03b26296bf693de5782c76843d2fb649cb66d4b05550c6a79c047ff7e1c3ae15"))
    (879650, uint256("227e1d2b738b6cd83c46d1d64617934ec899d77cee34336a56e61b71acd10bb2"))
    (895400, uint256("7796a0274a608fac12d400198174e50beda992c1d522e52e5b95b884bc1beac6"))//block that serial# range is enforced
    (895991, uint256("d53013ed7ea5c325b9696c95e07667d6858f8ff7ee13fecfa90827bf3c9ae316"))//network split here
    (908000, uint256("202708f8c289b676fceb832a079ff6b308a28608339acbf7584de533619d014d"))
    (1142400, uint256("98aff9d605bf123247f98b1e3a02567eb5799d208d78ec30fb89737b1c1f79c5"))
    (1679090, uint256("f747ce055ba1b12e1f2e842bd480bc647210799359cb2e553ab292065e3419d6")) //!< First block with a "wrapped" serial spend
    (1686229, uint256("bb42bf1e886a7c23474634c90893dd3d68a6ccbfea4ac92a98da5cad0c6a6cb7")) //!< Last block in the "wrapped" serial attack range
    (1778954, uint256("0d3241268264a2908d6babf00d9cd1ffb83d93d7bb4e428820127fe227c2029c")) //!< Network split here
    (1788528, uint256("ea9243ff8fc079fdd7a04f11fac415de4d98e1bb0dc38db6f79f8f8bbfdbe496"))*/; //!< Network split here
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1578945131, // * UNIX timestamp of last checkpoint block
    0,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x00000210aeb11eeabaaa6c8eae21191c35583b1276ba915f3fadbab5970fd167"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1578945131,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

bool CChainParams::HasStakeMinAgeOrDepth(const int contextHeight, const uint32_t contextTime,
        const int utxoFromBlockHeight, const uint32_t utxoFromBlockTime) const
{
    // before stake modifier V2, the age required was 60 * 60 (1 hour). Not required for regtest
    if (!IsStakeModifierV2(contextHeight))
        return NetworkID() == CBaseChainParams::REGTEST || (utxoFromBlockTime + nStakeMinAge <= contextTime);

    // after stake modifier V2, we require the utxo to be nStakeMinDepth deep in the chain
    return (contextHeight - utxoFromBlockHeight >= nStakeMinDepth);
}

int CChainParams::FutureBlockTimeDrift(const int nHeight) const
{
    if (IsTimeProtocolV2(nHeight))
        // PoS (TimeV2): 14 seconds
        return TimeSlotLength() - 1;

    // PoS (TimeV1): 3 minutes
    // PoW: 2 hours
    return (nHeight > LAST_POW_BLOCK()) ? nFutureTimeDriftPoS : nFutureTimeDriftPoW;
}

bool CChainParams::IsValidBlockTimeStamp(const int64_t nTime, const int nHeight) const
{
    // Before time protocol V2, blocks can have arbitrary timestamps
    if (!IsTimeProtocolV2(nHeight))
        return true;

    // Time protocol v2 requires time in slots
    return (nTime % TimeSlotLength()) == 0;
}

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
        pchMessageStart[0] = 0xc8;
        pchMessageStart[1] = 0xc8;
        pchMessageStart[2] = 0xca;
        pchMessageStart[3] = 0xcb; 
        vAlertPubKey = ParseHex("0474472bf706178bd4835e31bf2ee2c7daff2510d58c837491ada09c6184533c1731377d8cf897b763af3f876fe653ae2673f06df5ffb2665b615255dacc573a8e");
        nDefaultPort = 59472;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // PIVX starting difficulty is 1 / 2^12
        bnProofOfStakeLimit = ~uint256(0) >> 24;
        bnProofOfStakeLimit_V2 = ~uint256(0) >> 20; // 60/4 = 15 ==> use 2**4 higher limit
        nSubsidyHalvingInterval = 210000; //Not used?
        nMaxReorganizationDepth = 100; //Max number of forked blocks to be sent
        nEnforceBlockUpgradeMajority = 8100; // 75%
        nRejectBlockOutdatedMajority = 10260; // 95%
        nToCheckBlockUpgradeMajority = 10800; // Approximate expected amount of blocks in 7 days (1440*7.5)
        nMinerThreads = 0;
        nTargetSpacing = 1 * 60;                        // 1 minute
        nTargetTimespan = 40 * 60;                      // 40 minutes
        nTimeSlotLength = 60;                           // 60 seconds
        nTargetTimespan_V2 = 2 * nTimeSlotLength * 60;  // 30 minutes
        nMaturity = 20;                                // 20 confirmations for immature coins
        nStakeMinAge = 20 * 60;                         // 20 mins
        nStakeMinDepth = 20;
        nFutureTimeDriftPoW = 7200;
        nFutureTimeDriftPoS = 180;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 21000000 * COIN;
        nMinColdStakingAmount = 1 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 300;
        nPivxBadBlockTime = 1471401614; // Skip nBit validation of Block 259201 per PR #915
        nPivxBadBlocknBits = 0x1c056dac; // Skip nBit validation of Block 259201 per PR #915
        nModifierUpdateBlock = 1000000000;
        nZerocoinStartHeight = 1000000000; // Do not start
        nZerocoinStartTime = 2308871710; // Do not start
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 1000000000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 1000000000; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 1000000000; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 1000000000; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 1*COIN; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 1000000000; //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT DO NOT START
        nBlockDoubleAccumulated = 1050010;
        nEnforceNewSporkKey = 2308871710; //!> Sporks signed after X must use the new spork key
        nRejectOldSporkKey = 2308871710; //!> Fully reject old spork key USE THE OLD SPORK KEY
        nBlockStakeModifierlV2 = 1000000000;
        nBIP65ActivationHeight = 1;
        // Activation height for TimeProtocolV2, Blocks V7 and newMessageSignatures
        nBlockTimeProtocolV2 = 149216;

        // Public coin spend enforcement
        nPublicZCSpends = 1000000000;

        // New P2P messages signatures
        nBlockEnforceNewMessageSignatures = 1000000000;

        // Blocks v7
        nBlockLastAccumulatorCheckpoint = 1000000000;
        nBlockV7StartHeight = 1000000000;

        // Fake Serial Attack
        nFakeSerialBlockheightEnd = 1000000000;
        nSupplyBeforeFakeSerial = 1 * COIN;   // zerocoin supply at block nFakeSerialBlockheightEnd

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "https://simulacrum.trade";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 250 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("047fd76a69f2e7dcb414bfcce90d9134e0df9763104bfe1b67438e205344a5957084bc0d819c2e5dcea90285904a52f801a08e479cba1ad17a8ef2b29626750168") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
        genesis.nVersion = 6;
        genesis.nTime = 1578945131;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 11213578;

        hashGenesisBlock = genesis.GetHash();
        if(genesis.GetHash() != uint256("0x00000210aeb11eeabaaa6c8eae21191c35583b1276ba915f3fadbab5970fd167"))
        {
              printf("MSearching for genesis block...\n");
              uint256 hashTarget;
              hashTarget.SetCompact(genesis.nBits);
              while(uint256(genesis.GetHash()) > uint256(hashTarget))
              {
                  ++genesis.nNonce;
                  if (genesis.nNonce == 0)
                  {
                      printf("Mainnet NONCE WRAPPED, incrementing time");
                      std::cout << std::string("Mainnet NONCE WRAPPED, incrementing time:\n");
                      ++genesis.nTime;
                  }
                  if (genesis.nNonce % 10000 == 0)
                  {
                      printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                  }
              }
              printf("Mainnet block.nTime = %u \n", genesis.nTime);
              printf("Mainnet block.nNonce = %u \n", genesis.nNonce);
              printf("Mainnet block.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
              printf("Mainnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        }
        assert(hashGenesisBlock == uint256("0x00000210aeb11eeabaaa6c8eae21191c35583b1276ba915f3fadbab5970fd167"));
        assert(genesis.hashMerkleRoot == uint256("0xf7e4cec149e434a28b2edb54f7000a0a502e33f16c7f3f9ee7f269741d732b94"));

        //vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "simulacrum.seed.fuzzbawls.pw"));     // Primary DNS Seeder from Fuzzbawls

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 28);
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 50);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x11)(0x46)(0x47)(0x0A).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x11)(0x46)(0x46)(0x6f).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true; //Default false
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        nBudgetCycleBlocks = 43200; //!< Amount of blocks in a months period of time (using 1 minutes per) = (60*24*30)
        strSporkPubKey = "04827e2e4e96e5bf796ec76fae9f580f4a07b2833513c716382afd2ab8e8fbfc5906615b4ddac7c0befd16b3cc6b837a54489e7b354acbd0eef145b0faf2691a4a";
        strSporkPubKeyOld = "04f2c3c0545b7dfe32a985ea3a48e656ed4de12cd6dbf1367a3677896c30537bab30c49dd3ed427cd9f4839e740bd83c3d8d7cbe35d9d374278a5d2863e2b9f9d4";
        strObfuscationPoolDummyAddress = "SZeuUqCydvYPm69qepkk9j8vrxZn5JWwz8";
        nStartMasternodePayments = 1578945131; //Wed, 25 Jun 2014 20:36:16 GMT

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMaxZerocoinPublicSpendsPerTransaction = 637; // Assume about 220 bytes each input
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zpiv to be stakable

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
        nProposalEstablishmentTime = 60 * 60 * 24; // Proposals must be at least a day old to make it into a budget
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
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xa2;
        pchMessageStart[2] = 0xa3;
        pchMessageStart[3] = 0xa4;
        vAlertPubKey = ParseHex("047b2030ee8c0cca5312a8dea99dfd53fa9ac10fee66e7489dda10898df9e061d6847ae4a418bcb458418daf38fe4b509d3ecbcdba77efbdf859294fec0698c46c");
        nDefaultPort = 59474;
        nEnforceBlockUpgradeMajority = 4320; // 75%
        nRejectBlockOutdatedMajority = 5472; // 95%
        nToCheckBlockUpgradeMajority = 5760; // 4 days
        nMinerThreads = 0;
        nLastPOWBlock = 200;
        nPivxBadBlockTime = 1489001494; // Skip nBit validation of Block 259201 per PR #915
        nPivxBadBlocknBits = 0x1e0a20bd; // Skip nBit validation of Block 201 per PR #915
        nMaturity = 15;
        nStakeMinDepth = 100;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = 201576;
        nZerocoinStartTime = 2208871710;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 9902850; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 444020; //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1566860400; //!> Sporks signed after Monday, August 26, 2019 11:00:00 PM GMT must use the new spork key
        nRejectOldSporkKey = 1569538800; //!> Reject old spork key after Thursday, September 26, 2019 11:00:00 PM GMT
        nBlockStakeModifierlV2 = 1214000;
        nBIP65ActivationHeight = 851019;
        // Activation height for TimeProtocolV2, Blocks V7 and newMessageSignatures
        nBlockTimeProtocolV2 = 1347000;

        // Public coin spend enforcement
        nPublicZCSpends = 1106100;

        // New P2P messages signatures
        nBlockEnforceNewMessageSignatures = nBlockTimeProtocolV2;

        // Blocks v7
        nBlockLastAccumulatorCheckpoint = nPublicZCSpends - 10;
        nBlockV7StartHeight = nBlockTimeProtocolV2;

        // Fake Serial Attack
        nFakeSerialBlockheightEnd = -1;
        nSupplyBeforeFakeSerial = 0;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1578945131;
        genesis.nNonce = 11213578;

        hashGenesisBlock = genesis.GetHash();
        if(genesis.GetHash() != uint256("0x00000210aeb11eeabaaa6c8eae21191c35583b1276ba915f3fadbab5970fd167"))
        {
              printf("MSearching for genesis block...\n");
              uint256 hashTarget;
              hashTarget.SetCompact(genesis.nBits);
              while(uint256(genesis.GetHash()) > uint256(hashTarget))
              {
                  ++genesis.nNonce;
                  if (genesis.nNonce == 0)
                  {
                      printf("Testnet NONCE WRAPPED, incrementing time");
                      std::cout << std::string("Testnet NONCE WRAPPED, incrementing time:\n");
                      ++genesis.nTime;
                  }
                  if (genesis.nNonce % 10000 == 0)
                  {
                      printf("Testnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                  }
              }
              printf("Testnet block.nTime = %u \n", genesis.nTime);
              printf("Testnet block.nNonce = %u \n", genesis.nNonce);
              printf("Testnet block.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
              printf("Testnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        }
        assert(hashGenesisBlock == uint256("0x00000210aeb11eeabaaa6c8eae21191c35583b1276ba915f3fadbab5970fd167"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet simulacrum addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet simulacrum script addresses start with '8' or '9'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 30);     // starting with 'W'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet simulacrum BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x66)(0x46)(0x47)(0x0A).convert_to_container<std::vector<unsigned char> >();
        // Testnet simulacrum BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x66)(0x46)(0x46)(0x6f).convert_to_container<std::vector<unsigned char> >();
        // Testnet simulacrum BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        nBudgetCycleBlocks = 144; //!< Ten cycles per day on testnet
        strSporkPubKey = "04827e2e4e96e5bf796ec76fae9f580f4a07b2833513c716382afd2ab8e8fbfc5906615b4ddac7c0befd16b3cc6b837a54489e7b354acbd0eef145b0faf2691a4a";
        strSporkPubKeyOld = "04f2c3c0545b7dfe32a985ea3a48e656ed4de12cd6dbf1367a3677896c30537bab30c49dd3ed427cd9f4839e740bd83c3d8d7cbe35d9d374278a5d2863e2b9f9d4";
        strObfuscationPoolDummyAddress = "TBD";
        nStartMasternodePayments = 1578945131; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet

        nProposalEstablishmentTime = 60 * 5; // Proposals must be at least 5 mns old to make it into a test budget
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
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nDefaultPort = 51476;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nLastPOWBlock = 250;
        nMaturity = 100;
        nStakeMinAge = 0;
        nStakeMinDepth = 0;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 0;       //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = 300;
        nBlockZerocoinV2 = 300;
        nZerocoinStartTime = 1501776000;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 999999999; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 999999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 999999999; //Last valid accumulator checkpoint
        nBlockStakeModifierlV2 = 255;
        nBlockTimeProtocolV2 = 999999999;

        // Public coin spend enforcement
        nPublicZCSpends = 350;

        // Blocks v7
        nBlockV7StartHeight = nPublicZCSpends + 1;
        nBlockLastAccumulatorCheckpoint = nPublicZCSpends - 10;

        // New P2P messages signatures
        nBlockEnforceNewMessageSignatures = 1;

        // Fake Serial Attack
        nFakeSerialBlockheightEnd = -1;

        //! Modify the regtest genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1454124731;
        genesis.nNonce = 2402015;

        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
        //assert(hashGenesisBlock == uint256("0x4f023a2120d9127b21bbad01724fdb79b519f593f2a85b60d3d79160ec5f29df"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        /* Spork Key for RegTest:
        WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
        private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
        Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
        */
        strSporkPubKey = "043969b1b0e6f327de37f297a015d37e2235eaaeeb3933deecd8162c075cee0207b13537618bde640879606001a8136091c62ec272dd0133424a178704e6e75bb7";
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
        nDefaultPort = 51478;
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
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
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
