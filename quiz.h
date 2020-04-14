#ifndef QUIZ_H
#define QUIZ_H_
#include<bits/stdc++.h>
using namespace std ;

class Quiz
{
public:
    int thisType[5],RightOrWrong[5]= {0,0,0,0,0} ;
    int total = 0,RWAnswers =0;
    string thisQuestion[5] ;
    string thisChoices[5][4] ;
    string thisAnswer[5] ;
    string RightAnswers[5] ;
};


#endif // QUIZ_H_
