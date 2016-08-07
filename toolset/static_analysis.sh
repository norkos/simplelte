cppcheck --enable=warning,performance,style CP_*
cd build && cmake .. && scan-build-3.8 make -j3
