CC = gcc   
CFLAGS = -Wall  
CFILES =  src/red_black.c src/speed_compare.c 

all: myprogram  
	
redblack-test: 
	$(CC) $(CFLAGS) $(CFILES) tests/test_red_black.c -o test_redblack.out

speedtest:
	$(CC) $(CFLAGS) $(CFILES) -o speed_results.out

clean: 
	rm  *.out