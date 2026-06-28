#include <iostream>
#include <fstream>
#include <iomanip> //decimal points 
#include <string>
#include <algorithm> //built-in algorithum (sort,max/min,find)
#include <cctype> //toupper/tolower char
#include <cstring> //strlen/cpy
#include <limits>
#include<conio.h>  // ya character lata ha thaat shown ma na esa get_input aur to show menu again ka lia use kia ha ok
using namespace std;

const int subjects = 3;
const int max_students = 200;
//maximum student ka  record ke liye (200 students)
int get_input(); 

struct students {
  int id;
    string name;
    float marks [subjects];
    string subjectsname [subjects];
    float gpa;
    char grade;
};
// const int subjects = 6;
// const int max_students = 200; //maximum student ka  record ke liye (200 students),baad me const declare krne se struct ma use value error cause krty hn

void menu(){
    cout << "\n";
    cout << "====================================================\n";
    cout << "        STUDENT GRADEBOOK & RESULT ANALYZER\n";
    cout << "====================================================\n";
    cout << "  1. Add Student\n";
    cout << "  2. Display Students\n";
    cout << "  3. Compute GPA\n";
    cout << "  4. Sort by GPA\n";
    cout << "  5. Reports\n";
    cout << "  6. Search / Update / Delete Student\n";
    cout << "  7. Save Data\n";
    cout << "  8. Export Final Report\n";
    cout << "  9. Exit Program\n";
    cout << "----------------------------------------------------\n";
    cout << "Enter your choice (1 - 9): ";
}


void addStudent(students s[], int &n) {

    cout << "\n====================================\n";
    cout << "            ADD NEW STUDENT          \n";
    cout << "====================================\n";

    // ----------- ID Input (numeric only) -----------
    bool validID;
    do {
        validID = true;
        cout << "Student ID (numbers only): ";
        string idInput;
//idInput= get_input();
        cin >> idInput;
      //cin.ignore(1000);

       // Check if every character is a digit
        for (char c : idInput) {
            if (!isdigit(c)) {
                validID = false;
                cout << "Invalid input. ID must contain only numbers.\n";
                break;
            }
        }

        if (validID) {
            s[n].id = stoi(idInput);

            // Check uniqueness
            for (int i = 0; i < n; i++) {
                if (s[i].id == s[n].id) {
                    cout << " This ID already exists. Enter a unique ID.\n";
                    validID = false;
                    break;
                }
            }
        }
    } while (!validID);

 cin.ignore(); // Clear buffer after cin >> idInput

while (true) {
    cout << "Enter name of Student " << n+1<< " : ";
    getline(cin, s[n].name);

    bool valid = true;
    bool prevWasSpace = false;
    string tempName = s[n].name;
    
  // ya finish kray ga spaces ka lia ju keys use hoti hain unha triggerr spaces first
    size_t start = tempName.find_first_not_of(" \t\n\r\f\v");
    size_t end = tempName.find_last_not_of(" \t\n\r\f\v");
    
    if (start == string::npos) {
        valid = false;
    } else {
      tempName = tempName.substr(start, end - start + 1);
        
        // Process and validate har character ko
        for (char c : tempName) { // no use reference just check
            if (isalpha(c)) {
                prevWasSpace = false;
            } else if (c == ' ') {
                if (prevWasSpace) { // more than one spaces
                    valid = false;
                    break;
                }
                prevWasSpace = true;
            } else {
                valid = false; // Any other character
                break;
            }
        }
        
        // agr id store the finish name original case(name)store kray ga
        if (valid) {
            s[n].name;//temporary name
        }
    }

    if (valid && !s[n].name.empty()) {
        break; // valid input exit loop
    }

    cout << "Invalid!enter the name in letters(a-z)"<<endl<<endl;
    

}
    

    // ----------- Subject Names (alphabets only) -----------
    if (n == 0) {
        cout << "\nEnter Subject Names (a-z):\n";
        for (int i = 0; i < subjects; i++) {
            bool validSubject;
            do {
                validSubject = true;
                cout << "  Subject " << i + 1 << " : ";
                cin >> ws;
                getline(cin, s[n].subjectsname[i]);

                if (s[n].subjectsname[i].length() < 2) //only accept 2 minimum of a subject
                    validSubject = false;

                for (char c : s[n].subjectsname[i]) {
                    if (!isalpha(c) && c != ' ') validSubject = false;
                }

                if (!validSubject)
                    cout << "Invalid subject name Use only letters (a-z)\n";

            } while (!validSubject);
        }
    } else {
        for (int i = 0; i < subjects; i++)
            s[n].subjectsname[i] = s[0].subjectsname[i];
    }

    // ----------- Marks Input (numeric only) -----------
    cout << "\nEnter Marks (0-100):\n";
    for (int i = 0; i < subjects; i++) {
        bool validMark;
        do {
            validMark = true;
            cout << "  " << s[n].subjectsname[i] << " : ";
            string markInput;
            cin >> markInput;

            // Check if numeric
            for (char c : markInput) {
                if (!isdigit(c)) {
                    validMark = false;
                    cout << " Invalid input. Marks must be numeric.\n";
                    break;
                }
            }

            if (validMark) {
                int mark = stoi(markInput);
                if (mark < 0 || mark > 100) {
                    validMark = false;
                    cout << " Marks must be between 0 and 100.\n";
                } else {
                    s[n].marks[i] = mark;
                }
            }

        } while (!validMark);
    }

    n++;
    cout << "\nStudent record saved successfully.\n";
    cout << "====================================\n";
}


