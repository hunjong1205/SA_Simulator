#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#include "Feature_map.hpp"

using namespace std;

//Weight FIFO
class Weight_FIFO {
	private:
		int ****Weight;
		queue<int> *WFMAP_FIFO;

	public:
		Weight_FIFO();
		~Weight_FIFO(){ /* Add Deallocation Debugging */ };
		bool FIFOMapping(const int DRAM_Weight_fmap[][3][3][3], const Input_Weight_Info &info);
		auto FIFOtoPE(const Input_Weight_Info &info);
		void FIFOClear(const Input_Weight_Info &info);
};

bool Weight_FIFO::FIFOMapping(const int DRAM_Weight_fmap[][3][3][3], const Input_Weight_Info &info){

	// Weight_fmap Memory Allocation to DRAM
	Weight = new int *** [info.Filter_Num_Size];

	for(int m=0; m<info.Filter_Num_Size; m++)
	{
			Weight[m] = new int ** [info.Filter_Channel_Size];
			for(int c=0; c<info.Filter_Channel_Size; c++)
			{
				Weight[m][c] = new int * [info.Filter_Col_Size];
				for(int r=0; r<info.Filter_Col_Size; r++)
					Weight[m][c][r] = new int[info.Filter_Row_Size];
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
	
	return 1;

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
	for(int i=0; i<info.Filter_Num_Size; i++){
		for(int j=0; j<info.Filter_Row_Size; j++){
			for(int k=0; k<info.Filter_Col_Size; k++){
				for(int m=0; m<info.Filter_Channel_Size; m++){
					WFMAP_FIFO[Element_Index].push(Weight[i][m][k][j]);
				}
			}
		}
		Element_Index++;
	}
	*/


//}

auto Weight_FIFO::FIFOtoPE(const Input_Weight_Info &info){
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
	int **tmp = new int*[info.One_Filter_Size];
	for(int i=0; i<info.One_Filter_Size; i++) tmp[i] = new int[info.Filter_Num_Size];

	for(int i=0; i<info.Filter_Num_Size; i++){
		for(int c=0; c<info.Filter_Row_Size; c++){
			for(int b=0; b<info.Filter_Col_Size; b++){
				for(int a=0; a<info.Filter_Channel_Size; a++){
					tmp[info.One_Filter_Size - (a + b + c)][i] = Weight[i][a][b][c];
				}
			}
		}
	}

	return tmp;

}

void Weight_FIFO::FIFOClear(const Input_Weight_Info &info){

	// Memory Deallocation
	for(int m=0; m<info.Filter_Num_Size; m++)
	{
		for(int c=0; c<info.Filter_Channel_Size; c++)
		{
			for(int r=0; r<info.Filter_Row_Size; r++) delete[] Weight[m][c][r];
		delete[] Weight[m][c];
		}
		delete[] Weight[m];
	}

	delete[] Weight;
	Weight = nullptr;

	delete[] WFMAP_FIFO;
	WFMAP_FIFO = nullptr;
}

