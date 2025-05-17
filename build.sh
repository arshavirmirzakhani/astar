if [ ! -d build ]; then
    mkdir build
fi

cd build
cmake .. -DBUILD_SHARED_LIBS=OFF -DSDL_STATIC=ON -DSDL_SHARED=OFF
cmake --build . --config Release
cd ..
