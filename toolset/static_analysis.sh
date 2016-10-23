cppcheck --enable=warning,performance,style CP_*
cd build && cmake .. -DCMAKE_CXX_COMPILER="clang++-3.8" -DCMAKE_CXX_FLAGS="-std=c++1y" && scan-build-3.8 make -j3
