#ifndef QUESTIONS_H_
#define QUESTIONS_H_
#include<bits/stdc++.h>
using namespace std ;

int QuestionsAvailable=0 ;
string Temp1 ;

class Question
{
protected:
    string Quest;
    vector<string>Choices ;
public:
    static int QuestionID;
    Question(string quest)
    {
        Quest=quest;
        QuestionID++ ;
        QuestionsAvailable++ ;

    }
    void QuestSetter(string x)
    {
        Quest = x ;
    }
    void choicesPushBack(string x)
    {
        Choices.push_back(x);
    }
    string QuestGetter()
    {
        return Quest ;
    }
    string ChoicesGetter(int index)
    {
        return Choices[index] ;
    }
    void ClearChoices()
    {
        Choices.clear() ;
    }
    bool IsYourAnswerIsCorrect(string answer)
    {
        Temp1=Choices[0];
        transform(Temp1.begin(), Temp1.end(), Temp1.begin(), ::toupper);
        transform(answer.begin(), answer.end(), answer.begin(), ::toupper);

        if(Temp1==answer)
        {
            return true;
        }
        else
        {
            return false ;
        }
    }

};

int Question::QuestionID = 0 ;

class MCQ : public Question
{
    int mcqID ;


public:
    MCQ(string quest,string correct,string second,string third,string fourth):Question(quest)
    {
        Quest=quest;
        Choices.push_back(correct);
        Choices.push_back(second);
        Choices.push_back(third);
        Choices.push_back(fourth);
        mcqID =Question::QuestionID ;
    }
    int mcqIDGetter ()
    {
        return mcqID ;
    }

};

//=====================================================================//
// True Or False //
class TOF : public Question
{
    int tofID ;
public:
    TOF(string quest,string correct):Question(quest)
    {
        Quest=quest ;
        Choices.push_back(correct) ;
        tofID =Question::QuestionID ;
    }
    int tofIDGetter ()
    {
        return tofID ;
    }
};

//================================================================//
// CompleteQuestion Class //
class CompleteQuestion : public Question
{
    int cqID ;
public:
    CompleteQuestion(string quest,string correct):Question(quest)
    {
        Quest=quest ;
        Choices.push_back(correct) ;
        cqID =Question::QuestionID ;
    }
    int cqIDGetter ()
    {
        return cqID ;
    }

};
//=================================================================//


#endif // QUESTIONS_H_
