PE.o : PE.hpp
	g++ -c PE.hpp -o PE.o

InputWeight_Info.o : InputWeight_Info.hpp
	g++ -c InputWeight_Info.hpp -o InputWeight_Info.o
	
Unified_Buffer.o : Unified_Buffer.hpp
	g++ -c Unified_Buffer.hpp -o Unified_Buffer.o

Weight_FIFO.o : Weight_FIFO.hpp
	g++ -c Weight_FIFO.hpp -o Weight_FIFO.o

Accumulator.o : Accumulator.hpp
	g++ -c Accumulator.hpp -o Accumulator.o

ReadMNIST.o : ReadMNIST.hpp
	g++ -c ReadMNIST.hpp -o ReadMNIST.o

main.o : main.cpp PE.hpp Unified_Buffer.hpp Weight_FIFO.hpp Accumulator.hpp ReadMNIST.hpp InputWeight_Info.hpp
	g++ -c main.cpp -o main.o

main : PE.o Unified_Buffer.o Weight_FIFO.o Accumulator.o ReadMNIST.o InputWeight_Info.o main.o
	g++ PE.o Unified_Buffer.o Weight_FIFO.o Accumulator.o ReadMNIST.o InputWeight_Info.o main.o -o main

