#include <iostream>
#include "Weight_FIFO.hpp"
#include "Unified_Buffer.hpp"

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
