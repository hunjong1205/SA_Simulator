#include "PE.h"

using namespace std;

void PE::MAC(int Pre_psum = 0){
	PSUM = Scratchpad * IFMAP + Pre_psum;
}

void PE::Reset_Scratchpad(){
	this -> Scratchpad = 0;	
}

void PE::Set_Scratchpad(int Weight){
	this -> Scratchpad = Weight;	
}

// One_Filter_Size = Filter 한개당 Row * Col * Channel
void MXU::Set_PE_Weight(float Weight[][32], const Input_Weight_Info &info){
	for(int k = 0; k < info.One_Filter_Size; k++){
		for(int j = 0; j < info.Filter_Num_Size; j++)
			PEs[k][j].Set_Scratchpad(Weight[k][j]);
	}

	if(Weight){
		for(int i = 0; i <info.One_Filter_Size; i++)
			delete[] Weight[i];
		delete[] Weight;
		Weight = nullptr;
	}

	cout << "PE's Weight are configured! \n";
}

void MXU::Reset_PE_Weight(){
	for(int k=0; k<256; k++){
		for(int j=0; j<256; j++)
			PEs[k][j].Reset_Scratchpad();
	}
}

void MXU::MAC(const int* PE_Col){

	// Slide IFMAP in every PEs to next Column PE
	for(int i=0; i<256; i++){
		for(int j=0; j<255; j++) PEs[i][j+1].Set_Ifmap(PEs[i][j].Get_Ifmap());
	}

	// inputs New IFMAP to first Col PE
	for(int k=0; k<256; k++)
		PEs[k][0].Set_Ifmap(PE_Col[k]);

	// MAC Operation
	for(int m=0; m<256; m++){
		for(int n=0; n<256; n++)
		{
			// Slide PSUM in every PEs to next Row PE
			if(m == 0) PEs[m][n].MAC();
			else PEs[m][n].MAC(PEs[m-1][n].Get_PSUM());
		}
	} // then, PE[255][0~255] has Partial Sum

	cout << "MAC Operation is Done! \n";
}
void MXU::Get_MXU_Last_PSUM(int* PSUM){
//Get MUX's Partial Sum
	for(int k=0; k<256; k++) PSUM[k] = PEs[255][k].Get_PSUM();
}

