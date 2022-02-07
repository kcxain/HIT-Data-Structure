#include<iostream>
using namespace std;
int main(){
	freopen("test.in","r",stdin);
	string s;
	cin>>s;
	int ans = 0;
	for(int i = 0;i<(int)s.length()-2;i++)
		for(int j = i+1;j<(int)s.length()-1;j++)
			for(int k = j+1;k<(int)s.length();k++)
				if(s[i]=='Q'&&s[j]=='A'&&s[k]=='Q')
					ans++;
	cout<<ans<<endl;
	return 0;
}