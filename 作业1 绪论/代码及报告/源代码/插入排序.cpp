//直接选择排序，升序
#include<iostream>

using namespace std;
int main()
{
    int array[1000];
    /*读入数据*/
    int n;
    int temp;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> array[i];
    /*排序*/
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && array[j - 1] > array[j]; --j) {
            temp = array[j];
            array[j] = array[j - 1];
            array[j - 1] = temp;
        }
    }
    /*输出数据*/
    for (int i = 0; i < n; i++)
    {
        cout << array[i] << " ";
    }
    cout << '\n';
    return 0;
}
