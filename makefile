CFLAG = -c -std=c++11 -O2 -Wall -Wextra

bin/solver: obj/main.o obj/a_star.o obj/game_grid.o | bin
	g++ -o $@ $^

obj/main.o: src/main.cpp src/game_grid.h src/a_star.h | obj
	g++ $(CFLAG) -o $@ $<

obj/a_star.o: src/a_star.cpp src/a_star.h src/game_grid.h | obj
	g++ $(CFLAG) -o $@ $<

obj/game_grid.o: src/game_grid.cpp src/game_grid.h | obj
	g++ $(CFLAG) -o $@ $<

bin:
	mkdir bin

obj:
	mkdir obj

clean:
	-rm obj/*.o
