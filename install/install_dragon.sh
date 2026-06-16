#!/bin/bash
echo updating compilation tools
sudo apt update && sudo apt upgrade -y
sudo apt install -y build-essential cmake git jsoncpp-dev libuuid1 uuid-dev zlib1g-dev libssl-dev
echo install PostgreSQL
sudo apt install -y libpq-dev
sudo apt update
sudo apt install -y postgresql postgresql-contrib
sudo apt install -y libjsoncpp-dev
sudo apt install -y uuid-dev
sudo apt install -y libssl-dev zlib1g-dev
echo install dragon
git clone https://github.com/drogonframework/drogon.git
cd drogon
git submodule update --init
mkdir build
cd build
cmake ..
make -j$(nproc)
sudo make install

