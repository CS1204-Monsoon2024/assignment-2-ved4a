hash_program: main.cpp HashTable.cpp
	g++ -Wall main.cpp HashTable.cpp -o hash_program.out
clean:
	rm *.out
