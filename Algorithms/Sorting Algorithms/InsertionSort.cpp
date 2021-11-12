#include <iostream>
#include <algorithm>
#include <numeric>  // for std::accumulate
#include <utility>
#include <vector>
#include <string>
#include <random>
#include <cassert>

using namespace std;

//========================================================================
//  Set this to false to skip the insertion sort tests; you'd do this if
//  you're sorting so many items that insertion_sort would take more time
//  than you're willing to wait.

const bool TEST_INSERTION_SORT = true;

//========================================================================

//========================================================================
// Timer t;                 // create and start a timer
// t.start();               // restart the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

#include <chrono>

class Timer
{
  public:
    Timer()
    {
        start();
    }
    void start()
    {
        m_time = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const
    {
        std::chrono::duration<double, std::milli> diff =
                          std::chrono::high_resolution_clock::now() - m_time;
        return diff.count();
    }
  private:
    std::chrono::high_resolution_clock::time_point m_time;
};

//========================================================================

// These are used for random number generation

std::random_device aRandomDevice;
std::default_random_engine generator(aRandomDevice());

// Here's a class that is not cheap to copy because the objects contain a
// large array.

// We'll simplify writing our timing tests by declaring everything public
// in this class.  (We wouldn't make data public in a class intended for
// wider use.)

using IdType = int;

struct Student
{
    IdType id;
    double gpa;
    static const int NGRADES = 200;
    double grades[NGRADES];
    Student(IdType i) : id(i)
    {
        std::uniform_int_distribution<> distro(0, 4);

          // create random grades (from 0 to 4)
        for (size_t k = 0; k < NGRADES; k++)
            grades[k] = distro(generator);
          // (accumulate computes 0.0 + grades[0] + grades[1] + ...)
        gpa = accumulate(grades, grades + NGRADES, 0.0) / NGRADES;
    }
};

inline
bool compareStudent(const Student& lhs, const Student& rhs)
{
      // The Student with the higher GPA should come first.  If they have
      // the same GPA, then the Student with the smaller id number should
      // come first.  Return true iff lhs should come first.  Notice that
      // this means that a false return means EITHER that rhs should come
      // first, or there's a tie, so we don't care which comes first,

    if (lhs.gpa > rhs.gpa)
        return true;
    if (lhs.gpa < rhs.gpa)
        return false;
    return lhs.id < rhs.id;
}

inline

bool compareStudentPtr(const Student* lhs, const Student* rhs)
{
    return compareStudent(*lhs, *rhs);
}

void insertion_sort(vector<Student>& s, bool comp(const Student&, const Student&))
{

    if(s.empty()) return;
    int sorted = 1;
    
    while(sorted < s.size()){
        int sortedph = sorted;
        while((comp(s[sortedph],s[sortedph - 1])) && sortedph >= 1){
            swap(s[sortedph], s[sortedph - 1]);
            //decrement
            sortedph--;
        }
        sorted++;
    }
    
    
}

  // Report the results of a timing test

void report(string caption, double t, const vector<Student>& s)
{
    cout << t << " milliseconds; " << caption
             << "; first few students are\n\t";
    size_t n = s.size();
  //  if (n > 4)
 //       n = 4;
    for (size_t k = 0; k < n; k++)
        cout << " (" << s[k].id << ", " << s[k].gpa << ")";
    cout << endl;
}

int main()
{
    size_t nstudents;
    cout << "Enter number of students to sort: ";
    cin >> nstudents;
    if ( !cin  ||  nstudents <= 0)
    {
        cout << "You must enter a positive number.  Goodbye." << endl;
        return 1;
    }

      // Create a random ordering of id numbers 0 through nstudents-1
    vector<IdType> ids;
    for (size_t j = 0; j < nstudents; j++)
        ids.push_back(IdType(j));
    shuffle(ids.begin(), ids.end(), generator);  // from <algorithm>

      // Create a bunch of Students
    vector<Student> unorderedStudents;
    for (size_t k = 0; k < ids.size(); k++)
        unorderedStudents.push_back(Student(ids[k]));

      // Create a timer

    Timer timer;

      // Sort the Students using the STL sort algorithm.  It uses a variant
      // of quicksort called introsort.

    vector<Student> students(unorderedStudents);
    timer.start();
    sort(students.begin(), students.end(), compareStudent);
    report("STL sort", timer.elapsed(), students);
    assert(is_sorted(students.begin(), students.end(), compareStudent));  // from <algorithm>

      // Sort the already sorted array using the STL sort.  This should be
      // fast.

    timer.start();
    sort(students.begin(), students.end(), compareStudent);
    report("STL sort if already sorted", timer.elapsed(), students);
    assert(is_sorted(students.begin(), students.end(), compareStudent));



    if (TEST_INSERTION_SORT)
    {
          // Sort the original unsorted array using insertion sort.  This
          // should be really slow.  If you have to wait more than a minute,
          // try rerunning the program with a smaller number of Students.

        students = unorderedStudents;
        timer.start();
        insertion_sort(students, compareStudent);
        double elapsed = timer.elapsed();

        if (is_sorted(students.begin(), students.end(), compareStudent))
        {
            report("insertion sort if not already sorted", elapsed, students);

              // Sort the already sorted array using insertion sort.  This
              // should be fast.

            timer.start();
            insertion_sort(students, compareStudent);
            report("insertion sort if already sorted", timer.elapsed(), students);
            assert(is_sorted(students.begin(), students.end(), compareStudent));
        }
        else
            cout << "[Skipping tests of insertion_sort, since it's not correctly implemented.]" << endl;
    }

      // Since Students are expensive to copy, and since the STL's sort copies
      // Students O(N log N) times, let's sort POINTERS to the Students, then
      // make one final pass to rearrange the Students according to the
      // reordered pointers.  We'll write some code; you write the rest.

      // Set students to the original unsorted sequence
    students = unorderedStudents;

      // Start the timing
    timer.start();

      // Create an auxiliary copy of students to faciliate the later reordering.
      // We create it in a local scope so that we also account for the
      // destruction time.
    {
     vector<Student> auxStudents(students);

      // TODO:  Create a vector of Student pointers, and set each pointer
      //        to point to the corresponding Student in auxStudents.

        vector<Student*> ptrStudents;
        
        for(int i = 0; i < auxStudents.size(); i++)
            ptrStudents.push_back(&auxStudents[i]);
        
        sort(ptrStudents.begin(), ptrStudents.end(), compareStudentPtr);

        
      // TODO:  Sort the vector of pointers using the STL sort algorithm
      //        with compareStudentPtr as the ordering relationship.

        students.clear();
        
        for(int i = 0; i < ptrStudents.size(); i++)
            students.push_back(*(ptrStudents[i]));
        
        
      // TODO:  Using the now-sorted vector of pointers, replace each Student
      //        in students with the Students from auxStudents in the correct order.

    } // auxStudents will be destroyed here

      // Report the timing and verify that the sort worked
    report("STL sort of pointers", timer.elapsed(), students);
 //   assert(is_sorted(students.begin(), students.end(), compareStudent));
}
