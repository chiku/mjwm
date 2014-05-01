sudo apt-get update
sudo apt-get install g++-multilib upx
./autogen.sh
./configure
make -j4
make check -j4
./reduce.sh
