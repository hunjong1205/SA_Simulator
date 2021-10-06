#include <iostream>
#include "PE.hpp"
#include "Unified_Buffer.hpp"
#include "Weight_FIFO.hpp"
#include "Accumulator.hpp"

using namespace std;

void main() {
	// Input, Weight Data to Array Structure, Global Variable Set

	// Input Structure Variable
	int DRAM_Input_fmap [a][b][c];
	int DRAM_Weight_fmap [m][a][b][c];
	int Channel;
	int Input_fmap_Row;
	int Input_fmap_Col;
	int Strides;
	int Filter_Row;
	int Filter_Col;
	int Filter_Channel;
	int Filter_Num;

	// Simulator Variable
	int Cycle;
	int* PE_Col = new int[256];








	cout << "Simulation Config Start \n";

	//          1. Accelerator Configuration				 //
	/*********************** PE    ***************************/
	MXU MXU1();

	/*********************** Accumulators ********************/
	Accumulator Acc1();

	/*********************** IFMAP ***************************/
	// Input Array Structure to Unified Buffer(DRAM -> Unified Buffer) 
	Unified_Buffer UB1();

	// Unified Buffer to Input_fmap Queue
	UB1.QueueMapping(DRAM_Input_fmap, Input_fmap_Row, Input_fmap_Col, Strides, Filter_Row, Filter_Col, Filter_Channel);

	/*********************** Filter **************************/
	//Weight Array Structure to Weight FIFO
	Weight_FIFO WF1();
	WF1.FIFOMapping(&DRAM_Weight_fmap, Filter_Row, Filter_Col, Filter_Num, Filter_Channel);

	// Set_PE_Weight
	MXU1.Set_PE_Weight(WF1.FIFOtoPE(), Filter_Num, Filter_Row * Filter_Col * Filter_Channel);



	


	int* PSUM = new int[256];
	int Unified_Buffer_Index = 0;

	cout << "Simulation Execution Start \n";
	// PE execution(Push_PE_Input_fmap)
	while(1)
	{

		// 1. Input fmap to PE
		cout << "Start Input feature map Queue to PE \n"
		UB1.QueuetoPE(Unified_Buffer_Index++, PE_Col, Channel_Size);	// Queue에 뒷부분에서 PE로 어떻게 전달되는지?

		// 2. PE MAC Operation
		MXU1.MAC(PE_Col);

		// 3. Accumulate Partial_Sum
		MXU1.Get_MXU_Partial_Sum(PSUM);
		Acc1.Add_partialsum(PSUM, 256);

		++Cycle;
	}

	delete[] PSUM;
	delete[] PE_Col;
	PSUM = nullptr;
	PE_Col = nullptr;
	// PE's All Partial Sum to Unified Buffer
	UB1.Accumulator_to_Unified_Buffer(Acc1.Get_Psum_ptr(), Acc1.Get_Accumulator_Size());

}
