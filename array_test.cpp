#include <iostream>
#include <typeinfo>

using namespace std;

void func_call(const int DRAM[1][28][28]);

int main()
{
	int DRAM [2][1][28][28];

	for(int i = 0; i<2; i++){
		for(int j =0; j<1; j++){
			for(int k=0; k<28; k++){
				for(int m=0; m<28; m++){
					DRAM[i][j][k][m] = 100*i + 10*k + m;
					cout << DRAM[i][j][k][m] << ' ';
			   	}
			cout << '\n';
			}
		cout << '\n';
		}
	cout << '\n';
	}

//	cout << "func_call start!" << endl;

	cout << "DRAM[0][0][0][0] type is : " << typeid((int [][28][28])DRAM[1][0][0][0]).name() << endl;

// 	func_call((int [1][28][28])&DRAM[0][0][0][0]);

	return 0;
}	

void func_call(const int DRAM[1][28][28]){

		for(int j =0; j<1; j++){
			for(int k=0; k<28; k++){
				for(int m=0; m<28; m++) cout << DRAM[j][k][m] << ' ';
				cout << '\n';
			}
			cout << '\n';
		}
		cout << '\n';

}
