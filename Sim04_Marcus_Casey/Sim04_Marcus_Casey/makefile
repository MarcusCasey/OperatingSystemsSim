all: sim4
sim4: harness.o ConfigurationAPI.o MetaDataAPI.o processControlBlock.o HarnessAPI.o
	g++ -std=c++11 harness.o ConfigurationAPI.o MetaDataAPI.o processControlBlock.o  HarnessAPI.o -pthread -o sim4
Configuration.o: ConfigurationAPI.cpp
	g++ -std=c++11 -pthread -c ConfigurationAPI.cpp
harness.o: harness.cpp
	g++ -std=c++11 -pthread -c harness.cpp
MetaDataAPI.o: MetaDataAPI.cpp
	g++ -std=c++11 -pthread -c MetaDataAPI.cpp
processControlBlock.o: processControlBlock.cpp
	g++ -std=c++11 -pthread -c processControlBlock.cpp
HarnessAPI.o: HarnessAPI.cpp
	g++ -std=c++11 -pthread -c HarnessAPI.cpp
clean:
	rm -rf *.o sim4
