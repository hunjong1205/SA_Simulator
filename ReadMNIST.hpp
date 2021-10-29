#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Feature_map.hpp"
 
using namespace std;

int ReverseInt(int i);
void ReadMNIST(int NumberOfImages, int DataOfAnImage, vector<vector<double>> &arr, int Input_fmap[10000][1][28][28], Input_Weight_Info &info);
void ReadMNISTLabel(vector<unsigned char> &arr);
 
void Data(int Input_fmap[10000][1][28][28], Input_Weight_Info &info)
{
    vector<vector<double>> ai;
    ReadMNIST(10000, 784, ai, Input_fmap, info);                // 훈련데이터를 불러옴

//  vector<unsigned char> al;
//  ReadMNISTLabel(al);                        // 레이블을 읽어 옴
/*	for(int k = 0; k<100; k++){
			for(int i = 0; i < 28; i++){
				for(int j = 0; j < 28; j++){
				cout << ai[k][i*28 + j] <<' ';
				}
			cout << endl;
			}
	}
	cout << "vector ai size : " << ai.size() << endl;
	cout << "vector ai[0] size : " << ai[0].size() << endl;
*/
	
}
 
 
int ReverseInt(int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}
void ReadMNIST(int NumberOfImages, int DataOfAnImage, vector<vector<double>> &arr, int Input_fmap[10000][1][28][28], Input_Weight_Info &info)   // MNIST데이터를 읽어온다.
{
    arr.resize(NumberOfImages, vector<double>(DataOfAnImage));
    ifstream file("./t10k-images-idx3-ubyte", ios::binary);
    if (file.is_open())
    {
		cout << "File open Success !" << '\n';
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
 
        file.read((char*)&magic_number, sizeof(magic_number));
        magic_number = ReverseInt(magic_number);
        file.read((char*)&number_of_images, sizeof(number_of_images));
        number_of_images = ReverseInt(number_of_images);
        file.read((char*)&n_rows, sizeof(n_rows));
        n_rows = ReverseInt(n_rows);
		info.Input_fmap_Row_Size = n_rows;
        file.read((char*)&n_cols, sizeof(n_cols));
        n_cols = ReverseInt(n_cols);
		info.Input_fmap_Col_Size = n_cols;
		info.Input_fmap_Channel_Size = 1;
 
        char inputstring[1000];
        for (int i = 0; i<10000; ++i)
        {
            for (int r = 0; r<n_rows; ++r)
            {
                for (int c = 0; c<n_cols; ++c)
                {
                    unsigned char temp = 0;
                    file.read((char*)&temp, sizeof(temp));
                    arr[i][(n_rows*r) + c] = (double)temp;
					Input_fmap[i][0][r][c] = (int)temp;
                }
            }
        }
    }
}
 
void ReadMNISTLabel(vector<unsigned char> &arr){                // 레이블을 읽어온다.
    ifstream file("train-labels.idx1-ubyte");
    for (int i = 0; i<10000; ++i)
    {
        unsigned char temp = 0;
        file.read((char*)&temp, sizeof(temp));
        if (i > 7)
            arr.push_back((unsigned char)temp);
 
    }
}
