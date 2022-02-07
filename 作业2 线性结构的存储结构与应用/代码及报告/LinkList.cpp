#include <bits/stdc++.h>
using namespace std;

typedef struct LNode *LIST;
typedef int ElemType;
struct LNode{
    ElemType data;
    LIST next;
};
typedef LIST Position;

LIST Input();                        //输入数据
void Delete(int p, LIST L);          //删除给定元素
void DeleteSame(LIST L);             //对于已排好序的线性表，删除所有重复元素的算法
LIST reverse(LIST L);                     //将线性表逆置
LIST DataMove(int k, LIST L);             //线性表循环左移/右移 k 位
LIST Merge(LIST L1, LIST L2);             //合并两个非递减的线性表
void Print(LIST L);                       //打印线性表
void Attach(int data, LIST &Rear);  //尾插
LIST Input()
{
    LIST p, Rear,t;
    int N;
    cout << "有多少数据？" << endl;
    cin >> N;
    cout << "请输入数据：" << endl;
    p = new LNode;
    p->next = NULL;
    Rear = p;
    for (int i = 0; i < N; ++i)
    {
        int data;
        cin >> data;
        Attach(data, Rear);
    }
    t = p;
    p = p->next;
    delete t;
    return p;
}
void Delete(int p, LIST L)
{
    Position tmp, pre;
    int cnt = 0;
    pre = L;
    while (pre && cnt < p -2)
    {
        pre = pre->next;
        cnt++;
    }
    if (pre == NULL || cnt != p -2 || pre->next == NULL)
    {
        cout << "参数错误!" << endl;
    }
    else
    {
        tmp = pre->next;
        pre->next = tmp->next;
        delete tmp;
    }
}
void Print(LIST L)
{
    LIST p = L;
    while (p)
    {
        cout << p->data << ' ';
        p = p->next;
    }
}
void DeleteSame(LIST L)
{
    LIST cur = L;
    while (cur->next)
    {
        if (cur->data == cur->next->data)
        {
            cur->next = cur->next->next;
        }
        else
        {
            cur = cur->next;
        }
    }
}
LIST reverse(LIST L)
{
    LIST p;
    p = NULL;
    while(L != NULL){
        LNode *tmp = L->next;	
        L->next = p;
        p = L;
        L = tmp;
    }
    return p;
}
LIST DataMove(int k, LIST L)
{
    LIST tail = L;
    int len =1;
    while(tail->next){
        tail = tail->next;
        len++;
    }
    tail ->next =L;
    k = k%len;
    for(int i = 0;i<len-k;i++){
        tail = tail->next;
    }
    L=tail->next;
    tail->next =NULL;
    return L;
}
LIST Merge(LIST L1, LIST L2)
{
    if(L1==NULL)
        return L2;
    else if(L2==NULL)
        return L1;
    else if(L1->data < L2->data){
            L1->next = Merge(L1->next, L2);
            return L1;
        }
        else{
            L2->next = Merge(L2->next, L1);
            return L2;
        }
       
}
void Attach(int data, LIST &Rear){
    LIST p = new LNode;
    p->data = data;
    p->next = NULL;
    Rear->next = p;
    Rear = p;
}
int main()
{
    while (1)
    {
        cout << "1、删除给定元素" << endl;
        cout << "2、删除排好序的线性表中的重复数据" << endl;
        cout << "3、将线性表逆置" << endl;
        cout << "4、将线性表循环右移K位" << endl;
        cout << "5、合并两个线性表" << endl;
        cout << "6、退出" << endl;
        cout << "请输入对应功能的序号：" << endl;
        int n;
        cin >> n;
        if(n==6)
            return 0;
        LIST L = Input();
        if(n==5){
            LIST L2 = Input();
            cout << "合并后的线性表为：" << endl;
            Print(Merge(L, L2));
            getchar();
            getchar();
        }
        switch (n)
        {
        case 1:
            int p;
            cout << "要删除的元素位置为：" << endl;
            cin >> p;
            Delete(p, L);
            cout << "删除后的线性表为：" << endl;
            Print(L);
            getchar();
            getchar();
            break;
        case 2:
            
            DeleteSame(L);
            cout << "删除后的线性表为：" << endl;
            Print(L);
            getchar();
            getchar();
            break;
        case 3:
            cout << "逆置后的线性表为：" << endl;
            Print(reverse(L));
            getchar();
            getchar();
            break;
        case 4:
            int k;
            cout << "移动多少位？" << endl;
            cin >> k;
            cout << "移动后的线性表为：" << endl;
            Print(DataMove(k, L));
            getchar();
            getchar();
            break;
        case 5:
            return 0;
        }
    }
}
