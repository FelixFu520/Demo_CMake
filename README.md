# CMake Demo
## 构建命令
```
cmake -H. -B "out/build/GCC 11.2.0 x86_64-linux-gnu" -G "Unix Makefiles" -D USE_LIBRARY=ON -D MAKE_SHARED_LIBRARY=OFF -D CMAKE_CXX_COMPILER=gcc -D CMAKE_BUILD_TYPE=Release -D CMAKE_CXX_FLAGS="-fno-exceptions -fno-rtti"

cmake --build "out/build/GCC 11.2.0 x86_64-linux-gnu" --verbose
cmake --build "out/build/GCC 11.2.0 x86_64-linux-gnu" --target all
cmake --build "out/build/GCC 11.2.0 x86_64-linux-gnu" --target clean
cmake --build "out/build/GCC 11.2.0 x86_64-linux-gnu" --target rebuild_cache
cmake --build "out/build/GCC 11.2.0 x86_64-linux-gnu" --target edit_cache
```

