#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

//Weight FIFO
class Weight_FIFO {
	private:
		int ****Weight;
		int Weight_fmap_Row;
		int Weight_fmap_Col;
		int Weight_fmap_Num;
		int Weight_fmap_Channel;
		int Element_Size;
		queue<int> *WFMAP_FIFO;

	public:
		Weight_FIFO();
		~Weight_FIFO(){ /* Add Deallocation Debugging */ };
		void FIFOMapping(const int ****DRAM_Weight_fmap, int Weight_fmap_Row, int Weight_fmap_Col, int Weight_fmap_Num , int Weight_fmap_Channel);
		int** FIFOtoPE(const int One_Filter_Size);
		void FIFOClear();
};

void Weight_FIFO::FIFOMapping(const int ****DRAM_Weight_fmap, int Weight_fmap_Row, int Weight_fmap_Col, int Weight_fmap_Num , int Weight_fmap_Channel){
	this -> Weight_fmap_Row = Weight_fmap_Row;
	this -> Weight_fmap_Col = Weight_fmap_Col;
	this -> Weight_fmap_Num = Weight_fmap_Num;
	this -> Weight_fmap_Channel = Weight_fmap_Channel;
	this -> Element_Size = Weight_fmap_Num;

	// Weight_fmap Memory Allocation to DRAM
	Weight = new int *** [Weight_fmap_Num];

	for(int m=0; m<Weight_fmap_Num; m++)
	{
			Weight[m] = new int ** [Weight_fmap_Channel];
			for(int c=0; c<Weight_fmap_Channel; c++)
			{
				Weight[m][c] = new int * [Weight_fmap_Col];
				for(int r=0; r<Weight_fmap_Col; r++)
					Weight[m][c][r] = new int[Weight_fmap_Row];
			}
	}


	// DRAM -> Weight_FIFO
	if(memcpy(Weight, DRAM_Weight_fmap, sizeof(Weight)) != Weight) 
	{
		cout<< "Memcpy Error occured! \n";
	}

	// copy(DRAM_Weight_fmap, DRAM_Weight_fmap + Weight_Size, Weight);

	cout<< "Weight fmap transferred from DRAM to Unified Buffer \n";

	// DRAM -> FIFO 로 바로 넣는 방법도 가능함(아래 for문에서 DRAM_Weight_Fmap에서 AR2로 뽑아서 바로 FIFO에 넣을수 있음)
	// 현재는 DRAM(Off-Chip Memory) -> Weight_FIFO(On-Chip Memory 구현을 모방하기 위해 memcpy 사용함

}
// void Weight_FIFO::FIFOMapping(){
	// Replaced With Weight_FIFO constructor!

	// Malloc FIFO Size, It Needs FIFO Clear essentially!
	// this -> FIFO = new queue<AR>;

	// Malloc FIFO Size, It Needs FIFO Clear essentially!
	// this -> WFMAP_FIFO = new queue<int>[Element_Size];

	// Weight_FIFO to Weight_FIFO Queue
	/*
	int Element_Index = 0;
	for(int i=0; i<Weight_fmap_Num; i++){
		for(int j=0; j<Weight_fmap_Row; j++){
			for(int k=0; k<Weight_fmap_Col; k++){
				for(int m=0; m<Weight_fmap_Channel; m++){
					WFMAP_FIFO[Element_Index].push(Weight[i][m][k][j]);
				}
			}
		}
		Element_Index++;
	}
	*/


//}

int** Weight_FIFO::FIFOtoPE(const int One_Filter_Size){
	/*
	int tmp_array[Element_Size]; 
	for(int i = 0; i<Element_Size; i++){
		if(!WFMAP_FIFO[i].empty()){
		tmp_ptr[i] = WFMAP_FIFO[i].front();
		WFMAP_FIFO[i].pop();
		}
		else cout << "WFMAP_FIFO[%d] is empty" << i << "\n";

	}
	*/

	// Allocate temporal Weight Bus, Deallocate in MXU::Set_PE_Weight
	int **tmp = new int*[One_Filter_Size];
	for(int i=0; i<One_Filter_Size; i++) tmp[i] = new int[Weight_fmap_Num];

	for(int i=0; i<Weight_fmap_Num; i++){
		for(int c=0; c<Weight_fmap_Row; c++){
			for(int b=0; b<Weight_fmap_Col; b++){
				for(int a=0; a<Weight_fmap_Channel; a++){
					tmp[One_Filter_Size - (a + b + c)][i] = Weight[i][a][b][c];
				}
			}
		}
	}

	return tmp;

}

void Weight_FIFO::FIFOClear(){

	// Memory Deallocation
	for(int m=0; m<Weight_fmap_Num; m++)
	{
		for(int c=0; c<Weight_fmap_Channel; c++)
		{
			for(int r=0; r<Weight_fmap_Row; r++) delete[] Weight[m][c][r];
		delete[] Weight[m][c];
		}
		delete[] Weight[m];
	}

	delete[] Weight;
	Weight = nullptr;

	delete[] WFMAP_FIFO;
	WFMAP_FIFO = nullptr;
}

