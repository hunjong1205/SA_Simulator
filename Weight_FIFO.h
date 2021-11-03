#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#include "InputWeight_Info.h"

using namespace std;

//Weight FIFO
class Weight_FIFO {
	private:
		float ****Weight;
		queue<float> *WFMAP_FIFO;

	public:
		Weight_FIFO(){};
		~Weight_FIFO(){ /* Add Deallocation Debugging */ };
		bool FIFOMapping(const float DRAM_Weight_fmap[][1][3][3], const Input_Weight_Info &info);
		float** FIFOtoPE(const Input_Weight_Info &info);
		void FIFOClear(const Input_Weight_Info &info);
};
