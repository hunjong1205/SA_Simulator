#include <iostream>
#include "InputWeight_Info.h"

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

	void Set_PE_Weight(auto Weight, const Input_Weight_Info &info); 					//Get Weight from Weight FIFO
	void Reset_PE_Weight();
	void MAC(const int* PE_Col);
	void Get_MXU_Last_PSUM(int* PSUM);
};
