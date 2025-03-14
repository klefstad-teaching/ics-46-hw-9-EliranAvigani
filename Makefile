CXXFLAGS=-ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

all: ladder dijkstras

ladder: ladder_main.cpp ladder.cpp
	g++ $(CXXFLAGS) ladder_main.cpp ladder.cpp -o ladder

dijkstras: dijkstras_main.cpp dijkstras.cpp
	g++ $(CXXFLAGS) dijkstras_main.cpp dijkstras.cpp -o dijkstras

ladder_test: ladder.cpp
	g++ $(CXXFLAGS) -DTEST_LADDER ladder.cpp -o ladder_test

dijkstras_test: dijkstras.cpp
	g++ $(CXXFLAGS) -DTEST_DIJKSTRAS dijkstras.cpp -o dijkstras_test

test: ladder_test dijkstras_test
	./ladder_test
	./dijkstras_test

clean:
	/bin/rm -f ladder dijkstras ladder_test dijkstras_test