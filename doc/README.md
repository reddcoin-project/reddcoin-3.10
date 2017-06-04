Reddcoin 2.0.0 BETA
=====================

Copyright (c) 2009-2016 Bitcoin Developers
Copyright (c) 2014-2016 Reddcoin Developers


Setup
---------------------
[Reddcoin Core](http://reddcoin.com) is the original Reddcoin client and it builds the backbone of the network. However, it downloads and stores the entire history of Reddcoin transactions (which is currently several GBs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more. Thankfully you only have to do this once. If you would like the process to go faster you can [download the blockchain directly](bootstrap.md).

Running
---------------------
The following are some helpful notes on how to run Reddcoin on your native platform. 

### Unix

You need the Qt4 run-time libraries to run Reddcoin-Qt. On Debian or Ubuntu:

	sudo apt-get install libqtgui4

Unpack the files into a directory and run:

- bin/32/reddcoin-qt (GUI, 32-bit) or bin/32/reddcoind (headless, 32-bit)
- bin/64/reddcoin-qt (GUI, 64-bit) or bin/64/reddcoind (headless, 64-bit)



### Windows

Unpack the files into a directory, and then run reddcoin-qt.exe.

### OSX

Drag Reddcoin-Qt to your applications folder, and then run Reddcoin-Qt.

### Need Help?

* See the documentation at the [Reddcoin Wiki](https://wiki.reddcoin.com/)
for help and more information.
* Ask for help on [#reddcoin](http://webchat.freenode.net?channels=reddcoin) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=reddcoin).
* Ask for help on the [ReddcoinTalk](https://reddcointalk.org/) forums, in the [Technical Support board](https://www.reddcointalk.org/category/9/troubleshooting).

Building
---------------------
The following are developer notes on how to build Reddcoin on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OSX Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-msw.md)
- [ARM Raspbian Notes](build-arm.md)

Development
---------------------
The Reddcoin repo's [root README](https://github.com/reddcoin-project/reddcoin/blob/master/README.md) contains relevant information on the development process and automated testing.

- [Coding Guidelines](coding.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/bitcoin/doxygen/)
- [Translation Process](translation_process.md)
- [Unit Tests](unit-tests.md)

### Resources
* Discuss on the [ReddcoinTalk](https://reddcointalk.org/) forums, in the [Development & Technical Discussion board](https://www.reddcointalk.org/category/4/development-discussions).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Tor Support](tor.md)

License
---------------------
Distributed under the [MIT/X11 software license](http://www.opensource.org/licenses/mit-license.php).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](http://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
