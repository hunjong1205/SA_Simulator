PE.o : PE.hpp
	g++ -c PE.hpp

Feature_map.o : Feature_map.hpp
	g++ -c Feature_map.hpp
	
Unified_Buffer.o : Unified_Buffer.hpp
	g++ -c Unified_Buffer.hpp

Weight_FIFO.o : Weight_FIFO.hpp
	g++ -c Weight_FIFO.hpp

Accumulator.o : Accumulator.hpp
	g++ -c Accumulator.hpp

ReadMNIST.o : ReadMNIST.hpp
	g++ -c ReadMNIST.hpp

main.o : main.cpp PE.hpp Unified_Buffer.hpp Weight_FIFO.hpp Accumulator.hpp ReadMNIST.hpp Feature_map.hpp
	g++ -c main.cpp

main : PE.o Unified_Buffer.o Weight_FIFO.o Accumulator.o ReadMNIST.o Feature_map.o main.o
	g++ PE.o Unified_Buffer.o Weight_FIFO.o Accumulator.o ReadMNIST.o Feature_map.o main.o -o main

