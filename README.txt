To build the project make sure you have CMake and a C++ compiler (e. g., g++) installed.
Run these commands in the root folder to build the project (might take a while because cmake will fetch gtest):

mkdir ./build
cd ./build
cmake ../
make

Then you can do:

./run_tests

