#include <iostream>

using namespace std;

//MXU(includes PEs)
class MXU {
	private:
	PE **PEs;

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

	void Set_PE_Weight(const int* Weight, const int Filter_Num, const int One_Filter_Size); 					//Get Weight from Weight FIFO
	void Reset_PE_Weight();
	void MXU.MAC(const int* PE_Col);
	int* Get_MXU_Partial_Sum();
};

// One_Filter_Size = Filter 한개당 Row * Col * Channel
void MXU::Set_PE_Weight(const int* Weight, const int Filter_Num, const int One_Filter_Size){
	int Weight_index = 0;
	for(int k = 0; k < One_Filter_Size; k++){
		for(int j = 0; j < Filter_Num; j++)
			PEs[k][j].Set_Scratchpad(Weight[Weight_index++]);
	}
}

void MXU::Reset_PE_Weight(){
	for(int k=0; k<256; k++){
		for(int j=0; j<256; j++)
			PEs[k][j].Reset_Scratchpad();
	}
}

void MXU::MAC(const int* PE_Col){

	// Slide IFMAP in every PEs to next Column PE
	for(int j=0; i<256; i++){
		for(int i=0; j<256; j++){
		if(i < 255) PE[i+1][j].Set_Ifmap(PE[i][j].Get_Ifmap());
		}
	}

	// inputs New IFMAP to first Col PE
	for(int k=0; k<256; k++)
		PE[k][0].Set_Ifmap(PE_Col[k]);

	// MAC Operation
	for(int m=0; m<256; m++){
		for(int n=0; n<256; n++)
		{
			// Slide PSUM in every PEs to next Row PE
			if(m == 0) PE[m][n].MAC();
			else PE[m][n].MAC(PE[m-1][n].Get_PSUM());
		}
	} // then, PE[255][0~255] has Partial Sum
}
int* MXU::Get_MXU_Partial_Sum(){
//Get MUX's Partial Sum
	
}

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
	}
	int Get_Ifmap(){ return IFMAP;};
	int Set_Ifmap(int IFMAP) { this-> IFMAP = IFMAP; };
	void MAC(int Pre_psum = 0);  // Output Partial Sum
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
