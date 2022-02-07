#include<iostream>
using namespace std;

#define EdgeData int

//邻接矩阵
#define VertexData char
#define NumVertices 100

typedef struct{
	VertexData vertex[NumVertices];//顶点表
	EdgeData edge[NumVertices][NumVertices];//边表
	int n;//顶点数
	int e;//边数
}MTGraph;
//邻接表
typedef struct node{//边表
	int adjvex;//邻接点下标
	EdgeData cost;//权值
	struct node*next;//下一边指针
}EdgeNode;
typedef struct{//顶点表
	VertexData vertex;//顶点信息
	EdgeNode *firstedge;//边链表头指针
}VertexNode;
typedef struct{//邻接表
	VertexNode vexlist[NumVertices];
	int n;
	int e;
}AdjGraph;

/*---------------------栈操作-------------------*/
typedef struct stack{
	int d[NumVertices];
	int top;
}Stack;
void InitStack(Stack &S);
bool StackEmpty(Stack S);
void SPush(Stack &S,int x);
void SPop(Stack &S,int &x);
void STop(Stack S,int &x);
void InitStack(Stack &S){
    S.top = -1;
}

bool StackEmpty(Stack S){
    if(S.top==-1)
        return true;
    else
        return false;
}
void SPush(Stack &S,int x){
    if(S.top==NumVertices-1)
        return;
    S.d[++S.top] = x;
}
void SPop(Stack &S,int &x){
    if(S.top==-1)
        return;
    x = S.d[S.top--];
}
void STop(Stack S,int &x){
    if(S.top==-1)
        return;
    x = S.d[S.top];
}
/*----------------------------------------*/
/*---------------------队列操作-------------------*/
typedef struct queue{
    int front;
    int rear;
    int d[NumVertices];
}Queue;
void InitQueue(Queue &Q);
bool isEmpty(Queue Q);
void EnQueue(Queue &Q,int x);
void DeQueue(Queue &Q,int &x);
void InitQueue(Queue &Q){
    Q.rear = Q.front = 0;
    
}
bool isEmpty(Queue Q){
    if(Q.front==Q.rear)
        return true;
    else
        return false;
}
void EnQueue(Queue &Q,int x){
    if((Q.rear+1)%NumVertices==Q.front)
        return;
    Q.d[Q.rear] = x;
    Q.rear = (Q.rear+1)%NumVertices;
}
void DeQueue(Queue &Q,int &x){
    if(Q.rear==Q.front)
        return;
    x = Q.d[Q.front];
    Q.front = (Q.front+1)%NumVertices;
}
/*----------------------------------------*/

