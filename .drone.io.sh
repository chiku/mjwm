#/bin/bash

set -e

export CFLAGS="-m32 -Os -Wall -Wextra"
export CXXFLAGS="-m32 -Os -Wall -Wextra"
export LDFLAGS="-m32 -Os -Wall -Wextra"
export VERBOSE=1

reduce_binary_script=$(readlink -f $(dirname $0)/reduce.sh)

sudo apt-get update
sudo apt-get install g++-multilib upx

./autogen.sh
./configure --prefix $HOME/mjwm-install/usr/local
make clean
make -j4
make check -j4
make install

$reduce_binary_script

pushd $HOME/mjwm-install/usr/local/bin
mjwm_version=$(./mjwm --version | cut -d' ' -f2)
$reduce_binary_script
popd

pwd
pushd $HOME/mjwm-install
ls -l
tar -cvzf mjwm.tar.gz usr
popd
cp $HOME/mjwm-install/mjwm.tar.gz mjwm-$mjwm_version.tar.gz
cp $HOME/mjwm-install/usr/local/bin/mjwm mjwm-$mjwm_version

rm -r $HOME/mjwm-install
