#include "Unified_Buffer.h"

using namespace std;

void Unified_Buffer::QueueMapping(const uint8_t DRAM_input_fmap[1][28][28], const int Input_Index, const Input_Weight_Info &info){ 
	cout << "Start Unified_Buffer QueueMapping !" << endl;
	this -> Acc_Size = 0;
	this -> Input_fmap_square_length = (info.Input_fmap_Row_Size - info.Filter_Row_Size)/info.Strides + 1;
	this -> Input_fmap_square_length = Input_fmap_square_length * Input_fmap_square_length * 2 - 1;
	//input_fmap = new uint8_t **[info.Input_fmap_Channel_Size];


	// Input_fmap Memory Allocation to DRAM
	/*for(int i=0; i<info.Input_fmap_Channel_Size; i++){
		input_fmap[i] = new uint8_t * [info.Input_fmap_Row_Size];
		for(int j=0; j<info.Input_fmap_Row_Size; j++) input_fmap[i][j] = new uint8_t [info.Input_fmap_Col_Size];
	}

	// DRAM -> Unified_Buffer
	if(memcpy(input_fmap, DRAM_input_fmap, sizeof(DRAM_input_fmap)) != input_fmap)
	{
		cout<< "Memcpy Error occured! \n";
		exit(EXIT_FAILURE);
	}
	*/
	cout<< "Input fmap transferred from DRAM to Unified Buffer \n";
			
	int Start_Col= 0;
	int Start_Row= 0;
	int Element_Index = 0;
	Acc_Size = 0;

	// Malloc Queue Size, It Needs QueueClear essentially!
	// this -> FIFO = new queue<AR>;
	// Malloc Queue Size, It Needs QueueClear essentially!
	this -> IFMAP_FIFO = new queue<uint8_t>[info.One_Filter_Size];

	// Unified_Buffer to Input_Queue(Systolic_Data Setup)
	for(int Start_Row=0; Start_Row<(info.Input_fmap_Row_Size-info.Filter_Row_Size+1); Start_Row++){
		for(int Start_Col=0; Start_Col<(info.Input_fmap_Col_Size-info.Filter_Col_Size+1); Start_Col++){
			Element_Index = info.One_Filter_Size - 1;
			for(int j=Start_Row; j<info.Filter_Row_Size+Start_Row; j++){
				for(int k=Start_Col; k<info.Filter_Col_Size+Start_Col; k++){
					for(int i=0; i<info.Input_fmap_Channel_Size; i++){
						//if(Element_Index >= 0) // Index Error occured!
						IFMAP_FIFO[Element_Index--].push(DRAM_input_fmap[i][j][k]);
					}
				}
			}
		}
	}

	cout<< "Input fmap Unified_Buffer to Input_Queue Done! \n";

	// Memory Deallocation of input_fmap
	/*
	for(int i=0; i<info.Input_fmap_Channel_Size; i++){
		for(int j=0; j<info.Input_fmap_Row_Size; j++) delete [] input_fmap[i][j];
	}

	for(int i=0; i<info.Input_fmap_Channel_Size; i++) delete [] input_fmap[i];
	
	delete[] input_fmap;
	input_fmap = nullptr;
	*/
}

bool Unified_Buffer::QueuetoPE(int Cycle, int PE_Col[], const Input_Weight_Info &info){

	if(Cycle > (Input_fmap_square_length)){
		cout << "Queue to PE Transport is done! \n";
		return 0;
	}
	
	// Input_feature map 사각형 앞부분
	if(Cycle < (info.Filter_Num_Size - 1)){
		for(int i=0; i<(Cycle+1); i++){
			PE_Col[i] =	IFMAP_FIFO[i].front();		
			IFMAP_FIFO[i].pop();
		}	

		return 1;
	}

	// Input_feature map 사각형 중간 및 끝부분
	else{
		for(int i=0; i<info.One_Filter_Size; i++){
			if(!IFMAP_FIFO[i].empty()){
				PE_Col[i] =	IFMAP_FIFO[i].front();		
				IFMAP_FIFO[i].pop();
			}
		}	

		return 1;
	}
	
	return 0;

}

void Unified_Buffer::QueueClear(){
	delete[] IFMAP_FIFO;
	IFMAP_FIFO = nullptr;
}

void Unified_Buffer::Accumulator_to_Unified_Buffer(const int* ptr, const int Size)
{
	int* temp = new int[Size];

	if(Accumulator_Psum){
	for(int i=0; i<Acc_Size; i++)
		temp[i] = Accumulator_Psum[i];
	}

	Accumulator_Psum = temp;

	for(int k=0; k<Size; k++)
		Accumulator_Psum[Acc_Size] = ptr[k];

	Acc_Size += Size;
}










// Trash

/*
typedef struct AR{
	public:
		int *ptr;
		int Size;

		AR(int Filter_Size) 
		{
			ptr = new int[Filter_Size];
			Size = Filter_Size;
		}

		AR(const AR& AR_Origin)
		{
			this -> ptr = new int[AR_Origin.Size];
			memcpy(this -> ptr, AR_Origin.ptr, AR_Origin.Size);
		}

		void reset(int info.One_Filter_Size)
		{
			ptr = new int[info.One_Filter_Size];
		}
		~AR()
		{
			if(ptr) {
			delete[] ptr;
			ptr = nullptr;
			}
		}
};
*/


