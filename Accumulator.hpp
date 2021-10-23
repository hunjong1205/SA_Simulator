#include <iostream>

using namespace std;

class Accumulator {
	private:
	int* Psum_Accumulate;
	int Acc_Size;

	public:
	Accumulator(){
	Acc_Size = 0;
	}
	~Accumulator(){
	if(Psum_Accumulate) delete[] Psum_Accumulate;
	}

	void Add_PartialSum(const int* PSUM, const int Row_Size);
	int Get_Accumulator_Size();
	int* Get_Psum_ptr();
};

void Accumulator::Add_PartialSum(const int* PSUM, const int Row_Size){
	int* temp = new int[Acc_Size + Row_Size];

	for(int k=0; k<Acc_Size; k++)
		temp[k] = Psum_Accumulate[k];

	delete[] Psum_Accumulate;

	Psum_Accumulate = temp;	

	for(int i=0; i<Row_Size; i++)
		Psum_Accumulate[Acc_Size + i] = PSUM[i];
	
	Acc_Size += Row_Size;	
		
}

int Accumulator::Get_Accumulator_Size(){
	return Acc_Size;
}

int* Accumulator::Get_Psum_ptr(){
	return this -> Psum_Accumulate;
}
