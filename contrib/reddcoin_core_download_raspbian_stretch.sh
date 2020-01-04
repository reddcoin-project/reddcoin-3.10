#!/bin/bash

# ======================================================================================
# This script is for compiling Reddcoin Core wallet v3.0.0 on a unix environment
# with a non-SSE2 CPU such as Raspberry Pi's (ARM processor).
#
# Required operating system  Raspbian Stretch
# -------------------------  https://downloads.raspberrypi.org/raspbian/images/raspbian-2019-04-09
#
# How to run this script     set permission:    chmod +x reddcoin_core_download_raspbian_stretch.sh
# ----------------------     run script:        ./reddcoin_core_download_raspbian_stretch.sh
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

# Download and install dependencies for source code build
sudo apt-get update -y && sudo apt-get install -y libqt4-dev libprotobuf-dev libboost-all-dev wget pkg-config unzip
sudo sed -i 's/stretch/jessie/g' /etc/apt/sources.list
sudo apt-get update -y && sudo apt-get install -y libssl-dev
sudo sed -i 's/jessie/stretch/g' /etc/apt/sources.list

# Downloading Reddcoin Core wallet with ARM cpu support
wget https://github.com/cryptoBUZE/reddcoin/releases/download/rpi_raspbian_stretch_v3.0.0/reddcoin-cli
wget https://github.com/cryptoBUZE/reddcoin/releases/download/rpi_raspbian_stretch_v3.0.0/reddcoind
sudo chown pi reddcoin* && sudo chmod +x reddcoin*
sudo mv reddcoin* /usr/local/bin

# Create reddcoin.conf file for using Reddcoin Core command line interface and RPC calls
mkdir ~/.reddcoin && cd ~/.reddcoin
echo "rpcuser="$USER >> reddcoin.conf
read RPC_PWD < <(date +%s | sha256sum | base64 | head -c 32 ; echo)
echo "rpcpassword="$RPC_PWD >> reddcoin.conf

# Download snapshot of blockchain data
wget -O rdd_blkchain.zip https://sourceforge.net/projects/reddcoin-blockchain-snapshot/files/arm/rdd_blockchain_arm.zip/download
unzip rdd_blkchain.zip
rm rdd_blkchain.zip

# Running Reddcoin Core wallet daemon process
reddcoind -daemon