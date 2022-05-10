#include "classes.cpp"

#define PRINT(x) cout << x << endl;

int main(){
  string a = "Default";
  string b = "AD0001";
  string c = "asdf";
  Admin sample(a, b, c);
  
  Admin temp;
  if(!(temp.findPerson(b))){
    PRINT("Initialising Default Admin");
    sample.putPersonFile();
    }
  
  int person_choice;
  int main_choice;

  PRINT("");
  PRINT("Who are you???");
  PRINT("1. Admin");
  PRINT("2. Student");
  PRINT("3. Faculty");
  cin >> person_choice;

  switch(person_choice){
  case(1):{
    Admin lord;

    //Get ID
    cin.ignore();
    PRINT("");
    PRINT("Enter ID");
    string myID;
    getline(cin, myID);

    //Check if ID exists
    int exist = lord.findPerson(myID);

    if(!exist){
      PRINT("No such Admin exists!");
      break;
    }

    //Check Password
    int crt = lord.chkPassword();

    //Main
    if(exist && crt){
      while(main_choice != 5){
	    PRINT("Choose Options...");
	    PRINT("1. Modify Course");
	    PRINT("2. Modify Admin");
	    PRINT("3. Modify Faculty");
	    PRINT("4. Modify Student");
	    PRINT("5. Exit Program");
	    PRINT("6. Any other key to continue...");
	    cin >> main_choice;

	    switch(main_choice){
	    case(1):
	      sample.CourseManager();
	      break;
	    case(2):
	      sample.AdminManager();
	      break;
	    case(3):
	      sample.FacultyManager();
	      break;
	    case(4):
	      sample.StudentManager();
	      break;
	    default:
	      PRINT("Exiting Iteration....");
	    }
	    
      }
    }
    break;
  }
  case(2):{
    Student kid;

    //Get ID
    cin.ignore();
    PRINT("");
    PRINT("Enter ID");
    string myID;
    getline(cin, myID);

    //Check if ID exists
    int exist = kid.findPerson(myID);

    if(!exist){
      PRINT("No such student exists!");
      break;
    }

    //Check Password
    int crt = kid.chkPassword();
    
    if(exist && crt){
      while(main_choice != 5){
	PRINT("Choose Options...");
	PRINT("1. View All Courses");
	PRINT("2. Register Course");
	PRINT("3. Deregister Course");
	PRINT("4. See Grades");
	PRINT("5. Exit Program");
	PRINT("Any other key to continue");
	cin >> main_choice;
    
	switch(main_choice){
	case(1):{
	  Course temp;
	  temp.showAllCourses();
	  break;
	}
	case(2):{
	  kid.registerCourse();
	  break;
	}
	case(3):{
	  kid.deregisterCourse();
	  break;
	}
	case(4):{
	  kid.seeGrades();
	  break;
	}
	default:
	  PRINT("Exiting....");
	}
      }
    }	 
      
    else{
      PRINT("Incorrect Password!");
    }
    break;
  }
  case(3):{
    Faculty master;

    //Get ID
    PRINT("");
    cin.ignore();
    PRINT("Enter ID");
    string myID;
    getline(cin, myID);

    //Check if ID exists
    int exist = master.findPerson(myID);
    
    if(!exist){
      PRINT("No such faculty exists!");
      break;
    }
    
    //Check Password
    int crt = master.chkPassword();
    
    if(exist && crt){
      while(main_choice !=4){
	PRINT("Choose Options...");
	PRINT("1. See Teaching Courses");
	PRINT("2. See Students of a Course");
	PRINT("3. Update Grades of a Course");
	PRINT("4. Exit...");
	cin >> main_choice;
	
	switch(main_choice){
	case(1):{
	  master.seeCourses();
	  break;
	}
	case(2):{
	  master.seeStudents();
	  break;
	}
	case(3):{
	  master.updateGrades();
	  break;
	}
	default:
	  PRINT("Exiting....");
	}
      }
    }
    else{
      PRINT("Incorrect Password!");
    }
    break;
  }
  
  default:
    PRINT("Ending Program...");
  }
  return(0);
}
