#!/bin/bash

# ======================================================================================
# This script is for downloading Reddcoin Core wallet v3.0.0 on a unix environment
# with a non-SSE2 CPU such as Raspberry Pi's (ARM processor).
#
# Required operating system  Raspbian Jessie, Stretch or Buster
# -------------------------  download Jessie:   https://downloads.raspberrypi.org/raspbian/images/raspbian-2017-07-05
#                            download Stretch:  https://downloads.raspberrypi.org/raspbian/images/raspbian-2019-04-09
#                            download Buster:   https://www.raspberrypi.org/downloads/raspbian
#
# How to run this script     set permission:    chmod +x reddcoin_core_download_raspbian.sh
# ----------------------     run script:        ./reddcoin_core_download_raspbian.sh
#                            start wallet:      reddcoind -daemon
#                            get wallet info:   reddcoin-cli getinfo
#                            logfile:           tail -f ~/.reddcoin/debug.log
#
# More info                  script created by: cryptoBUZE
# ---------                  github:            https://github.com/cryptoBUZE
#                            reddcoin website:  https://reddcoin.com
# ======================================================================================

## General settings
REDDCOIN_ROOT=~/reddcoin-3.0.x
BDB_PREFIX="${REDDCOIN_ROOT}/db4"
RASPBIAN_VERSION=`cat /etc/os-release | grep VERSION=`
cd ~

## OS info
case $RASPBIAN_VERSION in
  *jessie*)  RASPBIAN_VERSION="jessie" ;;
  *stretch*) RASPBIAN_VERSION="stretch" ;;
  *buster*)  RASPBIAN_VERSION="buster" ;;
  *)         echo "You are not running Rasbian Jessie, Stretch or Buster" && exit 1 ;;
esac

## SWAP file config (needed for Raspberry Pi's with 1G or less memory)
echo "--- Setting swap file to 1G ---"
sudo sed -i "/CONF_SWAPSIZE=/ s/=.*/=1000/" /etc/dphys-swapfile
sudo dphys-swapfile setup
sudo dphys-swapfile swapon

## Download and install dependencies for running binaries (if not already installed) + downloading pre compiled Reddcoin Core wallet binaries
if [ $RASPBIAN_VERSION = "jessie" ]
then
  echo "--- Installing dependencies for Raspbian Jessie ---"
  sudo apt-get update -y && sudo apt-get install -y libqt4-dev libprotobuf-dev libboost-all-dev libminiupnpc-dev wget pkg-config unzip
  sudo apt-mark hold libqt4-dev libprotobuf-dev libboost-all-dev libssl-dev libminiupnpc-dev
  # Downloading pre compiled Reddcoin Core wallet binaries with ARM cpu support
  echo "--- Downloading pre compiled Reddcoin Core wallet for Raspbian Jessie ---"
  wget https://github.com/cryptoBUZE/reddcoin/releases/download/rpi_raspbian_jessie_v3.0.0/reddcoind
  wget https://github.com/cryptoBUZE/reddcoin/releases/download/rpi_raspbian_jessie_v3.0.0/reddcoin-cli
  wget https://github.com/cryptoBUZE/reddcoin/releases/download/rpi_raspbian_jessie_v3.0.0/reddcoin-qt
fi

if [ $RASPBIAN_VERSION = "stretch" ]
then
  echo "--- Installing dependencies for Raspbian Stretch ---"
  sudo apt-get update -y && sudo apt-get install -y libqt4-dev libprotobuf-dev libboost-all-dev wget pkg-config unzip
  sudo sed -i 's/stretch/jessie/g' /etc/apt/sources.list
  sudo apt-get update -y && sudo apt-get install -y libssl-dev
  sudo sed -i 's/jessie/stretch/g' /etc/apt/sources.list
  sudo apt-mark hold libqt4-dev libprotobuf-dev libboost-all-dev libssl-dev && sudo apt-get update -y
  # Downloading pre compiled Reddcoin Core wallet binaries with ARM cpu support
  echo "--- Downloading pre compiled Reddcoin Core wallet for Raspbian Stretch ---"
  wget https://github.com/cryptoBUZE/reddcoin/releases/download/rpi_raspbian_stretch_v3.0.0/reddcoind
  wget https://github.com/cryptoBUZE/reddcoin/releases/download/rpi_raspbian_stretch_v3.0.0/reddcoin-cli
  wget https://github.com/cryptoBUZE/reddcoin/releases/download/rpi_raspbian_stretch_v3.0.0/reddcoin-qt
fi

if [ $RASPBIAN_VERSION = "buster" ]
then
  echo "--- Installing dependencies for Raspbian Buster ---"
  sudo apt-get update -y && sudo apt-get install -y libqt4-dev libprotobuf-dev wget libboost-thread-dev libboost-program-options-dev libboost-filesystem-dev libboost-system-dev
  wget https://github.com/cryptoBUZE/reddcoin/releases/download/rpi_raspbian_buster_v3.0.0/libssl1.0.0_1.0.1t-1%2Bdeb8u6_armhf.deb
  wget https://github.com/cryptoBUZE/reddcoin/releases/download/rpi_raspbian_buster_v3.0.0/libssl-dev_1.0.1t-1%2Bdeb8u6_armhf.deb
  sudo dpkg -i libssl1.0.0_1.0.1t-1+deb8u6_armhf.deb
  sudo dpkg -i libssl-dev_1.0.1t-1+deb8u6_armhf.deb
  rm libssl*
  # Downloading pre compiled Reddcoin Core wallet binaries with ARM cpu support
  echo "--- Downloading pre compiled Reddcoin Core wallet for Raspbian Buster ---"
  wget https://github.com/cryptoBUZE/reddcoin/releases/download/rpi_raspbian_buster_v3.0.0/reddcoind
  wget https://github.com/cryptoBUZE/reddcoin/releases/download/rpi_raspbian_buster_v3.0.0/reddcoin-cli
  wget https://github.com/cryptoBUZE/reddcoin/releases/download/rpi_raspbian_buster_v3.0.0/reddcoin-qt
fi

## Setting permissions
sudo chown pi reddcoin* && sudo chmod +x reddcoin*
sudo mv reddcoind reddcoin-cli reddcoin-qt /usr/local/bin

## Create reddcoin.conf file for using Reddcoin Core command line interface and RPC calls
echo "--- Creating reddcoin.conf configuration file ---"
mkdir ~/.reddcoin && cd ~/.reddcoin
echo "rpcuser="$USER >> reddcoin.conf
read RPC_PWD < <(date +%s | sha256sum | base64 | head -c 32 ; echo)
echo "rpcpassword="$RPC_PWD >> reddcoin.conf

## Download snapshot of blockchain data
echo "--- Downloading latest blockchain data for fast synchronization of blocks after wallet startup ---"
wget -O rdd_blkchain.zip https://sourceforge.net/projects/reddcoin-blockchain-snapshot/files/arm/rdd_blockchain_arm.zip/download
unzip rdd_blkchain.zip
rm rdd_blkchain.zip

echo "Done! You can now start the Reddcoin Core wallet as a daemon process with 'reddcoind -daemon' or reddcoin-qt for running the wallet in desktop mode."
