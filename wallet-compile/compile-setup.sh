#!/bin/bash


#GIT Global config
GIT_USER_EMAIL = 'simulacrum.live@gmail.com'
git config --global user.name $GIT_USER_EMAIL
git config --global user.email $GIT_USER_EMAIL

#Get the setup script
curl -L -O https://raw.githubusercontent.com/simulacrum-trade/simulacrum/master/contrib/gitian-build.py

#make it executable
chmod +x gitian-build.py

#Get the prerequisites
sudo apt-get update
sudo apt-get install apt-cacher-ng

#Run the compile environment setup
./gitian-build.py --docker --setup


#add the macos required inputs for the gitian builder
wget https://github.com/simulacrum-trade/simulacrum/raw/master/wallet-compile/MacOSX10.11.sdk.tar.gz
wget https://github.com/simulacrum-trade/simulacrum/raw/master/wallet-compile/osslsigncode-1.7.1.tar.gz
mkdir gitian-builder
mkdir gitian-builder/inputs
cp MacOSX10.11.sdk.tar.gz gitian-builder/inputs/
cp osslsigncode-1.7.1.tar.gz gitian-builder/inputs/

#Run the compile
./gitian-build.py --docker -b -c -o w,l,m --detach-sign simulacrum master
