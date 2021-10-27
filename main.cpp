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
 // int DRAM_Input_fmap [1][28][28]; 
	int Input_fmap_Row_Size;
	int Input_fmap_Col_Size;

	// Simulator Variable
	int Cycle = 0;
	int* PE_Col = new int[256];








	cout << "Simulation Config Start \n";
	
	// Input fmap Settings, Filter fmap Settings
	cout << "Configure Input feature map & Filter feature map start! \n";
	
	Data(DRAM_Input_fmap, Input_fmap_Row_Size, Input_fmap_Col_Size);
	
		// Configure Filter from ML Library file
		// int DRAM_Weight_fmap [m][a][b][c]; // m : Num, a : Channel, b : Col, c : Row (?)
		// int Strides;
		int Filter_Row_Size = 3;
		int Filter_Col_Size = 3;
		int Filter_Channel_Size = 3;
		// int Filter_Num_Size;

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

	cout << "Simulation Execution Start \n";
	// PE execution(Push_PE_Input_fmap)
	while(Input_Index_Number < 10000)
	{

		// while(!UB1.QueueMapping) 으로 대체!
		// 1. Unified Buffer to Input_fmap Queue
		int temp[1][28][28] = (temp ***)DRAM_Input_fmap;
		UB1.QueueMapping(DRAM_Input_fmap[Input_Index][0][0][0], Input_Index, Input_fmap_Row_Size, Input_fmap_Col_Size, Filter_Row_Size, Filter_Col_Size, Filter_Channel_Size);

		// 2. Weight Array Structure to Weight FIFO
		// WF1.FIFOMapping(DRAM_Weight_fmap, Filter_Row, Filter_Col, Filter_Num, Filter_Channel);

		// 3. Set_PE_Weight
		// MXU1.Set_PE_Weight(WF1.FIFOtoPE(One_Filter_Size), Filter_Num, One_Filter_Size);

		cout << "Start Input feature map Queue to PE \n";

		// Input fmap to PE
		// Get Input fmap data using PE_Col
		// for()
		// (*) UB1.QueuetoPE(Unified_Buffer_Index++, PE_Col, One_Filter_Size);	// Queue에 뒷부분에서 PE로 어떻게 전달되는지?

		// 5. PE MAC Operation
		// MXU1.MAC(PE_Col);

		// 6. Accumulate Partial_Sum
		// MXU1.Get_MXU_Partial_Sum(&PSUM);
		// Acc1.Add_partialsum(PSUM, 256);

		++Cycle;
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
