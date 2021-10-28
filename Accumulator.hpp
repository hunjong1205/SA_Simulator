#include <iostream>

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

void Accumulator::Init_Accumulator(){
	for(int i = 0; i<256; i++) Psum_Accumulate[i] = 0;
}

void Accumulator::Add_PartialSum(const int* PSUM){
	/*
	int* temp = new int[Acc_Size + Row_Size];

	for(int k=0; k<Acc_Size; k++)
		temp[k] = Psum_Accumulate[k];

	delete[] Psum_Accumulate;

	Psum_Accumulate = temp;	

	for(int i=0; i<Row_Size; i++)
		Psum_Accumulate[Acc_Size + i] = PSUM[i];
	
	Acc_Size += Row_Size;	
	*/
	
	//Accumulate Memory
	for(int i=0; i<256; i++)
		Psum_Accumulate[i] += PSUM[i];	
		
}

int Accumulator::Get_Accumulator_Size(){
	return Acc_Size;
}

int* Accumulator::Get_Psum_ptr(){
	return Psum_Accumulate;
}
