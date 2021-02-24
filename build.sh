cd build && cmake .. -DCMAKE_INSTALL_PREFIX=../install

make install

mv libospath.a /lib/

mv Makefile ../Makefile

cd -
