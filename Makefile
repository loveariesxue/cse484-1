search: main.cpp 
	g++ -std=c++0x main.cpp -o search -I ./flann/headers ./flann/libs/linux/libflann_x64.a -lstdc++
