TARGET_FOLDER=$(cat target_folder.txt)
rm -rf build
mkdir build
cd build
cmake .. -DTARGET_FOLDER=${TARGET_FOLDER} -DCMAKE_CXX_COMPILER=g++-9
cmake --build .
cmake --build . --target test
cmake --build . --target package
