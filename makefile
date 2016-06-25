all:hello.out
	./hello.out
hello.out:hello.cpp
	g++ -o hello.out hello.cpp
clean:
	rm hello.out
