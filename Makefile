CC = g++
MAKE_CFLAGS = -g -Wall -Wextra -pedantic

ALL: main

%: %.cc
	$(CC) $(MAKE_CFLAGS) $(CFLAGS) $< -o $@

clean:
	rm main
