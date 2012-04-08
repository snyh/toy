#!/usr/bin/perl
use strict;
use warnings;
use DBI;
use Term::ANSIColor qw(:constants);


my $dbh = init_db();

show_quiz(
  {
    QUIZ=>"1. 查询硬盘容量至少30G的笔记本电脑制造商及该电脑的速度.",
    SQL=>"
    	SELECT DISTINCT maker, L.model, hd 
    	FROM Laptop L, Product P
	WHERE hd>=30 AND L.model = P.model;
	"
  }
);

show_quiz(
  {
    QUIZ=>"2. 查询制造商B生产的任意类型的所有产品的型号和价格",
    SQL=>"
    	SELECT Product.model, price 
   	FROM Product, Laptop 
	WHERE maker='B' AND Product.model = Laptop.model 
	UNION SELECT Product.model, price FROM Product, PC
	WHERE maker='B' and Product.model=PC.model
	UNION SELECT Product.model, price FROM Product, Printer
	WHERE maker='B' and Product.model=Printer.model;
	"
  }
);

show_quiz(
  {
    QUIZ=>"3. 查询出现在两种或两种以上PC中的硬盘大小",
    SQL=>"
    	SELECT DISTINCT p1.hd 
    	FROM PC p1, PC p2 
	WHERE p1.hd = p2.hd AND p1.model != p2.model;
	"
  }
);


show_quiz(
  {
    QUIZ=>"4. 查询每对具有相同速度和RAM的PC的型号。每一对只能列出一次；例如(i,j)已被列出， 则(j, i)就不能再被列出",
    SQL=>"
   	 SELECT p1.model, p2.model 
	 FROM PC p1, PC p2 
	 WHERE p1.ram=p2.ram AND p1.speed=p2.speed AND p1.model > p2.model;
	 "
  }
);

show_quiz(
  {
    QUIZ=>"5. 找出速度在3.0以上的PC制造商",
    SQL=>"
    	SELECT maker 
    	FROM Product WHERE model IN (
		SELECT model 
		FROM PC 
		WHERE speed>=3.0
	);
	"
  }
);

show_quiz(
  {
    QUIZ=>"6. 找出价格最高的打印机",
    SQL=>"
    	SELECT model 
	FROM Printer
	WHERE price >= ANY (
		SELECT price 
		FROM Printer
	);
	"
  }
);

show_quiz(
  {
    QUIZ=>"7. 找出速度比任何一台PC都慢的笔记本电脑。",
    SQL=>"
    	SELECT model FROM Laptop
	WHERE speed < ALL (
		SELECT speed FROM PC
	);
    "
  }
);

show_quiz(
  {
    QUIZ=>"8. 找出价格最低的颜色打印机的制造商",
    SQL=>"
    	SELECT maker FROM Product
	WHERE model IN (
		SELECT model FROM Printer
		WHERE price <= ALL (
			SELECT price FROM Printer
		)
	);
    "
  }
);

show_quiz(
  {
    QUIZ=>"9.查询厂商A生成的PC的平均价格.",
    SQL=>"
    	SELECT AVG(price) FROM PC, Product
	WHERE Product.model = PC.model AND
	      Product.maker = 'A'
     "
  }
);

show_quiz(
  {
    QUIZ=>"10.查询每种不同速度的PC的平均价格.",
    SQL=>"
    	SELECT speed, AVG(price) FROM PC
	GROUP BY speed;
    "
  }
);

show_quiz(
  {
    QUIZ=>"11.查询每家厂商生产的笔记本电脑的显示器尺寸的平均值.",
    SQL=>"
    	SELECT maker, AVG(screen) 
	FROM Product, Laptop
	WHERE Product.model = Laptop.model
	GROUP BY maker;
    "
  }
);

show_quiz(
  {
    QUIZ=>"12.查询至少生产三种不同型号PC的制造所",
    SQL=>"
    	SELECT maker FROM Product, PC
	WHERE Product.model = PC.model
	GROUP BY maker
	HAVING COUNT(Product.model) >= 3;
    "
  }
);

