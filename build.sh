BUILD_FOLDER=$(cat build_folder.txt)
rm -rf build
mkdir build
cd build
cmake .. -DBUILD_FOLDER=${BUILD_FOLDER}
cmake --build .
cmake --build . --target test
cmake --build . --target package
