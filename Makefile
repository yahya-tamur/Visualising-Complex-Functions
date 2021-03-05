CC = clang
CXX = clang++

#gifenc gives some unused-value errors
#add -Ofast
CFLAGS = -Ofast -Wall -Werror -Wextra -Wpedantic
CXXFLAGS = -Ofast -Wall -Werror -Wextra -Wpedantic

all: a.out

a.out: gifenc.o testImage.o params.o
	$(CXX) $(CXXFLAGS) gifenc.o testImage.o params.o

gifenc.o: gifenc.c gifenc.h
	$(CC) $(CFLAGS) -c gifenc.c

testImage.o: testImage.cc
	$(CXX) $(CXXFLAGS) -c testImage.cc

params.o: params.cc params.h
	$(CXX) $(CXXFLAGS) -c params.cc

clean:
	rm -rf gifenc.o testImage.o params.o a.out

