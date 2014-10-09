#/bin/bash

set_environment() {
  export VERBOSE=1
  export CFLAGS="-m32 -Os -Wall -Wextra"
  export CXXFLAGS="-m32 -Os -Wall -Wextra"
  export LDFLAGS="-m32 -Os -Wall -Wextra"
  install_base_dir="$HOME/mjwm-install"
  install_dir="$install_base_dir/usr/local"
}

install_prerequisites() {
  sudo apt-get update
  sudo apt-get install g++-multilib upx
}

build() {
  ./autogen.sh
  ./configure --prefix $install_dir
  make clean
  make -j4
  make check -j4
  make install
}

crunch_binary() {
  reduce_binary_script=$(readlink -f $(dirname $0)/reduce.sh)
  pushd $install_dir/bin
  $reduce_binary_script
  popd
}

artifact() {
  mjwm_version=$($install_dir/bin/mjwm --version | cut -d' ' -f2)
  pushd $install_base_dir
  tar -cvzf mjwm.tar.gz usr
  popd
  cp $install_base_dir/mjwm.tar.gz mjwm-$mjwm_version.tar.gz
  cp $install_dir/bin/mjwm mjwm-$mjwm_version
}

puppytize() {
  mjwm_version=$($install_dir/bin/mjwm --version | cut -d' ' -f2)
  size=$(ls -lah $install_dir/bin/mjwm | awk '{print $5}')
  pushd $install_base_dir
  echo "mjwm-${mjwm_version}-i686|mjwm|${mjwm_version}-i686||Utility|${size}||mjwm-${mjwm_version}-i686.pet||Create JWM menu|Slackware|14.0||" > pet.specs
  tar -cvzf mjwm.pet usr pet.specs
  md5sum mjwm.pet | cut -d' ' -f1 >> mjwm.pet
  popd
  cp $install_base_dir/mjwm.pet mjwm-$mjwm_version.pet
}

cleanup() {
  rm -r $install_base_dir
}

set -e

set_environment
install_prerequisites
build
crunch_binary
artifact
puppytize
cleanup
