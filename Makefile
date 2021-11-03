main : main.o Accumulator.o PE.o ReadMNIST.o Unified_Buffer.o Weight_FIFO.o
	g++ -o main main.o Accumulator.o PE.o ReadMNIST.o Unified_Buffer.o Weight_FIFO.o

main.o : InputWeight_Info.hpp Accumulator.h PE.h ReadMNIST.h Unified_Buffer.h Weight_FIFO.h main.cpp
	g++ -c -o main.o main.cpp

Accumulator.o : Accumulator.h Accumulator.cpp InputWeight_Info.hpp
	g++ -c -o Accumulator.o Accumulator.cpp

PE.o : PE.h	PE.cpp InputWeight_Info.hpp
	g++ -c -o PE.o PE.cpp

ReadMNIST.o : ReadMNIST.h ReadMNIST.cpp InputWeight_Info.hpp
	g++ -c -o ReadMNIST.o ReadMNIST.cpp

Unified_Buffer.o : Unified_Buffer.h Unified_Buffer.cpp InputWeight_Info.hpp
	g++ -c -o Unified_Buffer.o Unified_Buffer.cpp

Weight_FIFO.o : Weight_FIFO.h Weight_FIFO.cpp InputWeight_Info.hpp
	g++ -c -o Weight_FIFO.o	Weight_FIFO.cpp

clean :
	rm *.o
