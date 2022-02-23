SOURCES = $(wildcard src/*.cpp)

.PHONY: build run clean

build: target/main.exe

run: target/main.exe
	./target/main.exe

clean:
	rm ./target/main.exe

target/main.exe: $(SOURCES) | target
	g++ -Wall -Wextra -Wno-sign-compare -std=c++17 -march=native -O3 src/main.cpp -o $@

target:
	mkdir target
