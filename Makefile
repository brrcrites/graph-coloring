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
	 mcs.o\
	 tabucol.o\

CXXFLAGS=-Wall
CXXFLAGS+=-Iinclude/

TEST?=wheel
TEST_ARG?=$(WHEEL)
TEST_FLAG?=-m

vpath %.h include/
vpath %.cc src/

.PHONY:cleanup clean all debug release test

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

setflags: $(PRG)
ifeq ($(TEST),fullins)
	@echo "Running Fullins Test Suite"
	@$(eval TEST_ARG=$(FULLINS))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),insertions)
	@echo "Running Insertions Test Suite"
	@$(eval TEST_ARG=$(INSERTIONS))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),anna)
	@echo "Running Anna Test Suite"
	@$(eval TEST_ARG=$(ANNA))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),ash)
	@echo "Running Ash Test Suite"
	@$(eval TEST_ARG=$(ASH))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),david)
	@echo "Running David Test Suite"
	@$(eval TEST_ARG=$(DAVID))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),dsjc)
	@echo "Running DSJC Test Suite"
	@$(eval TEST_ARG=$(DSJC))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),dsjr)
	@echo "Running DSJR Test Suite"
	@$(eval TEST_ARG=$(DSJR))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),flat)
	@echo "Running Flat Test Suite"
	@$(eval TEST_ARG=$(FLAT))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),fpsol)
	@echo "Running FPSOL Test Suite"
	@$(eval TEST_ARG=$(FPSOL))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),games)
	@echo "Running Games Test Suite"
	@$(eval TEST_ARG=$(GAMES))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),homer)
	@echo "Running Homer Test Suite"
	@$(eval TEST_ARG=$(HOMER))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),huck)
	@echo "Running Huck Test Suite"
	@$(eval TEST_ARG=$(HUCK))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),inithx)
	@echo "Running Inithx Test Suite"
	@$(eval TEST_ARG=$(INITHX))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),jean)
	@echo "Running Jean Test Suite"
	@$(eval TEST_ARG=$(JEAN))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),le)
	@echo "Running Le Test Suite"
	@$(eval TEST_ARG=$(LE))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),miles)
	@echo "Running Miles Test Suite"
	@$(eval TEST_ARG=$(MILES))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),mug)
	@echo "Running Mug Test Suite"
	@$(eval TEST_ARG=$(MUG))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),mulsol)
	@echo "Running Mulsol Test Suite"
	@$(eval TEST_ARG=$(MULSOL))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),myciel)
	@echo "Running Myciel Test Suite"
	@$(eval TEST_ARG=$(MYCIEL))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),queen)
	@echo "Running Queen Test Suite"
	@$(eval TEST_ARG=$(QUEEN))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),r125)
	@echo "Running R125 Test Suite"
	@$(eval TEST_ARG=$(R125))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),r250)
	@echo "Running R250 Test Suite"
	@$(eval TEST_ARG=$(R250))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),r1000)
	@echo "Running R1000 Test Suite"
	@$(eval TEST_ARG=$(R1000))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),rtotal)
	@echo "Running All R Test Suites"
	@$(eval TEST_ARG=$(RTOTAL))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),school)
	@echo "Running School Test Suite"
	@$(eval TEST_ARG=$(SCHOOL))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),will)
	@echo "Running Will Test Suite"
	@$(eval TEST_ARG=$(WILL))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),zeroin)
	@echo "Running Zeroin Test Suite"
	@$(eval TEST_ARG=$(ZEROIN))
	@$(eval TEST_FLAG=-l)
else ifeq ($(TEST),bondymurty)
	@echo "Running Bondy-Murty Test Suite"
	@$(eval TEST_ARG=$(BONDYMURTY))
	@$(eval TEST_FLAG=-m)
else ifeq ($(TEST),chvatal)
	@echo "Running Chvatal Test Suite"
	@$(eval TEST_ARG=$(CHVATAL))
	@$(eval TEST_FLAG=-m)
else ifeq ($(TEST),cube)
	@echo "Running Cube Test Suite"
	@$(eval TEST_ARG=$(CUBE))
	@$(eval TEST_FLAG=-m)
else ifeq ($(TEST),dodeca)
	@echo "Running Dodecahedron Test Suite"
	@$(eval TEST_ARG=$(DODECA))
	@$(eval TEST_FLAG=-m)
else ifeq ($(TEST),grotzsch)
	@echo "Running Grotzsch Test Suite"
	@$(eval TEST_ARG=$(GROTZSCH))
	@$(eval TEST_FLAG=-m)
else ifeq ($(TEST),grunbaum)
	@echo "Running Grunbaum Test Suite"
	@$(eval TEST_ARG=$(GRUNBAUM))
	@$(eval TEST_FLAG=-m)
else ifeq ($(TEST),icosa)
	@echo "Running Icosahedron Test Suite"
	@$(eval TEST_ARG=$(ICOSA))
	@$(eval TEST_FLAG=-m)
else ifeq ($(TEST),kuratowski)
	@echo "Running Kuratowski Test Suite"
	@$(eval TEST_ARG=$(KURATOWSKI))
	@$(eval TEST_FLAG=-m)
else ifeq ($(TEST),india)
	@echo "Running Map of India Test Suite"
	@$(eval TEST_ARG=$(INDIA))
	@$(eval TEST_FLAG=-m)
else ifeq ($(TEST),mycielski)
	@echo "Running Mycielski Test Suite"
	@$(eval TEST_ARG=$(MYCIELSKI))
	@$(eval TEST_FLAG=-m)
else ifeq ($(TEST),octa)
	@echo "Running Octahedron Test Suite"
	@$(eval TEST_ARG=$(OCTA))
	@$(eval TEST_FLAG=-m)
else ifeq ($(TEST),petersen)
	@echo "Running Petersen Test Suite"
	@$(eval TEST_ARG=$(PETERSEN))
	@$(eval TEST_FLAG=-m)
else ifeq ($(TEST),ramsey)
	@echo "Running Ramsey Test Suite"
	@$(eval TEST_ARG=$(RAMSEY))
	@$(eval TEST_FLAG=-m)
else ifeq ($(TEST),tetra)
	@echo "Running Tetrahedron Test Suite"
	@$(eval TEST_ARG=$(TETRA))
	@$(eval TEST_FLAG=-m)
else ifeq ($(TEST),wheel)
	@echo "Running Wheel Test Suite (Default)"
	@$(eval TEST_ARG=$(WHEEL))
	@$(eval TEST_FLAG=-m)
else ifeq ($(TEST),all)
	@echo "Running All Test Test Suites"
	@$(eval TEST_ARG=all)
else
	@echo $(TEST) is not a valid test suite
	@$(eval TEST_ARG=null)
endif

test: setflags
	@if [ "$(TEST_ARG)" = "all" ] ; then \
		for test in $(LIST) ; do \
			echo Running $$test ;\
			./$(PRG) $$test -l ;\
		done ;\
		for test in $(MATRIX) ; do \
			echo Running $$test ;\
			./$(PRG) $$test -m ;\
		done ;\
	fi
	@if [ "$(TEST_ARG)" != "null" ] ; then \
		if [ "$(TEST_ARG)" != "all" ] ; then \
			for test in $(TEST_ARG) ; do \
				echo Running $$test ;\
				./$(PRG) $$test $(TEST_FLAG) ; \
			done ;\
		fi ;\
	fi
