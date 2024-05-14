# 844 走迷宫
给定一个 n×m 的二维整数数组，用来表示一个迷宫，数组中只包含 00 或 11，其中 00 表示可以走的路，11 表示不可通过的墙壁。

最初，有一个人位于左上角 (1,1)(1,1) 处，已知该人每次可以向上、下、左、右任意一个方向移动一个位置。

请问，该人从左上角移动至右下角 (n,m) 处，至少需要移动多少次。

数据保证 (1,1)(1,1) 处和 (n,m)处的数字为 00，且一定至少存在一条通路。

#### 输入格式

第一行包含两个整数 n 和 m。

接下来 n 行，每行包含 m个整数（00 或 11），表示完整的二维数组迷宫。

#### 输出格式

输出一个整数，表示从左上角移动至右下角的最少移动次数。

#### 数据范围

1≤n,m≤100

比较巧妙的点在于使用了 pair 这个对，存储每个点的信息，使用队列存储每个点
BFS 的逻辑主体顺序为
最开始引入起点进入队列，然后进入循环队列不为空的情况下进行循环，取出队列的第一个元素，横纵坐标，然后进行宽搜，宽搜的特性为最短问题，因此直接输出的结果就是最短路径，不需要再次进行筛选。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int N=110;
typedef pair<int,int> PII;
int f[N][N];//存储距离
int g[N][N];//存储地图
int n,m;

void bfs(int a,int b)
{
    queue<PII> q;
    q.push({a, b});
    //初始点的距离为 0.
    //可以不要这一句，因为f初始化的时候，各个点为0
    f[0][0] = 0;
    while(!q.empty())
    {
        PII start=q.front();
        q.pop();
        g[start.first][start.second]=1;
        int dx[4]={0,1,0,-1},dy[4]={-1,0,1,0};
        for(int i=0;i<4;i++)
        {
            int x=start.first+dx[i];
            int y=start.second+dy[i];
            //没走过
            if(g[x][y]==0)
            {
                g[x][y]=1;
                f[x][y]=f[start.first][start.second]+1;
                
                q.push({x,y});
            }
        }
    }
    cout<<f[n][m]<<endl;
}

int main()
{
    cin>>n>>m;
    memset(g, 1, sizeof(g));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>g[i][j];
        }
    }
    
    bfs(1,1);
    
    return 0;
}
```

# 845 八数码
在一个 3×3 的网格中，1∼8 这 8个数字和一个 `x` 恰好不重不漏地分布在这 3×3的网格中。

例如：

```
1 2 3
x 4 6
7 5 8
```

在游戏过程中，可以把 `x` 与其上、下、左、右四个方向之一的数字交换（如果存在）。

我们的目的是通过交换，使得网格变为如下排列（称为正确排列）：

```
1 2 3
4 5 6
7 8 x
```

例如，示例中图形就可以通过让 `x` 先后与右、下、右三个方向的数字交换成功得到正确排列。

交换过程如下：

```
1 2 3   1 2 3   1 2 3   1 2 3
x 4 6   4 x 6   4 5 6   4 5 6
7 5 8   7 5 8   7 x 8   7 8 x
```

现在，给你一个初始网格，请你求出得到正确排列至少需要进行多少次交换。

#### 输入格式

输入占一行，将 3×33×3 的初始网格描绘出来。

例如，如果初始网格如下所示：

```
1 2 3 
x 4 6 
7 5 8 
```

则输入为：`1 2 3 x 4 6 7 5 8`
#### 输出格式
输出占一行，包含一个整数，表示最少交换次数。

如果不存在解决方案，则输出 −1−1。
#### 输入样例：
```
2 3 4 1 5 x 7 6 8
```
#### 输出样例

```
19
```

1、题目的目标
![[Pasted image 20240104094624.png]]
求最小步数 -> 用 BFS
2、移动情况
![[Pasted image 20240104094637.png]]

移动方式：![[Pasted image 20240104094709.png]]
转以后：a = x + dx[i], b = y + dy[i].
思想：每一种情况作为 1 个节点，目标情况即为终点
从初始状况移动到目标情况 —> 求最短路
3、问题
第一点：怎么表示一种情况使其能作为节点？

第二点：如何记录每一个状态的“距离”（即需要移动的次数）？

第三点：队列怎么定义，dist 数组怎么定义？

4、解决方案

将 “3\*3 矩阵” 转化为 “字符串”

如：
​![[Pasted image 20240104094719.png]]

所以：

队列可以用 queue<string>
//直接存转化后的字符串
dist 数组用 unordered_map<string, int>
//将字符串和数字联系在一起，字符串表示状态，数字表示距离\\
5、矩阵与字符串的转换方式
![[Pasted image 20240104094910.png]]
```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_map>

Using namespace std;

Int bfs (string start)
{
    //定义目标状态
    String end = "12345678 x";
    //定义队列和 dist 数组
    queue<string> q;
    unordered_map<string, int> d;
    //初始化队列和 dist 数组
    q.push (start);
    D[start] = 0;
    //转移方式
    Int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

    while (q.size ())
    {
        auto t = q.front ();
        q.pop ();
        //记录当前状态的距离，如果是最终状态则返回距离
        Int distance = d[t];
        If (t == end) return distance;
        //查询 x 在字符串中的下标，然后转换为在矩阵中的坐标
        int k = t.find ('x');
        Int x = k / 3, y = k % 3;

        For (int i = 0; i < 4; i++)
        {
            //求转移后 x 的坐标
            Int a = x + dx[i], b = y + dy[i];
            //当前坐标没有越界
            if (a >= 0 && a < 3 && b >= 0 && b < 3)
            {
                //转移 x
                Swap (t[k], t[a * 3 + b]);
                //如果当前状态是第一次遍历，记录距离，入队
                if (!d.count (t))
                {
                    D[t] = distance + 1;
                    q.push (t);
                }
                //还原状态，为下一种转换情况做准备
                Swap (t[k], t[a * 3 + b]);
            }
        }
    }
    //无法转换到目标状态，返回-1
    Return -1;
}

Int main ()
{
    String c, start;
    //输入起始状态
    For (int i = 0; i < 9; i++)
    {
        Cin >> c;
        Start += c;
    }

    Cout << bfs (start) << endl;

    Return 0;
    }
    
```


# 