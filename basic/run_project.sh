rm -rf build
mkdir build
cd build
cmake ..
make -j8
cd ..

cp build/src/$1.uf2 /media/plaao/RPI-RP2/$1.uf2
