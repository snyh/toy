#include <stdio.h>
#include <sqlext.h>

#define  max_len  128

const char *quiz = 
"题目:\n"
"\t询问用户能接受的速度、硬盘大小和显示器尺寸的最小值。"
"找出满足要求的所有笔记本电脑(laptop)。"
"输出它们的说明(laptop 的所有属性)和它们的制造商。\n\n";

static void extract_error(char *fn, SQLHANDLE handle,
						  SQLSMALLINT type)
{
  SQLINTEGER i = 0;
  SQLINTEGER native;
  SQLCHAR state[7];
  SQLCHAR text[256];
  SQLSMALLINT len;
  SQLRETURN ret;

  fprintf(stderr, "\nTheDriver reported the following diagnostics whilst running %s\n\n", fn);
  do {
	  ret = SQLGetDiagRec(type, handle, ++i, state, &native,
						  text, sizeof(text), &len);
	  if (SQL_SUCCEEDED(ret))
		printf("%s:%ld:%ld:%s\n", state, i, native, text);
  } while (ret == SQL_SUCCESS);
}

void get_query_param(double* speed, double* hd, double* screen)
{
  printf("输入需要查询的最小值\n");
  printf("速度(GHz):");
  scanf("%lf", speed);
  printf("硬盘容量(GB):");
  scanf("%lf", hd);
  *hd = ceil(*hd);
  printf("屏幕大小:");
  scanf("%lf", screen);
}

void show_result(SQLHSTMT stmt)
{
  SQLCHAR model[max_len], maker[max_len]; 
  SQLDOUBLE speed, screen, price;
  SQLSMALLINT ram, hd;

  SQLBindCol(stmt, 1, SQL_C_CHAR, model, max_len, NULL);
  SQLBindCol(stmt, 2, SQL_C_DOUBLE, &speed, max_len, NULL);
  SQLBindCol(stmt, 3, SQL_C_SHORT, &ram, max_len, NULL);
  SQLBindCol(stmt, 4, SQL_C_SHORT, &hd, max_len, NULL);
  SQLBindCol(stmt, 5, SQL_C_DOUBLE, &screen, max_len, NULL);
  SQLBindCol(stmt, 6, SQL_C_DOUBLE, &price, max_len, NULL);
  SQLBindCol(stmt, 7, SQL_C_CHAR, maker, max_len, NULL);

  system("clear");
  printf("  型号  |  速度  |  内存  |  硬盘  | 显示器 |  价格  | 制造商 \n"
		 "--------+--------+--------+--------+--------+--------+--------\n");
  while (SQLFetch(stmt) != SQL_NO_DATA_FOUND) {
	  printf(" %-6s | %-6.2lf | %-6d | %-6d | %-6.1lf | %-6.1lf | %-6s \n", 
			 model, speed,    ram,     hd,    screen,   price,   maker);
  }
  printf("--------+-------+---------+--------+--------+--------+--------\n");
}

void query_show_laptop(SQLHDBC dbc, double speed, double hd, double screen)
{
  SQLHSTMT stmt;
  SQLRETURN ret;
  char sql[1024] = {0};

  SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
  sprintf(sql,
		  "SELECT laptop.*, product.maker from laptop, product"
		  "     WHERE speed>=%lf AND hd>=%lf AND screen>=%lf"
		  "		AND laptop.model=product.model;",
		  speed, hd, screen);
  printf("%s\n", sql);
  ret = SQLExecDirect(stmt, sql, SQL_NTS);

  if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
	  show_result(stmt);
  } else {
	  extract_error("查询错误", stmt, SQL_HANDLE_STMT);
  }
  SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}


int main()
{
  //打印当前题目
  printf(quiz);

  SQLHENV env;
  SQLHDBC dbc;
  SQLRETURN ret;

  //分配资源、建立连接
  SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
  SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
  SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);

  ret = SQLDriverConnect(dbc, NULL, "DSN=pgsql;", SQL_NTS,
						 NULL, 0, NULL,
						 SQL_DRIVER_COMPLETE);
  if (!SQL_SUCCEEDED(ret)) {
	  fprintf(stderr, "Failed to connect\n");
	  extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
	  return -1;
  }

  //程序逻辑
  double speed=0, hd=0, screen=0;
  get_query_param(&speed, &hd, &screen);
  query_show_laptop(dbc, speed, hd, screen);

  //释放资源
  SQLDisconnect(dbc);
  SQLFreeHandle(SQL_HANDLE_DBC, dbc);
  SQLFreeHandle(SQL_HANDLE_ENV, env);
  return 0;
}
