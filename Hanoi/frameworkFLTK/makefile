CXX = g++-8.2.0
CXXFLAGS = -g -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer

.SUFFIXES:

objs = game.o gameengine.o player.o ai.o pancakestack.o minimax.o find_solution.o Graph.o GUI.o Window.o Simple_window.o
ncurses = -lfltk -lfltk_images

all: main

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main: main.o $(objs) $(ncurses)

test: test.o  $(objs) $(ncurses)


run%: %
	@./$<

clean:
	$(RM) $(filter-out find_solution.o, $(wildcard *.o)) main test
