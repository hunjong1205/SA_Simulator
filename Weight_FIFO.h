#include <iostream>
#include <queue>
#include <vector>
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
		Weight_FIFO(){ cout << "\n" << "Weight FIFO Generated " << "\n" ; };
		~Weight_FIFO(){ 
		/* Add Deallocation Debugging */
		cout << "\n" << "Weight FIFO Generated " << "\n";
		};
		bool FIFOMapping(const float DRAM_Weight_fmap[32][1][3][3], const Input_Weight_Info &info);
		vector<vector<float>> FIFOtoPE(const Input_Weight_Info &info);
		void FIFOClear(const Input_Weight_Info &info);
};
