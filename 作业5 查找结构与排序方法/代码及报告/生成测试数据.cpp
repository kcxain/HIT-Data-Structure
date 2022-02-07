#include<iostream>
#include<fstream>
#include<cstdlib>
#include <time.h>
using namespace std;
const int Max = 2048;
int main() {
	ofstream outfile("inputdata1.txt");
	int data[Max];
	int j = 0;
	for (int i = 0; i <= Max; ++i) {
		if (i % 2) {
			data[j++] = i;
			outfile << i << endl;
		}
	}
	outfile.close();
	ofstream outfile1("inputdata2.txt");
	srand((int)time(NULL));
	for (int i = 0; i < 1000000; i++)
	{
		int pose = rand() % j;
		swap(data[pose],data[j-pose-1]);//随即交换
		swap(data[pose+1],data[j-pose-1]);
	}
	while(j--){
		outfile1<<data[j]<<endl;
	}
	outfile1.close();
}