#include <iostream>
#include "InputWeight_Info.h"

using namespace std;

class Accumulator {
	private:
	int* Psum_Accumulate;
	int Acc_Size;

	public:
	Accumulator(){
	Psum_Accumulate = new int[256];
	Acc_Size = 0;
	for(int i = 0; i<256; i++) Psum_Accumulate[i] = 0;
	}
	~Accumulator(){
	if(Psum_Accumulate) delete[] Psum_Accumulate;
	}

	void Init_Accumulator();
	void Add_PartialSum(const int* PSUM);
	int Get_Accumulator_Size();
	int* Get_Psum_ptr();
};
