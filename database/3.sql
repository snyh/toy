/*
 * 创建视图NewPC
   给出所有PC 的制造商、型号、速度、RAM 的大小、硬盘的容量和价格。
*/
CREATE VIEW NewPC as
SELECT product.maker, pc.* FROM product, pc
WHERE pc.model=product.model;

/*
 * 注意!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * 由于PostgreSQL不支持在View上建立Trigger
 * 因此使用PostgreSQL的RULE
 *
 * 经查询SQL Server在View上也只能创建
 * INSETEAD OF 触发器
 */

/* 2.1
 * 创建一个替换触发器用于处理对该视图的插入操作。
 */
CREATE RULE NewPC_insert AS ON INSERT TO NewPC
DO INSTEAD (
	INSERT INTO product VALUES(NEW.maker, NEW.model, 'pc');
	INSERT INTO pc VALUES(NEW.model, NEW.speed, NEW.ram, NEW.hd, NEW.price);
);


/* 2.2
 * 创建一个替换触发器用于处理对该视图中 price 属性的修改(针对某个给定的型号)。
 * TODO:model不存在的时候没有提示用户
 */
CREATE RULE NewPC_update AS ON UPDATE TO NewPC
DO INSTEAD (
	UPDATE pc 
	SET price = NEW.price
	WHERE model = NEW.model;
);


/* 3.1
 * 通过指定价格返回最接近此价格的PC型号
 */
CREATE TYPE test AS ("查询价格" text, "最接近价格" numeric, "型号"  text);

CREATE FUNCTION getpc_by_price(numeric) RETURNS SETOF test AS $$
my $rv = spi_exec_query(
	"SELECT model, price FROM pc 
	WHERE price >= $_[0]
	ORDER BY price ASC
	LIMIT 1;"
);
my $price1 = $rv->{rows}[0]->{price};
my $model1 = $rv->{rows}[0]->{model};

$rv = spi_exec_query(
	"SELECT model, price FROM pc 
	WHERE price <= $_[0]
	ORDER BY price DESC
	LIMIT 1;"
);
my $price2 = $rv->{rows}[0]->{price};
my $model2 = $rv->{rows}[0]->{model};

return [{"查询价格"=>$_[0], "最接近价格"=>$price1, "型号"=>$model1}] if not defined($price2);
return [{"查询价格"=>$_[0], "最接近价格"=>$price2, "型号"=>$model2}] if not defined($price1);

if ( ($price1-$_[0]) > ( $_[0] - $price2) ) {
	return [{"查询价格"=>$_[0], "最接近价格"=>$price2, "型号"=>$model2}];
} else {
	return [{"查询价格"=>$_[0], "最接近价格"=>$price1, "型号"=>$model1}];
}
$$ LANGUAGE plperl;
