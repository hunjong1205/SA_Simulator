#include <iostream>
#include <cstring>

using namespace std;

int main(){
	int **p = new int* [10];
	int **t = new int* [10];
	int count = 0;
	
	for(int i=0; i<10; ++i) p[i] = new int[10];
	for(int i=0; i<10; ++i) t[i] = new int[10];
	
	for(int k=0; k<10; k++){
		for(int j=0; j<10; j++){
			p[k][j] = k*10 + j;	
		}
	}
	
	memcpy(t, p, sizeof(t) * 10);

	cout << "p value : " << '\n';

	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			cout << p[i][j] << "." ;
		}
		cout <<'\n';
	}

	cout << "t value : " << '\n';

	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			cout << t[i][j] << "." ;
		}
		cout <<'\n';
	}

	for ( int i=0; i < 10; ++i) delete[] p[i];
	delete[] p;

//	for ( int i=0; i < 10; ++i) delete[] t[i];
	delete[] t;

	return 0;
}
