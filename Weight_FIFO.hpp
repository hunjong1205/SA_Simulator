#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

//Weight FIFO
class Weight_FIFO {
	private:
		int ****Weight;
		queue<AR> *FIFO;

	public:
		void FIFOMapping(const int *DRAM_Weight_fmap, int Weight_fmap_Row, int Weight_fmap_Col, int Weight_fmap_Num , int Weight_fmap_Channel);
		void FIFOClear();
		int* FIFOtoPE();
};

void Weight_FIFO::FIFOMapping(const int *DRAM_Weight_fmap, int Weight_fmap_Row, int Weight_fmap_Col, int Weight_fmap_Num , int Weight_fmap_Channel){
	// Memory Allocation(sized for Weight)
	Weight = new int ***[Weight_fmap_Num];
	for(int m=0; i<Weight_fmap_Num; m++)
	{
			Weight[m] = new **int[Weight_fmap_Channel];
			for(int c=0; c<Weight_fmap_Channel; c++)
			{
				Weight[m][c] = new *int[Weight_fmap_Row];
				for(int r=0; r<Weight_fmap_Row; r++)
					Weight[m][c][r] = new int[Weight_fmap_Col];
			}
	}

	// DRAM -> Weight_FIFO
	int Weight_Size = Weight_fmap_Num * Weight_fmap_Channel * Weight_fmap_Row * Weight_fmap_Col;
	memcpy(Weight, DRAM_Weight_fmap, sizeof(Weight) * Weight_fmap_Channel * Weight_fmap_Row * Weight_fmap_Col);
	// copy(DRAM_Weight_fmap, DRAM_Weight_fmap + Weight_Size, Weight);

	// DRAM -> FIFO 로 바로 넣는 방법도 가능함(아래 for문에서 DRAM_Weight_Fmap에서 AR2로 뽑아서 바로 FIFO에 넣을수 있음)
	// 현재는 DRAM(Off-Chip Memory) -> Weight_FIFO(On-Chip Memory 구현을 모방하기 위해 memcpy 사용함

	// Struct Construct
	AR AR2(Weight_fmap_Num);

	// Malloc FIFO Size, It Needs FIFOClear essentially!
	this -> FIFO = new queue<AR>;

	// Weight_FIFO to Weight_FIFO Queue
	int ptr_index;
	for(int c=0; c<Weight_fmap_Channel; c++){         // 3
		for(int k=0; k<Weight_Filter_Row; k++){          // 3
			for(int j=0; j<Weight_Filter_Col; j++){       // 3
				ptr_index = 0;
				for(int m=0; m<Weight_fmap_Num; m++){	  // m
					if(!AR2.ptr) cout << "AR2.ptr Error Occured!" << "\n";
					else *(AR2.ptr + ptr_index++) = Weight[m][c][k][j];
				}
				FIFO -> push(AR2);
				// Reset AR2
				AR2.reset(Weight_fmap_Num);
			}
		}
	}

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

}

void Weight_FIFO::FIFOClear(){
	// Delete FIFO AR
	while(!(FIFO -> empty())) FIFO -> pop();
	delete FIFO;
	FIFO = nullptr;
}

int* Weight_FIFO::FIFOtoPE(){
	int* tmp_ptr = new int[FIFO -> front().Size];
	memcpy(tmp_ptr, FIFO -> front().ptr, FIFO -> front().Size);
	FIFO -> pop();
	return tmp_ptr;
}
