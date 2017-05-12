CXXFLAGS =-std=c++11 -O3

seq: sequencer.o graph.o boyer.o
	${CXX} ${CXXFLAGS} -o $@ $^

sequencer.o: sequencer.cpp

graph.o: graph.cpp

boyer.o: boyer.cpp

clean:
	rm -f *.o
	rm -f seq