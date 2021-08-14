#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
using namespace std;

class account_query {
private:
    char account_number[20];
    char firstName[10];
    char lastName[10];
    float total_Balance;
public:
    void read_data();
    void show_data();
    void write_rec();
    void read_rec();
    void search_rec();
    void edit_rec();
    void delete_rec();
};
void account_query::read_data() {
    cout << "\nEnter Account Number: ";
    cin >> account_number;
    cout << "Enter First Name: ";
    cin >> firstName;
    cout << "Enter Last Name: ";
    cin >> lastName;
    cout << "Enter Balance: ";
    cin >> total_Balance;
    cout << endl;
}
void account_query::show_data() {
    cout << "Account Number: " << account_number << endl;
    cout << "First Name: " << firstName << endl;
    cout << "Last Name: " << lastName << endl;
    cout << "Current Balance: Rs.  " << total_Balance << endl;
    cout << "-------------------------------" << endl;
}
void account_query::write_rec() {
    ofstream outfile;
    outfile.open("record.bank", ios::binary | ios::app);
    read_data();
    outfile.write(reinterpret_cast < char * > (this), sizeof( * this));
    outfile.close();
}
void account_query::read_rec() {
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if (!infile) {
        cout << "Error in Opening! File Not Found!!" << endl;
        return;
    }
    cout << "======= Data From File =======\n" << endl;
    while (!infile.eof()) {
        if (infile.read(reinterpret_cast < char * > (this), sizeof( * this)) > 0) {
            show_data();
        }
    }
    infile.close();
    cout<<"\n\n";
    system("pause");
}
void account_query::search_rec() {
    int n = 1;
    ifstream infile;
    infile.open("record.bank", ios::binary);

    if (!infile) {
        cout << "\nError in opening! File Not Found!!" << endl;
        return;
    }
    infile.seekg(0, ios::end);
    int count = infile.tellg() / sizeof( * this);

    cout << "\n" << count << " records found in the file";
    char acc[20];

    cout << "\n\nEnter account Number to Search: ";
    cin >> acc;

    infile.seekg(0);
    infile.read(reinterpret_cast < char * > (this), sizeof( * this));

    while (n <= count) {
    if (strcmp(acc, account_number) == 0) {
            show_data();
            break;
        } else {
            n++;
            if (n > count)
                cout << "Wrong Account Number!!! \n";
            infile.seekg((n - 1) * sizeof( * this));
            infile.read(reinterpret_cast < char * > (this), sizeof( * this));
        }
    }

    cout<<"\n\n";
        system("pause");
}
void account_query::edit_rec() {
    char acc[20];
    fstream iofile;
    iofile.open("record.bank", ios:: in | ios::binary);
    if (!iofile) {
        cout << "\nError in opening! File Not Found!!" << endl;
        return;
    }
    iofile.seekg(0, ios::end);
    int count = iofile.tellg() / sizeof( * this);
    cout << "\nThere are " << count << " record in the file";
    cout << "\nEnter account Number to edit: ";
    cin >> acc;
    int n = 1;
    iofile.seekg((n - 1) * sizeof( * this));
    iofile.read(reinterpret_cast < char * > (this), sizeof( * this));

    while (n <= count) {
        if (strcmp(acc, account_number) == 0) {
            cout << "Account " << acc << " has following data" << endl;
            show_data();
            iofile.close();
            iofile.open("record.bank", ios::out | ios:: in | ios::binary);
            iofile.seekp((n - 1) * sizeof( * this));
            cout << "\nEnter data to Modify " << endl;
            read_data();
            iofile.write(reinterpret_cast < char * > (this), sizeof( * this));
            break;
        } else {
            n++;
            if (n > count)
                cout << "Wrong Account Number!!! \n";
            iofile.seekg((n - 1) * sizeof( * this));
            iofile.read(reinterpret_cast < char * > (this), sizeof( * this));
        }
    }
    cout<<"\n\n";
    system("pause");
}
void account_query::delete_rec() {
    int n;
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if (!infile) {
        cout << "\nError in opening! File Not Found!!" << endl;
        return;
    }
    infile.seekg(0, ios::end);
    int count = infile.tellg() / sizeof( * this);
    cout << "\n" << count << " records found in the file";
    cout << "\nEnter Record Number to Delete: ";
    cin >> n;
    fstream tmpfile;
    tmpfile.open("tmpfile.bank", ios::out | ios::binary);
    infile.seekg(0);
    for (int i = 0; i < count; i++) {
        infile.read(reinterpret_cast < char * > (this), sizeof( * this));
        if (i == (n - 1))
            continue;
        tmpfile.write(reinterpret_cast < char * > (this), sizeof( * this));
    }
    infile.close();
    tmpfile.close();
    remove("record.bank");
    rename("tmpfile.bank", "record.bank");
    cout<<"\n\n";
    system("pause");
}
int main() {
    account_query A;
    int choice;
    while (true) {
        system("clear");
        cout << "=============== Bank Management System ==============\n" << endl;
        cout << "Select one option below ";
        cout << "\n\t1. Add record to file";
        cout << "\n\t2. Show record from file";
        cout << "\n\t3. Search Record from file";
        cout << "\n\t4. Update Record";
        cout << "\n\t5. Delete Record";
        cout << "\n\t6. Quit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        system("clear");
        switch (choice) {
        case 1:
            A.write_rec();
            break;
        case 2:
            A.read_rec();
            break;
        case 3:
            A.search_rec();
            break;
        case 4:
            A.edit_rec();
            break;
        case 5:
            A.delete_rec();
            break;
        case 6:
            exit(0);
            break;
        default:
            cout << "\nEnter correct choice";
            exit(0);
        }
    }
    system("pause");
    return 0;
}
