//基于单词编码
//堆优化
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <iomanip>
using namespace std;

#define MaxWord 10000//最大单词种类数
#define mw 2*MaxWord-1

int totalword;//单词种类数
long long countword;//总单词数

typedef struct {
	double weight;
	int lchild;
	int rchild;
	int parent;
} HTNode;

typedef struct {
	string word;//单词
	double freq;//单词频率
	char code[MaxWord];//哈夫曼编码
} Orword;

HTNode HTreew[mw];
Orword Ow[MaxWord];

//堆结构
//最小堆
typedef struct {
	int num;//与Orword对应
	double weight;
} ElemType;
typedef struct{
	ElemType data[mw];
	int n;
}heap;
//堆功能
void InitHeap(heap& heap);//初始化
bool isHeapEmpty(heap heap);//判空
bool HeapFull(heap heap);//判满
void HeapInsert(heap& heap, ElemType m);//插入
ElemType HeapDeleteMin(heap& heap, int&num);//删除最小

void Initheap(heap& heap){
	heap.n = 0;
}
bool isHeapEmpty(heap heap){
	return (!heap.n);
}
bool HeapFull(heap heap){
	return (heap.n == MaxWord - 1);
}

void HeapInsert(heap& heap, ElemType m){
	int i;
	if (!HeapFull(heap))
	{
		i = ++heap.n;
		while ((i != 1) && (m.weight < heap.data[i / 2].weight))
		{
			heap.data[i] = heap.data[i / 2];
			i /= 2;
		}
	}
	heap.data[i].num = m.num;
	heap.data[i].weight = m.weight;
}
ElemType HeapDeleteMin(heap& heap){
	int parent = 1, child = 2;
	ElemType tmp,elem;
	if (!isHeapEmpty(heap))
	{
		elem = heap.data[1];
		tmp = heap.data[heap.n--];
		while (child <= heap.n)
		{
			if ((child < heap.n) && (heap.data[child].weight > heap.data[child + 1].weight))
				++child;
			if (tmp.weight <= heap.data[child].weight)
				break;
			heap.data[parent] = heap.data[child];
			parent = child;
			child *= 2;
		}
	}
	heap.data[parent] = tmp;
	return elem;
}
void CreatHeap(heap& heap){
	Initheap(heap);
	for(int i = 0;i<totalword;i++){
		ElemType m;
		m.num = i;
		m.weight = Ow[i].freq;
		HeapInsert(heap,m);
	}
}

//单词操作，返回总单词数
long long ReadFileWord() {
	string t;//将文本保存到字符串
	string w;//读取单词
	ifstream file("InputText.txt");
	if (!file) {
		cout << "Failed To Open The File!" << endl;
		return 0;
	}
	long long j = 0;//总字符与单词数
	char ch;
	while (file.get(ch)) {
		t += ch;
	}
	w = "";
	int i = 0;
	while (t[i]) {
		w = "";
		if (t[i] >= 'A' && t[i] <= 'z') {//如果这个字符为字母，开始记录
			while (t[i] >= 'A' && t[i] <= 'z') {
				w = w + t[i];
				i++;
			}
			j++;
		}
		else {
			w = t[i];//标点，直接记录
			i++;
			j++;
		}
		int index = 0;
		int flag = 0;
		while (Ow[index].word != "") {
			if (Ow[index].word == w) {
				Ow[index].freq++;//freq在这里为频数
				flag = 1;
				break;
			}
			else {
				index++;
			}
		}
		if (flag == 0) {
			totalword++;
			Ow[index].word = w;
			Ow[index].freq++;
		}
	}
	file.close();
	return j;
}
//利用堆找两个最小值
void SelectMinword(heap& heap,int& p1, int& p2) {
	p1 = HeapDeleteMin(heap).num;
	p2 = HeapDeleteMin(heap).num;
}
// void SelectMinword(int n, int& p1, int& p2) {
// 	int i, j;
// 	for (i = 0; i < n; ++i) {
// 		if (HTreew[i].parent == -1) {
// 			p1 = i;
// 			break;
// 		}
// 	}
// 	for (j = i + 1; j < n; ++j) {
// 		if (HTreew[j].parent == -1) {
// 			p2 = j;
// 			break;
// 		}
// 	}
// 	for (i = p1; i < n; ++i) {
// 		if ((HTreew[p1].weight > HTreew[i].weight) && (HTreew[i].parent == -1) && (p2 != i))
// 			p1 = i;
// 	}
// 	for (j = p2; j < n; ++j) {
// 		if ((HTreew[p2].weight > HTreew[j].weight) && (HTreew[j].parent == -1) && (p1 != j))
// 			p2 = j;
// 	}
// }

