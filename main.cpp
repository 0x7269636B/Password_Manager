#include "Classes.cpp"

#define ADMIN "__admin__"
#define ADMIN_PASSWORD "1234"

using namespace std;

void generate_db_data() {
    PasswordManager pm; // Create a password manager object

    pm.add_password("user1", "website1", "1234"); // Add a password
    pm.add_password("user2", "website2", "5678"); // Add a password
    pm.add_password("user3", "website3", "91011"); // Add a password
    pm.add_password("user4", "website4", "121314"); // Add a password
    pm.add_password("user5", "website5", "151617"); // Add a password
    pm.add_password("user6", "website6", "181920"); // Add a password
    pm.add_password("user7", "website7", "212223"); // Add a password
    pm.add_password("user8", "website8", "242526"); // Add a password
    pm.add_password("user9", "website9", "272829"); // Add a password
    pm.add_password("user10", "website10", "303132"); // Add a password
    pm.add_password("user11", "website11", "333435"); // Add a password
    pm.add_password("user12", "website12", "363738"); // Add a password
    pm.add_password("user13", "website13", "394041"); // Add a password
    pm.add_password("user14", "website14", "424344"); // Add a password
    pm.add_password("user15", "website15", "454647"); // Add a password
    pm.add_password("user16", "website16", "484950"); // Add a password
    pm.add_password("user17", "website17", "515253"); // Add a password
    pm.add_password("user18", "website18", "545556"); // Add a password
    pm.add_password("user19", "website19", "575859"); // Add a password
    pm.add_password("user20", "website20", "606162"); // Add a password
}

int main() {

    // generate_db_data();

    // authenticate admin __admin__
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    PasswordManager pm;

    if (username == ADMIN && password == ADMIN_PASSWORD){
        cout<<"Admin authenticated successfully"<<endl;
    } else {
        cout<<"Admin authentication failed"<<endl;
        return 0;
    }

    bool running = true;

    while (running) {

        // create a menu
        cout << "\n       Menu:" << endl;
        cout << "1. Add a password" << endl;
        cout << "2. Remove a password" << endl;
        cout << "3. Update a password" << endl;
        cout << "4. Get a password" << endl;
        cout << "5. List all passwords" << endl;
        cout << "6. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: { // Add a password
                string username, website, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter website: ";
                cin >> website;
                cout << "Enter password: ";
                cin >> password;
                PasswordManager pm;
                pm.add_password(username, website, password);
                cout<<"Password added successfully"<<endl;
                break;
            }
            case 2: { // Remove a password
                string username, website;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter website: ";
                cin >> website;
                PasswordManager pm;
                pm.remove_password(username, website);
                cout<<"Password removed successfully"<<endl;
                break;
            }
            case 3: { // Update a password
                string username, website, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter website: ";
                cin >> website;
                cout << "Enter password: ";
                cin >> password;
                PasswordManager pm;
                pm.update_password(username, website, password);
                cout<<"Password updated successfully"<<endl;
                break;
            }
            case 4: { // Get a password
                string username, website;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter website: ";
                cin >> website;
                PasswordManager pm;
                pm.get_password(username, website, true);
                // cout<<"Password retrieved successfully"<<endl;
                break;
            }
            case 5: { // List all passwords
                // generate_db_data();
                PasswordManager pm;
                pm.list_passwords();
                // cout<<"Password list retrieved successfully"<<endl;
                break;
            }
            case 6: { // Exit
                running = false;
                cout << "Exiting..." << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Acceptable choices are 1-6." << endl;
                break;
            }
        }
    }
    return 0;   // Return 0 to indicate successful completion
}