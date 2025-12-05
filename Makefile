CC = gcc   # This variable is which compiler to use, we will use the variable later by $(CC)
CFLAGS = -Wall  # this variable is command line arguments
CFILES =  src/red_black.c src/speed_compare.c 

all: myprogram  #runs target myprogram is nothing is passed into make

myprogram: # it needs to compile out to >>>map.out<<<!
	$(CC) $(CFLAGS) -o map.out $(CFILES)  
	
redblack-test: 
	$(CC) $(CFLAGS) $(CFILES) tests/test_red_black.c -o test_redblack.out

speedtest:
	$(CC) $(CFLAGS) $(CFILES)  -o speed_results.out


clean: #this is a clean target, it removes all the .out files, called via > make clean
	rm  *.out