void displayStudents(students s[], int n) {
    int i = 0;
    while (i < n) {
       cout<<endl<< s[i].id << " " << s[i].name
             << " GPA: " << fixed << setprecision(2) << s[i].gpa // setpresision  2 values  decimal ke baad store krta h
             << " Grade: " << s[i].grade << endl;
        i++;
    }
    
}

float calculateGPA(float marks[]){
    float sum=0;
      for(int i=0 ; i< subjects ;i++) 

    sum= sum + marks[i];
 return (sum/(subjects*100))*4; //4 is used to define gpa

}
char assignGrade(float gpa){
    if(gpa>=3.8) return 'A';
    else if(gpa>=3.0) return 'B';
    
    else if(gpa>=2.5) return 'C';
      else if(gpa>=2.0) return 'D';
    else return 'F';
}

void computeResults(students s[], int n){
    for(int i=0 ; i<n ; i++ ) {
        s[i].gpa = calculateGPA(s[i].marks);
        s[i].grade = assignGrade(s[i].gpa);
    }
}

void sortByGPA(students s[], int n){ //students ku decending gpa k according arrange/sort krne k liye
    for(int i=0; i < n-1;i++) //used bubble sort.
        for(int j=i+1 ;j < n ;j++)
            if(s[j].gpa > s[i].gpa)
                swap(s[i], s[j]); //exchange value by compared the gpa of students  
} 
//i student name and j is for subjects


void generateTopperList(students s[], int n) {
    cout<<endl << "\n\t\t::::::::::     TOP STUDENTS          :::::::::::::::::\t\t"<<endl;
    ofstream topperFile("toppers.txt"); 
    topperFile << "\t\t\tTop Students\n\n";

    int topCount = (n < 3) ? n : 3; // Maximum 3 toppers

    for (int i = 0; i < topCount; i++) {
        // Display on screen
        cout << "Name: " << s[i].name 
             << " | GPA: " << fixed << setprecision(2) << s[i].gpa 
             << " | Grade: " << s[i].grade << endl;
        cout << "ID: " << s[i].id << endl;

        // Save to file with nice formatting
        topperFile << "-------------------------------------------\n";
        topperFile << "Name : " << s[i].name << "\n";
        topperFile << "ID   : " << s[i].id << "\n";
        topperFile << "GPA  : " << fixed << setprecision(2) << s[i].gpa << "\n";
        topperFile << "Grade: " << s[i].grade << "\n";

        topperFile << "Subject-wise marks:\n";
        for (int j = 0; j < subjects; j++) {
            topperFile << "   " << s[i].subjectsname[j] 
                       << " : " << s[i].marks[j] << "\n";
        }
        topperFile << "\n"; // extra space between students
    }

    topperFile.close();

}


void subjectWiseAverage(students s[], int n){
    if(n == 0){
        cout << "No students available."<<endl;
        return;
    }

    // cout << "\n--- Subject Wise Averages ---"<<endl;
    for(int j = 0; j < subjects; j++){ // Loop through each subject
        // sare subjects ki average hr student k marks k according ...
        float sum = 0;
        for(int i = 0; i < n; i++)      // Sum marks for that subject
            sum += s[i].marks[j];

        // Display using the subject name from the first student
        cout << s[0].subjectsname[j] 
             << " Average: " 
             << fixed << setprecision(2) 
             << sum / n << endl;
    }
}


void passFailRatio(students s[], int n){
    int pass=0;
    int fail=0;
    for(int i=0;i<n;i++)                // sutudents k grades se generate kare ga pass and fail hone wale bachon k number 
        if(s[i].grade =='F') fail++ ;  
        else pass++;
    cout << "Pass: " << pass << "  Fail: " << fail << endl;
}



