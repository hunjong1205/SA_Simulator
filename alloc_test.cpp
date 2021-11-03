#include <iostream>
#include <queue>
#include <malloc.h>

using namespace std;

typedef struct AR{
	public:
		int * ptr;
		int size;

		AR(int size) 
		{
			ptr = new int[size];
			this -> size = size;
			cout <<" Constructor Called \n";
		};

		AR(const AR& AR_Origin)
		{
			cout << " Copy Constructor Called \n";
			this -> ptr = new int[AR_Origin.size];
			// memcpy
		}

		void reset(int num)
		{
			ptr = new int[num];
		};

		~AR()
		{
			if(ptr){
				cout << " delete[] ptr \n";
				delete[] ptr;
				ptr = nullptr;
			}
			else {
				cout << " ptr 존재 안함 \n";
			}
		};
};

int main(){

	queue<AR> FIFO;

//	FIFO = new queue<AR>;

	AR AR1(5);

	for(int i=0; i<5; i++){ *(AR1.ptr + i) = 1;}

	// Call Copy constructor
	FIFO.push(AR1);

	cout << "FIFO -> pop() called \n";

	FIFO.pop();

	cout << "test \n";
//	cout << "FIFO Deleted \n";

//	delete FIFO;
//	FIFO = nullptr;
	return 0;

	/*
	AR1.reset(5);
	for(int i=0; i<5; i++)
	*(AR1.ptr + i) = 3;
		
	cout << "FIFO Value : " << *(FIFO -> back().ptr) << endl;
	delete[] FIFO -> front().ptr;
	FIFO->front().ptr = nullptr;

	delete FIFO;
	return 0;
	*/
}
