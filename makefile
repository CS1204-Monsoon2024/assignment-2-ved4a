# Target to build the hash table program
hash_program: main.cpp HashTable.cpp
	g++ -Wall main.cpp HashTable.cpp -o hash_program.out

# Clean up generated files
clean:
	rm *.out