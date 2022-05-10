#include "classes.h"
#include <iostream>
#include <fstream>
#define PROP_COURSE 4
#define PROP_PERSON 3

//COURSES--------------------------------
string Course :: returnID(){
  return(ID);
}

string Course :: returnInstrID(){
  return(instrID);
}

void Course :: switchFloating(string C_ID){
  //Find Course
  findCourse(C_ID);
  
  //Get floating Value
  bool newFloating;
  cout << "Enter floating (1 -> Yes, 0 -> No): ";
  cin >> newFloating;

  //Copy of original course
  Course copy = *this;
  copy.floating = newFloating;
  delCourse(ID);
  copy.putCourseFile();
}

void Course :: getCourseDetails(){
  cin.ignore();
  cout << "ID: ";
  getline(cin, ID);

  cout << "Name: ";
  getline(cin, name);

  cout << "Instructor ID: ";
  getline(cin, instrID);
  
  cout << "Floating (1 for Yes, 0 for No): ";
  cin >> floating;

}

void Course :: printCourseDetails(){
  cout << "----------------COURSE DETAILS--------------------" << endl;
  cout << "ID: " << ID << endl;
  cout << "Name: " << name << endl;
  cout << "Instructor ID: " << instrID << endl;
  cout << "Floating: " << floating << endl;
  cout << "--------------------------------------------------" << endl;
}

string Course :: genFileName(){
  string path = ID;
  string ext = ".txt";
  string filepath = path + ext;
  return filepath;
}

ostream& operator << (ostream& outfile, const Course& sample){
  //ID
  outfile << sample.ID;
  outfile << "\n";

  //Name
  outfile << sample.name;
  outfile << "\n";

  //Instructor ID
  outfile << sample.instrID;
  outfile << "\n";
  
  //Floating
  outfile << sample.floating;
  outfile << "\n";

  return(outfile);
}

istream& operator >> (std::istream& infile, Course& sample){
  //Get
  getline(infile, sample.ID);
  getline(infile, sample.name);
  getline(infile, sample.instrID);
  infile >> sample.floating;
  infile.ignore();  

  //Return
  return(infile);
}

void Course::putCourseFile(){
  Faculty temp;
  int exist = temp.findPerson(instrID);
  if(exist){
    ofstream ofs("Sample.bin",ios::out|ios::binary|ios::app);
    ofs << *this;
    
    string filepath = genFileName();
    ofstream ofsnew;
    ofsnew.open(filepath, ios::out);
    ofsnew.close();
    
    cout << "Course details initialised/updated successfully..." << endl;
  }
  else{
    cout << "The faculty to teach this course does not exist" << endl;
  }
}
void Course::tempCourseFile(){
  ifstream ifs("Sample.bin",ios::in|ios::binary);
  ifs >> *this;
}

void Course::addCourse(){
   getCourseDetails();
   putCourseFile();
}

void Course::showAllCourses(){
  ifstream ifs("Sample.bin",ios::in|ios::binary);
  while(!ifs.eof()){
    if(ifs >> *this){
      printCourseDetails();
    }
  }
  ifs.close();
}

int Course:: findCourse(string C_Name){
  int found = 0;
  ifstream ifs("Sample.bin",ios::in|ios::binary);
  while(!ifs.eof()){
    if(ifs >> *this){
      if(ID == C_Name){
	cout << "Record Found" << endl;
	//printCourseDetails();
	return(PROP_COURSE*found + 1);
      }
      found++;
    }
  }
  cout << "Record not found!" << endl;
  return(0);
}

void Course:: delCourse(string C_Name){
  int found = findCourse(C_Name);
  if (found){
    //Delete
    string line;
    ofstream ofs("Replace.bin", ios::out|ios::binary);
    ifstream ifs("Sample.bin", ios::in|ios::binary);
    while(!ifs.eof()){
      if(ifs >> *this){
	if(!(ID == C_Name) ){
	  ofs << *this;
	}
      }
    }

    //Rename
    remove("Sample.bin");
    rename("Replace.bin", "Sample.bin");
    
    //Remove associated file (convert string to characters to insert into filename)
    remove(genFileName().c_str());
  }
}

