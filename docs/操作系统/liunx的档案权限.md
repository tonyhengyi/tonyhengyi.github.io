# Linux的档案权限
Linux最优秀的地方之一就在于他的多人多工环境。而为了让各个使用者具有较保密的档案资料，因此档案的权限管理就变的很重要了。 Linux一般将档案可存取的身份分为三个类别，分别是owner/group/others，且三种身份各有read/write/execute 等权限。

---

# 使用者与群组

## 档案拥有者(owner)
Linux是个多人多工的系统，因此可能常常会有多人同时使用这部主机来进行工作的情况发生， 为了考虑每个人的隐私权以及每个人喜好的工作环境，因此，这个『档案拥有者』的角色就显的相当的重要了！
档案拥有者即创建档案的人。

## 群组(group)
在Linux底下这样的限制是很简单啦！我可以经由简易的档案权限设定，就能限制非自己团队(亦即是群组啰) 的其他人不能够阅览内容啰！而且亦可以让自己的团队成员可以修改我所建立的档案！ 同时，如果我自己还有私人隐密的文件，仍然可以设定成让自己的团队成员也看不到我的档案资料。 

可以将家庭空间比作档案，每个家庭成员都是各自卧室的档案拥有者，别的成员不能随意翻动自己的东西，但家里面的客厅就是公共空间，大家都能在客厅里活动，也就是属于群组的内容。

也可以通过设置每个档案的权限改变上面所说的内容。

## 其他人(others)
也就是不属于刚刚所说的家庭成员的人，是不能够进入客厅更别说房间了。

#  Linux 档案权限概念
切换到超级用户查看各个档案的权限

```shell
zhy_clound@iZ2zefhns847t1cynpxco5Z:~$ su -
Password: 
root@iZ2zefhns847t1cynpxco5Z:~# ls -al
total 64
drwx------ 11 root root 4096 Jun  1 22:06 .
drwxr-xr-x 19 root root 4096 Jun  1 21:45 ..
-rw-------  1 root root   68 Jun  1 22:06 .bash_history
-rw-r--r--  1 root root 3106 Oct 15  2021 .bashrc
drwx------  2 root root 4096 May  8 11:27 .cache
drwx------  3 root root 4096 Jun  1 21:57 .config
drwxr-xr-x  3 root root 4096 Jun  1 21:55 .dotnet
drwx------  3 root root 4096 Jun  1 21:57 .local
drwxr-xr-x  2 root root 4096 May  8 11:42 .pip
-rw-r--r--  1 root root  161 Jul  9  2019 .profile
-rw-r--r--  1 root root   72 May  8 11:42 .pydistutils.cfg
drwxr-xr-x  2 root root 4096 May  8 11:42 .rpmdb
drwx------  3 root root 4096 May  8 11:26 snap
drwx------  2 root root 4096 May  8 11:26 .ssh
drwxr-xr-x  5 root root 4096 Jun  1 21:55 .vscode-server
-rw-r--r--  1 root root  183 Jun  1 21:54 .wget-hsts
root@iZ2zefhns847t1cynpxco5Z:~# 
```
![alt text](image.png)

```shell
-rw-r--r--  1 root root  183 Jun  1 21:54 .wget-hsts
```
其中第一栏表示档案类型与权限
* 第一个字元代表这个档案是『目录、档案或连结档等等』
  ·当为[ d ]则是目录
  ·当为[ - ]则是档案
  ·若是[ l ]则表示为连结档(link file)
  ·若是[ b ]则表示为装置档里面的可供储存的周边设备(可随机存取装置)；
  ·若是[ c ]则表示为装置档里面的序列埠设备，例如键盘、滑鼠(一次性读取装置)。

* 接下来的字元中，以三个为一组，且均为『rwx』 的三个参数的组合。其中，[ r ]代表可读(read)、[ w ]代表可写(write)、[ x ]代表可执行(execute)。 要注意的是，这三个权限的位置不会改变，如果没有权限，就会出现减号[ - ]而已。
    第一组为『档案拥有者可具备的权限』，以上面档案为例， 该档案的拥有者可以读写，但不可执行；
    第二组为『加入此群组之帐号的权限』；
    第三组为『非本人且没有加入本群组之其他帐号的权限』。



```
例题：
    若有一个档案的类型与权限资料为『-rwxr-xr--』，请说明其意义为何？
答：
    先将整个类型与权限资料分开查阅，并将十个字元整理成为如下所示：
    [-][rwx][rx-][r--]
    1   234  567 890
    1 为：代表这个档名为目录或档案，本例中为档案(-)；
    234为：拥有者的权限，本例中为可读、可写、可执行(rwx)；
    567为：同群组使用者权限，本例中为可读可执行(rx)；
    890为：其他使用者权限，本例中为可读(r)，就是唯读之意

同时注意到，rwx所在的位置是不会改变的，有该权限就会显示字元，没有该权限就变成减号(-)就是了。
```

