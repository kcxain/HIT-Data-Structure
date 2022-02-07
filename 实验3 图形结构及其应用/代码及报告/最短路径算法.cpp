#include<iostream>
#include<iomanip>
#include<fstream>
#include<time.h>
using namespace std;

#define inf 10000//定义无穷大
//邻接矩阵表示有向图
#define VertexData int
#define EdgeData int
#define Numvertices 20
//邻接矩阵
typedef struct {
	VertexData vertex[Numvertices];
	EdgeData edge[Numvertices][Numvertices];
	int n;
	int e;
} Graph;
//邻接表
typedef struct node { //边表
	int adjvex;//邻接点下标
	int cost;//权值
	struct node*next;//下一边指针
} EdgeNode;
typedef struct { //顶点表
	int vertex;//顶点信息
	EdgeNode *firstedge;//边链表头指针
} VertexNode;
typedef struct { //邻接表
	VertexNode vexlist[Numvertices];
	int n;
	int e;
} AdjGraph;
//堆结构
//最小堆
typedef struct {
	int num;
	int weight;
} ElemType;
typedef struct {
	ElemType data[Numvertices];
	int n;
} heap;
//堆功能
void InitHeap(heap& heap);//初始化
bool isHeapEmpty(heap heap);//判空
bool HeapFull(heap heap);//判满
void HeapInsert(heap& heap, ElemType m);//插入
ElemType HeapDeleteMin(heap& heap);//删除最小

void InitHeap(heap& heap) {
	heap.n = 0;
}
bool isHeapEmpty(heap heap) {
	return (!heap.n);
}
bool HeapFull(heap heap) {
	return (heap.n == Numvertices - 1);
}

