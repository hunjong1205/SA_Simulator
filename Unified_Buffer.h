#include "InputWeight_Info.h"
#include <iostream>
#include <queue>
#include <cstring>


using namespace std;

class Unified_Buffer {
	private:	
		int ***input_fmap;
		queue<int> *IFMAP_FIFO;
		int *Accumulator_Psum;
		int Acc_Size;
		int Input_fmap_square_length;
		

	public:
		Unified_Buffer();
		~Unified_Buffer(){
		if(Accumulator_Psum) delete Accumulator_Psum;
		}

		void QueueMapping(const int DRAM_input_fmap[1][28][28], const int Input_Index, const Input_Weight_Info &info);
		void QueueClear();
		bool QueuetoPE(int Cycle, int PE_Col[], const Input_Weight_Info &info);
		void Accumulator_to_Unified_Buffer(const int* ptr, const int Size);
};
