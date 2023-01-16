gcc -c code/*.c 

g++ -c code/*.cpp 

g++ *.o -lgdi32 -lole32 -loleaut32 -luuid -lwinmm -lmsimg32 -o sprite.exe

