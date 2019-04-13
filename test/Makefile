include ../mk.inc

all:
	$(CC) $(CFLAGS) *.c -o UT -L ../src -lsample -L wrap -lwrap $(LDFLAGS)

clean:
	@rm UT *.gc* 2>/dev/null
