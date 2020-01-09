Reddcoin Core version 3.0.1 is now available from:

  [https://github.com/reddcoin-project/reddcoin/releases](https://github.com/reddcoin-project/reddcoin/releases)

This is a new major version release of Reddcoin.  
Previously, the original and subsequent versions of Reddcoin were taken from a fork of the Litecoin code base.

With the release of Reddcoin V2.0.0, the code was based directly from a fork Bitcoin.
This allows for better source control and feature implementation from upstream changes into the future

With the release of Reddcoin V3.0.0, the PoSV stake reward has been improved to allow for a target 5% network growth 

Upgrading to this release is strongly recommended and required.  
Once a supermajority of 90% is reached, old wallets will no longer accept the new v5 blocks.

Please report bugs using the issue tracker at github:

  [https://github.com/reddcoin-project/reddcoin/issues](https://github.com/reddcoin-project/reddcoin/issues)

How to Upgrade
===============

If you are running an older version of Reddcoin, shut it down.  
Wait until it has completely shut down (which may take a few minutes for older versions).  
Run the installer (on Windows) or just copy over /Applications/Reddcoin-Qt (on Mac) or
reddcoind/reddcoin-qt (on Linux).

Start wallet

Notable changes
================

Core base code
------------------------------------

Reddcoin v3.0.0 introduced an updated PoSV method to better distribute staking rewards and target a overall 5% network growth.

Staking and relay policy enhancements
------------------------------------

To implement PoSV v2, Reddcoin Core's block templates are now for version 5 blocks only.  
When PoSV v2 consensus (Supermajority 9000/10000) is reached, only v5 blocks will be accepted by the network.  
This equates to approximately 90% of blocks being generated over 1 week period.

Blockchain Download
------------------------------------

Blockchain data for both testnet and mainnet along with instructions can be downloaded from github.

[https://github.com/reddcoin-project/bootstrap_files](https://github.com/reddcoin-project/bootstrap_files)


3.0.1 changelog
===============
36df6fdfb - John Nash, 2019-12-23 : add check explictly for v5 blocks or greater  
874dc1f0c - John Nash, 2019-12-17 : remove hardcoded global variable rearrange debug log output  
763b25db8 - John Nash, 2019-12-17 : move copyright to new line  
536baf635 - John Nash, 2019-12-17 : update version and set release state to false  
cde9009f3 - John Nash, 2019-12-17 : update copyright year  
ae41b7ed3 - John Nash, 2019-12-17 : set isSuperMajority to 90% for mainnet  
e43e1c8ed - John Nash, 2019-12-10 : additional logging to verify isSuperMajority in the debug.log output  
e31783cac - John Nash, 2019-12-05 : add/update public key for mainnet  
405c6f002 - John Nash, 2019-12-05 : add log output for current inflation rate  
9cc43c3f7 - John Nash, 2019-12-02 : determine calculated stake based on posv version  
7baa3bf75 - John Nash, 2019-11-25 : check the posv transaction for correct pubkey  
9ffa7ca38 - John Nash, 2019-11-21 : check for posv v1 or posv v2 blocks when calculating stake reward  
39f7aad68 - John Nash, 2019-11-14 : add logging  
0e283e6c3 - John Nash, 2019-11-13 : correct maths  
74cbdeffd - John Nash, 2019-11-11 : use new posv v2 functions addidtional logging  
35d7413b5 - John Nash, 2019-11-11 : add new proofofstakereward  
3d917216c - John Nash, 2019-11-11 : get inflation adjustment  
f63d17443 - John Nash, 2019-11-08 : add the developer output split fund output  
ca263c9c9 - John Nash, 2019-11-05 : add dev key to chainparams  
df6996ab0 - John Nash, 2019-11-05 : add block version checking  
14b663479 - John Nash, 2019-11-05 : increase block version  


Credits
--------

Thanks to everyone who contributed to coding, testing and feedback for this release, notably:

- @techadept
- @chris  
- @cryptobuze 
- @harmonyq  
- @mindredder  
- @paxtech  
