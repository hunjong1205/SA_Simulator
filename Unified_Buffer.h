#include "InputWeight_Info.h"
#include <iostream>
#include <queue>
#include <cstring>


using namespace std;

class Unified_Buffer {
	private:	
		//uint8_t ***input_fmap;
		queue<uint8_t> *IFMAP_FIFO;
		float *Accumulator_Psum;
		int Acc_Size;
		int Input_fmap_square_length;
		int Unified_Cycle;
		

	public:
		Unified_Buffer(){
			this -> Acc_Size = 0;
			this -> Input_fmap_square_length = 0;
			this -> Unified_Cycle = 1;
			cout << "\n" << "Unified_Buffer Generated " << "\n" ;
		};
		~Unified_Buffer(){
		if(Accumulator_Psum) delete[] Accumulator_Psum;
		if(IFMAP_FIFO) delete[] IFMAP_FIFO;
		cout << "\n" << "Unified_Buffer Deallocated" << "\n";
		};

		void QueueMapping(const uint8_t DRAM_input_fmap[1][28][28], const int Input_Index, const Input_Weight_Info &info);
		void QueueClear();
		bool QueuetoPE(int PE_Col[], const Input_Weight_Info &info);
		void Accumulator_to_Unified_Buffer(const float* ptr, const int Size);
};
