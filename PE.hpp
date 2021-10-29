#include <iostream>
#include "Feature_map.hpp"

using namespace std;

//PE
class PE {
	private: 
	// Multiply, Add, ScratchPad
	int Scratchpad;									// Store Weight
	int IFMAP;
	int PSUM;

	public:
	PE(){
		this -> Scratchpad = 0;
		this -> IFMAP = 0;
		this -> PSUM = 0;
	}
	int Get_Ifmap(){ return IFMAP;};
	int Set_Ifmap(int IFMAP) { this-> IFMAP = IFMAP; };
	void MAC(int Pre_psum);  // Output Partial Sum
	int Get_PSUM(){ return PSUM; };
	void Reset_Scratchpad();
	void Set_Scratchpad(int Weight);
};

void PE::MAC(int Pre_psum = 0){
	PSUM = Scratchpad * IFMAP + Pre_psum;
}

void PE::Reset_Scratchpad(){
	this -> Scratchpad = 0;	
}

void PE::Set_Scratchpad(int Weight){
	this -> Scratchpad = Weight;	
}

//MXU(includes PEs)
class MXU {
	private:
	PE **PEs;

	public:
	MXU(){
		PEs = new PE*[256];
		for(int i=0 ; i<256; i++) PEs[i] = new PE[256];
		cout <<"\n" << "PE[256 * 256] Generated \n" << "\n";
	}
	
	~MXU(){
		if(PEs){
		for(int i=0; i<256; i++) delete[] PEs[i];
		delete[] PEs;
		}
	}

	void Set_PE_Weight(const int** Weight, const Feature_map_info &info); 					//Get Weight from Weight FIFO
	void Reset_PE_Weight();
	void MAC(const int* PE_Col);
	void Get_MXU_Last_PSUM(int* PSUM);
};

// One_Filter_Size = Filter 한개당 Row * Col * Channel
void MXU::Set_PE_Weight(const int** Weight, const Feature_map_info &info){
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

