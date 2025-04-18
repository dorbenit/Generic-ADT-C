
JerryBoree: JerryBoreeMain.o MultiValueHashTable.o HashTable.o LinkedList.o KeyValuePair.o Jerry.o
	gcc JerryBoreeMain.o MultiValueHashTable.o HashTable.o LinkedList.o KeyValuePair.o Jerry.o -o JerryBoree

JerryBoreeMain.o: JerryBoreeMain.c MultiValueHashTable.h HashTable.h LinkedList.h KeyValuePair.h Defs.h Jerry.h
	gcc -c JerryBoreeMain.c

MultiValueHashTable.o: MultiValueHashTable.c MultiValueHashTable.h HashTable.h LinkedList.h Defs.h
	gcc -c MultiValueHashTable.c

HashTable.o: HashTable.c HashTable.h LinkedList.h KeyValuePair.h Defs.h
	gcc -c HashTable.c

LinkedList.o: LinkedList.c LinkedList.h KeyValuePair.h Defs.h
	gcc -c LinkedList.c

KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c

Jerry.o: Jerry.c Jerry.h Defs.h
	gcc -c Jerry.c

clean:
	rm -f *.o JerryBoree

