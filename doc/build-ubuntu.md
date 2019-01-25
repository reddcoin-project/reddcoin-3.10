# Building ReddCoin Core (Ubuntu)

## Clone the ReddCoin Repository.
```
	git clone https://github.com/reddcoin-project/reddcoin
```

## Install build dependency requirements
```
	sudo apt-get install build-essential libtool autotools-dev autoconf libboost-all-dev

```

## Install DB4.8 From bitcoin PPA
```
	// Add PPA
    	sudo add-apt-repository ppa:bitcoin/bitcoin
	sudo apt-get update

	// Install libdb4.8
	sudo apt-get install libdb4.8-dev libdb4.8++-dev
```

## Install Qt5 libraries.
```
	sudo apt-get install libqt5gui5 libqt5core5 libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev
```

## Install Optional Dependencies
```
	sudo apt-get install libminiupnpc-dev
	sudo apt-get install libqrencode-dev

```

## Install libssl1.0-dev
```
	// libssl1.1+ is detected incorrectly and causes build errors.
	sudo apt-get install libssl1.0-dev
```

## Build ReddCoin Core
```
	cd reddcoin
	./autogen.sh

	// If you wish to compile ReddCoin Core without wallet functionality you may use the --disable-wallet option
	./configure
	
	// You can build using multiple threads (where 4 is the number of threads.)
	make -j4
```

## Additional Notes

### UPNP
miniupnpc may be used for UPnP port mapping. It can be downloaded from here. UPnP support is compiled in and turned off by default. See the configure options for upnp behavior desired:

```
	--without-miniupnpc      No UPnP support miniupnp not required
	--disable-upnp-default   (the default) UPnP support turned off by default at runtime
	--enable-upnp-default    UPnP support turned on by default at runtime
```

### Disable Wallet Functionality

You can build ReddCoin Core Wallet functionality by using the `--disable-wallet` when you configure the build.