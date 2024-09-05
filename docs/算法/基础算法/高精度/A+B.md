
## 题目描述

高精度加法，相当于 a+b problem，**不用考虑负数**。

## 输入格式

分两行输入。$a,b \leq 10^{500}$。

## 输出格式

输出只有一行，代表 $a+b$ 的值。

## 样例 #1

### 样例输入 #1

```
1
1
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
1001
9099
```

### 样例输出 #2

```
10100
```

```cpp
#include<iostream>  
#include<string>  
using namespace std;  
  
string add(string str1,string str2)  
{  
    string str;  
    int len1=str1.length();  
    int len2=str2.length();  
    if(len1<len2)  
    {  
        for(int i=1;i<=len2-len1;i++)  
        {  
            str1='0'+str1;  
        }  
    }else{  
        for(int i=1;i<=len1-len2;i++)  
        {  
            str2="0"+str2;  
        }  
    }  
    len1=str1.length();  
    int cf=0;  
    int temp;  
    for(int i=len1-1;i>=0;i--)  
    {  
        temp=str1[i]-'0'+str2[i]-'0'+cf;  
        cf=temp/10;  
        temp=temp%10;  
        str=char(temp+'0')+str;  
    }  
    if(cf!=0) str=char('0'+cf)+str;  
  
    return str;  
}  
int main()  
{  
    string str1,str2;  
    cin>>str1>>str2;  
   cout<<add(str1,str2)<<endl;  
    return 0;  
}
```
对于三个函数 \( u(x) \)、\( v(x) \) 和 \( w(x) \) 的乘积 \( f(x) = u(x) v(x) w(x) \)，其 \( n \) 阶导数可以使用莱布尼茨公式的推广形式来求解。具体来说，三个函数的乘积的 \( n \) 阶导数可以表示为：

\[
f^{(n)}(x) = \sum_{k_1 + k_2 + k_3 = n} \frac{n!}{k_1! k_2! k_3!} u^{(k_1)}(x) v^{(k_2)}(x) w^{(k_3)}(x)
\]

其中，\( k_1 \)、\( k_2 \) 和 \( k_3 \) 是非负整数，表示 \( u \)、\( v \) 和 \( w \) 的导数的阶数，且它们的和为 \( n \)。\( u^{(k)}(x) \)、\( v^{(k)}(x) \) 和 \( w^{(k)}(x) \) 分别表示函数 \( u \)、\( v \) 和 \( w \) 的 \( k \) 阶导数。

这个公式的含义是：对于每一种将 \( n \) 阶导数分配给 \( u \)、\( v \) 和 \( w \) 的方式，我们都计算相应的导数并乘在一起，然后将所有这些结果相加。

如果你有具体的函数或需要进一步的解释，请告诉我！