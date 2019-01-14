# Snake
这是一个基于TCP协议C/S架构的贪吃蛇小游戏
## 运行环境：Linux终端

## gcc版本:gcc version 7.3.0 

## 分支
- master分支是单机版的贪吃蛇
- dev分支是网络版的贪吃蛇(有bug，正在更新)

## 语言
- 单机版的贪吃蛇(master分支)是用纯C语言编写的
- 网络版的贪吃蛇(dev分支)客户端用纯C语言编写（把单机版的拿过来改了下），服务器端用C++编写。

## 安装
```
git clone https://github.com/Monster12138/Snake.git
```
## 使用
```
cd ./Snake/client
```
```
./client
```
注意：服务器地址可以在Snake/client/client_contig.ini配置中修改，服务器地址项是server_addr
