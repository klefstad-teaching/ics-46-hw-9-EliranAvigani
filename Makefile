CXXFLAGS=-ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

all: ladder dijkstras

ladder: src/ladder_main.cpp src/ladder.cpp
	g++ $(CXXFLAGS) src/ladder_main.cpp src/ladder.cpp -o ladder

dijkstras: src/dijkstras_main.cpp src/dijkstras.cpp
	g++ $(CXXFLAGS) src/dijkstras_main.cpp src/dijkstras.cpp -o dijkstras

ladder_test: src/ladder.cpp
	g++ $(CXXFLAGS) -DTEST_LADDER src/ladder.cpp -o ladder_test

dijkstras_test: src/dijkstras.cpp
	g++ $(CXXFLAGS) -DTEST_DIJKSTRAS src/dijkstras.cpp -o dijkstras_test

test: ladder_test dijkstras_test
	./ladder_test
	./dijkstras_test

clean:
	/bin/rm -f ladder dijkstras ladder_test dijkstras_test