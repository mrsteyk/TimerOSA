TimerOSA:main.o
	g++ main.o -o TimerRe `fltk-config --ldstaticflags`
main.o:main.cxx
	g++ -std=c++11 -c main.cxx
