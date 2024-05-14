# 栈
## 20 有效的括号
```cpp
class Solution {

public:

    bool isValid(string s) {

        unordered_map<char,int> m{{'(',1},{'[',2},{'{',3}, {')',4},{']',5},{'}',6}};

  

        stack<char> st;

        bool istrue=true;

        for(char c:s){

            int flag=m[c];

            if(flag>=1&&flag<=3)    st.push(c);

            else if(!st.empty()&&m[st.top()]==flag-3)   st.pop();

            else {

                istrue=false;break;

            }

        }

            if(!st.empty()) istrue=false;

            return istrue;

        }

};
```
通过哈希判断，能否出入栈

## 94 二叉树的遍历
```cpp
栈S;
p= root;
while(p || S不空){ 
while(p){
p入S; 
p = p的左子树; 
} 
p = S.top 出栈;
访问p; 
p = p的右子树; } 
```