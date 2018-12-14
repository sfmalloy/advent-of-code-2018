CXX      = g++

CXXFLAGS = -O3 -Wall

LINK     := $(CXX)

Advent : Advent.o
	$(LINK) $(CXXFLAGS) $^ -o $@

Advent.o : Advent.cc Day.hpp Day01.hpp Day02.hpp Day03.hpp Day04.hpp Day05.hpp Day06.hpp Day08.hpp Day11.hpp

clean :
	@$(RM) Advent