//ADMIN
void Admin::CourseManager(){
  cout << "Welcome Admin " << name << endl;
  cout << "Choose options to continue... " << endl;
  int choice;
  cout << "1. Add Course" << endl;
  cout << "2. Show all Courses" << endl;
  cout << "3. Find Course" << endl;
  cout << "4. Delete Course" << endl;
  cout << "5. Update Course's Floating Status" << endl;
  cout << "Enter any other integer to exit..." << endl;

  cin >> choice;

  Course temp;
  
  switch(choice){
  case(1):
    temp.addCourse();
    break;
  case(2):
    temp.showAllCourses();
    break;
  case(3):
    {
      cout << "Enter CourseID: ";
      string tempID;
      cin.ignore();
      getline(cin, tempID);
      temp.findCourse(tempID);
      break;
    }
  case(4):
    {
      cout << "Enter CourseID: ";
      string tempID;
      cin.ignore();
      getline(cin, tempID);
      temp.delCourse(tempID);
      break;
    }
  case(5):
    {
      cout << "Enter CourseID: ";
      string tempID;
      cin.ignore();
      getline(cin, tempID);
      temp.switchFloating(tempID);
      break;
    }
  default:
    cout << "Exiting...." << endl;
  }
}

//PERSON----------------------------------------------------------
void Person :: getPersonDetails(){
  cin.ignore();
  
  cout << "ID: ";
  getline(cin, ID);
  
  cout << "Name: ";
  getline(cin, name);
    
  cout << "Password: ";
  getline(cin, password);
  
  cout << "Person details initialised/updated successfully..." << endl;
}

void Person :: printPersonDetails(){
  cout << "----------------PERSON DETAILS--------------------" << endl;
  cout << "ID: " << ID << endl;
  cout << "Name: " << name << endl;
  cout << "--------------------------------------------------" << endl;
}

int Person :: chkPassword(){
  //Get input
  string temp;
  cout << "Enter current password: ";
  getline(cin, temp);
  cin.ignore();

  //Compare
  if(!temp.compare(password)) return(1);
  else return(0);
}

ostream& operator << (ostream& outfile, const Person& sample){
  //ID
  outfile << sample.ID;
  outfile << '\n';

  //Name
  outfile << sample.name;
  outfile << '\n';

  //Password
  outfile << sample.password;
  outfile << '\n';
  
  return(outfile);
}

istream& operator >> (istream& infile, Person& temp){
  //Get
  getline(infile, temp.ID);
  getline(infile, temp.name);
  getline(infile, temp.password);

  //Return
  return(infile);

}

//ADMIN-------------------------------------------------
void Admin::putPersonFile(){
  ofstream ofs("Admin.bin",ios::out|ios::binary|ios::app);
  ofs << *this;
}

void Admin::tempPersonFile(){
  ifstream ifs("Admin.bin",ios::in|ios::binary|ios::app);
  ifs >> *this;
}

void Admin::addPerson(){
  getPersonDetails();
  putPersonFile();
}

void Admin::showAllPerson(){
  int i = 0;
  string buffer;
  ifstream ifs("Admin.bin",ios::in|ios::binary);
  while(!ifs.eof()){
    if(ifs >> *this){
      printPersonDetails();
    }
  }
  ifs.close();
}

int Admin::findPerson(string C_Name){
  int found = 0;
  ifstream ifs("Admin.bin",ios::in|ios::binary);
  while(!ifs.eof()){
    if(ifs >> *this){
      if(ID == C_Name){
	cout << "Record Found" << endl;
	return(PROP_PERSON*found + 1);
      }
      found++;
    }
  }
  cout << "Record not found!" << endl;
  return(0);
}

void Admin::delPerson(string C_Name){
  int found = findPerson(C_Name);
  if (found){
    //Delete
    string line;
    ofstream ofs("Replace.bin", ios::out|ios::binary);
    ifstream ifs("Admin.bin", ios::in|ios::binary);
    while(!ifs.eof()){
      if(ifs >> *this){
	if(!(ID == C_Name) ){
	  ofs << *this;
	}
      }
    }

    //Rename
    remove("Admin.bin");
    rename("Replace.bin", "Admin.bin");
  }
}

