#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student structure
typedef struct {
    char name[50];
    int id;
    float gpa;
} Student;

// Global variables
int maxStudents = 10;
Student* students;
int studentCount = 0;

// Function prototypes
void add_student();
void load_students(char *filename);
void list_students();
void save_students(char *filename);
void search_student();
void delete_student();

/*
    Main Function
    Interface for users to interact with the students records
    Users can add, delete, search and list students and save student records
 */
int main(void)
{
    // Allocate memory for students array
    students = (Student*) malloc(maxStudents * sizeof(Student));
    if (students == NULL) {
        printf("Memory not allocated for database.\n");
        return 1;
    }
    
    // Load in database
    load_students("students.txt");

    // Main program start
    printf("Welcome to the Student Records\n");

    while(1)
    {
        // Prints choices
        printf("\n(0) Save student records and exit\n");
        printf("(1) Add a new student\n");
        printf("(2) Search for an existing student\n");
        printf("(3) Delete an existing student\n");
        printf("(4) List all student records\n");
        printf("(5) Save a copy of the student records\n");

        // User input
        printf("Your choice [1-5]: ");
        int mainMenu;
        scanf("%d", &mainMenu);
	printf("\n");

        // Checks input
        switch(mainMenu)
        {
            // Saves and Exits
            case 0: 
                save_students("students.txt");
		free(students);
                exit(0);
                break;
            // Add new student
            case 1: 
                add_student();
                break;
            // Search for student
            case 2:
                search_student();
                break;
            // Delete existing student
            case 3:
                delete_student();
                break;
            // List all students
            case 4:
                list_students();
                break;
            // Save copy of records
            case 5:
                printf("Enter new file name for records to be copied to: ");
                char file[20];
                scanf("%19s", file); 
                save_students(file);
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}

/*
    Load Students
    Reads contents of file and load into memory
 */
void load_students(char *filename)
{
    FILE *file;
    file = fopen(filename, "r");

    // File cannot be opened
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    // Load info into memory
    while (fscanf(file, "%49[^,], %d, %f\n", students[studentCount].name, &students[studentCount].id, &students[studentCount].gpa) == 3)
    {
        studentCount++;
        if (studentCount >= maxStudents)
        {
            students = (Student*)realloc(students, (maxStudents + 1) * sizeof(Student));
      
            if (students == NULL) {
                printf("Not enough memory, some records are cannot be loaded in.\n");
                return;
            }

            maxStudents++;
        }
    }

    fclose(file);
}

/*
    Add Student
    Allows user to input a student's name, ID and GPA to be added to the system
*/
void add_student()
{
    // Check if memory allocation is needed
    if (students == NULL) {
        students = malloc(maxStudents * sizeof(Student));
        if (students == NULL) {
            printf("Memory allocation failed. Cannot add student.\n");
            return;
        }
    }

    // Checks to see if capacity is reached
    if (studentCount >= maxStudents)
    {
        students = (Student*)realloc(students, (maxStudents + 1) * sizeof(Student));
    
        if (students == NULL) {
            printf("Not enough memory, cannot add student.\n");
            return;
        }

        maxStudents++;
    }

    // User enters student info
    printf("Enter student name: ");
    getchar(); // Consume leftover newline
    fgets(students[studentCount].name, sizeof(students[studentCount].name), stdin); // User input
    students[studentCount].name[strcspn(students[studentCount].name, "\n")] = '\0'; // Remove newline

    printf("Enter student ID: ");
    scanf("%d", &students[studentCount].id);

    printf("Enter student GPA: ");
    scanf("%f", &students[studentCount].gpa);

    // Success!
    studentCount++;
    printf("Student was added successfully.\n");
}

/*
    List Students
    Formats all students saved in database in a table
*/
void list_students()
{
    printf("%-50s | %-10s | GPA\n", "NAME", "ID");
    for (int i = 0; i < studentCount; i++)
    {
        printf("%-50s | %-10d | %.2f\n", students[i].name, students[i].id, students[i].gpa);
    } 
}

/*
    Save Students
    Saves list of students to given filename
*/
void save_students(char *filename)
{
    FILE *file;
    file = fopen(filename, "w");

    // File cannot be opened
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    // Saves each student to the file
    for (int i = 0; i < studentCount; i++)
    {
        fprintf(file, "%s, %d, %.2f\n", students[i].name, students[i].id, students[i].gpa);
    } 

    // Success!
    fclose(file);
    printf("File saved successfully.\n");
}

void search_student()
{
    int id;

    printf("Enter the ID of the student to search: ");
    scanf("%d", &id);

    // Searches for student
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Student Found:\n");
            printf("Name: %s, ID: %d, GPA: %.2f\n", students[i].name, students[i].id, students[i].gpa);
            return;
        }
    }

    printf("No student with ID %d found.\n", id);
}

void delete_student()
{
    int id;

    printf("Enter the ID of the student to delete: ");
    scanf("%d", &id);

    // Searches for student
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
	    if (studentCount == 1)
	    {
		free(students); // No students left after deletion
		students = NULL;	
	    }
	    else
	    {

             	// Shift students to delete
                for (; i < studentCount - 1; i++) {
                    students[i] = students[i + 1];
            	}

	    	// Resize the array using realloc (using a temp array first)
          	Student *temp = realloc(students, (studentCount - 1) * sizeof(Student));
            	if (temp == NULL) {
                    printf("Memory reallocation failed. Unable to delete student.\n");
                    return;
            	}
	    	students = temp;
	    }

            // Success!
            studentCount--;
            printf("Student deleted.\n");
            return;
        }
    }

    printf("No student with ID %d found.\n", id);
}
