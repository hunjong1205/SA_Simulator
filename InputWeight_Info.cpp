#include "InputWeight_Info.h"

using namespace std;

Input_Weight_Info::Input_Weight_Info(int Input_Row_Size , int Input_Col_Size , int Input_Channel_Size , int Filter_Row_Size , int Filter_Col_Size , int Filter_Channel_Size , int Filter_Num_Size , int Strides ){
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

void Input_Weight_Info::print(){
	cout << "Input_fmap_Row_Size : " << Input_fmap_Row_Size << endl;
	cout << "Input_fmap_Col_Size : " << Input_fmap_Col_Size << endl;
	cout << "Input_fmap_Channel_Size : " << Input_fmap_Channel_Size << endl;
	cout << "Filter_Row_Size : " << Filter_Row_Size << endl;
	cout << "Filter_Col_Size : " << Filter_Col_Size << endl;
	cout << "Filter_Channel_Size : " << Filter_Channel_Size << endl;
	cout << "Filter_Num_Size : " << Filter_Num_Size << endl;
	cout << "One_Filter_Size : " << One_Filter_Size << endl;
}
