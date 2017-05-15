CXXFLAGS =-std=c++11 -pg -O3

seq: sequencer.o graph.o boyer.o
	${CXX} ${CXXFLAGS} -o $@ $^

graph.o: graph.cpp

boyer.o: boyer.cpp

sequencer.o: sequencer.cpp graph.o boyer.o

clean:
	rm -f *.o
	rm -f seq
	rm -f gmon.out
