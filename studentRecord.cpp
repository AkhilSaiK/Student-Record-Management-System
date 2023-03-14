#include<iostream>
#include<string>
#include<string.h>
#include<vector>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;
int numberlength(int );
class record;

class student{
    private:
    string name,roll;
    float marks[11],grades[11],sgpa;
    friend record;
};

class record{
    vector<student> students;
    string subjects[11]={"Discrete Mathematics","Design and Analysis of Algorithms","Design and Analysis of Algorithms Lab","Digital Electronics","Digital Electronics Lab","Hands on Using Python","OOP with C++","OOP with C++ Lab","ISCP-2","Principles of Economics","ISES-3"};
    float credits[11]={3,3,1,3,1,2,3,1,1,3,1};
    public:
    void initiate(){
        student temp_student;
        fstream file;
        string temp;
        int flag=0;
        file.open("studentrecord.txt",ios::in);
        if(file.is_open()){
             while(!file.eof()){
                getline(file,temp_student.name);
                getline(file,temp_student.roll);

                for(int i=0;i<11;i++){
                    getline(file,temp);
                    temp_student.marks[i]=stof(temp);
                }

                for(int i=0;i<11;i++){
                    getline(file,temp);
                    temp_student.grades[i]=stof(temp);
                }
                getline(file,temp);
                temp_student.sgpa=stof(temp);

                students.push_back(temp_student);
             }
        }
        file.close();
    }
    void allstudent(){
        if(students.empty()){
            cout<<"\t RECORD EMPTY"<<endl;
            return;
        }
        int i=1;
        cout<<"\nS.no  Registration no.  Name                      DM      DAA     DAA L   DE      DE L    Python  OOPS    OOP L   ISCP    ECO     ISES    SGPA"<<endl;
        for(student stu:students){
            displayStudentDetails(stu,i);
            cout<<"\n";
            i++;
        }
    }
    void getGrades(student &stud){
        /*
        100 10
        95-100 9
        90 to 94 8
        85 to 90 7
        80 to 85 6
        7o to 80 5
        60 to 70 4
        50 to 60 3
        40 to 50 2
        <40 1
        */
        for(int i=0;i<11;i++){
            if(stud.marks[i]==100)
            stud.grades[i]=10;
            else if(stud.marks[i]>94)
            stud.grades[i]=9;
            else if(stud.marks[i]>89)
            stud.grades[i]=8;
            else if(stud.marks[i]>84)
            stud.grades[i]=7;
            else if(stud.marks[i]>79)
            stud.grades[i]=6;
            else if(stud.marks[i]>69)
            stud.grades[i]=5;
            else if(stud.marks[i]>59)
            stud.grades[i]=4;
            else if(stud.marks[i]>49)
            stud.grades[i]=3;
            else if(stud.marks[i]>39)
            stud.grades[i]=2;
            else if(stud.marks[i]<40)
            stud.grades[i]=1;
        }
    }
    void addStudent(){
        student new_stu;
        cout<<"Enter Student Name: \n";
        cin.ignore();
        getline(cin,new_stu.name);
        cout<<"Enter Registration Number: ";
        cin>>new_stu.roll;
        cout<<"Enter Marks Details:"<<endl;
        for(int i=0;i<11;i++){
            cout<<subjects[i]<<": ";
            cin>>new_stu.marks[i];
        }
        getGrades(new_stu);
        calSGPA(new_stu);
        students.push_back(new_stu);
    }
    void calSGPA(student &stud){
        for(int i=0;i<11;i++){
            stud.sgpa+=(stud.grades[i]*credits[i]);
        }
        stud.sgpa/=22;
    }
    void displayStudentDetails(student &temp_student,int sno=1){
        int i,t;
        cout<<sno;
         t=6-numberlength(sno);
        for(i=0;i<t;i++)
        cout<<" ";

        cout<<temp_student.roll;
         t=18-temp_student.roll.size();
        for(i=0;i<t;i++)
        cout<<" ";

        cout<<temp_student.name;
         t=26-temp_student.name.size();
        for(i=0;i<t;i++)
        cout<<" ";

        for(int j=0;j<11;j++){
            cout<<temp_student.grades[j];
             t=8-numberlength(temp_student.grades[j]);
            for(i=0;i<t;i++)
            cout<<" ";
        }
        
        cout<<temp_student.sgpa<<endl;
    }
    void searchStudent(){
        string s;
        int flag=1;
        cout<<"Enter Registration Number of student: ";
        cin>>s;
        for(auto i:students){
            if(s.compare(i.roll)==0){
                flag=0;
                cout<<"\nS.no  Registration no.  Name                      DM      DAA     DAA L   DE      DE L    Python  OOPS    OOP L   ISCP    ECO     ISES    SGPA"<<endl;
                displayStudentDetails(i);
                break;
            }
        }
        if(flag)
        cout<<"\t STUDENT NOT FOUND"<<endl;
    }
    void deleteStudentRec(){//program stopping after this***************
        string s;
        int flag=1;
        cout<<"Enter ID of student to delete record: ";
        cin>>s;
        for(auto i=students.begin();i!=students.end();i++){
            if(s.compare(i->roll)==0){
                cout<<i->name<<"'s record deleted"<<endl;
                students.erase(i);
                flag=0;
                break;
            }
        }
        if(flag)
        cout<<"\t STUDENT NOT FOUND"<<endl;
    }
    void modifyStudentRec(){
        string s;
        int flag=1,i;
        cout<<"Enter ID of student to modify: ";
        cin>>s;
        for(i=0;i<students.size();i++){
            if(students[i].roll.compare(s)==0){
                flag=0;
                break;
            }
        }
        if(flag){
            cout<<"STUDENT NOT FOUND"<<endl;
            return;
        }
        else{
            cout<<"CURRENT DETAILS:"<<endl;
            cout<<"\nS.no  Registration no.  Name                      DM      DAA     DAA L   DE      DE L    Python  OOPS    OOP L   ISCP    ECO     ISES    SGPA"<<endl;
            displayStudentDetails(students[i]);
            cout<<"\tENTER NEW DETAILS:"<<endl;

            cout<<"Enter Student Name: \n";
            cin.ignore();
            getline(cin,students[i].name);
            cout<<"Enter Registration Number: ";
            cin>>students[i].roll;
            cout<<"Enter Marks Details:"<<endl;
            for(int j=0;j<11;j++){
                cout<<subjects[j]<<": ";
                cin>>students[i].marks[j];
            }
            getGrades(students[i]);
            calSGPA(students[i]);
        }
    }
    void showToppers(){
        sort(students.begin(),students.end(),[ ]( const auto& lhs, const auto& rhs ){
            return lhs.sgpa > rhs.sgpa;
        });
        int i=1;
        cout<<"\tTOP 3 STUDENTS:\n";
        cout<<"\nS.no  Registration no.  Name                      DM      DAA     DAA L   DE      DE L    Python  OOPS    OOP L   ISCP    ECO     ISES    SGPA"<<endl;
        for(student stu:students){
            if(i>3)
            break;
            displayStudentDetails(stu,i);
            cout<<"\n";
            i++;
        }
    }
    void SaveExit(){
        fstream file;
        file.open("studentrecord.txt",ios::out);
        if(file.is_open()){
            for(auto i:students){
                file<<i.name<<endl;
                file<<i.roll<<endl;
                for(int j=0;j<11;j++)
                file<<i.marks[j]<<endl;
                for(int j=0;j<11;j++)
                file<<i.grades[j]<<endl;
                
                file<<i.sgpa;
                if(i.roll!=students.back().roll)
                file<<endl;
            }
        }
        file.close();
        cout<<"FILE SAVED SUCCESFULLY"<<endl;
    }
};

