#include "PE.h"
#include "Unified_Buffer.h"
#include "Weight_FIFO.h"
#include "Accumulator.h"
#include "ReadMNIST.h"
#include "InputWeight_Info.h"

using namespace std;

int main(){
	// Input, Weight Data to Array Structure, Global Variable Set

	// Input Structure Variable
	// Matrix fixed [Number][Channel][Row][Columm]
	uint8_t DRAM_Input_fmap[10000][1][28][28]; // 10000 : # of input, 1 : Channel, 28 : Row, 28 : Col

	// Configure Filter from ML Library file
	float DRAM_Weight_fmap[32][1][3][3]; // m : Num, a : Channel, b : Row, c : Col (?)

	// Simulator Variable
	int* PE_Col = new int[256];

	cout << "Simulation Config Start \n";
	
	// Input fmap Settings, Filter fmap Settings
	cout << "Configure Input feature map & Filter from MNIST start! \n";

	Input_Weight_Info Info(0, 0, 0, 0, 0, 0, 0, 0);
	Data(DRAM_Input_fmap, DRAM_Weight_fmap, Info);
	Info.print();

	// Input, Filter Data test
	/*
	for(int i = 0; i<28; i++){
		for(int j = 0; j<28; j++){
			cout << (int)DRAM_Input_fmap[300][0][i][j] << "  ";
		}
		cout << endl;
	}

	*/


	for(int i=0; i<Info.Filter_Num_Size; i++)
	{
		for(int j=0; j<Info.Filter_Channel_Size; j++)
		{
			for(int k=0; j<Info.Filter_Row_Size; j++)
			{
				for(int p=0; p<Info.Filter_Col_Size; p++)
					cout <<  DRAM_Weight_fmap[i][j][k][p] << ' ';
			}
		}
		cout << "\n";
	}

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
	// Weight Array Structure to Weight FIFO
	Weight_FIFO WF1;


	float* PSUM = new float[256];
	int Input_Index = 0;

	bool Weight_FIFO_Init = 0;


	cout << "\n" << "Simulation Execution Start \n";
	// PE execution(Push_PE_Input_fmap)
	while(Input_Index < 10000)
	{

		// while(!UB1.QueueMapping) 으로 대체!
		// 1. Unified Buffer to Systolic Data Setup Queue
		UB1.QueueMapping(DRAM_Input_fmap[Input_Index], Input_Index, Info);

		if(!Weight_FIFO_Init){
			
		// 2. Weight Array Structure to Weight FIFO
		// Execute only once!
		Weight_FIFO_Init = WF1.FIFOMapping(DRAM_Weight_fmap, Info);

		// 3. Set PEs Weight
		MXU1.Set_PE_Weight(WF1.FIFOtoPE(Info), Info);
		}

		cout << "\n" << "Start Input feature map Queue to PE " << "\n";

		Acc1.Init_Accumulator();

		// 4. Input fmap to PE
		// Get Input fmap data using PE_Col
		while(UB1.QueuetoPE(PE_Col, Info)){
		
		// 5. PE MAC Operation
		MXU1.MAC(PE_Col);
		MXU1.Get_MXU_Last_PSUM(PSUM);
		
		// 6. Accumulate Partial_Sum
		Acc1.Add_PartialSum(PSUM);
   		}

		cout << "Debug \n" << endl;
		// 255 Cycle Mac Operation(This operation has no fetch input feature map)
		for(int i=0; i<255; i++)
		{
			MXU1.MAC(nullptr);
			MXU1.Get_MXU_Last_PSUM(PSUM);

			Acc1.Add_PartialSum(PSUM);
		}

		cout << "Debug Accumul\n" << endl;

		// 7. Accumulator PSUM to Unified_Buffer 
		UB1.Accumulator_to_Unified_Buffer(Acc1.Get_Psum_ptr(), Acc1.Get_Accumulator_Size());

		exit(1);


		++Input_Index;
		// UB1 Deallocation

	}

	// WF1 Deallocation
	cout << " Debug Point " << endl;
	delete[] PSUM;
	delete[] PE_Col;
	PSUM = nullptr;
	PE_Col = nullptr;
	// PE's All Partial Sum to Unified Buffer
    // UB1.Accumulator_to_Unified_Buffer(Acc1.Get_Psum_ptr(), Acc1.Get_Accumulator_Size());

	return 0;
}

// Input, Weight featuremap information -> Struct
// Weight_FIFO Configuration
// Input from Tensorflow 
