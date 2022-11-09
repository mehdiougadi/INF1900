STEPS TO FOLLOW!

make lib
./progmem -v -o out.o routine.txt
make install writeMemory
serieViaUSB -e -f out.o
make install main