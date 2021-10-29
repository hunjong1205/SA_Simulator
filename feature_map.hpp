#include <iostream>

using namespace std;

class Input_Weight_Info{
	public:
		Input_Weight_Info(int Input_Row_Size , int Input_Col_Size, int Input_Channel_Size, int Filter_Row_Size, int Filter_Col_Size, int Filter_Channel_Size, int Filter_Num_Size, int Strides);
		int	Input_fmap_Row_Size;
		int	Input_fmap_Col_Size;
		int Input_fmap_Channel_Size;
		
		int	Filter_Row_Size;
		int	Filter_Col_Size;
		int	Filter_Channel_Size;
		int	Filter_Num_Size;

		int Strides;

		int	One_Filter_Size;

};

Input_Weight_Info::Input_Weight_Info(int Input_Row_Size = 0, int Input_Col_Size = 0, int Input_Channel_Size = 0, int Filter_Row_Size = 0, int Filter_Col_Size = 0, int Filter_Channel_Size = 0, int Filter_Num_Size = 0, int Strides = 0){
	this -> Input_fmap_Row_Size = Input_Row_Size;
	this -> Input_fmap_Col_Size = Input_Col_Size;
	this -> Input_fmap_Channel_Size = Input_Channel_Size;
	this -> Filter_Row_Size = Filter_Row_Size;
	this -> Filter_Col_Size = Filter_Col_Size;
	this -> Filter_Channel_Size = Filter_Channel_Size;
	this -> Filter_Num_Size = Filter_Num_Size;
	this -> One_Filter_Size = Filter_Row_Size * Filter_Col_Size * Filter_Channel_Size;
	this -> Strides = Strides;

}
