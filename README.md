[TOC]

# Homework Manager 开发文档

## 项目说明

### 开发环境

- 开发环境：Qt 5.9.9

- 编译器：Qt Creator 4.11.0 （community)  32位

- 数据库：MySql Server 5.5  32位

注：qt和mysql的位数要对应，不能一个32位一个64位，否则不能连接成功

### 下载版本链接

1. git： https://github.com/Mattie0000001/C-HomeworkManager.git
2. 百度网盘： 链接：https://pan.baidu.com/s/1CGSYCf_lEsrF44ua6jQoZA 
   提取码：qku2

------

## 使用说明

### 编译前

**注：如果是可执行文件，只操作第二步即可，顺便最好把自己mysql数据库的用户名和密码改成root 和 123456**

1.  下载相应版本的qt creator 以及 MySQL

2.  数据库导入：

   在mysql中创建数据库hwmanager： 
     命令行中输入：**create database hwmanager;**
     命令行中输入：**use hwmanager;**

   将hwmanager.sql文件移至D盘（注：仅供参考，后文的路径根据sql文件的位置相应自行调  整），并在命令行中输入：**source d:/hwmanager.sql;**

3. 将MySQL Server 5.5 / lib / libmysql.dll复制到Qt creator安装目录下的bin目录中（如我的目录是E:\QT\Tools\QtCreator\bin）, 将 MySQL Server 5.5 / lib / libmysql.lib复制到Qt creator安装目录下的lib目录中（如我的目录是E:\QT\Tools\QtCreator\lib）

4.  将createDb.cpp文件中13、14行的username 和 password 改为自己数据库的用户名（一般默认为root）和密码

5.  操作完成后，即可编译

### 使用中

1.  在登录页面，通过点击radio选择自己的身份（管理员/老师/学生），账号和密码分别如下

| 身份   |        id（账号）         | 密码                       |
| ------ | :-----------------------: | -------------------------- |
| 管理员 |            1~3            | admin1（后面数字分别对应） |
| 学生   | 201930660001~201930660003 | 123456                     |
| 老师   |          001~005          | 123456                     |

2.  跳转到管理员页面：

+ 若想删除某个学生账号，则先选中此行，再点击delete按钮，删除成功则会提示

+ 若想添加某个学生账号，点击add按钮，弹出添加信息的窗口，输入相应信息，点击finish按钮即可

+ 若想返回登录界面，点击back按钮

+ 对老师账号的操作类似，不再赘述

3.  跳转到学生界面

+ 可以在页面看到当前周数、自己每科作业是否完成

+ 若想修改自己作业完成状态，例如，微积分作业完成，则点击calculus后的方框，出现对勾，点击update/save按钮，看到提示成功即可

+ 若想查看本科具体作业，点击此科后面的text按钮，可弹出弹窗，出现作业详细条目的表格
  - 注：只有当老师发布本科作业时，才可查看，否则，表格内容为空

+ 若想返回登录界面，点击back按钮

4.   跳转到教师界面

+ 可以在页面看到学生名单和作业上交情况统计

+ 若想发布作业或更改作业，点击 查看作业内容按钮 ， 弹出弹窗

 - 弹窗内的表格即为自己本周发布的作业

 - 若想删除已发布的作业，点击delete按钮

 - 若想添加作业，点击add按钮，在弹窗中填写相应作业内容，点击refresh按钮，提示成功即可

 - 若想修改作业，点击modify按钮，在弹窗中填写修改的周数和修改后的作业信息，点击保存更新按钮即可

 - 注：作业详细内容界面每次修改（添加/删除/更改）后，点击refresh按钮才会在表格中显示更新

## 文件说明

### 文件结构

|—HomeworkManager.pro          // 项目配置文件
|—Headers                                      // 头文件
|   |—mainwindow.h                               登录
|   |—createDB.h                                     数据库初始化、每周更新作业状态
|   |—administrator.h                             管理员
|   |—addstu.h                                         管理员----添加学生账号
|   |—addtea.h                                         管理员----添加教师账号
|   |—stu.h                                                学生
|   |—physics.h                                         物理学科作业具体内容
|   |.....(共五个学科)
|   |—tea.h                                                教师
|   |—hwdetail.h                                      作业具体内容显示、添加、删除、修改
|   |—addhw.h                                          添加作业
|   |—updatehw.h                                    更新作业
|—Source                                         //源文件
|   |—main.cpp                                       主程序
|   |—mainwindow.cpp
|   |—createDB.cpp
|   |....                        
|—Forms                                          //ui文件
|   |—mainwindow.ui
|   |—administrator.ui
|   |......

### 界面结构

| — 登录界面（mainwindow ）选择管理员/学生/老师身份并登录，成功后调转界面
|     |— 管理员 （administrator）：删除和创建学生/老师账号
|     |     |———学生信息添加（addstu）：创建学生账号（输入学生必要信息）
|     |     |———教师信息添加（addtea）：创建教师账号（输入教师必要信息）
|     |— 学生（student）：查看、修改每科作业的状态；查看作业具体内容
|     |     |———物理（physics）
|     |     |———工图（ed）
|     |     |———电路（circuit）
|     |     |———微积分（cal）
|     |     |———概率论（ps）
|     |— 老师 （teacher）：查看选此课的学生信息、统计学生作业未交人数、发布作业具体内容
|     |     |—作业具体（hwdetail）
|     |     |    |———添加作业（addhw）
|     |     |    |———更新作业（updatehw）



