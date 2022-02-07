//基于字符编码
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <iomanip>

using namespace std;
#define ASC 128
#define m 2*ASC-1//2n-1个节点

int totalch;//字符种类数
long long countch;//总字符数

typedef struct {
	double weight;
	int lchild;
	int rchild;
	int parent;
} HTNode;

typedef struct {
	char ch;//字符
	double freq;//字符频率
	char code[m];//哈夫曼编码
} Orchar;


HTNode HTree[m];
Orchar Or[ASC];//记录各字符信息

//分字符读文件，返回总字符数
long long ReadFile(string &text) {
	ifstream file("InputText.txt");
	if (!file) {
		cout << "Failed To Open The File!" << endl;
		return 0;
	}
	int List[ASC] = {0};//频数
	char ch;
	long long i = 0;//总字符数
	int total = 0;//字符种类数
	while (file.get(ch)) {
		text += ch;//测试
		List[(int)ch]++;
		i++;
	}
	file.close();
	int p = 0;
	for (int k = 0; k < ASC; ++k) {
		if (List[k]) {
			total++;
			Or[p].ch = k;
			Or[p].freq = (double)List[k] / i;
			p++;
		}
	}
	totalch = total;//字符种类数
	return i;
}
//初始化结点值
void InitHTree() {
	for (int i = 0; i < totalch; ++i)
		HTree[i].weight = Or[i].freq;
	for (int i = 0; i < m; ++i)
	{
		HTree[i].parent = -1;
		HTree[i].lchild = -1;
		HTree[i].rchild = -1;
	}
}
//选取两个最小数
void SelectMin(int n, int& p1, int& p2) {
	int i, j;
	for (i = 0; i < n; ++i) {
		if (HTree[i].parent == -1) {
			p1 = i;
			break;
		}
	}
	for (j = i + 1; j < n; ++j) {
		if (HTree[j].parent == -1) {
			p2 = j;
			break;
		}
	}
	for (i = p1; i < n; ++i) {
		if ((HTree[p1].weight > HTree[i].weight) && (HTree[i].parent == -1) && (p2 != i))
			p1 = i;
	}
	for (j = p2; j < n; ++j) {
		if ((HTree[p2].weight > HTree[j].weight) && (HTree[j].parent == -1) && (p1 != j))
			p2 = j;
	}
}
//创建数
void CreatHT() {
	int i, p1, p2;
	InitHTree();
	int n = totalch;
	for (i = n; i < 2 * n - 1; ++i)//0-n-1为字符
	{
		SelectMin(i, p1, p2);
		HTree[p1].parent = HTree[p2].parent = i;
		HTree[i].lchild = p1;
		HTree[i].rchild = p2;
		HTree[i].weight = HTree[p1].weight + HTree[p2].weight;
	}

}
//编码
void CharSetHuffmanEncoding() {
	int c, p, i; //cp分别为孩子和双亲的位置
	char cd[ASC + 1]; //临时存放编码
	cd[totalch] = '\0';
	int start;//编码在cd中的位置
	for (i = 0; i < totalch; ++i) {
		start = totalch;
		c = i;
		while ((p = HTree[c].parent) >= 0) {
			cd[--start] = (HTree[p].lchild == c) ? '0' : '1'; //左0右1
			c = p;//上溯
		}
		strcpy(Or[i].code, &cd[start]);
	}
}
//输出二进制文件
void HuffmanConpress() {
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
	//解释数据
	bfile << totalch;
	for (int i = 0; i < totalch; i++)
		bfile << Or[i].ch;
	for (int i = totalch; i < 2 * totalch - 1; ++i)
		bfile << (unsigned char)HTree[i].lchild << (unsigned char)HTree[i].rchild; //左右结点
	bfile << countch;
	int t;//查找
	unsigned char bin = 0;//1字节
	int index;
	int bitindex = 0;
	while (file.get(ch)) {
		for (t = 0; t < totalch; t++) {
			if (Or[t].ch == ch) //查码
				break;
		}
		for (index = 0; Or[t].code[index]; ++index) {
			if (Or[t].code[index] == '0')
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
//输出压缩信息
void CompressInformantion(string text) {
	double Inbits  = 8 * countch;
	double Outbits = 0;
	for (int i = 0; i < countch; i++) {
		int t;
		int j;
		for (t = 0; t < totalch; t++) {
			if (Or[t].ch == text[i]) //查码
				break;
		}
		for (j = 0; Or[t].code[j]; j++);
		Outbits += j;
	}
	cout << "理论压缩率为：" << (double)Outbits / Inbits * 100 << "%" << endl;
	struct _stat In, Out;
	_stat("InputText.txt", &In);
	_stat("CompressedFile.huffman", &Out);
	double Inbitst = In.st_size;
	double Outbitst = Out.st_size;
	cout << "实际压缩率为：" << (double)Outbitst / Inbitst * 100 << "%" << endl;
}

void test1() {
	string text;//文件读入字符串中
	countch = ReadFile(text);
	CreatHT();
	CharSetHuffmanEncoding();
	cout<<"--------------------基于字符的压缩--------------------"<<endl;
	cout << "这篇文章有" << " " << countch << " 个字符,共" << " " << totalch << " 种字符种类数。" << endl;
	cout << "各字符频率及其对应的哈夫曼编码为：" << endl;
	for (int i = 0; i < totalch; ++i) {
		cout << Or[i].ch << ":" << endl;
		cout << "频率：" << Or[i].freq << "   " << "编码：" << Or[i].code << endl;
	}
	HuffmanConpress();
	cout<<endl;
	CompressInformantion(text);
	cout<<"------------------------------------------------"<<endl;
}

int main() {
	test1();
	return 0;
}
