deps="cmake gcc g++ make unzip wget"
if [ "$ARCH" = "x64" ]
then
  dpkg --add-architecture i386
  deps="${deps} g++-multilib"
fi
apt-get update && apt-get install -y $deps
