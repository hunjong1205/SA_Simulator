#include <iostream>

using namespace std;

//MXU(includes PEs)
class MXU {
	private:
	PE **Unit;

	public:
	MXU(){
		Unit = new PE*[256];
		for(int i=0 ; i<256; i++) Unit[i] = new PE[256];
		cout <<"\n" << "PE[256 * 256] Generated \n" << "\n";
	}
	
	~MXU(){
		if(Unit){
		for(int i=0; i<256; i++) delete[] PE[i];
		delete[] PE;
		}
	}

	void Set_PE_Weight(int* Weight); 					//Get Weight from Weight FIFO
	void Reset_PE_Weight();
};

// One_Filter_Size = Filter 한개당 Row * Col * Channel
void MXU::Set_PE_Weight(const int* Weight, const int Filter_Num, const int One_Filter_Size){
	int Weight_index = 0;
	for(int k = 0; k < One_Filter_Size; k++){
		for(int j = 0; j < Filter_Num; j++)
			Unit[k][j].Set_Scratchpad(Weight[Weight_index++]);
	}
}

void MXU::Reset_PE_Weight(){
	for(int k=0; k<256; k++){
		for(int j=0; j<256; j++)
			Unit[k][j].Reset_Scratchpad();
	}
}

//PE
class PE {
	private: 
	// Multiply, Add, ScratchPad
	int Scratchpad;

	public:
	int MAC(int Mul_input_1, int Partial_input_2);  // Output Partial Sum
	void Reset_Scratchpad();
	void Set_Scratchpad(int Weight);
};

int PE::MAC(int Mul_input_1, int Partial_input_2){
	return Partial_input_2 + (Mul_input_1 * Scratchpad);
}

void PE::Reset_Scratchpad(){
	this -> Scratchpad = 0;	
}

void PE::Set_Scratchpad(int Weight){
	this -> Scratchpad = Weight;	
}
