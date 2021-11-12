//
//  main.cpp
//  toPostfix
//
//  Created by Akhil Vinta on 2/4/20.
//  Copyright © 2020 Akhil Vinta. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Student{
    public:
    
    Student(){}
    Student(double gpa, int grade){
        this -> gpa = gpa;
        this -> grade = grade;
    }
    
    double getGPA(){ return gpa; }
    int getGrade(){ return grade; }
    
private:
        double gpa;
        int grade;
    
};

class DumbStudent : public Student{
    
public:
    
    DumbStudent(double gpa, int grade, bool is_stupid) : Student(gpa,grade){
        this -> is_stupid = is_stupid;
    }
    
    void makeDumb(){ is_stupid = true; }
    bool getIs_Stupid(){ return is_stupid; }
    
private:
    bool is_stupid;
    
};


int main(int argc, const char * argv[]) {

    Student x(4.0,10);
    cout << x.getGrade() << endl;
    DumbStudent z(4.6,9,true);
    cout << z.getIs_Stupid() << endl;
    cout << z.getGrade() << endl;
    

}
