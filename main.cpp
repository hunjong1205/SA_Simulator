#include <iostream>
#include "PE.hpp"
#include "Unified_Buffer.hpp"
#include "Weight_FIFO.hpp"
#include "Accumulator.hpp"
#include "ReadMNIST.hpp"

using namespace std;

int main(){
	// Input, Weight Data to Array Structure, Global Variable Set

	// Input Structure Variable
	// Matrix fixed [Number][Channel][Row][Columm]
	int DRAM_Input_fmap [10000][1][28][28]; // 10000 : # of input, 1 : Channel, 28 : Row, 28 : Col
	int Input_fmap_Row_Size;
	int Input_fmap_Col_Size;

	// Simulator Variable
	int* PE_Col = new int[256];








	cout << "Simulation Config Start \n";
	
	// Input fmap Settings, Filter fmap Settings
	cout << "Configure Input feature map & Filter feature map start! \n";
	
	Data(DRAM_Input_fmap, Input_fmap_Row_Size, Input_fmap_Col_Size);
	
		// Configure Filter from ML Library file
		int DRAM_Weight_fmap [5][3][3][3]; // m : Num, a : Channel, b : Col, c : Row (?)
		int Strides = 1;
		int Filter_Row_Size = 3;
		int Filter_Col_Size = 3;
		int Filter_Channel_Size = 3;
		int Filter_Num_Size = 5;

		int One_Filter_Size = Filter_Row_Size * Filter_Col_Size * Filter_Channel_Size;
		

	cout << "Configured! \n";

	//          1. Accelerator Configuration				 //
	/*********************** PE    ***************************/
	MXU MXU1;

	/*********************** Accumulators ********************/
	Accumulator Acc1;

	/*********************** IFMAP ***************************/
	// Input Array Structure to Unified Buffer(DRAM -> Unified Buffer) 
	Unified_Buffer UB1;

	/*********************** Filter **************************/
	//Weight Array Structure to Weight FIFO
	Weight_FIFO WF1;


	int* PSUM = new int[256];
	int Unified_Buffer_Index = 0;
	int Input_Index = 0;

	bool Weight_FIFO_Init = 0;


	cout << "Simulation Execution Start \n";
	// PE execution(Push_PE_Input_fmap)
	while(Input_Index < 10000)
	{

		// while(!UB1.QueueMapping) 으로 대체!
		// 1. Unified Buffer to Input_fmap Queue
		UB1.QueueMapping(DRAM_Input_fmap[Input_Index], Input_Index, Input_fmap_Row_Size, Input_fmap_Col_Size, Filter_Row_Size, Filter_Col_Size, Filter_Channel_Size, Filter_Num_Size, Strides);

		// 2. Weight Array Structure to Weight FIFO
		if(!Weight_FIFO_Init)
		// Weight_FIFO_Init = WF1.FIFOMapping(DRAM_Weight_fmap, Filter_Row_Size, Filter_Col_Size, Filter_Num_Size, Filter_Channel_Size);

		// 3. Set PEs Weight
		// MXU1.Set_PE_Weight(WF1.FIFOtoPE(One_Filter_Size), Filter_Num_Size, One_Filter_Size);

		cout << "Start Input feature map Queue to PE \n";

		// 4. Input fmap to PE
		// Get Input fmap data using PE_Col
		Unified_Buffer_Index = 0;
		Acc1.Init_Accumulator();
		while(UB1.QueuetoPE(Unified_Buffer_Index++, PE_Col, One_Filter_Size)){
		
		// 5. PE MAC Operation
		MXU1.MAC(PE_Col);
		MXU1.Get_MXU_Last_PSUM(PSUM);
		
		// 6. Accumulate Partial_Sum
		Acc1.Add_PartialSum(PSUM);
		}

		// 7. Accumulator PSUM to Unified_Buffer 
		UB1.Accumulator_to_Unified_Buffer(Acc1.Get_Psum_ptr(), Acc1.Get_Accumulator_Size());



		++Input_Index;
		// UB1 Deallocation

	}

	// WF1 Deallocation

	delete[] PSUM;
	delete[] PE_Col;
	PSUM = nullptr;
	PE_Col = nullptr;
	// PE's All Partial Sum to Unified Buffer
    // UB1.Accumulator_to_Unified_Buffer(Acc1.Get_Psum_ptr(), Acc1.Get_Accumulator_Size());

	return 0;
}

// Input, Weight featuremap information -> Struct
