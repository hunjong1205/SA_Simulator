#include "InputWeight_Info.h"
#include <iostream>
#include <queue>
#include <cstring>


using namespace std;

class Unified_Buffer {
	private:	
		//uint8_t ***input_fmap;
		queue<uint8_t> *IFMAP_FIFO;
		int *Accumulator_Psum;
		int Acc_Size;
		int Input_fmap_square_length;
		

	public:
		Unified_Buffer(){};
		~Unified_Buffer(){
		if(Accumulator_Psum) delete Accumulator_Psum;
		if(IFMAP_FIFO) delete IFMAP_FIFO;
		};

		void QueueMapping(const uint8_t DRAM_input_fmap[1][28][28], const int Input_Index, const Input_Weight_Info &info);
		void QueueClear();
		bool QueuetoPE(int Cycle, int PE_Col[], const Input_Weight_Info &info);
		void Accumulator_to_Unified_Buffer(const int* ptr, const int Size);
};