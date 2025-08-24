# student-management-cpp
Console Student Management System in cpp (OOP+ file Handling)


# Student Management System (C++)

Console app to add/search/update/delete students, with CSV save/load.
- **Tech**: C++17, STL, file handling
- **Highlights**: O(1) lookup via `unordered_map`, clean CLI, persistence

## Build
```bash
cmake -S . -B build
cmake --build build
./build/student_mgmt



Roadmap

 Input validation + GPA range checks

 Sort & filter (by GPA/name)

 Import from CSV

 Basic tests