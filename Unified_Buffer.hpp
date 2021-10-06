#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

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

		void reset(int Element_Size)
		{
			ptr = new int[Element_Size];
		}
		~AR()
		{
			if(ptr) {
			delete[] ptr;
			ptr = nullptr;
			}
		}
};



class Unified_Buffer {
	private:	
		int ***input_fmap;
		int Channel;
		int Input_fmap_Row;
		int Input_fmap_Col;
		int Strides;
		int Element_Size;
		//queue<AR> *FIFO;
		queue<int> *IFMAP_FIFO;
		int *Accumulator_Psum;
		int Acc_Size;
		

	public:
		Unified_Buffer(){
		Acc_Size = 0;
		}

		~Unified_Buffer(){
		if(Accumulator_Psum) delete Accumulator_Psum;
		}

		void QueueMapping(const int ***DRAM_input_fmap, int Input_fmap_Row, int Input_fmap_Col, int Strides, int Filter_Row, int Filter_Col, int Filter_Channel);
		void QueueClear();
		void QueuetoPE();
		void Accumulator_to_Unified_Buffer(const int* ptr, const int Size);
};

void Unified_Buffer::QueueMapping(const int ***DRAM_input_fmap, int Input_fmap_Row, int Input_fmap_Col, int Strides, int Filter_Row, int Filter_Col, int Filter_Channel){

	this -> Input_fmap_Row = Input_fmap_Row;
	this -> Input_fmap_Col = Input_fmap_Col;
	this -> Channel = Filter_Channel;
	this -> Strides = Strides;
	input_fmap = new int **[Channel];

	// Input_fmap Memory Allocation to DRAM
	for(int i=0; i<Channel; i++){
		input_fmap[i] = new int * [Input_fmap_Row];
		for(int j=0; j<Input_fmap_Row; j++) input_fmap[i][j] = new int [Input_fmap_Col];
	}

	// DRAM -> Unified_Buffer
	memcpy(input_fmap, DRAM_input_fmap, sizeof(input_fmap) * Input_fmap_Row * Input_fmap_Col * Channel);

	cout<< "Input fmap transferred from DRAM to Unified Buffer \n";
		
	int Start_Col= 0;
	int Start_Row= 0;
	int Element_Index = 0;
	Element_Size = Filter_Channel * Filter_Row * Filter_Col;

	// Malloc Queue Size, It Needs QueueClear essentially!
	// this -> FIFO = new queue<AR>;
	
	// Malloc Queue Size, It Needs QueueClear essentially!
	this -> IFMAP_FIFO = new queue<int>[Element_Size];

	// Unified_Buffer to Input_Queue(Systolic_Data Setup)
	for(int Start_Row=0; Start_Row<input_fmap_Row-Filter_Row+1; Start_Row++){
		for(int Start_Col=0; Start_Col<input_fmap_Col-Filter_Col+1; Start_Col++){
			Element_Index = Element_Size;
			for(int j=Start_Row; j<Filter_Row+Start_Row; j++){
				for(int k=Start_Col; k<Filter_Col+Start_Col; k++){
					for(int i=0; i<Filter_Channel; i++){
						if(Element_Index < 0) // Index Error occured!
						IFMAP_FIFO[Element_Index--].push(input_fmap[i][j][k]);
					}
				}
			}
		}
	}

	cout<< "Input fmap Unified_Buffer to Input_Queue Done! \n";

	// Memory Deallocation of input_fmap
	for(int i=0; i<Channel; i++){
		for(int j=0; j<Input_fmap_Row; j++) delete [] input_fmap[i][j];
	}

	for(int i=0; i<3; i++) delete [] input_fmap[i];
	
	delete[] input_fmap;
	input_fmap = nullptr;

}

void Unified_Buffer::QueuetoPE(int Cycle, int* PE_Col, int Channel_Size){
	// while(!FIFO -> empty()) 방식으로 추가?
	/*
	int* tmp_ptr = new int[FIFO -> front().Size];
	memcpy(tmp_ptr, FIFO -> front().ptr, FIFO -> front().Size];
	FIFO -> pop();
	return tmp_ptr;
	*/
	int Cycle_tmp;
	if(Cycle > Channel_Size) Cycle_tmp = Channel_Size;
	else Cycle_tmp = Cycle + 1;
	for(int i=0; i<Cycle_tmp; i++){
		PE_Col[i] =	IFMAP_FIFO[i].front();		
		IFMAP_FIFO[i].pop();
	}	
	cout<< Cycle_tmp <<" cycle is done \n"
}

void Unified_Buffer::QueueClear(){
	// Delete FIFO AR
	/*	
	while(!(FIFO -> empty())) FIFO -> pop();
	delete FIFO;
	FIFO = nullptr;
	*/
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
