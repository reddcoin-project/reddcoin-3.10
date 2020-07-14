// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
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

/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
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
    (1091719, uint256("0x8456b8b6d1eef1ca71d176e49948b5125c38ac413797674c8fcf0691a2f875ca"))
    (1132039, uint256("0xb2a8999b48ce4212d64fa8be809419b979931ffdb8e0963c18feebd9b9222802"))
    (1172359, uint256("0x56e0863848054793910c8a814742fb09b2e26926a542c5c21cdcb8adce44c2f8"))
    (1212679, uint256("0xbce76bde00be65672fd8e73cb2fb8f1ff77554d7454c9f373d3937bd409cc2ae"))
    (1252999, uint256("0x0a5a3797b50426ff7d7d61a26dd638b4d9b450c986eef9f595230cf4eec8d43d"))
    (1293319, uint256("0x34abf8942d6ef1b7c2b7c54469bb5976a0e42a0b46d5b2a9edce653ef7407c82"))
    (1333639, uint256("0x5043a64580937b53dada19b53d06aeac35a22a0138f3ebe7552eec9de3496cb9"))
    (1373959, uint256("0x62d3853820d0a686941ee70d57a05d6a4bf1f2041b4a30a6d5a0c9938cc0e3b9"))
    (1414279, uint256("0x160611c311ff2432625ab12721185f6f17589116564cd30a843d9e4e243026c3"))
    (1454599, uint256("0xe0e8469d711b9202ca32ee8860770b08a18baaf317b94e52c51436d01d74b2e8"))
    (1494919, uint256("0x52b04f7e196a32034a5927b0d6faa6aa66ecb83563b12a2b2bc097b963028917"))
    (1535239, uint256("0x5e88742aaddc5522c95924a435b42edc8ac77e2efa9bc3fa0d883c92795f0384"))
    (1575559, uint256("0x0dedc34ed4cf8ab7d142fbc0d46bb4df6e670ea081061a3fac375346a79bf604"))
    (1615879, uint256("0x488de615fe220a7c1e89db59c58389bbb80dddfb93fe6d8a0bb935876164fb41"))
    (1656199, uint256("0xf4374f80000ac3d26d1db27351374c9487df4187df63bd1b2fa040fcc3996b7a"))
    (1696519, uint256("0xb0a14b1743e834c674d79397a02cb866f28c081b2d8b64050a50611a6b47f8b8"))
    (1736839, uint256("0x6f44a08e7a09893d95dc2271628a451d932b53782e292da9a197a6c4b7c72b9e"))
    (1777159, uint256("0xfafa0f25ed1c75a58148af890a1c871dddbaf043a753793b5fe2f47502edda98"))
    (1817479, uint256("0x42ce470859a46c77e5774db27b2d00b7c0265c4d2556d8f1106aee7006ef03f8"))
    (1857799, uint256("0xb144603ed32f83d8d35b4b7cebef7f6cd3c40e1d418322c7831a54de454fc629"))
    (1898119, uint256("0x43e0547f8b9138649fdcb3e3d590cc29ec658060bd1cffc24b316798c5892caf"))
    (1938439, uint256("0x6fe379f36055fdae8cceb610ca991989a54903024be645a736722e3bd998a6d3"))
    (1978759, uint256("0xfa4c90ce464816fec8dce0ff6060207e4440e765b464ab07e69c9d08d506b19e"))
    (2019079, uint256("0x62e7ee7ae512eebe15b83fb929ac14084f7abd5d56329cf67d521a8289def91b"))
    (2059399, uint256("0x1465b7307f87f25b86949850a070f6e57dbf82201c94ed9d6298802baa8cd48b"))
    (2099719, uint256("0x64a0b5d2255a35b9fa25fbbf424e060822f9bf527caee87af979782f75f7f8fe"))
    (2140039, uint256("0xefab922a28b266339d349c77904186fcc9fa61047be3dd283f927a11e37afab3"))
    (2180359, uint256("0x68eb8ae6eb80f826f3a40c8e3274e73ea7be787732e7e18206274703ebd2b758"))
    (2220679, uint256("0x97df9dfb9de984b8a1e8dc206bd5c54ac97607edab676137948388c9918a7479"))
    (2260999, uint256("0x10afaff132a9d85877a95c8a480d42586920137559df1f631cba2db9cb9ea01c"))
    (2301319, uint256("0x5d7a21c52624e7ad348915ad6ad7e39d0dbd5906327c2f205fa4073cc9d35b81"))
    (2341639, uint256("0xe8723dc93a313d7248031128714118dcc8e4a69fc7f75a820820f5fdfa701740"))
    (2381959, uint256("0x6d24d8f34b0979c75de3907f434a98881d669deb10baa8d2367585cb5e5f743b"))
    (2422279, uint256("0x18ea3b905655fd6e90136409074a14becc97eaa97157216cb7a6733dcdef6e93"))
    (2462599, uint256("0x4ea0d74708e601187f2bb501e913dc8eea8ab5fd16bcb18bece9200a089456e7"))
    (2502919, uint256("0x3b5765e5c86a6c168b6d4abcf7648248b5528cd6c5d2f21ead95e2c6e4f7f200"))
    (2543239, uint256("0xcf69068aaedb3f9c2dea524ffbd23204a0d5dc54fe5a724f4ef2154008a7d381"))
    (2583559, uint256("0x61d8efefc796f02098ad1d361ff0e9de1652ec36007953647f9c99a695882110"))
    (2623879, uint256("0xde13a7bedd88beac6be7042c971f307da882b55e555cbde99aa05299fd35172e"))
    (2664199, uint256("0xbf5a342935484775d0121f75e9f0131bc5c0a14d70941774add832e39b2f31fd"))
    (2704519, uint256("0x6ea30e05944d823d14297b7a815c5481c07ed036e6807148d7fe474715adf167"))
    (2744839, uint256("0x364d13facdc900e879f2e2f7db0b44a4c090004bcd1b7adc8fdebcc01a787e2d"))
    (2785159, uint256("0x5fb71d131544372542405bc64143620388d10abafdd4581a06516db77e621ef9"))
    (2825479, uint256("0x3175360e06db1096dd90286fa0885d00310843d3af6ba0367d63f05a1bff1272"))
    (2865799, uint256("0x9b674f80b52af1266bcba63c2f56afb27f6450017437cf555d7afb2ea8c51551"))
    (2906119, uint256("0xfe77c3953a272dad34267534216c5d61fd51314ee7238d1ac18e48e1c8580e95"))
    (2946439, uint256("0x3bd913f17fda7afb134eee707d19667da61506ffe43f43ac0f3862600f853fba"))
    (2986759, uint256("0xa7ce2b440bb607cf0469451165089772ddc09a12508a6e3ab81ff1a3ba014242"))
    (3027079, uint256("0x67ac62feac2997f95fe56f519984e8df758dc0d855ffeef8e1ba20ee870f34c1"))
    (3067399, uint256("0x09b90ba8825d1e29fcb95291abcfd22769380e1d83e2c22c6ac1c46bcbc9eb8c"))
    (3107719, uint256("0x20295578ddc0604bc44362cc4d6bef04549336e18740b0845b6fa119e282496a"))
    (3148039, uint256("0x1fe291200fa247d2ea1e1a33a0788734a646a033ada28b1a31fb1ce9805e4497"))
    (3188359, uint256("0x3a69bba8b252a461d0e76333cc50fec19a8fcfd4ad5bb7a8ce9c0e8ef7284b94"))
    (3228679, uint256("0x20b15eac55ba0cef31977e540d9034a0fdba574a3cb02c0f02b64ee947216eac"))
    (3268999, uint256("0x02bcaeebf00136b943cdd30832147e1f36f063cb6f71df52b6d0e55b5c633b5f")) //use this checkpoint as start when calculating
    (3309319, uint256("0x68ff1ef71586f083ab77090f60e52bc8bd121734baadf8b5c6afbada869649ae")) //remove this check point for next batch
    ;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1590916092, // * UNIX timestamp of last checkpoint block
    9539013,    // * total number of transactions between genesis and last checkpoint
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
    ( 201600, uint256("0x46fd0ab0bc0895f89a7f8352e72e151ed1be9fe6ff7d62bbec6d43b05458c9d9"))
    ( 241920, uint256("0x8c671692abd5b36672412d71d03897841262d6b1a9cb29f439b707e030d4aa51"))
    ( 282240, uint256("0x09483bb8c01e0c2aac620511a15dc525cc4826c4c4b3a337007c7fab0198c71d"))
    ( 322560, uint256("0x99c7bb4861bb9c8885733efad681b291af17ca1e70c8d7cdbc6d09df8305b114"))
    ( 362880, uint256("0xdc1a56e0626e211aa8a144e4caf4a64367a213fe2f5ba393ab007b0cc706f014"))
    ( 403200, uint256("0x106d8f5f33d9266e1e35593157bef0ecad13fd84de065637f494d6123a5c2c42"))
    ( 443520, uint256("0xb1c827f59674d2acc098f3c097727b7ed0f58472aecc55252a6250409bee0193"))
    ( 483840, uint256("0x52ec20b739d802198121d112148ff4da32370078a40345e7ef6ed0db525fdd63"))
    ( 524160, uint256("0x4e5c19862d151227c29cb6c9e7f2deef44220124d81f35f60614dd69b1b1804c"))
    ( 564480, uint256("0x342c2e6c860af3f750b57d36599ce18d49ac72e87687a55072ea8fd6262f36ee"))
    ( 604800, uint256("0x0780b8fce7fb9fd4480865ab5980b1715dfea8a27c02d9e71e35c84a1d008a46"))
    ( 645120, uint256("0xb58082261e9dc2f4fba3b6bbb97adcd89819968eef4bf481cb0589f34302c51b"))
    ( 685440, uint256("0x6d639b3dea2cc181acebe832dd92d497f7b49a3997d840cebd096e30a8e98552"))
    ( 725760, uint256("0xebb4cdfde0cec55257c5429bb1db40abf21a5b2809b3630eb07503f726ab9807"))
    ( 766080, uint256("0x4945bf80ad554feadf5d345319520d2b76260b7a2015f1d7b21b0ac65c04906d"))
    ( 806400, uint256("0x8c0608728243a49fd8edbba339afe108c5f796d448dea9b60882515fec056eb9"))
    ( 846720, uint256("0xec6c9e49637c4870638b7969dc7acf6a45bd82ce3464bc7dea7e5be028a976bc"))
    ( 887040, uint256("0xb2732aa37a598f7550c84bb7ee363e40cb476cbe984b767194ce3bf501239308"))
    ( 927360, uint256("0x55e234e46174f09a258855583d13d7a5b11637978364f8a485140963a3db2fbf"))
    ( 967680, uint256("0x4f80a611ec2b3e485a5c2e4d7b21aeb714b62ff58f593b1043cc8c5e9c36fc00"))
    (1008000, uint256("0x0848503f8c3613f5f4c05561399bc420572df2754c392e6b8ce518759e996643"))
    (1048320, uint256("0x1c9d333af280435fe32b134c1ae31328fa2f983efb7d68207df3d84ba066472d"))
    (1088640, uint256("0x79c9d325b945e775a29180e61b45d6fad8fb4608da254c3608c9de85867fae4d"))
    (1128960, uint256("0x16f4b9bce37d2d2969b952146be50c6f415f52187749e3c5609ea27fd7b7c62c"))
    (1169280, uint256("0x5c67a3fe2d85f9863dc660c18a3b712c59d3317674d4bc7794d07cb08ed3f69d"))
    (1209600, uint256("0xc915ede08f97177f8588e01f0b62bdb7f4f743a9829c8c44b371d697bd05558b"))
    (1249920, uint256("0x8635ba4efe02e3451bac996865a7c7beaf659afaa28920bd64f073518ac5d935"))
    (1290240, uint256("0x685522c29d13ccb3c0d2a6989d46e9ce525a2a8d8e498d8039aa55f529e63f93"))
    (1330560, uint256("0x9c3dce3e40b5ad69761bbe6190848df012daafefa191086b09e71694e7eb6cb3"))
    (1370880, uint256("0x0bcf702e5b3ed63e8f6b518c98af3e4b4c3eb4af7786e79695f0a559e1d241db"))
    (1411200, uint256("0xb42b460dc9d8dfc1d85e2c7c276d5d1deeaabc44f92fe86dcc25ce3c522192dd"))
    (1451520, uint256("0xb6b89c347230f31137288370f4eecfe7ff18a51c9892124b5f94a8a1bddb9a77"))
    (1491840, uint256("0xc1c3fdf13eac3f071e15660c78ff05d619135a7667884129207737bf3d96da1d"))
    (1532160, uint256("0x54ad30374b17765ebc4b831571e8478886fe2d59960ad4f3bca2db71e57a7d2e"))
    (1572480, uint256("0x145e13b011ea60e86fccd7c46ca3befec333f7671fea5ee139f09ba082ed598b"))
    (1612800, uint256("0x650283563cc74150381fa35da018f5e2e0c3b04476ae6140e30aa083911e8bd0"))
    (1653120, uint256("0xaa1f77075886a1e8cbd85f9c2d250a099b5838400906e482b9d56f14eac0e1c2"))
    (1693440, uint256("0x0b1a50da79027ba9feb55f5b7d5cb5a11c1cbe5e7bf3808e1d5a26da45341101"))
    (1733760, uint256("0x950049010ad58732a67981169788964c3e202623fafd24d87665c159cc589303"))
    (1774080, uint256("0xc6d0b689e9c2310a807fea4634d326abea55e27b2a6937735b7dcda3e01e5ca2"))
    (1814400, uint256("0x9f388b2b314cd522b229f9aa978379504879eee39765c35470e5cb8215a21f14"))
    (1854720, uint256("0x2bca7216eeff21fd313cc3502cde4c5a60ea1d5bdcde4e1548f7ab3429b2871b"))
    (1895040, uint256("0xe5b5bf6a7bfb789890e0e1a2c99e2a68fba1fb4a37c100ca6963a442f0bf82b1"))
    (1935360, uint256("0x65eaff429685a6882f945b3fb53379225e8e83d73c52d30787629c1c885f5f71"))
    (1975680, uint256("0x2cd67cb752fd01b95cef118c741809e7df8681bef71066bfe6bb0f001a04e635"))
    (2016000, uint256("0x1336e7ee3a4ce6f98ab67ede76d2bdb12c3d38cf49424b5374234e26a865da9b"))
    (2056320, uint256("0x2b092cd7de370861c39d81d4a4aa41c8d8485eec4f5e2de57d4c0263b8466660"))
    (2096640, uint256("0x1c8e35d9e5ebe86bd93047fde2811e54e54683046a5dd59ac2c8131adf628f06"))
    (2136960, uint256("0xd16e9df60491246c99088e99342b7cce07af8f3695d4bc5776e093ed1e6aa3f7"))
    (2177280, uint256("0x6f63601aaa8f1b5a189b27731b5e6435cbc428f34041939059f882a1b18d766a"))

    ;
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1592438956, // * UNIX timestamp of last checkpoint block
    4366262,     // * total number of transactions between genesis and last checkpoint
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
        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xdb;
        vAlertPubKey = ParseHex("0437b4b0f5d356f205c17ffff6c46dc9ec4680ffb7f8a9a4e6eebcebd5f340d01df00ef304faea7779d97d8f1addbe1e87308ea237aae3ead96e0a736c7e9477a1");
        nDefaultPort = 45444;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 200;
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
        nMaxTipAge = 8 * 60 * 60;

        // PoSV
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeReset = CBigNum(~uint256(0) >> 32); // 1
        nLastProofOfWorkHeight = 260800 - 1;
        vDevPubKey = ParseHex("03c8fc5c87f00bcc32b5ce5c036957f8befeff05bf4d88d2dcde720249f78d9313");
        nStakeMinAge = 8 * 60 * 60; // 8 hours
        nStakeMaxAge = 45 * 24 *  60 * 60; // 45 days

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         * 
         * CBlock(hash=12a765e31ffd4059bada, PoW=0000050c34a64b415b6b, ver=1, hashPrevBlock=00000000000000000000, hashMerkleRoot=97ddfbbae6, nTime=1317972665, nBits=1e0ffff0, nNonce=2084524493, vtx=1)
         *   CTransaction(hash=97ddfbbae6, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(0000000000, -1), coinbase 04ffff001d0104404e592054696d65732030352f4f63742f32303131205374657665204a6f62732c204170706c65e280997320566973696f6e6172792c2044696573206174203536)
         *     CTxOut(nValue=50.00000000, scriptPubKey=040184710fa689ad5023690c80f3a4)
         *   vMerkleTree: 97ddfbbae6
         */
        const char* pszTimestamp = "January 21st 2014 was such a nice day...";
        uint32_t nTime = 1390280400;
        CMutableTransaction txNew(nTime);
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
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
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

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
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
        nTargetTimespan = 24 * 60 * 60; //! 24 hours
        nTargetSpacing = 60; //! 1 minute
        nMaxTipAge = 0x7fffffff;

        nLastProofOfWorkHeight = 350 - 1; // Last POW block
        vDevPubKey = ParseHex("03081542439583f7632ce9ff7c8851b0e9f56d0a6db9a13645ce102a8809287d4f");

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1446002303;
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
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
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

/**
 * Regression test
 */
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
        nMaxTipAge = 8 * 60 * 60;
        nLastProofOfWorkHeight = 350 - 1;
        genesis.nTime = 1401051600;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 3;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 56444;
        assert(hashGenesisBlock == uint256("0x0472dc040de80ded8bd385a2b6bc6e4e05cb6432047efa07692724c6ccef40ac"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
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
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18445;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
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
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks)  { fDefaultConsistencyChecks=afDefaultConsistencyChecks; }
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

    SelectParams(network);
    return true;
}
