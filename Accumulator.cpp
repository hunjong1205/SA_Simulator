#include "Accumulator.h"

using namespace std;

void Accumulator::Init_Accumulator(){
	for(int i = 0; i<256; i++) Psum_Accumulate[i] = 0;
	Acc_Size = 255;
}

void Accumulator::Add_PartialSum(const float* PSUM){
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
	for(int i=0; i<256; i++){
		Psum_Accumulate[i] += PSUM[i];	
	}
		
}

int Accumulator::Get_Accumulator_Size(){
	return Acc_Size;
}

float* Accumulator::Get_Psum_ptr(){
	return Psum_Accumulate;
}
