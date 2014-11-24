#/bin/sh

set_environment() {
  export VERBOSE=1
  export CFLAGS="-m32 -Os -Wall -Wextra"
  export CXXFLAGS="-m32 -Os -Wall -Wextra"
  export LDFLAGS="-m32 -Os -Wall -Wextra"
  install_base_dir=`mktemp -d`
  install_dir="${install_base_dir}/usr/local"
  mjwm_binary_path="${install_dir}/bin/mjwm"
  current_dir="$(pwd)"
}

install_prerequisites() {
  sudo apt-get update
  sudo apt-get install g++-multilib upx
}

build() {
  ./autogen.sh
  ./configure --prefix "$install_dir"
  make clean
  make -j4
  make check -j4
  make install
}

crunch_binary() {
  reduce_binary_script=$(readlink -f $(dirname $0)/reduce.sh)
  cd "${install_dir}/bin"
  "$reduce_binary_script"
  cd "$current_dir"
}

assign_properties() {
  mjwm_version=$($mjwm_binary_path --version | cut -d' ' -f2)
  mjwm_size=$(ls -lah $mjwm_binary_path | awk '{print $5}')
  mjwm_package_base_dir="mjwm-${mjwm_version}-i686"
}

prepackage() {
  mkdir -p "${install_base_dir}/${mjwm_package_base_dir}/"
  mv "${install_base_dir}/usr" "${install_base_dir}/${mjwm_package_base_dir}/"
}

artifact() {
  cd "$install_base_dir"
  tar -cvzf mjwm.tar.gz "${mjwm_package_base_dir}"
  cd "$current_dir"
  cp "${install_base_dir}/mjwm.tar.gz" "mjwm-${mjwm_version}.tar.gz"
  cp "${install_base_dir}/${mjwm_package_base_dir}/usr/local/bin/mjwm" "mjwm-${mjwm_version}"
}

puppytize() {
  cd "$install_base_dir"
  echo "${mjwm_package_base_dir}|mjwm|${mjwm_version}-i686|||${mjwm_size}||${mjwm_package_base_dir}.pet||Create JWM menu|Slackware|14.0||" > "${mjwm_package_base_dir}/pet.specs"
  tar -cvzf mjwm.pet "${mjwm_package_base_dir}"
  checksum=$(md5sum mjwm.pet | cut -d' ' -f1)
  echo -n "$checksum" >> mjwm.pet
  cd "$current_dir"
  cp $install_base_dir/mjwm.pet mjwm-$mjwm_version.pet
}

cleanup() {
  rm -r "$install_base_dir"
}

run() {
  commnd=$1
  echo "--- Start $commnd ---"
  "$commnd"
  echo "--- End $commnd ---"
}


set -e

run set_environment
run install_prerequisites
run build
run crunch_binary
run assign_properties
run prepackage
run artifact
run puppytize
run cleanup
