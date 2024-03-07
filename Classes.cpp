# include "Classes.h"  // Include the header file
# include <iostream>    // Include the standard I/O library

using namespace std;

// overloading << operator to print the table
ostream& operator<<(ostream& os, Terminal& table) {// os: output stream, table: table object
    table.print();
    return os;
}

// Callback function to handle query results
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    /*
    * NotUsed: A pointer to void, which is not used in this function
    * argc: The number of columns in the result
    * argv: An array of strings representing the row data
    * azColName: An array of strings representing the column names
    * The function returns 0 to continue the query, or non-zero to stop the query
    */

    Terminal t; // Create a terminal object;

    // print title
    cout << "\n\nPASSWORDS:\n";
    for(int i = 0; i < argc; i++) {
        // std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n"; // Print column name and value
        // convert char* to string vector and add to the table
        vector<string> s = {azColName[i], (argv[i] ? argv[i] : "NULL")};
        t.add_row(s);
    }
    cout<<t<<endl; // print the table
    return 0; // Return 0 to indicate successful handling
}

bool DataBase::open_connection(const char* db_name){
    // Open a SQLite database connection
    rc = sqlite3_open(db_name, &db); // rc is the result code, 0 means successful
    if (rc != SQLITE_OK) {  // Check if the database is opened successfully (SQLITE_OK is a macro for 0)
        cout << "Cannot open database: " << sqlite3_errmsg(db) << endl; // Print error message if failed
        sqlite3_close(db);   // Close the database connection
        return false;            // Return with error code
    } else {
        return true;
    }
}

bool DataBase::close_connection(){
    sqlite3_close(db);  // Close the database connection
    return true;
}

bool DataBase::execute_read_query(query sql, bool print){
    // Execute the SQL statement to select data and pass the callback function
    if (print){
        rc = sqlite3_exec(db, sql, callback, 0, &err_msg); 
    } else {
        rc = sqlite3_exec(db, sql, 0, 0, &err_msg); 
    }
    if (rc != SQLITE_OK ) {  // Check if SQL execution is successful
        cout << "Failed to select data\n"; // Print error message if failed
        cout << "SQL error: " << err_msg << "\n"; // Print SQL error message
        sqlite3_free(err_msg);    // Free the error message
        sqlite3_close(db);        // Close the database connection
        return false;                 // Return with error code
    }

    return true;
}

bool DataBase::execute_cud_query(query sql){
    // Execute the SQL statement to select data and pass the callback function
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg); 
    if (rc != SQLITE_OK ) {  // Check if SQL execution is successful
        cout << "Failed in CUD\n"; // Print error message if failed
        cout << "SQL error: " << err_msg << "\n"; // Print SQL error message
        sqlite3_free(err_msg);    // Free the error message
        sqlite3_close(db);        // Close the database connection
        return false;                 // Return with error code
    }

    return true;
};

string PasswordManager::encode(string password){
    string encoded_password = password;
    return encoded_password;
}

string PasswordManager::decode(string password){
    string decoded_password = password;
    return decoded_password;
}

bool PasswordManager::add_password(string username, string website, string password){

    DataBase db;    // Create a database object
    query db_name = "sqlite.db";   // Database name
    db.open_connection(db_name);    // Open a database connection

    query create_query = "CREATE TABLE IF NOT EXISTS PASSWORDS("  \
        "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," \
        "USERNAME           TEXT    NOT NULL," \
        "WEBSITE           TEXT    NOT NULL," \
        "PASSWORD       TEXT    NOT NULL);";  // SQL query to create a table

    string in_query = "INSERT INTO PASSWORDS (USERNAME, WEBSITE, PASSWORD) "  \
        "VALUES ('" + username + "', '" + website + "' ,'" + password + "');"; // SQL query to insert data

    query insert_query = in_query.c_str(); // convert string to const char*

    db.execute_cud_query(create_query); // Execute a SQL query
    db.execute_cud_query(insert_query); // Execute a SQL query
    db.close_connection();   // Close the database connection
    return true;
}

bool PasswordManager::get_password(string username, string website, bool print){
    DataBase db;    // Create a database object
    query db_name = "sqlite.db";   // Database name
    db.open_connection(db_name);    // Open a database connection

    // SQL query to select data where username and website match
    string s_query = "SELECT Username, Website, Password FROM PASSWORDS " \
        "WHERE USERNAME = '" + username + "' AND WEBSITE = '" + website + "';";

    query select_query = s_query.c_str(); // convert string to const char*

    bool res = db.execute_read_query(select_query, print); // Execute a SQL query

    db.close_connection();   // Close the database connection
    return res;
}

bool PasswordManager::remove_password(string username, string website){
    DataBase db;    // Create a database object
    query db_name = "sqlite.db";   // Database name
    db.open_connection(db_name);    // Open a database connection

    // SQL query to delete data where username and website match
    string d_query = "DELETE FROM PASSWORDS WHERE USERNAME = '" + username + "' AND WEBSITE = '" + website + "';";

    query delete_query = d_query.c_str(); // convert string to const char*

    db.execute_cud_query(delete_query); // Execute a SQL query

    db.close_connection();   // Close the database connection
    return true;
}

bool PasswordManager::update_password(string username, string website, string password){
    DataBase db;    // Create a database object
    query db_name = "sqlite.db";   // Database name
    db.open_connection(db_name);    // Open a database connection

    // SQL query to update data where username and website match
    string u_query = "UPDATE PASSWORDS SET PASSWORD = '" + password + "' WHERE USERNAME = '" + username + "' AND WEBSITE = '" + website + "';";

    query update_query = u_query.c_str(); // convert string to const char*

    db.execute_cud_query(update_query); // Execute a SQL query

    db.close_connection();   // Close the database connection
    return true;
}

bool PasswordManager::list_passwords(){
    DataBase db;    // Create a database object
    query db_name = "sqlite.db";   // Database name
    db.open_connection(db_name);    // Open a database connection

    // SQL query to select all data
    query select_all_query = "SELECT * FROM PASSWORDS;";

    db.execute_read_query(select_all_query); // Execute a SQL query

    db.close_connection();   // Close the database connection
    return true;
};

void Terminal::add_row(const vector<string>& row) {
    data.push_back(row); // Add the row to the data stack
    update_column_widths(row); // Update the column widths
}

void Terminal::print(){
    print_horizontal_line();
    for (const auto& row : data) { // Iterate through the data stack
        // auto is used to automatically determine the type of the variable
        print_row(row);
        print_horizontal_line();
    }
}

void Terminal::update_column_widths(const vector<string>& row) {
    if (column_widths.empty()) { // If the column widths are empty
        column_widths.resize(row.size(), 0); // Resize the column widths to the size of the row
    }

    for (size_t i = 0; i < row.size(); ++i) { // Iterate through the row
        if (row[i].size() > column_widths[i]) {
            column_widths[i] = row[i].size(); // Update the column width if the row size is greater
        }
    }
}

void Terminal::print_row(const vector<string>& row){
    cout << "| ";
    for (size_t i = 0; i < row.size(); ++i) {
        // setw is used to set the width of the output
        cout << setw(column_widths[i]) << left << row[i] << " | "; // left align the output
    }
    cout << endl;
}

void Terminal::print_horizontal_line(){
    cout << "+";
    for (size_t width : column_widths) {
        // string is used to create a string of a specific length
        cout << string(width + 2, '-') << "+";
    }
    cout << endl;
}