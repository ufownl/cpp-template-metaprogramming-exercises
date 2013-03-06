all: finite_state_machine

finite_state_machine: main.o
	g++ main.o -o $@

main.o: event_dispatcher.h finite_state_machine.h generate_dispatcher.h main.cpp
	g++ -c -Wall -g main.cpp

clean:
	rm -f main.o finite_state_machine

.PHONY: all clean
