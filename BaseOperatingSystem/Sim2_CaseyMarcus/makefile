all: sim2
sim2: harness.o ConfigurationAPI.o MetaDataAPI.o processControlBlock.o HarnessAPI.o
	g++ -std=c++11 harness.o ConfigurationAPI.o MetaDataAPI.o processControlBlock.o  HarnessAPI.o -pthread -o sim2
Configuration.o: ConfigurationAPI.cpp
	g++ -std=c++11 -pthread -c ConfigurationAPI.cpp
harness.o: harness.cpp
	g++ -std=c++11 -pthread -c harness.cpp
MetaDeque.o: MetaDeque.cpp
	g++ -std=c++11 -pthread -c MetaDataAPI.cpp
processControlBlock.o: processControlBlock.cpp
	g++ -std=c++11 -pthread -c processControlBlock.cpp
HarnessAPI.o: HarnessAPI.cpp
	g++ -std=c++11 -pthread -c HarnessAPI.cpp
clean:
	rm -rf *.o sim2
