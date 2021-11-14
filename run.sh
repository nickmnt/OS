#bulid
gcc -o ./Build/placer placer.c
gcc -o ./Build/finder finder.c
gcc -o ./Build/decoder decoder.c
gcc -o ./Build/MainProcess MainProcess.c
#run
cd ./Build/
./MainProcess