void Admin:: AdminManager(){
 cout << "Welcome Admin " << name << endl;
  cout << "Choose options to continue... " << endl;
  int choice;
  cout << "1. Add Admin" << endl;
  cout << "2. Show all Admin" << endl;
  cout << "3. Find Admin" << endl;
  cout << "4. Delete Admin" << endl;
  cout << "Enter any other integer to exit..." << endl;

  cin >> choice;

  Admin temp;
  
  switch(choice){
  case(1):
    temp.addPerson();
    break;
  case(2):
    temp.showAllPerson();
    break;
  case(3):
    {
    cout << "Enter AdminID: ";
    string tempID;
    cin >> tempID;
    temp.findPerson(tempID);
    break;
    }
  case(4):
    {
    cout << "Enter AdminID: ";
    string tempID;
    cin >> tempID;
    temp.delPerson(tempID);
    break;
    }
  default:
    cout << "Exiting...." << endl;
  }
}

//FACULTY----------------------------------
void Faculty::putPersonFile(){
  ofstream ofs("Faculty.bin",ios::out|ios::binary|ios::app);
  ofs << *this;
}

void Faculty::tempPersonFile(){
  ifstream ifs("Faculty.bin",ios::in|ios::binary|ios::app);
  ifs >> *this;
}

void Faculty::addPerson(){
  getPersonDetails();
  putPersonFile();
}

void Faculty::showAllPerson(){
  int i = 0;
  string buffer;
  ifstream ifs("Faculty.bin",ios::in|ios::binary);
  while(!ifs.eof()){
    if(ifs >> *this){
      printPersonDetails();
    }
  }
  ifs.close();
}

int Faculty::findPerson(string C_Name){
  int found = 0;
  ifstream ifs("Faculty.bin",ios::in|ios::binary);
  while(!ifs.eof()){
    if(ifs >> *this){
      if(ID == C_Name){
	cout << "Record Found" << endl;
	printPersonDetails();
	return(PROP_PERSON*found + 1);
      }
      found++;
    }
  }
  cout << "Record not found!" << endl;
  return(0);
}

void Faculty::delPerson(string C_Name){
  int found = findPerson(C_Name);
  
  if(found){
    //Delete
    ofstream ofs("Replace.bin", ios::out|ios::binary);
    ifstream ifs("Faculty.bin", ios::in|ios::binary);
    while(!ifs.eof()){
      if(ifs >> *this){
	if(!(ID == C_Name)){
	  ofs << *this;
	}
      }
    }

    //Rename
    remove("Faculty.bin");
    rename("Replace.bin", "Faculty.bin");
  }
}

void Admin:: FacultyManager(){
 cout << "Welcome Admin " << name << endl;
  cout << "Choose options to continue... " << endl;
  int choice;
  cout << "1. Add Faculty" << endl;
  cout << "2. Show all Faculty" << endl;
  cout << "3. Find Faculty" << endl;
  cout << "4. Delete Faculty" << endl;
  cout << "Enter any other integer to exit..." << endl;

  cin >> choice;

  Faculty temp;
  
  switch(choice){
  case(1):
    temp.addPerson();
    break;
  case(2):
    temp.showAllPerson();
    break;
  case(3):
    {
    cout << "Enter FacultyID: ";
    string tempID;
    cin >> tempID;
    temp.findPerson(tempID);
    break;
    }
  case(4):
    {
    cout << "Enter FacultyID: ";
    string tempID;
    cin >> tempID;
    temp.delPerson(tempID);
    break;
    }
  default:
    cout << "Exiting...." << endl;
  }
}

//STUDENT--------------------------------
void Student::putPersonFile(){
  ofstream ofs("Student.bin",ios::out|ios::binary|ios::app);
  ofs << *this;
}

void Student::tempPersonFile(){
  ifstream ifs("Student.bin",ios::in|ios::binary|ios::app);
  ifs >> *this;
}

void Student::addPerson(){
  getPersonDetails();
  putPersonFile();
}