void HeapInsert(heap& heap, ElemType m) {
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
ElemType HeapDeleteMin(heap& heap) {
	int parent = 1, child = 2;
	ElemType tmp, elem;
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
/*--------------------------------------------------------------*/
AdjGraph* ConverttoM(Graph *G) {
	AdjGraph* Gc = new AdjGraph;
	Gc->e = G->e;
	Gc->n = G->n;
	for (int i = 0; i < Gc->n; ++i) {
		Gc->vexlist[i].vertex = G->vertex[i];
		Gc->vexlist[i].firstedge = NULL;
	}
	EdgeNode* temp;
	for (int i = 0; i < G->n; ++i) {
		for (int j = 0; j < G->n; ++j) {
			if (G->edge[i][j]) {
				temp = Gc->vexlist[i].firstedge;//尾插
				Gc->vexlist[i].firstedge = new EdgeNode;
				Gc->vexlist[i].firstedge->adjvex = j;
				Gc->vexlist[i].firstedge->cost = G->edge[i][j];//权值
				Gc->vexlist[i].firstedge->next = temp;
			}
		}
	}
	return Gc;
}
void CreatGraph(Graph *G) {
	ifstream file("Graph.txt");
	file >> G->n;
	file >> G->e;
	for (int i = 0; i < G->n; ++i) { //初始化
		for (int j = 0; j < G->n; ++j) {
			G->edge[i][j] = inf;
		}
	}
	for (int i = 0; i < G->n; ++i) { //对角线置1
		G->edge[i][i] = 0;
	}
	for (int i = 0; i < G->n; ++i) {
		file >> G->vertex[i];
	}
	for (int i = 0; i < G->e; i++) {
		int a, b, weight;
		file >> a >> b >> weight;
		G->edge[a][b] = weight;
	}
}
int selectmin(Graph* G, int d[], bool s[]) { //V-s中找到w使d[w]最小
	int temp = inf;
	int w = 0;
	for (int i = 0; i < G->n; i++) {
		if (!s[i] && d[i] < temp) {
			temp = d[i];
			w = i;
		}
	}
	return w;
}
//Dijkstra算法
void Dijkstra(Graph *G, int start, int d[], int p[], bool s[]) {
	for (int i = 0; i < G->n; ++i) {
		d[i] = G->edge[start][i]; //初始化d
		s[i] = false;
		p[i] = start;
	}
	s[start] = true;
	for (int i = 0; i < G->n - 1; ++i) {
		int w = selectmin(G, d, s);
		s[w] = true;
		for (int v = 0; v < G->n; ++v) {
			if (!s[v]) {
				int sum = d[w] + G->edge[w][v];
				if (sum < d[v]) {
					d[v] = sum;
					p[v] = w;
				}
			}
		}
	}
}
//Dijkstra算法堆优化
void Dijkstra_heap(AdjGraph *A, int start, int d[], int p[], bool s[]) {
	heap heap;
	InitHeap(heap);
	for (int i = 0; i < A->n; ++i) {
		d[i] = inf;
		s[i] = false;
		p[i] = start;
	}
	d[start] = 0;
	ElemType temp;
	temp.num = start;
	temp.weight = d[start];
	HeapInsert(heap, temp);
	while (!isHeapEmpty(heap)) {
		temp = HeapDeleteMin(heap);
		int v = temp.num;//当前点
		if (s[v]) continue;
		s[v] = true;
		EdgeNode* ptr;
		for (ptr = A->vexlist[v].firstedge; ptr != NULL; ptr = ptr->next) {
			if (d[ptr->adjvex] > d[v] + ptr->cost) {
				d[ptr->adjvex] = d[v] + ptr->cost;
				temp.num = ptr->adjvex;
				temp.weight = d[ptr->adjvex];
				p[ptr->adjvex] = v;
				HeapInsert(heap, temp);
			}
		}
	}
}
//Floyd算法
void Floyd(int d[][Numvertices], Graph* G, int p[][Numvertices]) {
	for (int i = 0; i < G->n; ++i) {
		for (int j = 0; j < G->n; ++j) {
			d[i][j] = G->edge[i][j];
			p[i][j] = -1;//p记录中间节点
		}
	}
	for (int k = 0; k < G->n; k++) {
		for (int i = 0; i < G->n; ++i) {
			for (int j = 0; j < G->n; j++) {
				if (d[i][k] + d[k][j] < d[i][j]) {
					d[i][j] = d[i][k] + d[k][j];
					p[i][j] = k;
				}
			}
		}
	}
}
//打印路径算法
void printroad(Graph* G, int start, int d[], int p[]) {
	for (int i = 0; i < G->n; ++i) {
		cout << start << "->" << i << ":" << endl;
		int temp = i;//记录路径节点
		int r[Numvertices];//保存路径节点
		int j = 0;
		if (d[i] == inf) {
			cout << "无路径！" << endl;
			cout << endl;
		}
		else if (i == start) {
			cout << "路径";
			cout << start << "->" << start << endl;
			cout << "距离：" << endl;
			cout << 0 << endl;
			cout << endl;
		}
		else {
			while (temp != start) {
				r[j++] = temp;
				temp = p[temp];
			}
			r[j++] = start;
			cout << "路径：";
			while (j--) {
				cout << r[j];
				if (j != 0)
					cout << "->";
			}
			cout << endl;
			cout << "距离：" << d[i] << endl;
			cout << endl;
		}
	}
}
void printroad_A(AdjGraph* G, int start, int d[], int p[]) {
	for (int i = 0; i < G->n; ++i) {
		cout << start << "->" << i << ":" << endl;
		int temp = i;//记录路径节点
		int r[Numvertices];//保存路径节点
		int j = 0;
		if (d[i] == inf) {
			cout << "无路径！" << endl;
			cout << endl;
		}
		else if (i == start) {
			cout << "路径";
			cout << start << "->" << start << endl;
			cout << "距离：" << endl;
			cout << 0 << endl;
			cout << endl;
		}
		else {
			while (temp != start) {
				r[j++] = temp;
				temp = p[temp];
			}
			r[j++] = start;
			cout << "路径：";
			while (j--) {
				cout << r[j];
				if (j != 0)
					cout << "->";
			}
			cout << endl;
			cout << "距离：" << d[i] << endl;
			cout << endl;
		}
	}
}
//Dijkstra算法相关操作
void ManageDijkstra(int mode) {
	Graph *G = new Graph;
	CreatGraph(G);
	AdjGraph *A = ConverttoM(G);
	int d[Numvertices];//源点0到顶点i的当前最短路径长度
	int p[Numvertices];//最短路径最后经过的点
	bool s[Numvertices];
	int start;
	cout << "请输入源点:" << endl;
	cin >> start;
	if (mode == 1) {
		Dijkstra(G, start, d, p, s);
		printroad(G, start, d, p);
	}
	else {
		Dijkstra_heap(A, start, d, p, s);
		printroad_A(A, start, d, p);
		//实验比较时间
		const int Times = 100000;
		clock_t _start, _stop;
		int m = Times;
		_start = clock();
		while (m--) {
			Dijkstra(G, start, d, p, s);
		}
		_stop = clock();
		double duration1 = (double)(_stop - _start) / CLK_TCK;
		m = Times;
		_start = clock();
		while (m--) {
			Dijkstra_heap(A, start, d, p, s);
		}
		_stop = clock();
		double duration2 = (double)(_stop - _start) / CLK_TCK;
		cout << "原始Dijkstra算法运行" << Times << "次的时间为：" << endl;
		cout << duration1 << endl;
		cout << "堆优化Dijkstra算法运行" << Times << "次的时间为：" << endl;
		cout << duration2 << endl;
	}

}
//最短路径矩阵得到任意两点路径(递归)
void printpath(int p[][Numvertices], int i , int j) {
	int k = p[i][j];
	if (k != -1) {
		printpath(p, i, k);
		cout << k << "->";
		printpath(p, k, j);
	}
}
//输出问题2的Floyd算法,输出所有
void PrintAns2Floyd(Graph* G, int d[][Numvertices], int p[][Numvertices]) {
	cout << "最短距离矩阵为：" << endl;
	for (int i = 0; i < G->n; i++) {
		for (int j = 0; j < G->n; j++) {
			cout << setw(6) << d[i][j];
		}
		cout << endl;
	}
	cout << "最短路径矩阵为(-1表示直接到达)：" << endl;
	for (int i = 0; i < G->n; i++) {
		for (int j = 0; j < G->n; j++) {
			cout << setw(4) << p[i][j] << " ";
		}
		cout << endl;
	}
	cout << "所有点的最短路径为:" << endl;
	for (int i = 0; i < G->n; ++i) {
		for (int j = 0; j < G->n; ++j) {
			if (i != j) {
				cout << i << "->" << j << ":" << endl;
				cout << "路径：";
				cout << i << "->";
				printpath(p, i, j);
				cout << j;
				cout << endl;
				cout << "距离：" << d[i][j] << endl;
				cout << endl;
			}
		}
	}
}
//输出问题3的Floyd算法,指定终点
void PrintAns3Floyd(Graph *G, int d[][Numvertices], int p[][Numvertices]) {
	cout << "请输入终点:" << endl;
	int c;
	cin >> c;
	for (int i = 0; i < G->n; ++i) {
		while (d[i][c] == inf) {
			cout << i << "->" << c << ":" << endl;
			cout << "无路径！" << endl;
			cout << endl;
			i++;
		}
		cout << i << "->" << c << ":" << endl;
		cout << "路径：";
		cout << i << "->";
		printpath(p, i, c);
		cout << c;
		cout << endl;
		cout << "距离：" << d[i][c] << endl;
		cout << endl;
	}
}
//输出问题4的Floyd算法,指定起点和终点
void PrintAns4Floyd(Graph *G, int d[][Numvertices], int p[][Numvertices]) {
	cout << "请分别输入两点:" << endl;
	int u, v;
	cin >> u >> v;
	if (d[u][v] == inf) {
		cout << u << "->" << v << ":" << endl;
		cout << "无路径！" << endl;
	}
	else {
		cout << u << "->" << v << ":" << endl;
		cout << "路径：";
		cout << u << "->";
		printpath(p, u, v);
		cout << v;
		cout << endl;
		cout << "距离：" << d[u][v] << endl;
		cout << endl;
	}
	if (d[v][u] == inf) {
		cout << v << "->" << u << ":" << endl;
		cout << "无路径！" << endl;
		return;
	}
	else {
		cout << v << "->" << u << ":" << endl;
		cout << "路径：";
		cout << v << "->";
		printpath(p, v, u);
		cout << u;
		cout << endl;
		cout << "距离：" << d[v][u] << endl;
		cout << endl;
	}
}
//Floyd算法相关操作
void ManageFloyd(int mode) {
	Graph *G = new Graph;
	CreatGraph(G);
	int d[Numvertices][Numvertices];//最短距离矩阵
	int p[Numvertices][Numvertices];//最短路径矩阵
	Floyd(d, G, p);
	if (mode == 2)
		PrintAns2Floyd(G, d, p);
	else if (mode == 3)
		PrintAns3Floyd(G, d, p);
	else
		PrintAns4Floyd(G, d, p);
}
//Warshall算法
void Warshall() {
	Graph *G = new Graph;
	CreatGraph(G);
	int nn[Numvertices][Numvertices];
	//邻接矩阵初始处理
	for (int i = 0; i < G->n; ++i) {
		for (int j = 0; j < G->n; j++) {
			if (G->edge[i][j] == inf)
				nn[i][j] = 0;
			else
				nn[i][j] = 1;
		}
	}
	for (int k = 0; k < G->n; k++) {
		for (int i = 0; i < G->n; ++i) {
			for (int j = 0; j < G->n; j++) {
				if (nn[i][k] && nn[k][j]) {
					nn[i][j] = 1;
				}
			}
		}
	}
	cout << "可达矩阵为：" << endl;
	for (int i = 0; i < G->n; ++i) {
		for (int j = 0; j < G->n; ++j) {
			cout << nn[i][j] << " ";
		}
		cout << endl;
	}
}
void test() {
	while (1) {
		cout << "1、单源最短路径的Dijkstra算法" << endl;
		cout << "2、全局最短路径的Floyd-Warshall算法" << endl;
		cout << "3、指定汇点的最短路径" << endl;
		cout << "4、指定一对点的对间最短路径" << endl;
		cout << "5、Warshall算法求可达矩阵" << endl;
		cout << "6、堆结构实现Dijkstra算法,实验比较时间" << endl;
		int mode;
		cout << "请输入模式：" << endl;
		cin >> mode;
		switch (mode)
		{
		case 1:
			ManageDijkstra(1);
			break;
		case 2:
			ManageFloyd(2);
			break;
		case 3:
			ManageFloyd(3);
			break;
		case 4:
			ManageFloyd(4);
			break;
		case 5:
			Warshall();
			break;
		case 6:
			ManageDijkstra(2);
		}

	}
}
int main(void) {
	test();
	return 0;
}
