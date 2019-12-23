Reddcoin Core version 3.0.0 is now available from:

  [https://github.com/reddcoin-project/reddcoin/releases](https://github.com/reddcoin-project/reddcoin/releases)

This is a new major version release, bringing both new features and
bug fixes.

Please report bugs using the issue tracker at github:

  https://github.com/reddcoin-project/reddcoin/issues

How to Upgrade
--------------

If you are running an older version, shut it down. Wait until it has completely
shut down (which might take a few minutes for older versions), uninstall all
earlier versions of Reddcoin, then run the installer (on Windows) or just copy
over /Applications/Reddcoin-Qt (on Mac) or reddcoind/reddcoin-qt (on Linux).

If you are upgrading from version 1.4.1 or earlier, the first time you run
3.0.0 your blockchain files may be re-indexed, which will take anywhere from 
30 minutes to several hours, depending on the speed of your machine.

On Windows, do not forget to uninstall all earlier versions of the Reddcoin
client first, especially if you are switching to the 64-bit version.

Windows 64-bit installer
-------------------------

It is recommended to install the 64-bit version if your system supports it.

NOTE: Release candidate Windows binaries are not code-signed; use PGP
and the SHA256SUMS.asc file to make sure your binaries are correct.
In the final 3.0.0 release, Windows setup.exe binaries will be code-signed.

OSX 10.5 / 32-bit no longer supported
-------------------------------------

3.0.0 drops support for older Macs. The minimum requirements are now:
* A 64-bit-capable CPU (see http://support.apple.com/kb/ht3696);
* Mac OS 10.6 or later (see https://support.apple.com/kb/ht1633).

Downgrading warnings
--------------------

The 'chainstate' for this release is not always compatible with previous
releases, so if you run 3.0.0 and then decide to switch back to a
1.4.x release you might get a blockchain validation error when starting the
old release (due to 'pruned outputs' being omitted from the index of
unspent transaction outputs).

Running the old release with the -reindex option will rebuild the chainstate
data structures and correct the problem.

Also, the first time you run a 1.4.x release on a 3.0.0 wallet it will rescan
the blockchain for missing spent coins, which will take a long time (tens
of minutes on a typical machine).

Rebranding to Reddcoin Core
---------------------------

To reduce confusion between Reddcoin-the-network and Reddcoin-the-software we
have renamed the reference client to Reddcoin Core.


Autotools build system
-----------------------

For 3.0.0 we continue to use an autotools-based build system instead of individual
(q)makefiles.

Using the standard "./autogen.sh; ./configure; make" to build Reddcoin-Qt and
reddcoind makes it easier for experienced open source developers to contribute 
to the project.

Be sure to check doc/build-*.md for your platform before building from source.

Blockchain Download
------------------------------------

Blockchain data for both testnet and mainnet along with instructions can be downloaded from github.

[https://github.com/reddcoin-project/bootstrap_files](https://github.com/reddcoin-project/bootstrap_files)

3.0.0 Release notes
=======================

3.0.0 rc1 changelog
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
