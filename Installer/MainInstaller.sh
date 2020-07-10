DIR=`pwd`

finish() {
	echo "Cleaning up..."
	rm $DIR/SDL2-2.0.3.tar.gz || true
	rm $DIR/SDL2_ttf-2.0.12.tar.gz || true
	rm $DIR/SDL2_image-2.0.0.tar.gz || true
	rm $DIR/SDL2_mixer-2.0.0.tar.gz || true
	rm -rf $DIR/SDL2_image-2.0.0  || true
	rm -rf $DIR/SDL2_ttf-2.0.12  || true
	rm -rf $DIR/SDL2-2.0.3 || true
	rm -rf $DIR/SDL2_mixer-2.0.0 || true
	rm -rf $DIR/download || true
}

trap finish EXIT

if [[ $UID != 0 ]]; then
    echo "Please run this script with sudo:"
    echo "sudo $0 $*"
    exit 1
fi

apt-get update
apt-get install -y \
	build-essential \
	libopencv-dev \
	libao-dev \
	libasound2-dev \
	libpulse-dev \
	libdbus-1-dev \
	libudev-dev 

#SDL2.0
wget https://www.libsdl.org/release/SDL2-2.0.3.tar.gz
tar -xzvf SDL2-2.0.3.tar.gz
(	
	cd SDL2-2.0.3
	./configure
	make -j4
	make install -j4
)

#Freetype2 (For SDL2_ttf)
wget https://sourceforge.net/projects/freetype/files/freetype2/2.10.2/freetype-2.10.2.tar.gz/download
tar -xzvf download
(
	cd freetype-2.10.2
	./configure --enable-freetype-config
	make -j4
	make install -j4
)

#SDL2_ttf
wget https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.12.tar.gz
tar -xzvf SDL2_ttf-2.0.12.tar.gz
(	
	cd SDL2_ttf-2.0.12
	./configure
	make -j4
	make install -j4
)

#SDL2_image
wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.0.tar.gz
tar -xzvf SDL2_image-2.0.0.tar.gz
(
	cd SDL2_image-2.0.0
	./configure
	make -j4
	make install -j4
	cd ..
)	

#SDL2_mixer
wget https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.0.tar.gz
tar -xzvf SDL2_mixer-2.0.0.tar.gz
(
	cd SDL2_mixer-2.0.0
	#SMPEG
	cd external/smpeg2-2.0.0
	./configure
	make -j4
	make install -j4
	cd ../..
	./configure
	make -j4
	make install -j4
)
