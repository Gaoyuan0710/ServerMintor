ServerMintor
============
基于B/S架构的服务器信息检测系统

Demo [http://monitor.alinuxer.net](http://monitor.alinuxer.net)

##项目说明 
- **client目录** ：
>用C++编写,采集cpu占用率,内存占用率等信息,,采用Protocol Buffer格式,定时发往服务端.并可及时接受服务端的命令,更新发送频率,重启服务器,杀死指定进程.

- **MonitorServer目录** 
>用Java编写,采用Netty框架,对各个客户机发来的信息进行存储,并对前端发来的请求消息进行响应。
- **WEB** :

#### 
