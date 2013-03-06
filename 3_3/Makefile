TITLE = 3_3

all: $(TITLE)

$(TITLE): $(TITLE).o
	g++ $(TITLE).o -o $@

$(TITLE).o: $(TITLE).cpp
	g++ -c -Wall -g $(TITLE).cpp

clean: 
	rm -f $(TITLE).o $(TITLE)

.PHONY: all clean
