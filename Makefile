CC = g++
MAKE_CFLAGS = -g -Wall -Wextra -pedantic

PROGS=container matrix separate main
ALL: $(PROGS)

%: %.cc %.h
	$(CC) $(MAKE_CFLAGS) $(CFLAGS) $< -o $@

clean:
	rm -f $(PROGS)
