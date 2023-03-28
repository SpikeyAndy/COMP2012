CPPFLAGS = -std=c++11 -fsanitize=address -g

all: lab4.exe

lab4.exe: Employee.o Full_time.o Contract.o main.cpp
	g++11 -o $@ $(CPPFLAGS) Employee.o Full_time.o Contract.o main.cpp

%.o: %.cpp
	g++11 $(CPPFLAGS) -c $< -o $@ 

clean:
	del *.o *.exe
# On Windows, use: del *.o *.exe
# On Linux or MacOS, use: rm -f *.o *.exe