第二栏表示有多少档名连结到此节点(i-node)：
第三栏表示这个档案的拥有者
第四栏表示这个档案的所属群组
第五栏表示这个档案的大小
第六栏为这个档案的建档日期或者是最近的修改日期：
第七栏为这个档案的档名
    如果前面加了一个.的话说明是隐藏档案

# 如何改变Linux的档案权限
通过命令
* chgrp ：改变档案所属群组
* chown ：改变档案拥有者
* chmod ：改变档案的权限, SUID, SGID, SBIT等等的特性
  
----

## 改变所属群组, chgrp
change group的缩写
要被改变的群组名称必须要在/etc/group档案内存在才行，否则就会显示错误！

假设在/etc/group里面已经存在一个名为users的群组， 但是testing这个群组名字就不存在/etc/group当中

```shell
[root@study ~]# chgrp [-R] dirname/filename ...
选项与参数：
-R : 进行递回(recursive)的持续变更，亦即连同次目录下的所有档案、目录
     都更新成为这个群组之意。常常用在变更某一目录内所有的档案之情况。
范例： 
[root@study ~]# chgrp users initial-setup-ks.cfg 
[root@study ~]# ls -l 
-rw-r--r--. 1 root users 1864 May 4 18:01 initial-setup -ks.cfg
[root@study ~]# chgrp testing initial-setup-ks.cfg 
chgrp: invalid group: `testing' <== 发生错误讯息啰～找不到这个群组名～
```

## 改变档案拥有者, chown
change owner的缩写
语法如下
```shell
[root@study ~]# chown [-R] 帐号名称档案或目录
[root@study ~]# chown [-R] 帐号名称:群组名称档案或目录
选项与参数：
-R : 进行递回(recursive)的持续变更，亦即连同次目录下的所有档案都变更

范例：将initial-setup-ks.cfg 的拥有者改为bin这个帐号： 
[root@study ~]# chown bin initial-setup-ks.cfg 
[root@study ~]# ls -l 
-rw-r- -r--. 1 bin   users 1864 May 4 18:01 initial-setup-ks.cfg

范例：将initial-setup-ks.cfg 的拥有者与群组改回为root： 
[root@study ~]# chown root:root initial-setup-ks.cfg 
[root@study ~]# ls -l 
- rw-r--r--. 1 root root 1864 May 4 18:01 initial-setup-ks.cfg
```

一个常用的使用改变权限的场景是在复制使用别人的档案时候
```shell
[root@study ~]# cp .bashrc .bashrc_test 
[root@study ~]# ls -al .bashrc*
-rw-r--r--. 1 root root 176 Dec 29 2013 .bashrc
-rw-r--r--. 1 root root 176 Jun 3 00:04 .bashrc_test    <==新档案的属性没变
```
先把两个隐藏的文档粘贴过来，可以看到档案的属性还是root，其他用户无权更改，所以此时需要更改档案的权限，拥有者………

## 改变权限, chmod
改变权限有几种不同的方式
### 使用数字来改变权限
-rw-r--r--
例如对于这段字符来说，使用二进制来解析
owner = rw- = 4+2+0 = 6
group = r-- = 4+0+0 = 4
others= r-- = 4+0+0 = 4
此时的语法是这样的
```shell
[root@study ~]# chmod [-R] xyz 档案或目录
选项与参数：
xyz : 就是刚刚提到的数字类型的权限属性，为rwx 属性数值的相加。
-R : 进行递回(recursive)的持续变更，亦即连同次目录下的所有档案都会变更
```
范例如下
```shell
[root@study ~]# ls -al .bashrc 
-rw-r--r-- . 1 root root 176 Dec 29 2013 .bashrc
[root@study ~]# chmod 777 .bashrc 
[root@study ~]# ls -al .bashrc 
-rwxrwxrwx . 1 root root 176 Dec 29 2013 .bashrc
```
### 使用符号来改变权限
基本上就九个权限分别是(1)user (2)group (3)others三种身份啦！那么我们就可以藉由u, g, o来代表三种身份的权限！此外，a则代表all 亦即全部的身份！那么读写的权限就可以写成r, w, x

假如我们要『设定』一个档案的权限成为『-rwxr-xr-x』时，基本上就是：

user (u)：具有可读、可写、可执行的权限；
group 与others (g/o)：具有可读与执行的权限。
```shell
[root@study ~]# chmod u=rwx,go=rx .bashrc 
# 注意喔！那个u=rwx,go=rx 是连在一起的，中间并没有任何空白字元！ 
[root@study ~]# ls -al .bashrc 
-rwxr-xr-x . 1 root root 176 Dec 29 2013 .bashrc
```
如果想要人均添加读的权限
```shell
[root@study ~]# ls -al .bashrc 
-rwxr-xr-x . 1 root root 176 Dec 29 2013 .bashrc
[root@study ~]# chmod a+w .bashrc 
[root@study ~]# ls -al .bashrc 
-rwxrwxrwx . 1 root root 176 Dec 29 2013 .bashrc
```
