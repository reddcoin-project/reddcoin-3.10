//
// Unit tests for block-chain checkpoints
//

#include "checkpoints.h"

#include "uint256.h"

#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(Checkpoints_tests)

BOOST_AUTO_TEST_CASE(sanity)
{
    uint256 p1000 = uint256("0x9d849e078deac30d58372db898318186cf5073a7f0b109b4776393b21b7b4e5a");
    uint256 p184000 = uint256("0xe22e6b027cd49cd9aa2ba6df0e0c264c2eed5656b1fa39052c8235d52f2b04d6");
    BOOST_CHECK(Checkpoints::CheckHardened(1000, p1000));
    BOOST_CHECK(Checkpoints::CheckHardened(184000, p184000));

    
    // Wrong hashes at checkpoints should fail:
    BOOST_CHECK(!Checkpoints::CheckHardened(1000, p184000));
    BOOST_CHECK(!Checkpoints::CheckHardened(184000, p1000));

    // ... but any hash not at a checkpoint should succeed:
    BOOST_CHECK(Checkpoints::CheckHardened(1000+1, p184000));
    BOOST_CHECK(Checkpoints::CheckHardened(184000+1, p1000));

    BOOST_CHECK(Checkpoints::GetTotalBlocksEstimate() >= 184000);
}    

BOOST_AUTO_TEST_SUITE_END()
