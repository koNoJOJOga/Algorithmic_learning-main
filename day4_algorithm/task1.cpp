#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

struct E
{
	int x, y, t;
}a[100002];

int f[1002], n, m;

int cmp(const E &a, const E &b)
{
    return a.t < b.t;
}
int find(int x)
{
    return f[x] == x ? x : (f[x]=find(f[x]));
}
int getin()
{
	int x = 0;
    char ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
	return x;
}
int main()
{
	n = getin(), m = getin();
	if(n == 1)
    {
        cout<<0;
        return 0;
    }
	for(int i = 1; i <= m; i ++ ) a[i].x = getin(), a[i].y = getin(), a[i].t = getin();
	sort(a+1, a+m+1, cmp);
	for(int i = 1; i <= n; i ++ ) f[i] = i; // 初始化
	for(int i = 1; i <= m; i ++ )
	{
		int fx = find(a[i].x), fy = find(a[i].y);
		if(fx != fy) f[fx] = fy, n --;
		if(n == 1)
        {
            cout << a[i].t;
            return 0;
        }
	}
	cout << -1 << endl;
    return 0;
}