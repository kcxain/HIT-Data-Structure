//基于字符编码
//堆优化
//K哈夫曼树
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <iomanip>
using namespace std;

#define ASC 128
#define m 2*ASC-1//2n-1个节点

#define Max_K 9

int k;//k值
int totalch;//字符种类数
int nn;//补0之后的字符种类数
long long countch;//总字符数

typedef struct {
	double weight;
	int child[Max_K];//K个子节点
	int parent;
} HTNode;

typedef struct {
	char ch;//字符
	double freq;//字符频率
	char code[m];//哈夫曼编码
} Orchar;

HTNode HTree[m];
Orchar Or[ASC];


//堆结构
//最小堆
typedef struct {
	int num;//与Orword对应
	double weight;
} ElemType;
typedef struct{
	ElemType data[m];
	int n;
}heap;

//堆功能
void InitHeap(heap& heap);//初始化
bool isHeapEmpty(heap heap);//判空
bool HeapFull(heap heap);//判满
void HeapInsert(heap& heap, ElemType t);//插入
ElemType HeapDeleteMin(heap& heap, int& num);//删除最小

void Initheap(heap& heap){
	heap.n = 0;
}
bool isHeapEmpty(heap heap){
	return (!heap.n);
}
bool HeapFull(heap heap){
	return (heap.n == m - 1);
}

void HeapInsert(heap& heap, ElemType t){
	int i;
	if (!HeapFull(heap))
	{
		i = ++heap.n;
		while ((i != 1) && (t.weight < heap.data[i / 2].weight))
		{
			heap.data[i] = heap.data[i / 2];
			i /= 2;
		}
	}
	heap.data[i].num = t.num;
	heap.data[i].weight = t.weight;
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
	for(int i = 0;i<totalch;i++){
		ElemType t;
		t.num = i;
		t.weight = Or[i].freq;
		HeapInsert(heap,t);
	}
}

//利用堆找 K 个最小值
void SelectMinword(heap& heap,int p[]) {
	for(int i = 0;i<k;i++){
		p[i] = HeapDeleteMin(heap).num;
		//cout<<p[i]<<endl;
	}
}

//读文件
long long ReadFile(){
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
//初始化节点值
void InitHTree(){
	for (int i = 0; i < totalch; ++i)
		HTree[i].weight = Or[i].freq;
	for (int i = totalch; i < 2*totalch-1; ++i)
		HTree[i].weight = 0;
	for (int i = 0; i < m; ++i){
		HTree[i].parent = -1;
		for (int j = 0; j < k; ++j){
			HTree[i].child[j] = -1;
		}
	}
}
//创建树
void CreatHTree() {
	int i = totalch;
	InitHTree();
	heap heap;
	CreatHeap(heap);
	int n = totalch;
	//第一次取 k 个，后面相当于取k-1个数，剩余部分补0
	if ((n - 1) % (k - 1)) {
		for (int i = 0; i < (k - 1) - (n - 1) % (k - 1); ++i){
			ElemType t;
			t.num = -1;
			t.weight = 0;
			HeapInsert(heap, t);
		}
	}
	//现在有 n + (k - 1) - (n - 1) % (k - 1)个叶节点
	nn = n + (k - 1) - (n - 1) % (k - 1);
	//非叶节点有 (nn-1)/(k-1) 个
	for (i = n; i < n + (nn-1)/(k-1) - 1; ++i){
		int p[Max_K];//最小权值节点
		SelectMinword(heap,p);
		for (int j = 0; j < k; ++j){
			HTree[p[j]].parent = i;
			HTree[i].child[j] = p[j];
			HTree[i].weight += HTree[p[j]].weight;
		}
		ElemType t;
		t.num = i;
		t.weight = HTree[i].weight;
		HeapInsert(heap,t);
	}
}
//编码
void SetHuffmanEncoding() {
	int c, p, i; //cp分别为孩子和双亲的位置
	char cd[m + 1]; //临时存放编码
	cd[totalch] = '\0';
	int start;//编码在cd中的位置
	for (i = 0; i < totalch; ++i) {
		start = totalch;
		c = i;//c用来遍历叶子节点
		//cout<<HTree[c].parent<<endl;
		while ((p = HTree[c].parent) >= 0) {
			int j;
			for(j = 0;j<k;j++){
				if(HTree[p].child[j] == c)
					break;
			}
			cd[--start] = j+'0';//第j个儿子
			c = p;//上溯
		}
		strcpy(Or[i].code, &cd[start]);
	}
}
void test(){
	countch = ReadFile();
	CreatHTree();
	SetHuffmanEncoding();
	printf("-------------------- %d-哈夫曼树的压缩--------------------",k);
	for (int i = 0; i < totalch; ++i){
		cout<< Or[i].ch<<":"<<endl;
		cout<<"频率:"<<Or[i].freq<<"   "<<"编码："<<Or[i].code<<endl;
	}
}
int main(void){
	cout<<"请输入 K 值："<<endl;
	cin>>k;
	test();
}