void saveToFile(students s[], int n){
    ofstream file("students.txt"); // student data will be stored 
    file << "::::::::: Student Data :::::::::\n\n";

    for(int i = 0; i < n; i++){
        file << "ID: " << s[i].id << "\n";
        file << "Name: " << s[i].name << "\n";
        file << "GPA: " << fixed << setprecision(2) << s[i].gpa << "\n";
        file << "Grade: " << s[i].grade << "\n";
        file << "Subject-wise Marks:\n";
        for(int j = 0; j < subjects; j++){
            file << "   " << s[i].subjectsname[j] << ": " << s[i].marks[j] << "\n";
        }
        file << "-------------------------------\n\n";
    }

    file.close();
}


void loadFromFile(students s[], int &n){
    ifstream file("students.txt"); // the strudent data stored in student.txt
    n=0;
    while(file >> s[n].id >> s[n].name){
        for(int j=0;j<subjects;j++) file >> s[n].marks[j]; //data store krta h according to order
        n++;
    }
}



void exportReport(students s[], int n) {
    ofstream r("report.txt");
    if (!r) {
        cout << "Error opening report.txt!" << endl;
        return;
    }

     r << "\t\t\t ::::::::::::::         FINAL REPORT        :::::::::::::::: \t\t\t "<<endl<< endl;

    //  Number of failed students
    int failCount = 0;
    for (int i = 0; i < n; i++) {
        if (s[i].grade == 'F') failCount++;
    }
    r << "Number of students failed: " << failCount << "\n\n";

    //  Subject-wise averages
    r << "\t\t\t :::::::::::::: Subject-wise Average Marks  :::::::::::::::: \t\t\t "<<endl<<endl;
    for (int j = 0; j < subjects; j++) {
        float sum = 0;
        for (int i = 0; i < n; i++) sum += s[i].marks[j];
        r << s[0].subjectsname[j] << ": " << fixed << setprecision(2) << sum / n << "\n";
    }


    //  All students’ details
    r << "\n\t\t\t :::::::::::::      All Students Details    ::::::::::::::::\t\t\t" <<endl<<endl;

    for (int i = 0; i < n; i++) {
        r << "ID: " << s[i].id << " | Name: " << s[i].name 
          << " | GPA: " << fixed << setprecision(2) << s[i].gpa 
          << " | Grade: " << s[i].grade << "\n";
        r << "Subject-wise marks:"<<endl;
        for (int j = 0; j < subjects; j++)
            r << "   " << s[i].subjectsname[j] << ": " << s[i].marks[j] << "\n";
        r << "\n";
    }

    r.close();
}
// ye end py function is liye banaya h k jb user data delete kare ik student ka tu files se b uska data delete ho gye 
void searchAndUpdateStudent(students s[], int &n) { // n passed by reference
    int id;
    cout << "\nEnter Student ID to search: ";
    cin >> id;

    int index = -1;// linear search is used 
    for (int i = 0; i < n; i++) {
        if (s[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Student with ID " << id << " not found." << endl;
        return;
    }

    // Display current student information
    cout << "\t--- Student Information ---" << endl;
    cout << "ID: " << s[index].id << "\n";
    cout << "Name: " << s[index].name << "\n";
    for (int i = 0; i < subjects; i++)
        cout << s[index].subjectsname[i] << ": " << s[index].marks[i] << "\n";
    cout << "GPA: " << fixed << setprecision(2) << s[index].gpa << "\n";
    cout << "Grade: " << s[index].grade << "\n";

    // Ask user if they want to update marks or new marks add krne k liye 
    char choice;
    cout << "\nDo you want to update the marks of this student? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        // Update marks
        for (int i = 0; i < subjects; i++) {
            cout << "Enter new marks for " << s[index].subjectsname[i] << ": ";
            while (!(cin >> s[index].marks[i]) || s[index].marks[i] < 0 || s[index].marks[i] > 100) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid marks (0-100). Enter again: ";
            }
        }
        // Recompute GPA and grade
        s[index].gpa = calculateGPA(s[index].marks);
        s[index].grade = assignGrade(s[index].gpa);

        cout << "\nMarks updated successfully!" << endl;
        cout << "Updated GPA: " << s[index].gpa << ", Grade: " << s[index].grade << "\n";

        // Update all files after marks update
        saveToFile(s, n);
        exportReport(s, n);

        sortByGPA(s, n); // update toppers
        ofstream topperFile("toppers.txt");
        topperFile << "\t\t\tTop Students\n";
        int topCount = (n < 3) ? n : 3;
        for (int i = 0; i < topCount; i++) {
            topperFile << "ID: " << s[i].id << "\t | Name: " << s[i].name
                       << "\t | GPA: " << fixed << setprecision(2) << s[i].gpa
                       << "\t | Grade: " << s[i].grade << "\n";
            for (int j = 0; j < subjects; j++)
                topperFile << "   " << s[i].subjectsname[j] << ": " << s[i].marks[j] << "\n";
            topperFile << "\n";

        }
        topperFile.close();
    }

    // Ask user if they want to delete student after marks update or if they said no to update marks
    cout << "\nDo you want to delete this student? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        for (int i = index; i < n - 1; i++) {
            s[i] = s[i + 1]; // Shift students left
        }
        n--; // Reduce student count

        cout << "\nStudent deleted successfully!" << endl;

        // Update all files after deletion
        saveToFile(s, n);
        exportReport(s, n);

         // ager marks change kiye h ty it will recompute the gpa and grade
        sortByGPA(s, n); // update toppers
        ofstream topperFile("toppers.txt");
        topperFile << "\t\t\tTop Students\n";
        int topCount = (n < 3) ? n : 3;
        for (int i = 0; i < topCount; i++) {
            topperFile << "ID: " << s[i].id << " Name: " << s[i].name
                       << " GPA: " << fixed << setprecision(2) << s[i].gpa
                       << " Grade: " << s[i].grade << "\n";
            for (int j = 0; j < subjects; j++)
                topperFile << "   " << s[i].subjectsname[j] << ": " << s[i].marks[j] << "\n";
            topperFile << "\n";
        }
        topperFile.close();

        cout << "\nall files updated successfully  deletion" << endl;
    } else {
        cout << "\nNo deletion performed. Student information remains." << endl;
    }
}



