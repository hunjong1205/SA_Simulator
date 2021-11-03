#include <iostream>
#ifndef INPUTWEIGHT_INFO_H
#define INPUTWEIGHT_INFO_H


using namespace std;

class Input_Weight_Info{
	public:
		Input_Weight_Info(int Input_Row_Size, int Input_Col_Size, int Input_Channel_Size, int Filter_Row_Size, int Filter_Col_Size, int Filter_Channel_Size, int Filter_Num_Size, int Strides);
		int	Input_fmap_Row_Size;
		int	Input_fmap_Col_Size;
		int Input_fmap_Channel_Size;
		
		int	Filter_Row_Size;
		int	Filter_Col_Size;
		int	Filter_Channel_Size;
		int	Filter_Num_Size;

		int Strides;

		int	One_Filter_Size;
		void print();
};
#endif
