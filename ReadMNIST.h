#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "InputWeight_Info.h"
 
using namespace std;

int ReverseInt(int i);
void ReadMNIST(int NumberOfImages, int DataOfAnImage, vector<vector<double>> &arr, uint8_t Input_fmap[10000][1][28][28], Input_Weight_Info &info);
void ReadMNISTLabel(vector<unsigned char> &arr);
void ReadWeights(float Weights[32][1][3][3], Input_Weight_Info &info);
void Data(uint8_t Input_fmap[10000][1][28][28], float Weights[32][1][3][3], Input_Weight_Info &info);