int get_input()
{
    int input = 0;
    char ch = 0;
    int count = 0;

    while(true)
    {
        ch = _getch();
        bool valid = false;
        if(count > 0 && ch == 13){
            break;
        }
        if (ch == 8 && count > 0) {
            input /= 10;
            count--;
            cout << "\b \b";
            continue;
        }
        if((ch >= '0' && ch <='9')){
            count++;
            valid = true;
        }
        if(ch == 32){
            valid = false;
        }
        
        if(valid){
            int digit = ch - 48;
            input = (input * 10) + digit;
            cout << ch;
        }
    }
    return input;
}


bool isValidChoice(int choice) {
    return (choice >= 1 && choice <= 9);
}


int main() {
    students s[max_students];
    int n = 0, choice;

    cout << "\t\t\t\t============ PF FINAL THEPRY PROJECT ============== \t\t\t\t" << endl;
    cout << "\t\t\t\t============ NOOR FATIMA             ============== \t\t\t\t" << endl;
    cout << "\t\t\t\t============ ROLL-NO:2025-SE-512    =============== \t\t\t\t" << endl;

    loadFromFile(s, n); // Load existing data


        // Handle choices
        do{

        menu();
        choice = get_input();
        
        if (!isValidChoice(choice)) {
            cout << "\n Invalid choice! Please enter 1-9." << endl;
            cout << "Press enter key to continue...";
            cin.ignore();
           
        getchar();  //Wait for key press
            continue;  // wapis apna menu ko show krwa using continue for easyness
        }
        
        // Process valid choice...

        if(choice == 1) addStudent(s, n);

        else if(choice == 2){cout<<""<<endl;
             displayStudents(s, n);
            
         cout<<endl;

        }
        
        else if(choice == 3) {
            cout << "\n \nresults computed successfully.\t\t" << endl;
            computeResults(s, n);
            cout<<endl;
        }
        else if(choice == 4) {
            cout << "\n\n Data arranged according to GPA successfully\t\t";
            sortByGPA(s, n);
        }
        else if(choice == 5) {
            sortByGPA(s, n);  // Ensure students are sorted by GPA first
            generateTopperList(s, n);
            cout << "\t\t::::::::::  Average of every subject :::::::::::::::::\t\t" << endl;
            subjectWiseAverage(s, n);
            cout << "\t\t::::::::::  Pass and Fail students   :::::::::::::::::\t\t" << endl;
            passFailRatio(s, n);
        }
        else if(choice == 6) searchAndUpdateStudent(s, n);
        else if(choice == 7) {
            cout << "\nThe data is saved successfully to the file." << endl;
            saveToFile(s, n);
        }
        else if(choice == 8) {
            cout <<"\n Result generated successfully.\n";
            exportReport(s, n);
        }

    } while(choice != 9);

    saveToFile(s, n);
    cout << "\nData saved. Program terminated." << endl;
    cout << "Students grade book is generated successfully." << endl<<endl;
    cout<<"::::::::::::::::::(bye,bye!!)::::::::::::::::::"<<endl;


    return 0;
}