# Kevin Albert | kaalbert@ucsc.edu
CC		= g++
CFLAGS	= -Ofast -c -std=c++11 -Wextra -Wall
LDFLAGS	= -std=c++11 -Wextra -Wall
SRC		= test.cpp parser.cpp parse_context.cpp ast.cpp
HEADERS	= parser.h
OBJ		= $(SRC:.cpp=.o)
GENSRC	= grammar.cpp scanner.cpp 
GENOBJ	= $(GENSRC:.cpp=.o)
EXE		= mech

$(EXE): $(OBJ) $(GENOBJ) 
	$(CC) $(LDFLAGS) $^ -o $(EXE)

$(OBJ): %.o: %.cpp $(GENSRC) 
	$(CC) $(CFLAGS) $< -o $@ 

$(GENOBJ): %.o: %.cpp grammar.h 
	$(CC) -c -std=gnu++11 $< -o $@

scanner.cpp: scanner.cpp.messy
	sed 's|register ||' <scanner.cpp.messy >scanner.cpp

scanner.cpp.messy: scanner.l grammar.h parser.h
	flex --outfile=$@ $< 2>/dev/null

Makefile.deps: grammar.h
	g++ -MM $(SRC) >$@

grammar.h: grammar.cpp

grammar.cpp: grammar.y parser.h
	bison --defines=grammar.h --output=$@ $<


include Makefile.deps

clean:
	rm -f $(EXE) *.o scanner.cpp.messy $(GENSRC) grammar.h grammar.output Makefile.deps
