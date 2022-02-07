#include<iostream>
#include<fstream>
using namespace std;
const int Max = 100000;
typedef struct BSTNode *BSTree;
struct BSTNode{
	int key;
	BSTree lchild;
	BSTree rchild;
};
//BST的插入
int BST_insert(BSTree &T,int k){
	if(T==NULL){//第一次插入，创建根节点
		T = new BSTNode;
		T->key = k;
		T->lchild = NULL;
		T->rchild = NULL;
		return 1;//创建成功，返回1
	}
	else if(k==T->key)
		return 0;//存在相同关键字，插入失败
	else if(k<T->key)
		return BST_insert(T->lchild,k);
	else
		return BST_insert(T->rchild,k);

}
//BST的查找
BSTree BST_search(BSTree &T,int k,int &count){
	BSTree p = T;
	while(p){
		count++;
		if(k==p->key)
			return p;
		if(k>p->key)
			p = p->rchild;
		else
			p = p->lchild;
	}
	return p;//查找不到，返回空
}
//BST的删除
//该函数用于待删除节点既有左子树又有右子树的情况
//返回直接后继的关键字并删除直接后继
int deletemin(BSTree &T){
	int tmp;
	BSTree p;
	if(T->lchild==NULL){
		p = T;
		tmp = T->key;
		T = T->rchild;
		delete p;
		return tmp;	
	}//T就是最小
	else return deletemin(T->lchild);//最小结点一定在左子树上
}
void BST_delete(BSTree &T,int k){
	if(T!=NULL){
		if(k<T->key)
			BST_delete(T->lchild,k);
		else if(k>T->key)
			BST_delete(T->rchild,k);
		else//等于了
			if(T->rchild==NULL)//右子树为空
				T=T->lchild;
			else if(T->lchild==NULL)//左子树为空
				T=T->rchild;
			else
				T->key = deletemin(T->rchild);
	}
}
//BST的排序
void visit(BSTree T){
	cout<<T->key<<" ";
}
//中序遍历
void BST_sort(BSTree &T){
	if(T!=NULL){
		BST_sort(T->lchild);
		visit(T);
		BST_sort(T->rchild);
	}
}
//BST的建立
void BST_creat(BSTree &T,int data[],int n){
	T=NULL;
	for(int i = 0;i<n;i++){
		BST_insert(T,data[i]);
	}
}
// void test01(){
// 	BSTree T;
// 	ifstream infile; 
//     infile.open("inputdata1.txt");
//     int in; //临时存放单个数据
//     int data[Max];
//     int i = 0;//记录数据数量
//     while(infile>>in){
//     	data[i++] = in;
//   	}	
//   	BST_creat(T,data,i);
//   	int k;
//   	cout<<"Insert a number:"<<endl;
//   	cin>>k;
//   	BST_insert(T,k);
//   	BST_sort(T);
//   	cout<<endl;
//   	cout<<"Delete a number:"<<endl;
//   	cin>>k;
//   	BST_delete(T,k);
//   	BST_sort(T);
// }
// void test02(){
// 	BSTree T;
// 	ifstream infile; 
//     infile.open("inputdata1.txt");
//     int in; //临时存放单个数据
//     int data[Max];
//     int i = 0;//记录数据数量
//     while(infile>>in){
//     	data[i++] = in;
//   	}	
//   	BST_creat(T,data,i);
//   	int k;
//   	cout<<"Search a number:"<<endl;
//   	cin>>k;
//   	BSTree p = BST_search(T,k);
//   	cout<<p->key;
// }
void TimesOfSearch(BSTree &T,int data[],int i){
  	BST_creat(T,data,i);
  	int counts = 0;
  	int j = 0;//查找成功的数的个数
  	int countf = 0;
  	int k = 0;//查找失败的数的个数
  	for (int i = 0; i <= 2048; ++i){
  		if(i%2){//这是能查找成功的
  			j++;
  			BST_search(T,i,counts);
  		}
  		else{//这是不能查找成功的
  			k++;
  			BST_search(T,i,countf);
  		}
  	}
  	double ASLs = (double)counts/j;
  	double ASLf = (double)countf/k;
  	cout<<"查找成功的平均查找长度为："<<ASLs<<endl;
  	cout<<"查找失败的平均查找长度为："<<ASLf<<endl;
}
int main(){
	//test01();
	//test02();
	BSTree T;
	ifstream infile; 
    infile.open("inputdata1.txt");
    int in; //临时存放单个数据
    int data[Max];
    int i = 0;//记录数据数量
    while(infile>>in){
    	data[i++] = in;
  	}
  	infile.close();	
	TimesOfSearch(T,data,i);

	BSTree S;
	ifstream infile2; 
    infile2.open("inputdata2.txt");
    int in2; //临时存放单个数据
    int data2[Max];
    int j = 0;//记录数据数量
    while(infile2>>in2){
    	data2[j++] = in2;
  	}
  	infile.close();
  	TimesOfSearch(S,data2,j);	
  	BST_sort(S);
}