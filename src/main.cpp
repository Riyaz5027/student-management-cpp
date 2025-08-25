#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct student
{
    /* data */
    int id{};
    string name{};
    string cls;
    double gpa{};
};
void print_menu()
{
    cout << "\n=== Student Management System ===\n";
    cout << "1) Add Student\n";
    cout << "2) List Students\n";
    cout << "3) Find by id\n";
    cout << "4) Update student\n";
    cout << "5) Delete student\n";
    cout << "6) Save to file\n";
    cout << "7) Load from file\n";
    cout << "0) Exit\n> ";
}
int main()
{
    vector<student> db;
    unordered_map<int, size_t> idx; // id -> position for o(1) lookup

    auto rebuild_index = [&]() { // To avoid any mismatch for arrays
        idx.clear();
        for (size_t i = 0; i < db.size(); ++i)
        {
            idx[db[i].id] = i;
        }
    };

    auto save = [&]()
    {
        ofstream out("students.csv");
        if (!out)
        {
            cerr << "Cannot open file.\n";
            return;
        }
        out << "id,name,class,gpa\n";
        for (auto &s : db)
            out << s.id << ',' << quoted(s.name) << ',' << quoted(s.cls) << ',' << s.gpa << '\n';
        cout << "Saved " << db.size() << " students.\n";
    };

    auto load = [&]()
    {
        ifstream in("students.csv");
        if (!in)
        {
            cerr << "No file found; start fresh.\n";
            return;
        }
        db.clear();
        string header;
        getline(in, header);
        string line;
        while (getline(in, line))
        {
            stringstream ss(line);
            student s;
            char comma;
            ss >> s.id >> comma >> quoted(s.name) >> comma >> quoted(s.cls) >> comma >> s.gpa;
            db.push_back(s);
        }
        rebuild_index();
        cout << "Loaded " << db.size() << " students.\n";
    };

    int choice;
    do
    {
        print_menu();
        if (!(cin >> choice))
            break;

        if (choice == 1)
        {
            student s;
            cout << "id: ";
            cin >> s.id;
            if (idx.count(s.id))
            {
                cout << "id exists.\n";
                continue;
            }
            cout << "name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, s.name);
            cout << "class: ";
            getline(cin, s.cls);
            cout << "gpa: ";
            cin >> s.gpa;
            db.push_back(s);
            idx[s.id] = db.size() - 1;
            cout << "Added.\n";
        }
        else if (choice == 2)
        {
            for (auto &s : db)
                cout << s.id << " | " << s.name << " | " << s.cls << " | " << s.gpa << "\n";
        }
        else if (choice == 3)
        {
            int id;
            cout << "id: ";
            cin >> id;
            if (!idx.count(id))
            {
                cout << "not found.\n";
                continue;
            }
            auto &s = db[idx[id]];
            cout << s.id << " | " << s.name << " | " << s.cls << " | " << s.gpa << "\n";
        }
        else if (choice == 4)
        {
            int id;
            cout << "id: ";
            cin >> id;
            if (!idx.count(id))
            {
                cout << "not found.\n";
                continue;
            }
            auto &s = db[idx[id]];
            cout << "new name (enter to skip): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string line;
            getline(cin, line);
            if (!line.empty())
                s.name = line;
            cout << "new class (enter to skip): ";
            getline(cin, line);
            if (!line.empty())
                s.cls = line;
            cout << "new gpa (-1 to skip): ";
            double g;
            cin >> g;
            if (g >= 0)
                s.gpa = g;
            cout << "Updated.\n";
        }
        else if (choice == 5)
        {
            int id;
            cout << "id: ";
            cin >> id;
            if (!idx.count(id))
            {
                cout << "not found.\n";
                continue;
            }
            size_t pos = idx[id];
            db.erase(db.begin() + pos);
            rebuild_index();
            cout << "Deleted.\n";
        }
        else if (choice == 6)
        {
            save();
        }
        else if (choice == 7)
        {
            load();
        }
    } while (choice != 0);

    cout << "Bye!\n";

    return 0;
}