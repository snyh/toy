/*
 * 建立用户U1、U2、U3、U4、U5、U6、U7,全部为Public角色。
 * (PostgreSQL 中任何ROLE都自动拥有Public权限)
 */
CREATE USER U1;
CREATE USER U2;
CREATE USER U3;
CREATE USER U4;
CREATE USER U5;
CREATE USER U6;
CREATE USER U7;

/* 把查询Product表的权限授给用户U1。*/
GRANT SELECT ON product TO U1;

/*把对Product表和Laptop表的全部操作权限授予用户U2 和U3. */
GRANT ALL ON product, laptop TO U2, U3;

/*把对表Laptop的查询权限授予U1、U2、U3、U4、U5、U6、U7. */
GRANT SELECT ON laptop TO U1, U2, U3, U4, U5, U6, U7;

/*把查询Printer表和修改打印机价格的权限授给用户U4. */
GRANT SELECT, UPDATE ON printer TO U4;

/*把对表Product和PC的INSERT权限授予U5,并允许U5将此权限再授予其他用户. */
GRANT INSERT ON product, pc TO U5 WITH GRANT OPTION;

/*用户U5将对表Product和PC的INSERT权限授予U6,并允许将权限转授给其他用户. */
SET ROLE U5;
GRANT INSERT ON product, pc TO U6 WITH GRANT OPTION;

/*用户U6将对表Product和PC的INSERT权限授予U7. */
SET ROLE U6;
GRANT INSERT ON product, pc TO U7;
