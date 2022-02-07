#include <iostream>
#include <vector>
using namespace std;

#define Max 1000
#define datatype char
#define ElemType BTREE
//输出
int x;
char pre[Max];
//二叉树宽度递归
int MAX = 0;
int count[100];

typedef struct BT_node *BTREE;
struct BT_node{
    BTREE lchild;
    BTREE rchild;
    datatype data;
};
typedef struct stack{
    ElemType d[Max];
    int top;
}Stack;

typedef struct queue{
    int front;
    int rear;
    ElemType d[Max];
}Queue;

//栈操作
void InitStack(Stack &S);
bool StackEmpty(Stack S);
void SPush(Stack &S,ElemType x);
void SPop(Stack &S,ElemType &x);
void STop(Stack S,ElemType &x);

//队列操作
void InitQueue(Queue &Q);
bool isEmpty(Queue Q);
void EnQueue(Queue &Q,ElemType x);
void DeQueue(Queue &Q,ElemType &x);

//二叉树操作(1 2题)
void CreatBTre(BTREE &T);//先序序列保存二叉树
void PrintBT(BTREE BT);//打印二叉树
void PreOrderre(BTREE T);//先序遍历，递归
void InOrderre(BTREE T);//中序遍历，递归
void PostOrderre(BTREE T);//后序遍历，递归
void PreOrder(BTREE T);//先序遍历，非递归
void InOrder(BTREE T);//中序遍历，非递归
void PostOrder(BTREE T);//后序遍历，非递归
void LevelOrder(BTREE T);//层次遍历
void Visit(BTREE T);//访问节点
//二叉树算法(3 4题)
bool CheckTree(BTREE T);//判断是否为完全二叉树
int TreeMaxWidthre(BTREE T);//计算二叉树宽度,递归
int TreeMaxWidth(BTREE T);//计算二叉树宽度，非递归

