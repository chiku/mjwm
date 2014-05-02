#/bin/bash

set -e

reduce_binary_script=$(readlink -f $(dirname $0)/reduce.sh)

sudo apt-get update
sudo apt-get install g++-multilib upx

export CFLAGS="-Os -Wall -Wextra"
export CXXFLAGS="-Os -Wall -Wextra"
export LDFLAGS="-Os -Wall -Wextra"

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

rm -r $HOME/mjwm-install
