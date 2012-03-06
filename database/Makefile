all:
	@echo 使用make show_number 显示实验源码
	@echo 使用make number 运行实验结果
	@echo 使用make createdb 初始化数据库
	@echo 使用make backup 备份数据库
	@echo 使用make restore 恢复数据库

show_1: 1.pl
	@vim 1.pl
1: 1.pl
	./1.pl
	@echo "恢复数据库..."
	@dropdb productdb -U postgres
	@createdb productdb -U postgres
	@psql -q -U postgres productdb < init.sql 2&> /dev/null

show_2: 2_create.sql 2_revoke.sql
	@vim 2_create.sql 2_revoke.sql
2: 2_create.sql 2_revoke.sql
	clear
	@echo -e "-------------导入授权语句2_create.sql-------------\n"
	@psql -U postgres productdb -q < 2_create.sql
	@echo "测试效果(以下语句均应成功运行)"
	@echo "(U4 更新Printer表的价格:)"
	@echo -e "SET ROLE U4; UPDATE printer SET price=1.1 WHERE model='3001';\n"
	@echo "(U7 向Product和PC表中插入一条新PC的信息:)"
	@echo -e "SET ROLE U7; INSERT INTO pc values('8051', 0.01, 0.01, 0, 5);\n" 
	@psql -U postgres productdb -q

	clear
	@echo -e "-------------导入权限回收语句2_revoke.sql---------\n"
	@psql -U postgres productdb -q < 2_revoke.sql
	@echo "测试效果(以下语句均应无法运行)"
	@echo "(用户U3 查询表Laptop:)"
	@echo -e "SET ROLE U3; SELECT * FROM laptop;\n"
	@echo "(用户U6 向Product和PC 表中插入一条新PC的信息:)"
	@echo -e "SET ROLE U6; INSERT INTO product values('T', 'test', 'pc');\n"
	@psql -U postgres productdb -q

	clear
	@echo "PostgreSQL中 用户 和 角色 没有本质区别因此不做测试"
	@read

	clear
	@echo "恢复数据库中..."
	@echo "REVOKE ALL PRIVILEGES ON printer FROM U4 CASCADE;" | psql -q -U postgres productdb;
	@echo "REVOKE ALL PRIVILEGES ON product FROM U1,U2,U3 CASCADE;" | psql -q -U postgres productdb;
	@echo "REVOKE ALL PRIVILEGES ON laptop FROM U2,U3 CASCADE;" | psql -q -U postgres productdb;
	@echo "DROP ROLE U7;DROP ROLE U6; DROP ROLE U5; DROP ROLE U4; DROP ROLE U3; DROP ROLE U2; DROP ROLE U1" | psql -q -U postgres;

	@dropdb productdb -U postgres
	@createdb productdb -U postgres
	@psql -q -U postgres productdb < init.sql 2&> /dev/null

show_3: 3.sql
	@vim 3.sql
3: 3.sql
	clear
	@echo "题目:"
	@echo "1.创建视图NewPC给出所有PC 的制造商、型号、速度、RAM 的大小、硬盘的容量和价格."
	@echo "创建一个替换触发器用于处理对该视图的插入操作."
	@echo "创建一个替换触发器用于处理对该视图中 price 属性的修改(针对某个给定的型号)."
	@echo "创建存储过程通过指定价格返回最接近此价格的PC型号"

	@echo "create language plperl;" | psql -q -U postgres productdb
	@psql -q -U postgres productdb < 3.sql
	@echo -e "---------------复制以下语句进行测试--------------------"
	@echo "1.1 SELECT * FROM NewPC WHERE speed>=3.0;"
	@echo "1.2 SELECT avg(price) FROM NewPC WHERE maker='A';"
	@echo "2.1 INSERT INTO NewPC VALUES('maker', 'model', speed, ram, hd, price);"
	@echo "2.2 UPDATE NewPC SET price=新价格 WHERE model=型号;"
	@echo "3.1 SELECT * FROM getpc_by_price(价格);"
	@psql -U postgres productdb -q
	@echo "恢复数据库..."
	@dropdb productdb -U postgres
	@createdb productdb -U postgres
	@psql -q -U postgres productdb < init.sql 2&> /dev/null

show_4: 4_esql.pgc
	@vim 4_esql.pgc
4: 4_esql
	clear
	@./4_esql
4_esql: 4_esql.pgc
	ecpg 4_esql.pgc
	gcc 4_esql.c -o 4_esql -lecpg
	/bin/rm 4_esql.c

show_5: 5_odbc.c
	@vim 5_odbc.c
5: 5_odbc.c
	clear
	@tcc -run -lodbc 5_odbc.c

createdb:
	dropdb productdb -U postgres
	createdb productdb -U postgres
	psql -U postgres productdb < init.sql 2& >/dev/null

backup:
	pg_dump -U "postgres" -F custom -b productdb > .data.backup

restore:
	dropdb productdb -U postgres
	pg_restore -C -d postgres -U postgres .data.backup