show_quiz(
  {
    QUIZ=>"2.1. 通过两条INSERT 语句在数据库中添加如下信息: 厂商C生产的型号为1100
    的PC, 其速度为3.2, RAM容量为1024, 硬盘容量为180, 售价\$2499",
    SQL=>"INSERT INTO PC VALUES('1100', 3.2, 1024, 180, 2499);",
    TYPE=>"OTHER"
  }
);

show_quiz(
  {
    QUIZ=>"2.2. 删除所有硬盘容量低于100GB的PC.",
    SQL=>"DELETE FROM PC WHERE hd < 100;",
    TYPE=>"OTHER"
  }
);

show_quiz(
  {
    QUIZ=>"2.3. 厂商A收购了厂商B, 将所有B生成的产品改为由A生产.",
    SQL=>"UPDATE product SET maker='A' WHERE maker='B';",
    TYPE=>"OTHER"
  }
);

show_quiz(
  {
    QUIZ=>
	"3.1.对于每个基本表定义它的外键
	 	 由于2.1中插入了model=1100的pc,但product中并没有此项
		 所以第二条语句会失败",
    SQL=>
	"ALTER TABLE laptop ADD FOREIGN KEY (model) REFERENCES Product (model);
	ALTER TABLE pc ADD FOREIGN KEY (model) REFERENCES Product (model);
	ALTER TABLE printer ADD FOREIGN KEY (model) REFERENCES Product (model);",
    TYPE=>"OTHER"
  }
);

show_quiz(
	{
		QUIZ=>"3.2.定义以下基于属性的约束:
		(1) 笔记本电脑的速度至少是2.0
		(2) 打印机的类型只能是激光、喷墨、点阵。
		(3) 产品类型只能是PC、笔记本电脑和打印机。",
		SQL=>
		"ALTER TABLE Laptop ADD CHECK(price>2.0);
		ALTER TABLE Printer 
		ADD CHECK(type IN ('ink-jet', 'laser', 'dot'));
		ALTER TABLE Product 
		ADD CHECK(type IN ('pc', 'laptop', 'printer'));",
		TYPE=>"OTHER"
	}
);

show_quiz(
	{
		QUIZ=>"3.3. 定义以下基于元组CHECK约束:
		(1) 处理器速度低于2.0的PC价格不能超过\$600.
		(2) 显示器小于15英寸的笔记本电脑要么硬盘至少有40GB，要么价格低于\$1000",
		SQL=>"未找到基于check的可行方案.",
		TYPE=>"ONLYSHOW"
	}
);


sub init_db {
	my $dbh = DBI->connect("DBI:PgPP:database=productdb;host=localhost", "postgres");
	if (not $dbh) {
		print "数据库未连接";
		exit;
	}
	return $dbh;
}


sub show_quiz {
	system("clear");
	my $arg = shift;
	print "题目:\n\t";
	print BOLD, BLUE, $arg->{"QUIZ"},"\n", RESET;
	print "SQL:\n\t";
	print BOLD, RED, $arg->{"SQL"}, "\n", RESET;
	print "运行结果:\n\t";

	return if (defined($arg->{TYPE}) and $arg->{TYPE} eq "ONLYSHOW");
	if (defined($arg->{TYPE}) and  $arg->{TYPE} eq "OTHER") {
		my $rc = $dbh->do($arg->{"SQL"});
		if($rc) {
			print BOLD, RED, "运行成功\n", RESET;
		} else {
			print BOLD, RED, "运行失败\n", RESET;
		}
		readline;
		return;
	}

	my $sth = $dbh->prepare($arg->{"SQL"});
	$sth->execute();

	my $names = $sth->{'NAME'};
	my $numFields = $sth->{'NUM_OF_FIELDS'};
	print BOLD, RED;
	for (my $i = 0; $i < $numFields; $i++) {
		printf("%s\t",  $$names[$i]);
	}
	print RESET;
	print "\n";
	while (my $ref = $sth->fetchrow_arrayref()) {
		for(my $i=0; $i < $numFields; $i++) {
			printf("\t%s", $$ref[$i]);
		}
		printf "\n";
	}
	print "\n------------回车显示下一问题----------\n";
	readline;
	system("clear");
}
