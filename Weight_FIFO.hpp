#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

//Weight FIFO
class Weight_FIFO {
	private:
		int ****Weight;
		queue<int> *FIFO;

	public:
		void FIFOMapping(int *DRAM_Weight_fmap, int Weight_fmap_Row, int Weight_fmap_Col, int Weight_fmap_Num , int Weight_fmap_Channel);
		void FIFOClear();
		void FIFOtoPE();
};

void Weight_FIFO::FIFOMapping(int *DRAM_Weight_fmap, int Weight_fmap_Row, int Weight_fmap_Col, int Weight_fmap_Num , int Weight_fmap_Channel){
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
	copy(DRAM_Weight_fmap, DRAM_Weight_fmap + Weight_Size, Weight);

	// DRAM -> FIFO 로 바로 넣는 방법, 있을까?
	//	this -> FIFO = new queue[Weight_Size / Weight_fmap_Num];
	//  for(int i=0; i<Weight_Size/Weight_fmap_Num; i++)
	//	FIFO[i].push

	// Weight PE Mapping
	int n = 0;      //Number of Weight Vector Size
	temp2 vector[Filter_H * Filter_W * Filter_Channel]
	for(int c=0; c<Weight_fmap_Channel; c++){         // 3
		for(int k=0; k<Weight_Filter_Row; k++){          // 3
			for(int j=0; j<Weight_Filter_Col; j++){       // 3
				for(int m=0; m<Num_of_Filter; m++)     // m
				{FIFO[FIFO_Index].push(Weight[m][c][k][j]);}
			FIFO_Index++;
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
	delete[] FIFO;
}

void Weight_FIFO::FIFOtoPE(){
}
