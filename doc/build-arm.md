## Build reddcoind, reddcoin-cli on Raspberry Pi running Raspbian

#### Keyboard-Layout
	
	sudo raspi-config
		
		(oder sudo dpkg-reconfigure keyboard-configuration)

#### Refresh system

	sudo apt-get update
	sudo apt-get upgrade
	sudo reboot

#### Install dependencies

	sudo apt-get install git automake libssl-dev libboost1.50-all-dev libboost-all-dev libminiupnpc-dev eject

#### Build BerkeleyDB

	cd ~
	wget http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz
	sudo tar -xzvf db-4.8.30.NC.tar.gz
	cd db-4.8.30.NC/build_unix
	../dist/configure --enable-cxx
	make
	sudo make install

#### Set BerkeleyDB headers

	export CPATH="/usr/local/BerkeleyDB.4.8/include"
	export LIBRARY_PATH="/usr/local/BerkeleyDB.4.8/lib"
	export LD_LIBRARY_PATH=/usr/local/BerkeleyDB.4.8/lib/

(execute this after every reboot)

#### Download source code

	cd ~
	git clone https://github.com/joroob/reddcoin.git

#### Get the Makefile

	cd reddcoin
	./autogen.sh
	./configure --with-gui=no --disable-tests	
	
		(maybe this will work: ./configure --disable-tests CXXFLAGS="--param ggc-min-expand=1 --param ggc-min-heapsize=32768" CPPFLAGS="-I${BDB_PREFIX}/include/ -O2" CXXFLAGS="-march=armv7-a -mfpu=vfpv3-d16" LDFLAGS="-L${BDB_PREFIX}/lib/" --enable-sse2=no --with-gui=no)

#### Compile reddcoind/reddcoin-cli

	cd src
	make
	sudo make install

### Additional notes
#### Create reddcoin.conf

	cd ~
	mkdir .reddcoin && cd .reddcoin
	nano reddcoin.conf
	rpcuser=<insert a username>
	rpcpassword=<insert a pwd>

#### Bootstrap.dat

	cd ~/.reddcoin
	wget https://github.com/reddcoin-project/reddcoin/releases/download/v2.0.0.0/bootstrap.dat.xz
	xz -d bootstrap.dat.xz
In order to import the Bootstrap blockchain you have to run the daemon for the first time without internet connection. It is not possible to import blocks to an already partially synchronized blockchain. The amount of connections to the network during Bootstrap-import should be 0.

#### Start the daemon

	cd ~/reddcoin/src
	./reddcoind -daemon
	./reddcoin-cli <command eg.: getinfo, getwalletinfo, getstakinginfo, ... , stop>
