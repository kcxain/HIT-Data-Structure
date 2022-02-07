//译码器
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;
#define ASC 128
#define m 2*ASC-1//2n-1个节点
//第一位，编码总数total(char型)
//下total位，字符(char型)
//下total-1位，哈夫曼树(int型)
int total;
long long count;
typedef struct {
	double weight;
	int lchild;
	int rchild;
	int parent;
} HTNode;
typedef struct {
	char ch;//字符
	double freq;//字符频率
	char code[ASC];//哈夫曼编码
} Orchar;
HTNode HTree[m];
Orchar Or[ASC];
int main(){
	ifstream bfile("CompressedFile.huffman",ios::binary);
	ofstream file("OutputText.txt");
	if(!bfile){
		cout<<"Failed To Open The Compressed File!"<<endl;
		return 0;
	}
	//字符种类数
	bfile>>total;
	bfile>>noskipws;//设置读取空白符
	//各字符
	for (int i = 0; i < total; ++i){
		bfile>>Or[i].ch;
	}
	//哈夫曼树节点
	for (int i = total; i < 2 * total - 1; ++i)//0-n-1为字符
	{
		unsigned char p1,p2;
		bfile>>p1>>p2;
		HTree[i].lchild = (int)p1;
		HTree[i].rchild = (int)p2;
	}
	//字符数
	bfile>>count;
	cout<<"读入成功！"<<endl;
	cout<<"这篇文章有"<<" "<<count<<" 个字符,共"<<" "<<total<<" 种字符种类数。"<<endl;
	unsigned char b1;
	bfile >> b1;
	int i = 0;
	int j = 2*total-2;
	int ccount = 0;
	while(ccount<count){
		if (((b1 >> (7 - i)) & 1))
			j = HTree[j].rchild;
		else
			j = HTree[j].lchild;
		++i;
		if (j < total)
		{
			file << Or[j].ch;
			ccount++;
			j = 2 * total - 2;
		}
		if (i == 8)
		{
			i = 0;
			bfile>>b1;
		}
	}
	bfile.close();
	file.close();
	cout << "解压成功！" << endl;
}