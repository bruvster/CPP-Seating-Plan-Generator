Compiler = g++
CFlags = -Wall -Wextra

run: build/SearchAgent.o 
	${Compiler} ${CFlags} build/SearchAgent.o  -o bin/run

build/SearchAgent.o: SearchAgent.cpp
	${Compiler} ${CFlags} -c -o build/SearchAgent.o SearchAgent.cpp 


clean:
	rm -f build/SearchAgent.o 