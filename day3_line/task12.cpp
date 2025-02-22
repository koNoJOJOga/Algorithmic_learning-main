#include<iostream>
using namespace std;
int n;
int a[130][130];//存储题目中的矩阵
int sum[130][130];
int qz[130][130];//qz[i][j]指的是第i行到j的前缀和
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            qz[i][j]=qz[i][j-1]+a[i][j];//求前缀和
            sum[i][j]=qz[i][j]+sum[i-1][j];//计算sum
        }
    }
    int mx=-99999999;//存储答案
    for(int x1=1;x1<=n;x1++){
    	for(int y1=1;y1<=n;y1++){
    		for(int x2=1;x2<=n;x2++){
    			for(int y2=1;y2<=n;y2++){
    				if(x2<x1 || y2<y1) continue;//如果左上角比右下角还要大，就不用求了，下一个
    				mx=max(mx,sum[x2][y2]+sum[x1-1][y1-1]-sum[x2][y1-1]-sum[x1-1][y2]);//求最大值
    			}
    		}
    	}
    }
    cout<<mx;//输出
	return 0;
}