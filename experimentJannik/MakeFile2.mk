OBJECTS = "H:\Informatik\C++\blow-off-those-legs\experimentJannik\soldier.o"

prog: $(OBJECTS)
	H:\Programme\Dev-Cpp\MinGW64\bin\g++.exe $(OBJECTS) -o H:\Informatik\tmp\soldier.exe -std=c++11 -Wall

%.o: "H:\Informatik\C++\blow-off-those-legs\experimentJannik\soldier.cpp" "H:\Informatik\C++\blow-off-those-legs\experimentJannik\soldier.hpp"
	"H:\Programme\Dev-Cpp\MinGW64\bin\g++" -c "H:\Informatik\C++\blow-off-those-legs\experimentJannik\soldier.cpp" -std=c++11