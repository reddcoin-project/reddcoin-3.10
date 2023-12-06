Reddcoin Core integration/staging tree
=====================================

[![Build Status](https://travis-ci.org/reddcoin-project/reddcoin.svg?branch=master)](https://travis-ci.org/reddcoin-project/reddcoin)

https://www.reddcoin.com

Copyright (c) 2009-2020 Bitcoin Core Developers  
Copyright (c) 2014-2020 Reddcoin Core Developers

### Notice

In preparation of moving to an updated code base, this repository is being renamed (and potentially archived)  
The new location will be https://github.com/reddcoin-project/reddcoin-3.10  
If you have cloned this repo previously, you will need to update and refresh git source links  
```
NEW_URL=https://github.com/reddcoin-project/reddcoin-3.10
git remote set-url origin NEW_URL
```

This current repository location https://github.com/reddcoin-project/reddcoin will be used for the updated code base of  
https://github.com/reddcoin-project/reddcoin-0.22


That is, [Reddcoin 0.22](https://github.com/reddcoin-project/reddcoin-0.22) => [Reddcoin](https://github.com/reddcoin-project/reddcoin)

If you have cloned this repo previously, you will need to update and refresh git source links  
```
NEW_URL=https://github.com/reddcoin-project/reddcoin
git remote set-url origin NEW_URL
```


ref:
- https://docs.github.com/en/repositories/creating-and-managing-repositories/renaming-a-repository
- https://docs.github.com/en/repositories/archiving-a-github-repository/archiving-repositories


What is Reddcoin?
----------------

Reddcoin is an experimental new digital currency that enables instant payments to
anyone, anywhere in the world. Reddcoin uses peer-to-peer technology to operate
with no central authority: managing transactions and issuing money are carried
out collectively by the network. Reddcoin Core is the name of open source
software which enables the use of this currency.

Reddcoin first started in January 2014 as a variant of Litecoin using Scrypt as
the Proof-of-Work (PoW) hash algorithm.
 - 1 minute block target
 - 100,000 coins per block
 - subsidy halves every 500,000 blocks
 - subsidy halves every 50,000 blocks starting at block 140,000
 - difficulty retarget: every block using Kimoto's gravity well


On 2nd August 2014 at block 260,800 Reddcoin transitioned to its own original Proof-of-Stake-Velocity (PoSV)
algorithm which replaced Proof-of-Work (PoW).
 - 1 minute block target
 - just under 27 billion mined in PoW phase
 - 5% annual interest in PoSV phase
 - difficulty retarget: every block using Kimoto's gravity well
 - white paper: http://www.reddcoin.com/papers/PoSV.pdf
 - FAQs paper: http://www.reddcoin.com/papers/PoSV_FAQ.pdf

On December 2015 work commenced on porting directly from Bitcoin v0.9 whilst maintaining the original functionality.
 - allowing for better maintainabilty
 - monitoring of upstream features
 - improved code consistency and sharing

For more information, as well as an immediately useable, binary version of
the Reddcoin Core software, see http://www.reddcoin.com

License
-------

Reddcoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see http://opensource.org/licenses/MIT.

Development process
-------------------

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the Reddcoin
development team members simply pulls it.

If it is a *more complicated or potentially controversial* change, then the patch
submitter will be asked to start a discussion (if they haven't already) on the relevant forum channel.

The patch will be accepted if there is broad consensus that it is a good thing.
Developers should expect to rework and resubmit patches if the code doesn't
match the project's coding conventions (see [doc/coding.md](doc/coding.md)) or are
controversial.

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/reddcoin-project/reddcoin/tags) are created
regularly to indicate new official, stable release versions of Bitcoin.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write unit tests for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run (assuming they weren't disabled in configure) with: `make check`

Every pull request is built for Windows, Linux and OSx on a dedicated server,
and unit and sanity tests are automatically run. The binaries produced may be
used for manual QA testing — a link to them will appear in a comment on the
pull request posted by [BitcoinPullTester](https://github.com/BitcoinPullTester). See https://github.com/TheBlueMatt/test-scripts
for the build/test scripts.

### Manual Quality Assurance (QA) Testing

Large changes should have a test plan, and should be tested by somebody other
than the developer who wrote the code.
See https://github.com/bitcoin/QA/ for how to create a test plan.

Translations
------------

Changes to translations as well as new translations can be submitted to
[Reddcoin Core's Transifex page](https://www.transifex.com/projects/p/reddcoin/).

Translations are periodically pulled from Transifex and merged into the git repository. See the
[translation process](doc/translation_process.md) for details on how this works.

**Important**: We do not accept translation changes as GitHub pull requests because the next
pull from Transifex would automatically overwrite them again.

Translators should also subscribe to the [mailing list](https://groups.google.com/forum/#!forum/reddcoin-translators).

Development tips and tricks
---------------------------

**compiling for debugging**

Run configure with the --enable-debug option, then make. Or run configure with
CXXFLAGS="-g -ggdb -O0" or whatever debug flags you need.

**debug.log**

If the code is behaving strangely, take a look in the debug.log file in the data directory;
error and debugging messages are written there.

The -debug=... command-line option controls debugging; running with just -debug will turn
on all categories (and give you a very large debug.log file).

The Qt code routes qDebug() output to debug.log under category "qt": run with -debug=qt
to see it.

**testnet and regtest modes**

Run with the -testnet option to run with "play reddcoins" on the test network, if you
are testing multi-machine code that needs to operate across the internet.

If you are testing something that can run on one machine, run with the -regtest option.
In regression test mode, blocks can be created on-demand; see qa/rpc-tests/ for tests
that run in -regtest mode.

**DEBUG_LOCKORDER**

Reddcoin Core is a multithreaded application, and deadlocks or other multithreading bugs
can be very difficult to track down. Compiling with -DDEBUG_LOCKORDER (configure
CXXFLAGS="-DDEBUG_LOCKORDER -g") inserts run-time checks to keep track of which locks
are held, and adds warnings to the debug.log file if inconsistencies are detected.