int numberlength(int n){
    int count=0,i;
    while(n>0){
        n=n/10;
        count++;
    }
    return count;
}
int main(){
    // student();
    record secB;
    secB.initiate();
    int opt=-1;
    string wait;
    while(opt!=0){
        system("pause");
        system("CLS");
        cout<<"\n\tMain Menu\n";
        cout<<"1. Add Student Record\n";
        cout<<"2. Modify Student Record\n";
        cout<<"3. Delete Student Record\n";
        cout<<"4. Display Particular Student Record\n";
        cout<<"5. Display all Student Records\n";
        cout<<"6. Display Toppers\n";
        cout<<"0. Save and Exit\n";
        cout<<"choose 0-6: ";
        cin>>opt;
        switch(opt){
            case 1: secB.addStudent();
                    break;
            case 2: secB.modifyStudentRec();
                    break;
            case 3: secB.deleteStudentRec();
                    break;
            case 4: secB.searchStudent();
                    break;
            case 5: secB.allstudent();
                    break;
            case 6: secB.showToppers();
                    break;
            case 0: secB.SaveExit();
                    break;

            default:cout<<"Invalid choice\n";
        }
    }
}
//Display format:
// S.no  Registration no.  Name                      DM      DAA     DAA L   DE      DE L    Python  OOPS    OOP L   ISCP    ECO     ISES  SGPA
// 111   AP21110010123     yashwanth sai narasimha   9       9       9       9       9       9       9       9       9       9       9     sgpa
