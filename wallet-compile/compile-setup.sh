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