#include <iostream>

using namespace std;

void func_call(int ****DRAM);

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

	cout << "func_call start!" << endl;

	func_call(DRAM);

	return 0;
}	

void func_call(int ****DRAM){
	int ****tmp;

	tmp = DRAM;
	for(int i=0; i<2; i++){
		for(int j =0; j<1; j++){
			for(int k=0; k<28; k++){
				for(int m=0; m<28; m++) cout << tmp[i][j][k][m] << ' ';
				cout << '\n';
			}
			cout << '\n';
		}
		cout << '\n';
	}

}
