#include <iostream>

using namespace std;

class Unified_Buffer {
	private:	
		int ***input_fmap;
	
	public:
		Unified_Buffer(){
			input_fmap = new int **[Channel];
			for(int i=0; i<Channel; i++){
					input_fmap[i] = new int * [Input_fmap_Row];
					for(int j=0; j<Input_fmap_Row; j++) input_fmap[i][j] = new int [Input_fmap_Col];
			}
		}

		~Unified_Buffer(){
			for(int i=0; i<Channel; i++){
				for(int j=0; j<Input_fmap_Row; j++) delete [] input_fmap[i][j];
			}

			for(int i=0; i<3; i++) delete [] input_fmap[i];
			
			delete[] input_fmap;
		}

		void QueueMapping();


};

void Unified_Buffer::QueueMapping(){
	vector<int> v(Queue_Size, 0);
	int Start_Width = 0;
	int Start_Height = 0;
	int Max_Vector_Element_Num = Filter_H * Filter_W * Filter_Channel;
	int Vector_Index = 0;
	for(Start_Height=0; Start_Height<input_fmap_Height-Filter_Height+1; Start_Height++){
		for(Start_Width=0; Start_Width<input_fmap_Width-Filter_Width+1; Start_Width++){
			for(i=0; i<3; i++){
				for(j=Start_Height; j<Filter_Height-Start_Height; j++){
					for(k=Start_Width; k<Filter_Width-Start_Width; k++){
						v.insert(v.begin() + Vector_Index, input_fmap[i][j][k];
						Vector_Index++;
					}
				}
			}
		}
	}
	// Inputs Vector to Queue
	Queue< 

	Vector

}
