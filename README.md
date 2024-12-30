# Student Records Management System

## Overview
This program is a simple **Student Records Management System** written in C. It allows users to manage student information, including adding, listing, searching, deleting, and saving student records to a file. The program dynamically manages memory to handle an arbitrary number of student records.

## Features
- **Add Students**: Input a student's name, ID, and GPA.
- **List Students**: Display all students in a tabular format.
- **Search Students**: Find a student by their ID.
- **Delete Students**: Remove a student record by ID.
- **Save Records**: Save the student records to a file.
- **Load Records**: Load student records from an existing file.

## Program Flow
1. Load student records from `students.txt` at startup (if available).
2. Present a menu for the user to interact with:
    - Add a student.
    - Search for a student.
    - Delete a student.
    - List all students.
    - Save records to a specified file.
3. Save the student records to `students.txt` and exit on request.

## Usage

### Compile the Program
Use `gcc` to compile the program:
```bash
gcc -o student_records student_records.c
```

### Run the Program
Run the compiled program:
```bash
./student_records
```

### Menu Options
- **(0)** Save student records and exit.
- **(1)** Add a new student.
- **(2)** Search for an existing student.
- **(3)** Delete an existing student.
- **(4)** List all student records.
- **(5)** Save a copy of the student records to a new file.

### File Format
The program uses a simple CSV-like format for storing records:
```
Name, ID, GPA
John Doe, 123, 3.5
Jane Smith, 456, 3.8
```

## Implementation Details

### Data Structure
- **Student Structure**: Contains the name, ID, and GPA of a student.
```c
typedef struct {
    char name[50];
    int id;
    float gpa;
} Student;
```

- **Dynamic Array**: Manages students dynamically with `malloc` and `realloc`.

### Key Functions
- **`load_students(char *filename)`**: Loads student records from a file.
- **`add_student()`**: Adds a new student to the array.
- **`list_students()`**: Lists all students in a formatted table.
- **`save_students(char *filename)`**: Saves all student records to a file.
- **`search_student()`**: Searches for a student by ID.
- **`delete_student()`**: Deletes a student by ID and resizes the array.

### Memory Management
- Dynamically allocates memory for the student records using `malloc` and `realloc`.
- Frees memory when the program exits or when a student record is deleted.

## Sample Interaction
```
Welcome to the Student Records

(0) Save student records and exit
(1) Add a new student
(2) Search for an existing student
(3) Delete an existing student
(4) List all student records
(5) Save a copy of the student records
Your choice [1-5]: 1

Enter student name: John Doe
Enter student ID: 123
Enter student GPA: 3.7
Student was added successfully.
```

## Future Enhancements
- Add input validation for IDs and GPAs.
- Allow sorting of records by name, ID, or GPA.
- Support for exporting to other formats like JSON or XML.
- Enhance error handling for file operations.

## License
This project is open-source and available under the MIT License.