//
void InitStack(Stack &S){
    S.top = -1;
}
//栈功能
bool StackEmpty(Stack S){
    if(S.top==-1)
        return true;
    else
        return false;
}
void SPush(Stack &S,ElemType x){
    if(S.top==Max-1)
        return;
    S.d[++S.top] = x;
}
void SPop(Stack &S,ElemType &x){
    if(S.top==-1)
        return;
    x = S.d[S.top--];
}
void STop(Stack S,ElemType &x){
    if(S.top==-1)
        return;
    x = S.d[S.top];
}
//队列功能
void InitQueue(Queue &Q){
    Q.rear = Q.front = 0;
    
}
bool isEmpty(Queue Q){
    if(Q.front==Q.rear)
        return true;
    else
        return false;
}
void EnQueue(Queue &Q,ElemType x){
    if((Q.rear+1)%Max==Q.front)
        return;
    Q.d[Q.rear] = x;
    Q.rear = (Q.rear+1)%Max;
}
void DeQueue(Queue &Q,ElemType &x){
    if(Q.rear==Q.front)
        return;
    x = Q.d[Q.front];
    Q.front = (Q.front+1)%Max;
}
//树操作
//先序序列建立二叉树、递归
void CreatBTre(BTREE &T){
    datatype ch;
    cin>>ch;

    if(ch=='#')T=NULL;
    else{
        T = new BT_node;
        T->data=ch;
        CreatBTre(T->lchild);
        CreatBTre(T->rchild);
    }
}
void printd(){
    cout<<pre[x];
    if(pre[x]=='#') return;
    cout<<"(";
    x++;
    printd();
    cout<<",";
    x++;
    printd();
    cout<<")";
}
void PrintBT(BTREE BT){
    Stack S;
    for(int i=0;i<Max;i++){
        pre[i] = ' ';
    }
    x = 0;
    InitStack(S);
    BTREE p = BT;
    while(p||!StackEmpty(S)){
        if(p){
            pre[x++]=p->data;
            SPush(S,p);
            p = p->lchild;
        }
        else{
            pre[x++]='#';
            SPop(S,p);
            p=p->rchild;
        }
    }
    pre[x++]='#';
    x=0;
    printd();
    cout<<endl;
}
void Visit(BTREE T){
    cout<<T->data<<' ';
}
void PreOrderre(BTREE T){
    if(T!=NULL){
        Visit(T);
        PreOrderre(T->lchild);
        PreOrderre(T->rchild);
    }
}
void InOrderre(BTREE T){
    if(T!=NULL){
        InOrderre(T->lchild);
        Visit(T);
        InOrderre(T->rchild);
    }
}
void PostOrderre(BTREE T){
    if(T!=NULL){
        PostOrderre(T->lchild);
        PostOrderre(T->rchild);
        Visit(T);
    }
}
void PreOrder(BTREE T){
    BTREE p = T;
    Stack S;
    InitStack(S);
    while(p||!StackEmpty(S)){
        if(p){
            Visit(p);
            SPush(S,p);
            p = p->lchild;
        }
        else{
            SPop(S,p);
            p = p->rchild;
        }
    }
}
void InOrder(BTREE T){
    BTREE p = T;
    Stack S;
    InitStack(S);
    while(p||!StackEmpty(S)){
        if(p){
            SPush(S,p);
            p = p->lchild;
        }
        else{
            SPop(S,p);
            Visit(p);
            p = p->rchild;
        }
    }
}
void PostOrder(BTREE T){
    Stack S;
    InitStack(S);
    BTREE p = T;
    BTREE tag = NULL;//记录是否从右子节点返回
    while(p||!StackEmpty(S)){
        if(p){
            SPush(S,p);
            p = p->lchild;
        }
        else{
            STop(S,p);
            if(p->rchild&&p->rchild!=tag)
                p = p->rchild;
            else{
                SPop(S,p);
                Visit(p);
                tag = p;
                p = NULL;//节点弹出，p指针重置
            }
        }
    }
}
void LevelOrder(BTREE T){
    Queue Q;
    InitQueue(Q);
    BTREE p;
    EnQueue(Q,T);
    while(!isEmpty(Q)){
        DeQueue(Q,p);
        Visit(p);
        if(p->lchild)
            EnQueue(Q,p->lchild);
        if(p->rchild)
            EnQueue(Q,p->rchild);
    }
}
bool CheckTree(BTREE T){
    Queue Q;
    InitQueue(Q);
    if(T==NULL)
        return true;
    EnQueue(Q,T);
    BTREE p;
    while(!isEmpty(Q)){
        DeQueue(Q,p);
        if(p->lchild&&p->rchild){
            EnQueue(Q,p->lchild);
            EnQueue(Q,p->rchild);
        }
        else if(p->rchild&&!p->lchild)
            return false;
        else{
            if(p->lchild&&!p->rchild)
                EnQueue(Q,p->lchild);
            while(!isEmpty(Q)){
                DeQueue(Q,p);
                if(p->lchild||p->rchild)
                    return false;
            }
        }
    }
    return true;
}
void find(BTREE T,int k)
{
    if(T==NULL)  return;
    count[k]++;
    if(MAX<count[k]) 
        MAX=count[k];
    find(T->lchild,k+1);
    find(T->rchild,k+1);
}
int TreeMaxWidthre(BTREE T){
    find(T,0);
    return MAX;
}
int TreeMaxWidth(BTREE T){
    BTREE p;
    int level[Max];//保存层次节点
    Queue Q;
    InitQueue(Q);
    EnQueue(Q,T);
    level[Q.rear] = 1;//根节点层次
    int max = 0;
    while(!isEmpty(Q)){
        DeQueue(Q,p);
        int k = level[Q.front];
        if(p->lchild){
            EnQueue(Q,p->lchild);
            level[Q.rear] = k+1;//新一层
        }
        if(p->rchild){
            EnQueue(Q,p->rchild);
            level[Q.rear] = k+1;//新一层
        }
        int i=0;
        k = 1;
        while(i<=Q.rear){
            int n = 0;
            while(i<=Q.rear&&level[i] == k){
                n++;
                i++;
            }
            k = level[i];
            if(n>max){
                max = n;
            }
        }
    }
    return max;
}
int main() {
    BTREE T;
    cout<<"input a tree:"<<endl;
    CreatBTre(T);
    cout<<"your tree is:"<<endl;
    PrintBT(T);
    cout<<"pre order(recurrence):"<<endl;
    PreOrderre(T);
    cout<<endl;
    cout<<"pre order:"<<endl;
    PreOrder(T);
    cout<<endl;
    cout<<"in order(recurrence):"<<endl;
    InOrderre(T);
    cout<<endl;
    cout<<"in order:"<<endl;
    InOrder(T);
    cout<<endl;
    cout<<"post order(recurrence):"<<endl;
    PostOrderre(T);
    cout<<endl;
    cout<<"post order:"<<endl;
    PostOrder(T);
    cout<<endl;
    cout<<"level order:"<<endl;
    LevelOrder(T);
    cout<<endl;
    cout<<endl;
    if(CheckTree(T))
        cout<<"it is a complete binary tree!"<<endl;
    else
        cout<<"it is NOT a complete binary tree!"<<endl;
    cout<<"the max wideth is:"<<endl;
    cout<<TreeMaxWidthre(T)<<endl;
    return 0;
}
