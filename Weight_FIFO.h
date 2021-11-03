#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#include "InputWeight_Info.h"

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
