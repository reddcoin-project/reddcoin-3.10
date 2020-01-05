#!/bin/bash

# ======================================================================================
# This script is for compiling Reddcoin Core wallet v3.0.0 on a unix environment
# with a non-SSE2 CPU such as Raspberry Pi's (ARM processor).
#
# Required operating system  Raspbian Buster
# -------------------------  https://www.raspberrypi.org/downloads/raspbian
#
# How to run this script     set permission:    chmod +x reddcoin_core_compile_raspbian_buster.sh
# ----------------------     run script:        ./reddcoin_core_compile_raspbian_buster.sh
#                            start wallet:      reddcoind -daemon
#                            get wallet info:   reddcoin-cli getinfo
#                            logfile:           tail -f ~/.reddcoin/debug.log
#
# More info                  script created by: cryptoBUZE
# ---------                  github:            https://github.com/cryptoBUZE
#                            reddcoin website:  https://reddcoin.com
# ======================================================================================

# General settings
REDDCOIN_ROOT=~/reddcoin-3.0.x
BDB_PREFIX="${REDDCOIN_ROOT}/db4"
cd ~

# SWAP file config (needed for Raspberry Pi's with 1G or less memory)
sudo sed -i "/CONF_SWAPSIZE=/ s/=.*/=1000/" /etc/dphys-swapfile
sudo dphys-swapfile setup
sudo dphys-swapfile swapon

# Change apt source repo from buster to stretch since we need dependencies with some older versions
sudo sed -i 's/buster/stretch/' /etc/apt/sources.list

# Download and install dependencies for source code build
sudo apt-get update -y && sudo apt-get install -y git build-essential libqt4-dev libprotobuf-dev protobuf-compiler libtool autotools-dev autoconf wget pkg-config libboost-thread-dev libboost-program-options-dev libboost-filesystem-dev libboost-system-dev
wget https://github.com/cryptoBUZE/reddcoin/releases/download/rpi_raspbian_buster_v3.0.0/libssl1.0.0_1.0.1t-1%2Bdeb8u6_armhf.deb
wget https://github.com/cryptoBUZE/reddcoin/releases/download/rpi_raspbian_buster_v3.0.0/libssl-dev_1.0.1t-1%2Bdeb8u6_armhf.deb
sudo dpkg -i libssl1.0.0_1.0.1t-1+deb8u6_armhf.deb
sudo dpkg -i libssl-dev_1.0.1t-1+deb8u6_armhf.deb

# Downloading and unpacking of Reddcoin Core wallet source code with ARM cpu support
wget 'https://github.com/reddcoin-project/reddcoin/archive/v3.0.x.zip'
unzip v3.0.x.zip && rm v3.0.x.zip

# Downloading and unpacking of Berkeley database
wget 'http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz'
tar -xzvf db-4.8.30.NC.tar.gz && rm -r db-4.8.30.NC.tar.gz

# Compile Berkeley database and Reddcoin Core wallet source files
mkdir -p $BDB_PREFIX
cd db-4.8.30.NC/build_unix/
../dist/configure --enable-cxx --disable-shared --with-pic --prefix=$BDB_PREFIX
make install
cd $REDDCOIN_ROOT
./autogen.sh
./configure --disable-tests LDFLAGS="-L${BDB_PREFIX}/lib/" CPPFLAGS="-I${BDB_PREFIX}/include/ -O2"
make

# Shrink compiled files and making Reddcoin Core wallet available system-wide
strip src/reddcoind && strip src/reddcoin-cli && strip src/qt/reddcoin-qt
sudo make install

# Cleanup after compile
sudo rm -r $REDDCOIN_ROOT ~/db-4.8.30.NC ~/libssl*

# Create reddcoin.conf file for using Reddcoin Core command line interface and RPC calls
mkdir ~/.reddcoin && cd ~/.reddcoin
echo "rpcuser="$USER >> reddcoin.conf
read RPC_PWD < <(date +%s | sha256sum | base64 | head -c 32 ; echo)
echo "rpcpassword="$RPC_PWD >> reddcoin.conf

# Download snapshot of blockchain data
wget -O rdd_blkchain.zip https://sourceforge.net/projects/reddcoin-blockchain-snapshot/files/arm/rdd_blockchain_arm.zip/download
unzip rdd_blkchain.zip
rm rdd_blkchain.zip