//初始化结点值
void InitHTreeword() {
	for (int i = 0; i < totalword; ++i)
		HTreew[i].weight = Ow[i].freq;
	for (int i = 0; i < mw; ++i)
	{
		HTreew[i].parent = -1;
		HTreew[i].lchild = -1;
		HTreew[i].rchild = -1;
	}
}
//创建树
void CreatHTword() {
	int i, p1, p2;
	InitHTreeword();
	heap heap;
	CreatHeap(heap);
	int n = totalword;
	for (i = n; i < 2 * n - 1; ++i)//0-n-1为字符
	{
		SelectMinword(heap,p1, p2);
		HTreew[p1].parent = HTreew[p2].parent = i;
		HTreew[i].lchild = p1;
		HTreew[i].rchild = p2;
		HTreew[i].weight = HTreew[p1].weight + HTreew[p2].weight;
		ElemType m;
		m.num = i;
		m.weight = HTreew[i].weight;
		HeapInsert(heap,m);
	}
}
//编码
void WordSetHuffmanEncoding() {
	int c, p, i; //cp分别为孩子和双亲的位置
	char cd[MaxWord + 1]; //临时存放编码
	cd[totalword] = '\0';
	int start;//编码在cd中的位置
	for (i = 0; i < totalword; ++i) {
		start = totalword;
		c = i;
		while ((p = HTreew[c].parent) >= 0) {
			cd[--start] = (HTreew[p].lchild == c) ? '0' : '1'; //左0右1
			c = p;//上溯
		}
		strcpy(Ow[i].code, &cd[start]);
	}
}
//计算频率
void ConvertFreq(){
	for(int i = 0;Ow[i].word!="";i++){
		Ow[i].freq = (double)Ow[i].freq/countword;
	}
}
void wordHuffmanConpress(){
	ifstream file("InputText.txt");
	char ch;
	if (!file) {
		cout << "Failed To Open The Original Text!" << endl;
	}
	ofstream bfile;
	bfile.open("CompressedFile.huffman", ios::binary);
	if (!bfile) {
		cout << "Failed To Open The Compressed Text!" << endl;
	}
	//无解释数据
	int t;//查找
	unsigned char bin = 0;//1字节
	int index;
	int bitindex = 0;
	string s;
	while (file.get(ch)) {
		s += ch;
	}
	string w = "";
	int i = 0;
	while (s[i]) {
		w = "";
		if (s[i] >= 'A' && s[i] <= 'z') {//如果这个字符为字母，开始记录
			while (s[i] >= 'A' && s[i] <= 'z') {
				w = w + s[i];
				i++;
			}
		}
		else {
			w = s[i];//标点，直接记录
			i++;
		}
		for (t = 0; t < totalword; t++) {
			if (Ow[t].word == w) //查码
				break;
		}
		for (index = 0; Ow[t].code[index]; ++index) {
			if (Ow[t].code[index] == '0')
				bin = bin << 1;
			else
				bin = (bin << 1) + 1;

			bitindex++;
			if (bitindex == 8) {
				bfile << bin;
				bitindex = 0;
				bin = 0;
			}

		}
	}
	if (bitindex) { //最后不足8位
		bin = bin << (8 - bitindex);
		bfile << bin << (unsigned char)bitindex;
	}
	file.close();
	bfile.close();
}
void CompressInformantionword(){
	struct _stat In, Out;
	_stat("InputText.txt", &In);
	_stat("CompressedFile.huffman", &Out);
	double Inbitst = In.st_size;
	double Outbitst = Out.st_size;
	cout << "实际压缩率为：" << (double)Outbitst / Inbitst * 100 << "%" << endl;
}
void test2() {
	countword = ReadFileWord();
	ConvertFreq();
	CreatHTword();
	WordSetHuffmanEncoding();
	cout<<"--------------------基于单词的压缩--------------------"<<endl;
	cout << "这篇文章有" << " " << countword << " 个单词(含标点),共" << " " << totalword << " 种单词(含标点)种类数。" << endl;
	cout << "各单词(含标点)频率及其对应的哈夫曼编码为：" << endl;
	for (int i = 0; i < totalword; ++i) {
		cout << Ow[i].word << ":" << endl;
		cout << "频率：" << Ow[i].freq << "   " << "编码：" << Ow[i].code << endl;
	}
	wordHuffmanConpress();
	cout<<endl;
	CompressInformantionword();
	cout<<"------------------------------------------------"<<endl;
	//测试
	// double sum = 0;
	// for(int i = 0;Ow[i].word!="";i++){
	// 	cout<<Ow[i].word<<":"<<Ow[i].freq<<endl;
	// 	sum +=Ow[i].freq;
	// }
	// cout<<sum;
}
void DeCompressWord(){
	ifstream bfile("CompressedFile.huffman",ios::binary);
	ofstream file("OutputText.txt");
	if(!bfile){
		cout<<"Failed To Open The Compressed File!"<<endl;
		return;
	}
	bfile>>noskipws;//设置读取空白符
	unsigned char b1;
	bfile >> b1;
	int i = 0;
	int j = 2*totalword-2;
	int ccount = 0;
	while(ccount<countword){
		if (((b1 >> (7 - i)) & 1))
			j = HTreew[j].rchild;
		else
			j = HTreew[j].lchild;
		++i;
		if (j < totalword)
		{
			file << Ow[j].word;
			ccount++;
			j = 2 * totalword - 2;
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
int main() {
	test2();
	DeCompressWord();
	return 0;
}
