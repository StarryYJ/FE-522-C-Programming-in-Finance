//
// Created by DELL on 2020/3/7.
//

#ifndef Q3_Q3_H
#define Q3_Q3_H

# include "std_lib_facilities.h"


// Because we're not allowed to use standard library function
// I wrote one myself to realize functionality of "strlen"
int getLength(char* str){
    int k = 0;
    while (str[k] != '\0'){
        k++;
    }
    return k;
}

char* mystrdup(char* s){
    char* d = new char[getLength(s) + 1];
    int NUM = getLength(s);
    int j;
    for (j = 0; j < NUM; j++) {
        *(d+j) = *(s+j);
    }
    *(d+j) = '\0';
    return d;
}

char* myfindx(char* s, char* x){
    int sNUM = getLength(s), xNUM = getLength(x), count, i, j;
    char* temp;
    for (i = 0; i < sNUM-xNUM+1; i++) {
        count = 0;
        for (j = 0; j < xNUM; j++) {
            if (*(s+i+j) == *(x+j)) {count++;}
        }
        if (count == xNUM) { return (char*)s+i; }
    }
    cout << "No occurrence." << endl;
    return nullptr;
}

int mystrcmp(char *s1, char* s2){
    int i;
    int minLength = min(getLength(s1), getLength(s2));
    for(i=0; i < minLength; i++){
        if(s1[i]-'@' > s2[i] - '@'){
            return 1;
        }
        else if(s1[i]-'@' < s2[i] - '@'){
            return -1;
        }
    }
    if(s1[i]=='\0' & s2[i]!='\0'){
        return -1;
    }
    else if(s1[i]!='\0' & s2[i]=='\0'){
        return 1;
    }
    return 0;
}







//char* mystrdup(char* s);
//char* myfindx(char* s, char* x);
//int mystrcmp(char* s1, char* s2);
//
//
//
//char* mystrdup(char* s){
//    &s
//    char* newStr[];
//}
//
//char* myfindx(char* s, char* x){
//
//}
//
//int mystrcmp(char* s1, char* s2){
//
//}

#endif //Q3_Q3_H
