objects=Exercise_15.o RBTImplementation.o
Exercise_15 : $(objects)
	gcc $(objects) -o Exercise_15
Exercise_15.o :Exercise_15.c RBTInterface.h RBTTypes.h
	gcc -c Exercise_15.c
RBTImplementation.o :RBTImplementation.c RBTInterface.h RBTTypes.h
	gcc -c RBTImplementation.c
clean:
	rm Exercise_15 $(objects)
