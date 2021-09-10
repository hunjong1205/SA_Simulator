#include <iostream>

using namespace std;

//TPU
class TPU {
//controller 포함
//Unified to MXU
//Weight FIFO to MXU
//MXU to Unified
	private:
	MXU MXU1;
	Weight_FIFO Weight_FIFO1;
	Unified_Buffer Unified_Buffer1;

	private:
	void Unified_to_MXU();
	void Weight_FIFO_to_MXU();
	void MXU_to_Unified();


};

void TPU::Unified_to_MXU(){
//Unified_to_MUX의 Queue에서 pop
}

void TPU::Weight_FIFO_to_MXU(){

}

void TPU::MXU_to_Unified(){

}

//MXU(includes PEs)
class MXU {
	private:
	PE **Unit;

	public:
	MXU(){
		Unit = new PE*[256];
		for(int i=0 ; i<256; i++) Unit[i] = new PE[256];
	}
	
	~MXU(){
		for(int i=0; i<256; i++) delete[] PE[i];
		delete[] PE;
	}

	void Set_PE_Weight(int** Weight); 					//Get Weight from Weight FIFO
};

void MXU::Set_PE_Weight(int** Weight){
	for(int k = 0; k < 256; k++){
		for(int j = 0; j < 256; j++)
			Unit[k][j].Set_Scratchpad(Weight[k][j]);
	}
}

//PE
class PE {
	private: 
	// Multiply, Add, ScratchPad
	int Scratchpad;

	public:
	int MAC(int Mul_input_1, int Partial_input_2);  // Output Partial Sum
	void reset_Scratchpad();
	void Set_Scratchpad(int Weight);
};

int PE::MAC(int Mul_input_1, int Partial_input_2){
	return Partial_input_2 + (Mul_input_1 * Scratchpad);
}

void PE::reset_Scratchpad(){
	this -> Scratchpad = 0;	
}

void PE::Set_Scratchpad(int Weight){
	this -> Scratchpad = Weight;	
}

//Weight FIFO
class Weight_FIFO {
	private:
		int **Weight;

	public:
		Weight_FIFO(){
			Weight = new int*[256];
			for(int i=0; i<256; ++i) Weight[i] = new int[256];
		}

		~Weight_FIFO(){
			for(int i=0; i<256; ++i) delete[] Weight[i];
			delete[] Weight;
		}
		void Set_Weight(int** Weight);						// DRAM -> Weight_FIFO
}

void Weight_FIFO::Set_Weight(int** Weight){
	memcpy(this -> Weight, Weight, sizeof(this -> Weight) * 256);
}

//Unified Buffer
class Unified_Buffer {
	private:
		//Queue Saving input_fmap
		int ***input_fmap;
		int ***output_fmap;

	public:
		Unified_Buffer(){
			input_fmap = new int **[3];
			for(int i=0; i<3; i++){
					input_fmap[i] = new int * [256];
					for(int j=0; j<256; j++) input_fmap[i][j] = new int [256];
			}
		}

		~Unified_Buffer(){
			for(int i=0; i<3; i++){
				for(int j=0; j<256; j++) delete [] input_fmap[i][j];
			}

			for(int i=0; i<3; i++) delete [] input_fmap[i];
			
			delete[] input_fmap;
		}




int main() {
	// Input, Weight Data to Array Structure, Global Variable Set
	// Class Declaration

	int DRAM_Input_fmap [a][b][c];
	int DRAM_Weight_fmap [m][a][b][c];
	int Channel;
	int Input_fmap_Row;
	int Input_fmap_Col;







	// Input Array Structure to Unified Buffer(DRAM -> Unified Buffer) 
	Unified_Buffer UB1(DRAM_Input_fmap, Channel, Input_fmap_Row, Input_fmap_Col);

	// Unified Buffer to Input_fmap Queue
	UB1.QueueMapping();

	
	//Weight Array Structure to Weight FIFO
	Weight_FIFO WF1();
	WF1.FIFOMapping(&DRAM_Weight_fmap, );


	// Queue to PE(Both of Weight, Input fmap)




	// PE execution




	// PE Partial Sum to Unified Buffer
