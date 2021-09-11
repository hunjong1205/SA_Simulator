#include <iostream>
#include <cstring>
#include <queue>
#include <cmath>

using namespace std;

typedef struct AR{
	public:
		int *ptr;

		AR(int Filter_Size) : 
		{
			ptr = new int[Filter_Size];
		}

		~AR() :
		{
			delete[] ptr;
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
		Unified_Buffer(int ***DRAM_input_fmap, int Channel, int Input_fmap_Row, int Input_fmap_Col, int Strides){
			input_fmap = new int **[Channel];

			this -> Input_fmap_Row = Input_fmap_Row;
			this -> Input_fmap_Col = Input_fmap_Col;
			this -> Channel = Channel;
			this -> Strides = Strides;

			for(int i=0; i<Channel; i++){
					input_fmap[i] = new int * [Input_fmap_Row];
					for(int j=0; j<Input_fmap_Row; j++) input_fmap[i][j] = new int [Input_fmap_Col];
			}
		// Data Transport(DRAM -> Unified Buffer)
		memcpy(input_fmap, DRAM_input_fmap, sizeof(input_fmap) * Input_fmap_Row * Input_fmap_Col);
		
		}

		~Unified_Buffer(){
			for(int i=0; i<Channel; i++){
				for(int j=0; j<Input_fmap_Row; j++) delete [] input_fmap[i][j];
			}

			for(int i=0; i<3; i++) delete [] input_fmap[i];
			
			delete[] input_fmap;
		}

		void QueueMapping(int Filter_Row, int Filter_Col, int Filter_Channel);
		void QueueClear();
		void QueuetoPE();


};

void Unified_Buffer::QueueMapping(int Filter_Row, int Filter_Col, int Filter_Channel){
	int Start_Col= 0;
	int Start_Row= 0;
	int Element_Size = Filter_Channel * Filter_Row * Filter_Col;
	int FIFO_Element[Element_Size];
	int Element_Index = 0;

	// Struct Construct
	AR AR1(Element_Size);

	// Malloc Queue Size, It Needs QueueClear essentially!
	this -> FIFO = new queue<AR>;

	//this -> FIFO = new queue[pow((Input_fmap_Row-Filter_Row)/Strides + 1, 2)];
	int FIFO_Index= 0;

	for(Start_Row=0; Start_Row<input_fmap_Row-Filter_Row+1; Start_Row++){
		for(Start_Col=0; Start_Col<input_fmap_Col-Filter_Col+1; Start_Col++){
			for(i=0; i<Filter_Channel; i++){
				for(j=Start_Row; j<Filter_Row+Start_Row; j++){
					for(k=Start_Col; k<Filter_Col+Start_Col; k++){
						if(!AR1.ptr) cout << "AR1.ptr Error Occured" << "\n";
						else *(AR1.ptr++) = input_fmap[i][j][k];
					}
				}
			}
			FIFO.push(AR1);
			// Reset AR1
			AR1 = AR AR2(Element_Size);
		}
	}
}

void Unified_Buffer::QueueClear(){
	delete[] FIFO;
}

void Unified_Buffer::QueuetoPE(){
	
}
