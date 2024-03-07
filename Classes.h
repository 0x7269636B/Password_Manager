#include <sqlite3.h>    // Include SQLite headers
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

typedef const char* query;

// Callback function to handle query results
static int callback(
    void *NotUsed, 
    int argc,  
    char **argv,
    char **azColName
);

class DataBase {
public:
    sqlite3 *db;        // SQLite database object
    char *err_msg = 0;  // Error message
    int rc;             // Result code
public:
    bool open_connection(const char * db_name);
    bool close_connection();
    bool execute_read_query(const char *sql, bool print = true);
    bool execute_cud_query(const char *sql);

};

class PasswordManager {
public:
    string encode(string password);
    string decode(string password);
    bool add_password(string username, string website, string password);
    bool remove_password(string username, string website);
    bool update_password(string username, string website, string password);
    bool get_password(string username, string website, bool print = true);
    bool list_passwords();
};

class Terminal {
private:
    vector<vector<string>> data;
    vector<size_t> column_widths;
public:
    Terminal() {}
    void add_row(const vector<string>& row);
    void print();
private:
    void update_column_widths(const vector<string>& row) ;
    void print_row(const vector<string>& row);
    void print_horizontal_line();
};