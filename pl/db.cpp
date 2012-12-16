#include <db_cxx.h>
#include <iostream>
#include <string>
#include <memory.h>

using namespace std;

class MyDb {
    public:
        MyDb() = delete;
        MyDb(std::string& path, std::string& dbName);

        ~MyDb() { close(); }

        Db& getDb() { return m_db; }

    private:
        Db m_db;
        std::string m_dbname;
        u_int32_t m_flags;
        void close();
};


MyDb::MyDb(std::string& path, std::string& dbName)
    : m_db(NULL, 0),
    m_dbname(path + dbName),
    m_flags(DB_CREATE)
{
    try {
        m_db.set_error_stream(&std::cerr);
        m_db.open(NULL, m_dbname.c_str(), NULL, DB_BTREE, m_flags, 0);
    } catch (DbException& e) {
        std::cerr << "Error opening database: " << m_dbname << std::endl;
        std::cerr << e.what() << endl;
    } catch (std::exception& e) {
        std::cerr << "Error opening database: " << m_dbname << std::endl;
        std::cerr << e.what() << endl;
    }
}

void MyDb::close() 
{
    try {
        m_db.close(0);
        cout << "Database " << m_dbname << " is closed." << endl;
    } catch (DbException& e) {
        cerr << "Error closing database: " << m_dbname << endl;
        cerr << e.what() << endl;
    } catch (std::exception& e) {
        cerr << "Error closing database: " << m_dbname << endl;
        cerr << e.what() << endl;
    }
}

int main()
{
    string path = "./";
    string name = "snyh.db";
    MyDb db(path, name);

    db.getDb().stat_print(DB_STAT_ALL);

    double money = 122.34;
    char* description = "Grocery bill.";

    Dbt key(&money, sizeof(money));
    Dbt data(description, strlen(description) + 1);

    int ret = db.getDb().put(NULL, &key, &data, DB_NOOVERWRITE);
    if (ret == DB_KEYEXIST) {
        db.getDb().err(ret, "Put failed because key %lf alerady exists", money);
    }
}
