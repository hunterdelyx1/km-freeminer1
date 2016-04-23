# Kmfreeminer

Kmfreeminer is an open source sandbox game inspired by [Minecraft](https://minecraft.net/).

Kmfreeminer is based on freeminer which is developed by a [number of contributors](https://github.com/freeminer/freeminer/graphs/contributors) from all over the globe.

## Installing

## Default controls
- `W` `A` `S` `D`: move
- `Space`: jump/climb
- `Shift`: sneak/go down
- `Q`: drop item
- `I`: inventory
- Mouse: turn/look
- Mouse left: dig/punch
- Mouse right: place/use
- Mouse wheel: select item
- `Esc`: pause menu
- `T`: chat
- `Z`: zoom
- `Tab`: player list
- `~`: toggle console

## Compiling
Install dependencies. Here's an example for

Debian/Ubuntu:
```sh
sudo apt-get install build-essential libirrlicht-dev cmake libbz2-dev \
libpng12-dev libjpeg-dev libfreetype6-dev libxxf86vm-dev libgl1-mesa-dev \
libsqlite3-dev libvorbis-dev libopenal-dev libcurl4-openssl-dev libluajit-5.1-dev \
libleveldb-dev libsnappy-dev libgettextpo0 libmsgpack-dev libgmp-dev libspatialindex-dev
# optional:
sudo apt-get install libhiredis-dev cmake-curses-gui
```
___
Fedora:
```sh
# the first five is the closest to Debian/Ubuntu build-essential
sudo yum install make automake gcc gcc-c++ kernel-devel cmake \
irrlicht-devel bzip2-devel libpng-devel libjpeg-turbo-devel freetype-devel \
libXxf86vm-devel mesa-libGL-devel sqlite-devel libvorbis-devel \
openal-soft-devel libcurl-devel luajit-devel leveldb-devel snappy-devel \
gettext-devel msgpack msgpack-devel spatialindex-devel
```
___
Arch Linux:
```sh
sudo pacman -S curl irrlicht leveldb libvorbis luajit openal sqlite cmake msgpack-c freetype2
```
___
Gentoo/Funtoo:
```sh
emerge -av media-libs/libvorbis media-libs/openal dev-games/irrlicht \
dev-libs/msgpack dev-libs/leveldb sci-libs/libspatialindex
```
___
OS X:
```sh
brew install cmake freetype gettext hiredis irrlicht jpeg leveldb libogg \
libvorbis luajit msgpack
```

<sup>Recommended irrlicht version: `1.8.2`</sup>

Download source code:
<<<<<<< HEAD
```sh
git clone --recursive https://github.com/kmfreeminer/kmfreeminer.git
cd kmfreeminer
```

<sup>Recommended minimum compiler version: `gcc 4.8` or `clang 3.3`</sup>

Build it (GNU/Linux):
```sh
mkdir _build && cd _build
cmake ..
nice make -j $(nproc || sysctl -n hw.ncpu || echo 2)
```

or for debian based:
```sh
curl https://raw.githubusercontent.com/freeminer/freeminer/master/build/debian_ogles.sh | sh
```

Build it (OS X):
```sh
mkdir _build && cd _build
cmake .. -DGETTEXT_LIBRARY=/usr/local/opt/gettext/lib/libgettextlib.dylib -DGETTEXT_INCLUDE_DIR=/usr/local/opt/gettext/include
make -j8 package
```
(if the make command doesn't work on OS X install bsdmake)

Build it (windows):

[vs2013](build/windows_vs2015)

[vs2015](build/windows)


Play it!
```
cd ..
bin/freeminer
```