//创建邻接矩阵
void CreatMGragh(MTGraph* G){
	cout<<"请输入顶点数："<<endl;
	cin>>G->n;
	cout<<"请输入边数："<<endl;
	cin>>G->e;
	cout<<"请输入顶点编号："<<endl;
	for(int i = 0;i<G->n;i++)
		cin>>G->vertex[i];
	for (int i = 0; i < G->n; ++i)
		for(int j = 0; j < G->n; ++j)
			G->edge[i][j] = 0;//初始化
	cout<<"请输入边和权值："<<endl;
	for(int k = 0;k<G->e;k++){
		int i,j,w;
		cin>>i>>j>>w;
		G->edge[i][j] = w;//w为权值
	}
}
//创建邻接表
void CreateGraph(AdjGraph *G){
	cout<<"请输入顶点数："<<endl;
	cin>>G->n;
	cout<<"请输入边数："<<endl;
	cin>>G->e;
	cout<<"请输入顶点编号："<<endl;
	for (int i = 0; i < G->n; ++i){
		cin>>G->vexlist[i].vertex;
		G->vexlist[i].firstedge = NULL;
	}
	int a,b,c;
	EdgeNode* temp;
	cout<<"请输入边和权值："<<endl;
	for (int i = 0; i < G->e; ++i){
		cin>>a>>b>>c;
		temp = G->vexlist[a].firstedge;//尾插
		G->vexlist[a].firstedge = new EdgeNode;
		G->vexlist[a].firstedge->adjvex = b;
		G->vexlist[a].firstedge->cost = c;
		G->vexlist[a].firstedge->next = temp;
	}
}
//邻接矩阵转邻接表
AdjGraph* ConverttoM(MTGraph *G){
	AdjGraph* Gc = new AdjGraph;
	Gc->e = G->e;
	Gc->n = G->n;
	for (int i = 0; i < Gc->n; ++i){
		Gc->vexlist[i].vertex = G->vertex[i];
		Gc->vexlist[i].firstedge = NULL;
	}
	EdgeNode* temp;
	for (int i = 0; i < G->n; ++i){
		for (int j = 0; j < G->n; ++j){
			if(G->edge[i][j]){
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
//邻接表转邻接矩阵
MTGraph* ConverttoA(AdjGraph* G){
	MTGraph* Gc = new MTGraph;
	Gc->e = G->e;
	Gc->n = G->n;
	for (int i = 0; i < Gc->n; ++i){
		Gc->vertex[i] = G->vexlist[i].vertex;
		EdgeNode* temp = G->vexlist[i].firstedge;
		while(temp){
			Gc->edge[i][temp->adjvex] = temp->cost;
			temp = temp->next;
		}
	}
	return Gc;
}
//搜索
int dfn[NumVertices];//编号
bool visited[NumVertices];//访问标记
void visitm(MTGraph *G,int i){//访问矩阵的节点
	cout<<G->vertex[i]<<" ";
}
void visita(AdjGraph *G,int i){//访问表的节点
	cout<<G->vexlist[i].vertex<<" ";
}
//邻接矩阵DFSre
void DFSMXre(MTGraph *G, int i, int &count){
	visitm(G,i);
	visited[i] = true;
	dfn[i] = count++;//得序号
	for (int j = 0; j < G->n; ++j){
		if(G->edge[i][j] && (!visited[j])){
			DFSMXre(G,j,count);
		}
	}
}
void DFSMre(MTGraph *G){
	int count = 1;
	for (int i = 0; i < G->n; ++i){
		visited[i] = false;
	}
	for (int i = 0; i < G->n; ++i){
		if(!visited[i])
			DFSMXre(G,i,count);
	}
}
//邻接表DFSre
void DFSAXre(AdjGraph* G,int i ,int &count){
	EdgeNode* p;
	visita(G,i);
	visited[i] = true;
	dfn[i] = count++;
	p = G->vexlist[i].firstedge;
	while(p){
		if(!visited[p->adjvex])
			DFSAXre(G,p->adjvex,count);
		p= p->next;
	}
}
void DFSAre(AdjGraph* G){
	int count = 1;
	for (int i = 0; i < G->n; ++i){
		visited[i] = false;
	}
	for (int i = 0; i < G->n; ++i){
		if(!visited[i])
			DFSAXre(G,i,count);
	}
}

//邻接矩阵DFS
void DFSMX(MTGraph *G,int i,int &count){
	Stack S;
	InitStack(S);
	SPush(S,i);
	visitm(G,i);
	visited[i] = true;
	dfn[i] = count++;
	for(int j = 0;;){
		if(j==G->n){
			if(StackEmpty(S))
				break;
			SPop(S,i);
			j = 0;
		}
		if(G->edge[i][j]&&!visited[j]){
			visited[j] = true;
			visitm(G,j);
			dfn[j] = count++;
			SPush(S,j);
			i = j;//从j开始
			j = -1;
		}
		++j;
	}
}
void DFSM(MTGraph *G){
	int count = 1;
	for (int i = 0; i < G->n; ++i){
		visited[i] = false;
	}
	for (int i = 0; i < G->n; ++i){
		if(!visited[i])
			DFSMX(G,i,count);
	}
}
//邻接表DFS
void DFSAX(AdjGraph* G,int i,int &count){
	Stack S;
	InitStack(S);
	SPush(S,i);
	visita(G,i);
	visited[i] = true;
	dfn[i] = count++;
	while(1){
		EdgeNode *p = G->vexlist[i].firstedge;
		while(p){
			if(!visited[p->adjvex]){
				SPush(S,p->adjvex);
				visita(G,p->adjvex);
				visited[p->adjvex] = true;
				dfn[p->adjvex] = count++;
				if(G->vexlist[p->adjvex].firstedge)//下一个顶点
					p = G->vexlist[p->adjvex].firstedge;
				else
					p = p->next;
			}
			else
				p = p->next;
		}
		if(StackEmpty(S))
			break;
		SPop(S,i);
	}
}
void DFSA(AdjGraph *G){
	int count = 1;
	for (int i = 0; i < G->n; ++i){
		visited[i] = false;
	}
	for (int i = 0; i < G->n; ++i){
		if(!visited[i])
			DFSAX(G,i,count);
	}
}
//BFS
int bfn[NumVertices];
//邻接矩阵BFS
void BFSMX(MTGraph *G,int i, int &count){
	Queue Q;
	InitQueue(Q);
	visited[i] = true;
	visitm(G,i);
	bfn[i] = count++;
	EnQueue(Q,i);
	while(!isEmpty(Q)){
		int i;
		DeQueue(Q,i);
		for(int j = 0;j<G->n;j++){
			if(G->edge[i][j]&&!visited[j]){
				visitm(G,j);//访问j
				visited[j] = true;
				bfn[j] = count++;
				EnQueue(Q,j);//访问后入队
			}
		}
	}
}
void BFSM(MTGraph *G){
	int count = 1;
	for (int i = 0; i < G->n; ++i){
		visited[i] = false;
	}
	for (int i = 0; i < G->n; ++i){
		if(!visited[i]){
			BFSMX(G,i,count);
		}
	}

} 
//邻接表BFS
void BFSAX(AdjGraph *G,int i,int &count){
	EdgeNode *p;
	Queue Q;
	InitQueue(Q);
	visita(G,i);
	visited[i] = true;
	bfn[i] = count++;
	EnQueue(Q,i);
	while(!isEmpty(Q)){
		int i;
		DeQueue(Q,i);
		p = G->vexlist[i].firstedge;
		while(p){
			if(!visited[p->adjvex]){
				visita(G,p->adjvex);
				visited[p->adjvex] = true;
				bfn[p->adjvex] = count++;
				EnQueue(Q,p->adjvex);
			}
			p = p->next;
		}
	}

}
void BFSA(AdjGraph *G){
	int count = 1;
	for (int i = 0; i < G->n; ++i){
		visited[i] = false;
	}
	for (int i = 0; i < G->n; ++i){
		if(!visited[i]){
			BFSAX(G,i,count);
		}
	}
}
void printm(MTGraph *G){
	for (int i = 0; i < G->n; ++i){
		for (int j = 0; j < G->n; ++j){
			cout<<G->edge[i][j];
			cout<<" ";
		}
		cout<<endl;
	}
}
void printa(AdjGraph *A){
	EdgeNode *p;
	for (int i = 0; i < A->n; ++i){
		cout<<i<<" "<<A->vexlist[i].vertex<<":";
		p = A->vexlist[i].firstedge;
		while(p){
			cout<<i<<"->"<<p->adjvex<<" ";
			p = p->next;
		}
		cout<<endl;
	}
}
void cald(AdjGraph* A,int in[],int out[]){
	EdgeNode *p;
	for (int i = 0; i < A->n; ++i){
		p = A->vexlist[i].firstedge;
		while(p){
			out[i]++;
			in[p->adjvex]++;
			p = p->next;
		}
	}
}
int main(){
	cout<<"请选择模式："<<endl;
	cout<<"1. 用邻接矩阵建图"<<endl;
	cout<<"2. 用邻接表建图"<<endl;
	int mode;
	cin>>mode;
	MTGraph* G = new MTGraph;
	AdjGraph* A = new AdjGraph;
	int in[NumVertices] = {0};
	int out[NumVertices] = {0};
	switch(mode)
	{
		case 1:
		CreatMGragh(G);
		cout<<"邻接矩阵为："<<endl;
		printm(G);
		cout<<"转换为邻接表为："<<endl;
		A = ConverttoM(G);
		printa(A);
		cout<<"广度优先搜索序列为："<<endl;
		BFSM(G);
		cout<<endl;
		cout<<"广度优先编号为："<<endl;
		for (int i = 0; i < G->n; ++i){
			cout<<bfn[i]<<" ";
		}
		cout<<endl;
		cout<<"深度优先搜索序列为："<<endl;
		DFSMre(G);
		cout<<endl;
		cout<<"深度优先编号为："<<endl;
		for (int i = 0; i < G->n; ++i){
			cout<<dfn[i]<<" ";
		}
		cout<<endl;
		break;
		case 2:
		CreateGraph(A);
		cout<<"邻接表为："<<endl;
		printa(A);
		cout<<"转换为邻接矩阵为："<<endl;
		G = ConverttoA(A);
		printm(G);
		cout<<"广度优先搜索序列为："<<endl;
		BFSA(A);
		cout<<endl;
		cout<<"广度优先编号为："<<endl;
		for (int i = 0; i < A->n; ++i){
			cout<<bfn[i]<<" ";
		}
		cout<<endl;
		cout<<"深度优先搜索序列为："<<endl;
		DFSAre(A);
		cout<<endl;
		cout<<"深度优先编号为："<<endl;
		for (int i = 0; i < A->n; ++i){
			cout<<dfn[i]<<" ";
		}
		cout<<endl;
		cald(A,in,out);
		cout<<"各顶点入度为："<<endl;
		for (int i = 0; i < A->n; ++i){
			cout<<in[i]<<" ";
		}
		cout<<endl;
		cout<<"各顶点出度为："<<endl;
		for (int i = 0; i < A->n; ++i){
			cout<<out[i]<<" ";
		}
		cout<<endl;
		cout<<"各顶点度为："<<endl;
		for (int i = 0; i < A->n; ++i){
			cout<<in[i]+out[i]<<" ";
		}
		cout<<endl;
		break;
	}
}