void Student::showAllPerson(){
  int i = 0;
  string buffer;
  ifstream ifs("Student.bin",ios::in|ios::binary);
  while(!ifs.eof()){
    if(ifs >> *this){
      printPersonDetails();
    }
  }
  ifs.close();
}

int Student::findPerson(string C_Name){
  int found = 0;
  ifstream ifs("Student.bin",ios::in|ios::binary);
  while(!ifs.eof()){
    if(ifs >> *this){
      if(ID == C_Name){
	cout << "Record Found" << endl;
	return(PROP_PERSON*found + 1);
      }
      found++;
    }
  }
  cout << "Record not found!" << endl;
  return(0);
}

void Student::delPerson(string C_Name){
  int found = findPerson(C_Name);
  //cout << found;

  if(found){
    //Delete
    string line;
    ofstream ofs("Replace.bin", ios::out|ios::binary);
    ifstream ifs("Student.bin", ios::in|ios::binary);
    while(!ifs.eof()){
      if(ifs >> *this){
	if(!(ID == C_Name) ){
	  ofs << *this;
	}
      }
    }

    //Rename
    remove("Student.bin");
    rename("Replace.bin", "Student.bin");
  }
  else{
    cout << "Student does not exist" << endl;
  }
}

void Admin:: StudentManager(){
  cout << "Welcome Admin " << name << endl;
  cout << "Choose options to continue... " << endl;
  int choice;
  cout << "1. Add Student" << endl;
  cout << "2. Show all Students" << endl;
  cout << "3. Find Student" << endl;
  cout << "4. Delete Student" << endl;
  cout << "Enter any other integer to exit..." << endl;

  cin >> choice;

  Student temp;
  
  switch(choice){
  case(1):
    temp.addPerson();
    break;
  case(2):
    temp.showAllPerson();
    break;
  case(3):
    {
    cout << "Enter StudentID: ";
    string tempID;
    cin.ignore();
    cin >> tempID;
    temp.findPerson(tempID);
    break;
    }
  case(4):
    {
    cout << "Enter StudentID: ";
    string tempID;
    cin.ignore();
    cin >> tempID;
    temp.delPerson(tempID);
    break;
    }
  default:
    cout << "Exiting...." << endl;
  }
}

int findReport(string FileName, string C_Name){
  ifstream ifs(FileName.c_str(), ios::in|ios::binary);
  int i = 1;
  string myID;
  int myGrade;
  while(!ifs.eof()){
    getline(ifs, myID);
    ifs >> myGrade;
    ifs.ignore();
    if(myID == C_Name){
      
      return(i);
    }
    else{
      i++;
    }
  }
  return(0);
}

void Student:: registerCourse(){
  //Get ID
  cout << "Enter Course ID: ";
  string myID;
  cin.ignore();
  getline(cin, myID);

  //Find Course
  Course temp;
  int exist = temp.findCourse(myID);
  
  //If course exists and not registered, add studentID, Grade (deafult 0 for unassigned)
  //Also check if floating
  if((exist) && (!findReport(temp.genFileName(), ID)) && (temp.floating)){
    //Open File
    ofstream ofs(temp.genFileName().c_str(), ios::out|ios::binary|ios::app);
    
    //Add ID + Grade
    ofs << ID;
    ofs << "\n";
    ofs	<< 0;
    ofs << "\n";
        
  }
  else{
    cout << "That course does not exist!!!/You have already Registered" << endl;
  }
  
}

void Student :: deregisterCourse(){
  //Get CID
  cout << "Enter Course ID: ";
  string myCID;
  cin.ignore();
  getline(cin, myCID);

  //Find Course
  Course temp;
  int exist = temp.findCourse(myCID);
  int reg = findReport(temp.genFileName(), ID);
        
  //If course exists add studentID, Grade 
  if(exist){
    //Check if student has registered
    if(reg){
      //Open both files
      ofstream ofs("Replace.txt", ios::out|ios::binary);
      ifstream ifs(temp.genFileName().c_str(), ios::in|ios::binary);

      //Read and write
      int i = 1;
      string myID;
      int myGrade;
      while(!ifs.eof()){
	if(i != reg){
	  getline(ifs, myID);
	  ifs >> myGrade;
	  ifs.ignore();
	  ofs << myID;
	  ofs << myGrade;
	}
	i++;
       }

      //Remove and rename
      remove(temp.genFileName().c_str());
      rename("Replace.txt", temp.genFileName().c_str());
    }
    else{
      cout << "Course not registered by student!!" << endl;
    }
  }
  else{
    cout << "That course does not exist!!!" << endl;
  }
  
}

