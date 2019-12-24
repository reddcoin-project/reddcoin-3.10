# Compiling and running Reddcoin on Raspberry Pi
## 0. Overview
1. Install OS
2. Configure OS
3. Install packages
4. Compile BerkeleyDB
5. Set environmental variables
6. Download and compile Reddcoin source code
7. Reddcoin config file
8. Download Blockchain
9. Set up Reddcoin as service
10. Reddcoin-client, commands
11. Import existing wallet

## 1. Install OS
I recommend Raspbian Jessie Lite:
- Small and clean distro
  - Energy efficient
  - Quick download (400MB)
- No Reddcoin-qt Wallet with GUI required

[https://www.raspberrypi.org/downloads/raspbian/](https://www.raspberrypi.org/downloads/raspbian)

Burn downloaded image to SD card using [Etcher](https://etcher.io/)
    
## 2. Configure OS
Login using default password

    raspberry

Change keyboard layout

    sudo dpkg-reconfigure keyboard-configuration

Change default password

    passwd

Enter su (Super User) password, then return to pi user

    su
    passwd
    exit

Refresh OS

    sudo apt-get update
    sudo apt-get dist-upgrade

Enable SSH

    sudo systemctl enable ssh
    sudo systemctl start ssh
    sudo systemctl status ssh

Now you will be able to access your Raspberry Pi from a computer in the same network using SSH

- [PuTTY](http://www.putty.org/ "Download PuTTY") is a SSH client for Windows and Unix.
Download and install it: [https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html)

- Get the IP address of your Raspberry Pi (should be similar to 192.168.x.x)

        ifconfig

- Start your SSH client, enter IP address, Port 22 and open connection. Login user:pi
## 3. Install packages

    sudo apt-get install git automake libssl-dev libboost1.50-all-dev libboost-all-dev libminiupnpc-dev eject

## 4. Compile BerkeleyDB

    cd ~
    wget http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz
    sudo tar -xzvf db-4.8.30.NC.tar.gz
    cd db-4.8.30.NC/build_unix
    ../dist/configure --enable-cxx
    make
    sudo make install

## 5. Set environmental variables
1. Variables for compiling Reddcoin

        export CPATH="/usr/local/BerkeleyDB.4.8/include"
        export LIBRARY_PATH="/usr/local/BerkeleyDB.4.8/lib"

2. Variable for running Reddcoin

        sudo nano /etc/ld.so.conf.d/daemon-libs.conf 

    Copy and paste

        /usr/local/BerkeleyDB.4.8/lib/

    and save the config file.

    Reload config

        sudo ldconfig

## 6. Download and compile Reddcoin source code
1. Download source code

        cd ~
        git clone https://github.com/joroob/reddcoin.git

2. Configure Makefile

        cd reddcoin
        ./autogen.sh
        ./configure --with-gui=no --disable-tests

3. Compile reddcoind (daemon) and reddcoin-cli (client)

        cd src
        make

## 7. Reddcoin config file

    mkdir ~/.reddcoin
    nano ~/.reddcoin/reddcoin.conf

Copy and paste

    rpcuser=<Insert a random username here>
    rpcpassword=<Insert a LONG random password here>

insert username and password and save the config file.

## 8. Download Blockchain

    cd ~/.reddcoin
    wget https://github.com/reddcoin-project/reddcoin/releases/download/v2.0.0.0/bootstrap.dat.xz
    xz -d bootstrap.dat.xz

In order to import the Bootstrap blockchain you have to run Reddcoin (Step 9) for the first time without internet connection. It is not possible to import blocks to an already partially network-synchronized blockchain. The amount of connections to the network during import should be 0. The import process will take several hours.

## 9. Set up Reddcoin as service
1. Create service file

        sudo nano /etc/systemd/system/reddcoin.service

    Copy and paste

        [Unit]
        Description=Reddcoin
        [Service]
        User=pi
        ExecStart=/home/pi/reddcoin/src/reddcoind
        WorkingDirectory=/home/pi/reddcoin/src/
        Restart=always
        [Install]
        WantedBy=multi-user.target
    
    and save the service file.

2. Register, enable and start Reddcoin service (Reddcoin daemon)

        sudo systemctl daemon-reload
        sudo systemctl enable reddcoin.service
        sudo systemctl start reddcoin.service

    Check service status

        sudo systemctl status reddcoin.service

Reddcoin will now auto start on startup and auto start after service crash.



---
If it is necessary, use

    sudo systemctl disable reddcoin.service
    
to stop Reddcoin service
## 10. Reddcoin client, commands
We interact with the Reddcoin service using the Reddcoin client

    ~/reddcoin/src/reddcoin-cli help

To avoid typing the full file path all the time

    sudo cp ~/reddcoin/src/reddcoin-cli /usr/local/bin

From now on you can type *redd* and double tab for autocompletion
### Important commands
*Enable staking*

    reddcoin-cli walletpassphrase yourpassword 9999999 true

You have to enter your wallet passphrase every time you disable and reenable the Reddcoin service (e.g. reboot)

Make sure to delete your shell's history after you entered your wallet passphrase. Bash command:

    > ~/.bash_history && history -c

</br>

*General information*

    reddcoin-cli getinfo

*Information about staking process*

    reddcoin-cli getstakinginfo

*Last transactions*

    reddcoin-cli listtransactions

## 11. Import existing wallet
Here we use FileZilla's SFTP (SSH file transfer protocol). You configure FileZilla the same way you configured PuTTY: IP of your Raspberry Pi, User:pi, your password.
1. Disable Reddcoin service
2. In FileZilla open connection to your Raspberry Pi and drag and drop your existing wallet.dat file into the .reddcoin folder
3. Enable Reddcoin service
4. Reddcoin will now autostart and rescan blockchain for transactions assoziated with your addresses. This will take some time. During the rescan Reddcoin service is not responding

</br>
</br>
---
I hope everything worked fine! It took some time to write this up.
Leave a small tip Rb8754QZvpbw6DjrMV1qX9SnHzYnSyXRMC




