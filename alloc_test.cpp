#include <iostream>
#include <queue>

using namespace std;

typedef struct AR{
	public:
		int * ptr;

		AR(int size) 
		{
			ptr = new int[size];
			cout <<" Constructor Called \n";
		};

		void reset(int num)
		{
			ptr = new int[num];
		};

		~AR()
		{
			if(ptr != NULL){
				cout << " delete[] ptr \n";
				delete[] ptr;
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

	FIFO.push(AR1);

	cout << "FIFO -> pop() called \n";

	FIFO.pop();

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