void Student :: seeGrades(){
  //Traverse through every course and check for students
  Course temp;
  string CID;
  ifstream ifs("Sample.bin",ios::in|ios::binary);
  while(!ifs.eof()){
    if(ifs >> temp){
      //Every ID
      CID = temp.returnID();

      //Open File, find student and print Grade
      ifstream ifsnew(temp.genFileName().c_str(), ios::in|ios::binary);
      int i = 1;
      string myID;
      int myGrade;
      while(!ifsnew.eof()){
	getline(ifsnew, myID);
	ifsnew >> myGrade;
	ifsnew.ignore();
	if(myID == ID){//Student ID is being compared
	  cout << CID << " : " << myGrade << endl;
	}
      }
    }
  }
}

void Faculty :: seeCourses(){
  Course temp;
  string instructor;
  ifstream ifs("Sample.bin",ios::in|ios::binary);
  while(!ifs.eof()){
    if(ifs >> temp){
      if((instructor = temp.returnInstrID()) == ID){
	string presentID = temp.returnID();
	cout << presentID << endl;
      }
    }
  }
  ifs.close();
}

bool Faculty :: chkCourse(string C_ID){
  Course temp;
  string instructor;
  ifstream ifs("Sample.bin",ios::in|ios::binary);
  while(!ifs.eof()){
    if(ifs >> temp){
      if((instructor = temp.returnInstrID()) == ID){
	ifs.close();
	return(1);
      }
    }
  }
  return(0);
}

void Faculty :: seeStudents(){
  //Get course ID
  string C_ID;
  cout << "Enter CourseID:" << endl;
  cin.ignore();
  getline(cin, C_ID);
  
  //Check for Course with given ID
  Course temp;
  int exist = temp.findCourse(C_ID);
  int teach = chkCourse(C_ID);

  //If yes, then print Students : Grades
  if(exist && teach){
    ifstream ifs(temp.genFileName().c_str(), ios::in|ios::binary);
    string StuID;
    int StuGrade;
    while(!ifs.eof()){
      getline(ifs, StuID);
      ifs >> StuGrade;
      ifs.ignore();
      if(StuID == "") break;
      cout << StuID << ": " << StuGrade << endl;
    }
    
  }
  else if(!exist){
    cout << "Course not Found!" << endl;
  }
  else{
    cout << "Course not taught by this Faculty!" << endl;
  }
  
}

void Faculty::updateGrades(){
  //Get course ID
  string C_ID;
  cout << "Enter CourseID:" << endl;
  cin.ignore();
  getline(cin, C_ID);
  
  //Check for Course with given ID
  Course temp;
  int exist = temp.findCourse(C_ID);
  int teach = chkCourse(C_ID);

  //If yes, then print Students : Grades
  if(exist && teach){
    ifstream ifs(temp.genFileName().c_str(), ios::in|ios::binary);
    ofstream ofs("Temp.txt", ios::out|ios::binary);
    string StuID;
    int OldGrade;
    int NewGrade;
    while(!ifs.eof()){
      //Old Data
      getline(ifs, StuID);
      ifs >> OldGrade;
      ifs.ignore();

      if(StuID == "")break;

      //New Grade
      cout << "Enter Grade for " << StuID << ": ";
      cin >> NewGrade;

      //Update
      ofs << StuID;
      ofs << "\n";
      ofs << NewGrade;
      ofs << "\n"; 
      
    }

    //File change
    remove(temp.genFileName().c_str());
    rename("Temp.txt", temp.genFileName().c_str());
  }
  else if(!exist){
    cout << "Course not Found!" << endl;
  }
  else{
    cout << "Course not taught by this Faculty!" << endl;
  }
  
}
