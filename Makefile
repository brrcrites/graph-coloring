# Makefile
#

-include test_cases.mk

SHELL=/bin/sh

.SUFFIXES:
.SUFFIXES: .cc .h

PRG=graphColoring
OBJS=main.o\
	 graph.o\
	 dsatur.o\
	 hybrid.o\
	 lmxrlf.o\
	 chordal.o\
	 tabucol.o\
	 graph_coloring.o
DOT=*.dot

TEST=$(WHEEL)

CXXFLAGS=-Wall
CXXFLAGS+=-Iinclude/


vpath %.h include/
vpath %.cc src/

.PHONY:cleanup clean all debug release
all: release

release: $(PRG)
	$(MAKE) cleanup

debug: $(PRG)

$(PRG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(PRG) $^

test: $(PRG)
	./$(PRG) $(TEST)
	

#----------------------------------------------

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

cleanup:
	@rm -f $(OBJS) $(DOT)

clean: cleanup
	@rm -f $(PRG)
