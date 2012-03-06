/*收回用户U4修改Printer表的价格的权限. */
REVOKE UPDATE ON printer FROM U4 CASCADE;

/*收回U1、U2、U3、U4、U5、U6、U7对表Laptop的查询权限. */
REVOKE SELECT ON laptop FROM U1, U2, U3, U4, U5, U6, U7 CASCADE;

/*收回用户U5 对表Product和PC的INSERT权限. */
REVOKE INSERT ON product, pc FROM U5 CASCADE;
