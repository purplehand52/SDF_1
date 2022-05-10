#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Course{
 private:
  string name;
  string ID;
  string instrID;
  friend ostream& operator << (ostream& outfile, const Course& sample);
  friend istream& operator >> (istream& infile, Course& sample);
  friend class Admin;
 public:
  bool floating;
  //Return Attributes
  string returnID();
  string returnInstrID();
  //Change Floating
  void switchFloating(string C_ID);
  //File Name
  string genFileName();
  //Access
  void putCourseFile();
  void tempCourseFile();
  //Details
  void getCourseDetails();
  void printCourseDetails();
  //Add, Show, Find, Delete
  void addCourse();
  void showAllCourses();
  int findCourse(string C_Name);
  void delCourse(string C_Name);	
};

class Person{
 private:
  friend ostream& operator << (ostream& outfile, const Person& sample);
  friend istream& operator >> (istream& infile, Person& temp);
 protected:
  string name;
  string ID;
  string password;
  //Access
  virtual void putPersonFile() = 0;
  virtual void tempPersonFile() = 0;
  //Details
  void getPersonDetails();
  void printPersonDetails();
  //Add, Show, Find, Delete
  virtual void addPerson() = 0;	
  virtual void showAllPerson() = 0;
  virtual int findPerson(string C_Name) = 0;
  virtual void delPerson(string C_Name) = 0;
 public:
  int chkPassword();
};

class Admin : public Person{
 public:
  //Add Course
  //Delete Course
  //Float*/Unfloat*
  //View Course
  void CourseManager();
  
  //Add Student
  //Delete Student
  //View Student
  void StudentManager();
  
  //Add Faculty
  //Delete Faculty
  //View Faculty
  void FacultyManager();
  
  //Add Admin
  //Delete Admin
  //View Admin
  void AdminManager();
  
  //Simple Constructor
  Admin(){
  
  }
  
  //Advanced Constructor
  Admin(string &myName, string &myID, string &myPassword){
   name = myName;
   ID = myID;
   password = myPassword;
  }
  
  void putPersonFile();
  void tempPersonFile();
  void addPerson();
  void showAllPerson();
  int findPerson(string C_Name);
  void delPerson(string C_Name);
  
  /*Add Student to Course
  Remove Student from Course*/
};

class Faculty : public Person{
 private:
  bool chkCourse(string C_ID);
 public:
  void putPersonFile();
  void tempPersonFile();
  void addPerson();
  void showAllPerson();
  int findPerson(string C_Name);
  void delPerson(string C_Name);
  
  //Look Courses
  void seeCourses();
  //Look Students
  void seeStudents();
  //Submit Grades
  void updateGrades();
};

class Student : public Person{
 public:
  void putPersonFile();
  void tempPersonFile();
  void addPerson();
  void showAllPerson();
  int findPerson(string C_Name);
  void delPerson(string C_Name);
  
  //Register Courses
  void registerCourse();
  //Deregister Courses
  void deregisterCourse();
  //See Grades
  void seeGrades();
  void CoursePortal();
};

int findReport(string FileName, string C_Name);

