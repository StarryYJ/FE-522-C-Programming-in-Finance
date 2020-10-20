#include "std_lib_facilities.h"
#include "Q3.h"

// Details of functions are all included in header file "homework1.h"


int main(){
    // sub-question 1
    char* q = new char[5];
    q[0] = 'a';
    q[1] = 's';
    q[2] = 'd';
    q[3] = 'f';
    q[4] = 0;
    char* s2 = mystrdup(q);
//    cout<<"Original address: "<< &q << endl;
//    cout<<"New address: "<< &s2 << endl;
//    cout<<"Value in new address: "<< s2 << "\n" << endl;

    // sub-question 2
    char* s3 = new char[3];
    s3[0] = 's';
    s3[1] = 'd';
    s3[2] = 0;
    char* s4 = myfindx(q, s3);
//    cout << "Initially q is: " << q << endl;
//    q[1] = 't';
//    cout << "q is now: " << q << endl;
//    cout << "And my returned pointer now point to value: " << *s4 << "\n" << endl;

    char* s5 = new char[3];
    s5[0] = 'a';
    s5[1] = 's';
    s5[2] = 0;

    // sub-question 3
    cout << "first is before second: " << endl;
    cout << "q is: " << q << ", s3 is: " << s3 << endl;
    cout << mystrcmp(q, s3) << endl;

    cout << "second is before first: " << endl;
    cout << "s3 is: " << s3 << ", q is: " << q << endl;
    cout << mystrcmp(s3, q) << endl;

    cout << "similar but shorter: " << endl;
    cout << "q is: " << q << ", s5 is: " << s5 << endl;
    cout << mystrcmp(q, s5) << endl;

    cout << "equivalent string: " << endl;
    cout << "s2 is: " << s2 << ", q is: " << q << endl;
    cout << mystrcmp(s2, q) << "\n" << endl;



    // test character computation
    cout << "test" << endl;
    cout << 'A' - '@' << "\n" << endl;





    //char* s2 = new char[5];
    //char* s3 = s1;
//    s2[0] = 'a';
//    s2[1] = 's';
//    s2[2] = 'd';
//    s2[3] = 'f';
//    s2[4] = 0;

//    cout << &s1 << endl;
//    cout << &s2 << endl;
//    cout << *(s1++) << endl;
//    cout << &s3 << endl;

//    delete [] s1;
//    delete [] s3;

    //cout<<"copy: "<< mystrdup(s1) << endl;
//
//    char* s3 = "d";
//    cout<<"find index: "<< myfindx(s2, s3) << endl;
//    cout<<"compare s1 and s2: "<< mystrcmp(s1, s2) << endl;
//    cout<<"compare s1 and s3: "<< mystrcmp(s1, s3) << endl;
    return 0;
}




