这个只是数据库的一个作业
不过我用perl等来完成的
题目都在输出里面或者源代码里面.

涉及到一些sql基本的东西和odbc, pgsql, esql等.

通过makefile初始化数据库展示等.

make自动补全效果如下:
[snyh@snyh database]$ make
 -- make targets --
1         3         4_esql    all       createdb  show_1    show_3    show_5  
2         4         5         backup    restore   show_2    show_4 

createdb, restore分别是创建数据库和恢复之前北方的数据
backup就是用来备份的了.
1 2 3 4 5分别是运行各个题目
show_x 只是简单的用VIM打开源程序方便看题目和程序

使用perl DBI和pgsql

涉及到的SQL内容都是比较简单的, 个人比较满意的是使用makefile来管理和展示.
