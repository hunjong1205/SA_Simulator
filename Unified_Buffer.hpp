#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

typedef struct AR{
	public:
		int *ptr;

		AR(int Filter_Size) : 
		{
			ptr = new int[Filter_Size];
		}

		void reset(int Element_Size):
		{
			ptr = new int[Element_Size];
		}
		~AR() :
		{
			if(ptr) delete[] ptr;
		}
};



class Unified_Buffer {
	private:	
		int ***input_fmap;
		int Channel;
		int Input_fmap_Row;
		int Input_fmap_Col;
		int Strides;
		queue<AR> *FIFO;

	public:
		void QueueMapping(const int ***DRAM_input_fmap, int Input_fmap_Row, int Input_fmap_Col, int Strides, int Filter_Row, int Filter_Col, int Filter_Channel);
		void QueueClear();
		void QueuetoPE();
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
	memcpy(input_fmap, DRAM_input_fmap, sizeof(input_fmap) * Input_fmap_Row * Input_fmap_Col);
		
	int Start_Col= 0;
	int Start_Row= 0;
	int Element_Size = Filter_Channel * Filter_Row * Filter_Col;
	int FIFO_Element[Element_Size];
	int Element_Index = 0;

	// Struct Construct
	AR AR1(Element_Size);

	// Malloc Queue Size, It Needs QueueClear essentially!
	this -> FIFO = new queue<AR>;

	// Unified_Buffer to Input_Queue(Systolic_Data Setup)
	int ptr_index;
	for(int Start_Row=0; Start_Row<input_fmap_Row-Filter_Row+1; Start_Row++){
		for(int Start_Col=0; Start_Col<input_fmap_Col-Filter_Col+1; Start_Col++){
			ptr_index = 0;
			for(int i=0; i<Filter_Channel; i++){
				for(int j=Start_Row; j<Filter_Row+Start_Row; j++){
					for(int k=Start_Col; k<Filter_Col+Start_Col; k++){
						if(!AR1.ptr) cout << "AR1.ptr Error Occured" << "\n";
						else *(AR1.ptr + ptr_index++) = input_fmap[i][j][k];
					}
				}
			}
			FIFO -> push(AR1);
			// Reset AR1
			AR1.reset(Element_Size);
		}
	}

	// Memory Deallocation of input_fmap
	for(int i=0; i<Channel; i++){
		for(int j=0; j<Input_fmap_Row; j++) delete [] input_fmap[i][j];
	}

	for(int i=0; i<3; i++) delete [] input_fmap[i];
	
	delete[] input_fmap;
	input_fmap = nullptr;

}

void Unified_Buffer::QueueClear(){
	// Delete FIFO AR
	while(!(FIFO -> empty())){
   		delete[] FIFO -> front().ptr;
		FIFO -> front().ptr = nullptr;
		FIFO -> pop();
	}
	delete FIFO;
	FIFO = nullptr;
}

int* Unified_Buffer::QueuetoPE(){
	AR tmp_AR = FIFO -> front();
	int* tmp_ptr = new int[_msize(tmp_AR.ptr)/sizeof(int)];
	memcpy(tmp_ptr, tmp_AR.ptr, _msize(tmp_AR.ptr)/sizeof(int));
	delete[] tmp_AR.ptr;
	FIFO -> pop();
	return tmp_ptr;
}
