# Makefile
#

-include test_cases.mk

SHELL=/bin/sh

.SUFFIXES:
.SUFFIXES: .cc .h

PRG=graphColoring
DOT=*.dot
OBJS=main.o\
	 graph.o\
	 dsatur.o\
	 hybrid.o\
	 lmxrlf.o\
	 chordal.o\
	 tabucol.o\
	 graph_coloring.o

CXXFLAGS=-Wall
CXXFLAGS+=-Iinclude/

TEST?=wheel

vpath %.h include/
vpath %.cc src/

.PHONY:cleanup clean all debug release
all: release

release: $(PRG)
	$(MAKE) cleanup

debug: $(PRG)

$(PRG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(PRG) $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

#----------------------------------------------
# Cleaning Commands
#----------------------------------------------

cleanup:
	@rm -f $(OBJS) $(DOT)

clean: cleanup
	@rm -f $(PRG)

#----------------------------------------------
# Test Running Command
#----------------------------------------------

test: $(PRG)
ifeq ($(TEST),fullins)
	@echo "Running Fullins Test Suite"
	@for test in $(FULLINS) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),insertions)
	@echo "Running Insertions Test Suite"
	@for test in $(INSERTIONS) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),anna)
	@echo "Running Anna Test Suite"
	@for test in $(ANNA) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),ash)
	@echo "Running Ash Test Suite"
	@for test in $(ASH) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),david)
	@echo "Running David Test Suite"
	@for test in $(DAVID) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),dsjc)
	@echo "Running DSJC Test Suite"
	@for test in $(DSJC) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),dsjr)
	@echo "Running DSJR Test Suite"
	@for test in $(DSJR) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),flat)
	@echo "Running Flat Test Suite"
	@for test in $(FLAT) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),fpsol)
	@echo "Running FPSOL Test Suite"
	@for test in $(FPSOL) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),games)
	@echo "Running Games Test Suite"
	@for test in $(GAMES) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),homer)
	@echo "Running Homer Test Suite"
	@for test in $(HOMER) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),huck)
	@echo "Running Huck Test Suite"
	@for test in $(HUCK) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),inithx)
	@echo "Running Inithx Test Suite"
	@for test in $(INITHX) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),jean)
	@echo "Running Jean Test Suite"
	@for test in $(JEAN) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),le)
	@echo "Running Le Test Suite"
	@for test in $(LE) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),miles)
	@echo "Running Miles Test Suite"
	@for test in $(MILES) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),mug)
	@echo "Running Mug Test Suite"
	@for test in $(MUG) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),mulsol)
	@echo "Running Mulsol Test Suite"
	@for test in $(MULSOL) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),myciel)
	@echo "Running Myciel Test Suite"
	@for test in $(MYCIEL) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),queen)
	@echo "Running Queen Test Suite"
	@for test in $(INSERTIONS) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),r125)
	@echo "Running R125 Test Suite"
	@for test in $(R125) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),r250)
	@echo "Running R250 Test Suite"
	@for test in $(R250) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),r1000)
	@echo "Running R1000 Test Suite"
	@for test in $(R1000) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),rtotal)
	@echo "Running All R Test Suites"
	@for test in $(RTOTAL) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),school)
	@echo "Running School Test Suite"
	@for test in $(SCHOOL) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),will)
	@echo "Running Will Test Suite"
	@for test in $(WILL) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),zeroni)
	@echo "Running Zeroni Test Suite"
	@for test in $(ZERONI) ; do \
		./$(PRG) $$test -e ; \
	done
else ifeq ($(TEST),bondymurty)
	@echo "Running Bondy-Murty Test Suite"
	@for test in $(BONDYMURTY) ; do \
		./$(PRG) $$test -t ; \
	done
else ifeq ($(TEST),chvatal)
	@echo "Running Chvatal Test Suite"
	@for test in $(CHVATAL) ; do \
		./$(PRG) $$test -t ; \
	done
else ifeq ($(TEST),cube)
	@echo "Running Cube Test Suite"
	@for test in $(CUBE) ; do \
		./$(PRG) $$test -t ; \
	done
else ifeq ($(TEST),dodeca)
	@echo "Running Dodecahedron Test Suite"
	@for test in $(DODECA) ; do \
		./$(PRG) $$test -t ; \
	done
else ifeq ($(TEST),grotzsch)
	@echo "Running Grotzsch Test Suite"
	@for test in $(GROTZSCH) ; do \
		./$(PRG) $$test -t ; \
	done
else ifeq ($(TEST),grunbaum)
	@echo "Running Grunbaum Test Suite"
	@for test in $(GRUNBAUM) ; do \
		./$(PRG) $$test -t ; \
	done
else ifeq ($(TEST),icosa)
	@echo "Running Icosahedron Test Suite"
	@for test in $(ICOSA) ; do \
		./$(PRG) $$test -t ; \
	done
else ifeq ($(TEST),kuratowski)
	@echo "Running Kuratowski Test Suite"
	@for test in $(KURATOWSKI) ; do \
		./$(PRG) $$test -t ; \
	done
else ifeq ($(TEST),india)
	@echo "Running Map of India Test Suite"
	@for test in $(INDIA) ; do \
		./$(PRG) $$test -t ; \
	done
else ifeq ($(TEST),mycielski)
	@echo "Running Mycielski Test Suite"
	@for test in $(MYCIELSKI) ; do \
		./$(PRG) $$test -t ; \
	done
else ifeq ($(TEST),octa)
	@echo "Running Octahedron Test Suite"
	@for test in $(OCTA) ; do \
		./$(PRG) $$test -t ; \
	done
else ifeq ($(TEST),petersen)
	@echo "Running Petersen Test Suite"
	@for test in $(PETERSEN) ; do \
		./$(PRG) $$test -t ; \
	done
else ifeq ($(TEST),ramsey)
	@echo "Running Ramsey Test Suite"
	@for test in $(RAMSEY) ; do \
		./$(PRG) $$test -t ; \
	done
else ifeq ($(TEST),tetra)
	@echo "Running Tetrahedron Test Suite"
	@for test in $(TETRA) ; do \
		./$(PRG) $$test -t ; \
	done
else ifeq ($(TEST),wheel)
	@echo "Running Wheel Test Suite (Default)"
	@for test in $(WHEEL) ; do \
		./$(PRG) $$test -t ; \
	done
else ifeq ($(TEST),all)
	@echo "Running All Test Test Suites"
	@for test in $(LIST) ; do \
		./$(PRG) $$test -e ; \
	done
	@for test in $(MATRIX) ; do \
		./$(PRG) $$test -t ; \
	done
else
	@echo $(TEST) is not a valid test suite
endif
