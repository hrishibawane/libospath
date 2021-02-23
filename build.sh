cd build && cmake .. -DCMAKE_INSTALL_PREFIX=../install

make install

rm libospath.a

mv Makefile ../Makefile

cd -
