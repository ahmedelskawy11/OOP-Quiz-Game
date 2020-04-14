#include <bits/stdc++.h>
#include <iomanip>
#include <time.h>
#include <fstream>
#include "questions.h"
#include "user.h"
#include "quiz.h"

using namespace std;

//Global Variables //
string Temp2 ;
int NumberOFUsers,init=1,LastTwoQuizzesReapet=0,highest =0, lowest =10,total ;
int mcqArray[3],tfArray[0],cqArray[1],RandomlyChoices[4] ;
double MCQRight=0, CQRight=0, TFRight = 0  ;
bool AdminOrPlayer, LoginOrNot = false;
//--------------------------//

//  All Functions //
bool LoginFun() ;
void AddNewUser() ;
bool IsUserAlreadyAdded(string );
void ViewAllUsers() ;

void AddingNewQuestions() ;
bool questionExist(string,string) ;
void DelQuestion(int ) ;
void LoadQuestionsFromFile() ;

void RandomizeQuestions(int [],int,int);
void RandomChoices (int []) ;
void RandomTypesPushBack() ;

void DisplayScoreStat() ;
double calcAverage() ;
void PrintingAllScores() ;
void PrintingLastTwoQuizzes() ;
// --------------------//

//  Data Vectors //
vector <MCQ> allMCQ ;
vector <TOF> allTOF ;
vector <CompleteQuestion> allCQ ;
vector <User> allUsers ;
vector<Quiz>LastTwoQuizzes ;
vector<int>RandomTypes ;
// --------------------//

//============================== Starting Of The Main Function =============================================//
int main()
{
    RandomTypesPushBack() ;

    cout<<"*******************************************************************\n" ;
    cout<<"\t\tWelcome to the Quiz game program V2.0!\n" ;
    cout<<"*******************************************************************\n" ;

    allUsers.push_back(Admin("User","User","ADMIN","admin")) ;
    allUsers.push_back(Player("User","User","PLAYER","111")) ;

    // The Whole Program //
    while(init == 1)
    {
        int init2= 1 ;
        int choice ;

        while(LoginOrNot!= true)
            LoginFun() ;

        AdminOrPlayer = allUsers[NumberOFUsers].Passing() ;
        system ("CLS");

        // ---------------- The Admin Menu -----------------------------//
        if(AdminOrPlayer)
        {
            cout << "\nWelcome "<< allUsers[NumberOFUsers].FirstNameGetter()
                 <<" "<<allUsers[NumberOFUsers].LastNameGetter()
                 <<" ( "<<allUsers[NumberOFUsers].RoleGetter()<<" ) "
                 <<", please choose from the following options:\n\n"
                 << "\t[1] Switch accounts\n"
                 << "\t[2] Update your name\n"
                 << "\t[3] View all users\n"
                 << "\t[4] Add new user\n"
                 << "\t[5] View all questions\n"
                 << "\t[6] Add new question\n"
                 << "\t[7] Load questions from file\n"
                 << "\t[8] Exit the program\n"
                 << "\nMy choice: " ;
            cin>>choice ;

            switch(choice)
            {
            case 1:
                system ("CLS");
                LoginOrNot = false ;
                cin.ignore(256, '\n');
                break;
            case 2:
            {
                cin.ignore(256, '\n');
                string first,second ;
                cout<<"Please Input your First Name: " ;
                getline(cin,first);
                cout<<"Please Input your Last Name: " ;
                getline(cin,second);

                allUsers[NumberOFUsers].FirstNameSetter(first);
                allUsers[NumberOFUsers].LastNameSetter(second);

                cout<<"Done \n" ;
                system ("PAUSE");
                system ("CLS");
                break ;
            }
            case 3:
                ViewAllUsers() ;
                break ;
            case 4:
                AddNewUser() ;
                break ;
            case 5:
            {
                system ("CLS");
                cout<<"Number of questions Has Already Added: "<<Question::QuestionID<<endl ;
                cout<<"Number of questions available: "<<QuestionsAvailable<<endl ;
                cout<<"\n---------------------------------------------------\n";
                cout<<"MCQ Questions list (Total: "<<allMCQ.size()<<")\n";
                cout<<"\n---------------------------------------------------\n";

                for(int i=0; i<allMCQ.size(); i++)
                {
                    cout<<"["<<i+1<<"]"<<"(ID:"<<allMCQ[i].mcqIDGetter()<<")"<<allMCQ[i].QuestGetter()<<"\n" ;
                    cout<<"\t[a]"<<allMCQ[i].ChoicesGetter(0)<<"\t[b]"+allMCQ[i].ChoicesGetter(1)<<"\t[c]"
                        <<allMCQ[i].ChoicesGetter(2)<<"\t[d]"<<
                        allMCQ[i].ChoicesGetter(3)<<endl<<endl ;
                }

                cout<<"\n---------------------------------------------------\n";
                cout<<"TF Questions list (Total: "<<allTOF.size()<<")\n";
                cout<<"\n---------------------------------------------------\n";

                for(int i=0; i<allTOF.size(); i++)
                {
                    cout<<"["<<i+1<<"]"<<"(ID:"<<allTOF[i].tofIDGetter()<<")"<<allTOF[i].QuestGetter()
                        <<" (Answer: "+allTOF[i].ChoicesGetter(0)+")\n\n";
                }

                cout<<"\n---------------------------------------------------\n";
                cout<<"Complete Questions list (Total: "<<allCQ.size()<<")\n";
                cout<<"\n---------------------------------------------------\n";

                for(int i=0; i<allCQ.size(); i++)
                {
                    cout<<"["<<i+1<<"]"<<"(ID:"<<allCQ[i].cqIDGetter()<<")"<<allCQ[i].QuestGetter()
                        <<" (Answer: "+allCQ[i].ChoicesGetter(0)+")\n\n";

                }

                cout<<"\n---------------------------------------------------\n";
                cout<<"Press [d] and the question ID if you want to delete a question\n";
                cout<<"Press [b] if you want to go back to the main menu\n" ;
                char choice2 ;
                cin>>choice2 ;

                while(1)
                {
                    if(choice2=='b'||choice2=='B')
                        break ;
                    else if(choice2=='d'||choice2=='D')
                    {
                        int urchoice ;
                        cin>>urchoice ;

                        if(urchoice > 0 && urchoice<=Question::QuestionID )
                            DelQuestion(urchoice) ;
                        else
                        {
                            cout<<"Invalid ID\n";
                            system("PAUSE");
                        }
                        break ;
                    }
                    else
                    {
                        cout<<"Invalid Choice Please Enter It Again\n" ;
                        cin>>choice2 ;
                    }
                }
                break ;
            }
            case 6:
                AddingNewQuestions() ;
                break ;
            case 7:
                LoadQuestionsFromFile() ;
                break ;
            case 8:
                init = 0 ;
                break ;
            }


        }
        // --------------------------------- The Player Menu -----------------------------//
        else
        {
            cout << "\nWelcome "<< allUsers[NumberOFUsers].FirstNameGetter()
                 <<" "<<allUsers[NumberOFUsers].LastNameGetter()
                 <<" ( "<<allUsers[NumberOFUsers].RoleGetter()<<" ) "
                 <<", please choose from the following  options:\n\n"
                 << "\t[1] Switch accounts\n"
                 << "\t[2] Update your name\n"
                 << "\t[3] Start a new quiz\n"
                 << "\t[4] Display your scores statistics\n"
                 << "\t[5] Display all your scores\n"
                 << "\t[6] Display details of your last 2 quizzes\n"
                 << "\t[7] exit the program \n"
                 << "\nMy choice: " ;
            cin>>choice ;

            switch(choice)
            {
            case 1:
            {
                LoginOrNot = false ;
                system ("CLS");
                cin.ignore(256, '\n');
                break;
            }
            case 2:
            {
                cin.ignore(256, '\n');
                string first,second ;

                cout<<"Please Input your First Name: " ;
                getline(cin,first);
                cout<<"Please Input your Last Name: " ;
                getline(cin,second);

                allUsers[NumberOFUsers].FirstNameSetter(first);
                allUsers[NumberOFUsers].LastNameSetter(second);

                cout<<"Done \n" ;
                system ("PAUSE");
                system ("CLS");
                break;
            }
            case 3:
            {
                system("CLS") ;
                cout<<endl ;
                if(Question::QuestionID<5)
                {
                    cout<<"Please Add More Question To Start Any Quiz.\n\n" ;
                }
                else if(allMCQ.size()<3)
                {
                    cout<<"Please Add More MCQ Questions \n\n" ;
                }
                else if(allCQ.size()<1)
                {
                    cout<<"Please Add More Complete Questions \n\n" ;
                }
                else if(allTOF.size()<1)
                {
                    cout<<"Please Add More True Or False Questions \n\n" ;
                }
                else
                {
                    LastTwoQuizzes.push_back(Quiz()) ;
                    total = 0 ;
                    LastTwoQuizzesReapet=0;

                    RandomizeQuestions(mcqArray,allMCQ.size(),3) ;
                    RandomizeQuestions(tfArray,allTOF.size(),1) ;
                    RandomizeQuestions(cqArray,allCQ.size(),1) ;

                    random_shuffle(RandomTypes.begin(), RandomTypes.end());

                    int cqItrator=0,tfItrator=0,mcqItrator=0 ;

                    // Displaying the Quiz //
                    for(int i=0; i<RandomTypes.size(); i++)
                    {
                        switch(RandomTypes[i])
                        {
                        case 1:
                        {
                            LastTwoQuizzes[LastTwoQuizzes.size()-1].thisType[LastTwoQuizzesReapet]=1 ;
                            int repeat = 1 ;
                            char asnwer ;
                            RandomChoices(RandomlyChoices);

                            cout<<" [ " << i+1 << " ] " <<allMCQ[mcqArray[mcqItrator]].QuestGetter()<<endl<<endl ;
                            LastTwoQuizzes[LastTwoQuizzes.size()-1].thisQuestion[LastTwoQuizzesReapet] =allMCQ[mcqArray[mcqItrator]].QuestGetter();
                            cout<<"\t[a]"<<allMCQ[mcqArray[mcqItrator]].ChoicesGetter(RandomlyChoices[0])
                                <<"\t[b]"+allMCQ[mcqArray[mcqItrator]].ChoicesGetter(RandomlyChoices[1])<<"\t[c]"
                                <<allMCQ[mcqArray[mcqItrator]].ChoicesGetter(RandomlyChoices[2])<<"\t[d]"
                                <<allMCQ[mcqArray[mcqItrator]].ChoicesGetter(RandomlyChoices[3])<<endl<<endl ;

                            LastTwoQuizzes[LastTwoQuizzes.size()-1].thisChoices[LastTwoQuizzesReapet][0]=allMCQ[mcqArray[mcqItrator]].ChoicesGetter(RandomlyChoices[0]) ;
                            LastTwoQuizzes[LastTwoQuizzes.size()-1].thisChoices[LastTwoQuizzesReapet][1]=allMCQ[mcqArray[mcqItrator]].ChoicesGetter(RandomlyChoices[1]) ;
                            LastTwoQuizzes[LastTwoQuizzes.size()-1].thisChoices[LastTwoQuizzesReapet][2]=allMCQ[mcqArray[mcqItrator]].ChoicesGetter(RandomlyChoices[2]) ;
                            LastTwoQuizzes[LastTwoQuizzes.size()-1].thisChoices[LastTwoQuizzesReapet][3]=allMCQ[mcqArray[mcqItrator]].ChoicesGetter(RandomlyChoices[3]) ;
                            LastTwoQuizzes[LastTwoQuizzes.size()-1].RightAnswers[LastTwoQuizzesReapet]=allMCQ[mcqArray[mcqItrator]].ChoicesGetter(0) ;

                            mcqItrator++ ;

                            while(repeat==1)
                            {
                                cout<<"Your Choice: " ;
                                cin>>asnwer ;
                                LastTwoQuizzes[LastTwoQuizzes.size()-1].thisAnswer[LastTwoQuizzesReapet][0]=asnwer ;
                                switch(asnwer)
                                {
                                case'a':
                                    case'A':
                                        {
                                            if(RandomlyChoices[0]== 0)
                                    {
                                        LastTwoQuizzes[LastTwoQuizzes.size()-1].RightOrWrong[LastTwoQuizzesReapet]=2 ;
                                            total+=2 ;
                                            MCQRight++ ;
                                            LastTwoQuizzes[LastTwoQuizzes.size()-1].RWAnswers++ ;
                                        }
                                repeat =0 ;
                                        break ;
                                }
                                case'b':
                                    case'B':
                                        {
                                            if(RandomlyChoices[1]==0)
                                    {
                                        LastTwoQuizzes[LastTwoQuizzes.size()-1].RightOrWrong[LastTwoQuizzesReapet]=2 ;
                                            total+=2 ;
                                            MCQRight++ ;
                                            LastTwoQuizzes[LastTwoQuizzes.size()-1].RWAnswers++ ;
                                        }
                                repeat =0 ;
                                        break ;
                                }
                                case'c':
                                    case'C':
                                        {
                                            if(RandomlyChoices[2]==0)
                                    {
                                        LastTwoQuizzes[LastTwoQuizzes.size()-1].RightOrWrong[LastTwoQuizzesReapet]=2 ;
                                            total+=2 ;
                                            MCQRight++ ;
                                            LastTwoQuizzes[LastTwoQuizzes.size()-1].RWAnswers++ ;
                                        }
                                repeat =0 ;
                                        break ;
                                }
                                case'd':
                                    case'D':
                                        {
                                            if(RandomlyChoices[3]==0)
                                    {
                                        LastTwoQuizzes[LastTwoQuizzes.size()-1].RightOrWrong[LastTwoQuizzesReapet]=2 ;
                                            total+=2 ;
                                            MCQRight++ ;
                                            LastTwoQuizzes[LastTwoQuizzes.size()-1].RWAnswers++ ;
                                        }
                                repeat =0 ;
                                        break ;
                                }
                                default:
                                {
                                    cout<<"Invalid Answer \n\n" ;
                                    break ;
                                }
                                }

                            }
                            cout<<"------------------------------------------------------" ;
                            cout<<"\n" ;
                            break ;
                        }
                        case 2:
                        {
                            LastTwoQuizzes[LastTwoQuizzes.size()-1].thisType[LastTwoQuizzesReapet]=2 ;
                            string answer ;
                            cout<<" [ " << i+1 << " ] "<<allCQ[cqArray[cqItrator]].QuestGetter()<<"\n\tYour Answer: ";
                            LastTwoQuizzes[LastTwoQuizzes.size()-1].thisQuestion[LastTwoQuizzesReapet]=allCQ[cqArray[cqItrator]].QuestGetter();
                            if(RandomTypes[i-1]!=3)
                            {
                                cin.ignore(256, '\n');
                            }
                            getline(cin,answer);
                            LastTwoQuizzes[LastTwoQuizzes.size()-1].thisAnswer[LastTwoQuizzesReapet]=answer ;
                            transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
                            LastTwoQuizzes[LastTwoQuizzes.size()-1].RightAnswers[LastTwoQuizzesReapet]=allCQ[cqArray[cqItrator]].ChoicesGetter(0) ;
                            Temp1=allCQ[cqArray[cqItrator]].ChoicesGetter(0) ;
                            transform(Temp1.begin(), Temp1.end(), Temp1.begin(), ::toupper);
                            if(answer==Temp1)
                            {
                                LastTwoQuizzes[LastTwoQuizzes.size()-1].RightOrWrong[LastTwoQuizzesReapet]=3 ;
                                total+=3 ;
                                LastTwoQuizzes[LastTwoQuizzes.size()-1].RWAnswers++ ;
                                CQRight++ ;
                            }
                            cqItrator++ ;
                            cout<<"------------------------------------------------------" ;
                            cout<<"\n" ;
                            break ;
                        }
                        case 3:
                        {
                            LastTwoQuizzes[LastTwoQuizzes.size()-1].thisType[LastTwoQuizzesReapet]=3 ;
                            string SecAnswer ;
                            cout<<" [ " << i+1 << " ] "<<allTOF[tfArray[tfItrator]].QuestGetter()<<" True Or False \n"<<"\tYour Answer: " ;
                            LastTwoQuizzes[LastTwoQuizzes.size()-1].RightAnswers[LastTwoQuizzesReapet]=allTOF[tfArray[tfItrator]].ChoicesGetter(0) ;
                            LastTwoQuizzes[LastTwoQuizzes.size()-1].thisQuestion[LastTwoQuizzesReapet]=allTOF[tfArray[tfItrator]].QuestGetter();
                            if(RandomTypes[i-1]!=2)
                            {
                                cin.ignore(256, '\n');
                            }
                            while(true)
                            {
                                getline(cin,SecAnswer);
                                LastTwoQuizzes[LastTwoQuizzes.size()-1].thisAnswer[LastTwoQuizzesReapet]=SecAnswer ;
                                transform(SecAnswer.begin(), SecAnswer.end(), SecAnswer.begin(), ::toupper);
                                if(SecAnswer=="TRUE"||SecAnswer=="FALSE")
                                {
                                    break ;
                                }
                                else
                                {
                                    cout<<"Invalid Answer:\n \t Your Answer: " ;
                                }
                            }
                            Temp1 = allTOF[tfArray[tfItrator]].ChoicesGetter(0);
                            transform(Temp1.begin(), Temp1.end(), Temp1.begin(), ::toupper);
                            if(Temp1==SecAnswer)
                            {
                                LastTwoQuizzes[LastTwoQuizzes.size()-1].RightOrWrong[LastTwoQuizzesReapet]=1 ;
                                total+=1 ;
                                LastTwoQuizzes[LastTwoQuizzes.size()-1].RWAnswers++ ;
                                TFRight++ ;
                            }

                            tfItrator++ ;
                            cout<<"------------------------------------------------------" ;
                            cout<<"\n" ;
                            break ;
                        }
                        default:
                            cout<<"Invalid Input \n " ;
                        }
                        LastTwoQuizzesReapet++ ;

                    }
                    cout<<"Your Total Score For This Quiz: "<<total<<"/10"<<endl<<endl  ;
                    LastTwoQuizzes[LastTwoQuizzes.size()-1].total = total ;
                    if(total > highest)
                    {
                        highest = total ;
                    }
                    if(total < lowest)
                    {
                        lowest = total ;
                    }

                }
                system("PAUSE") ;
                break ;
            }
            case 4:
            {
                system("CLS") ;
                if(LastTwoQuizzes.size()==0)
                {
                    cout<<"You Should Start Quiz First \n" ;
                    system("PAUSE");
                }
                else
                {
                    DisplayScoreStat() ;
                    char choice ;
                    int repeat = 1 ;
                    while(repeat==1)
                    {
                        cin>>choice;
                        switch(choice)
                        {
                        case 'B':
                        case 'b':
                        {
                            repeat=0 ;
                            break ;
                        }
                        case 'E':
                        case 'e':
                        {
                            repeat = 0 ;
                            init = 0 ;
                            break ;
                        }
                        default :
                        {
                            cout<<"Invalid Choice Enter It Again\n" ;
                            break ;
                        }

                        }

                    }
                }
                break ;
            }
            case 5:
            {
                PrintingAllScores() ;
                system("PAUSE") ;
                break ;
            }
            case 6:
            {
                if(LastTwoQuizzes.size()==0)
                {
                    cout<<"You Should Start Quiz First \n" ;
                    system("PAUSE");
                    break ;
                }
                PrintingLastTwoQuizzes() ;
                system("PAUSE") ;
                break ;
            }
            case 7:
            {
                init=0 ;
                break ;
            }

            }
        }

    }

    return 0 ;

}
// =================== End Of The Main Function ========================== //

// --------------------  User Functions  ---------------------------------- //

// First One Makes You Login To Program.
bool LoginFun()
{
    string user,pass ;
    bool UserNameFound = false ;
    cout<<"Please enter your User Name: ";
    getline(cin,user);

    transform(user.begin(), user.end(), user.begin(), ::toupper);

    for(int i=0 ; i<User::ID; i++)
    {
        Temp1 = Login[i][0];
        transform(Temp1.begin(), Temp1.end(), Temp1.begin(), ::toupper);
        if(user==Temp1)
        {
            UserNameFound = true ;
            break ;
        }
    }

    if(UserNameFound)
    {

        cout<<"Please enter your password: " ;
        getline(cin,pass);
        for(int i=0; i<User::ID; i++)
        {
            NumberOFUsers = i ;
            Temp1 = Login[i][0];
            Temp2 = Login[i][1];
            transform(Temp1.begin(), Temp1.end(), Temp1.begin(), ::toupper);
            if(user==Temp1 && pass==Temp2)
            {
                LoginOrNot = true ;
                break;
            }
        }
        if(LoginOrNot==false)
        {
            cout<<"Wrong Password Please Try Again"<<endl ;
            system ("PAUSE");
            system ("CLS");

        }
    }
    else
    {
        cout<<"Wrong User Name Please Try Again."<<endl ;
        system ("PAUSE");
        system ("CLS");
    }


    return LoginOrNot ;
}
//_____________________________________________________________________//

// Adding User Function.
void AddNewUser()
{
    system("CLS");
    cin.ignore(256, '\n');
    int init2= 1 ;
    while(init2==1)
    {
        string firstname,lastname,user,pass,theRole;
        cout<<"Please Input your First Name: " ;
        getline(cin,firstname) ;
        cout<<"Please Input your Last Name: " ;
        getline(cin,lastname) ;
        cout<<"Please Input your UserName: " ;
        getline(cin,user) ;
        Temp1 = user ;
        transform(Temp1.begin(), Temp1.end(), Temp1.begin(), ::toupper);
        if(IsUserAlreadyAdded(Temp1))
        {
            cout<<"This UserName Already Added Please Try Again : \n" ;
            system("PAUSE") ;
            system ("CLS");
        }
        else
        {
            cout<<"Please Input Your Password: " ;
            getline(cin,pass) ;
            cout<<"Please Input The Role: ";
            getline(cin,theRole) ;
            transform(theRole.begin(), theRole.end(), theRole.begin(), ::toupper);
            if(theRole=="ADMIN")
            {
                allUsers.push_back(Admin(firstname,lastname,user,pass)) ;
                init2=0 ;
                break ;
            }
            else if(theRole=="PLAYER")
            {
                allUsers.push_back(Player(firstname,lastname,user,pass)) ;
                init2=0 ;
                break ;
            }
            else
            {
                cout<<"Invalid Role Please Input All Data Again\n" ;
                system("PAUSE") ;
                system ("CLS");
            }
        }
    }
}
//_____________________________________________________________________//

// To Check If There Is The Same UserName.
bool IsUserAlreadyAdded(string user)
{
    bool flag = false ;
    for (int i=0; i<allUsers.size(); i++)
    {
        if (allUsers[i] == user)
        {
            flag = true;
            break ;
        }

    }

    return flag ;
}
//_____________________________________________________________________//

// Printing All Users Data.
void ViewAllUsers()
{
    system("CLS");
    cout<<"\n" ;
    cout << "Existing users in the system: \n\n" ;
    cout.width(18);
    cout << left <<"First name" ;
    cout.width(18);
    cout << left <<"Last name" ;
    cout.width(18);
    cout << left <<"UserName";
    cout <<"Role \n\n" ;
    for(int i=0; i<(User::ID); i++)
    {
        allUsers[i].ViewUser();
    }
    cout<<endl ;
    char choice;
    cout<<"Press [n] if you want to add a new user or [b] to go back to the main menu.\n" ;
    cout<<"Choice: " ;
    cin>>choice ;

    while(1)
    {
        if(choice=='n'|| choice=='N')
        {
            AddNewUser() ;
            break ;
        }
        else if(choice == 'b'||choice=='B')
        {
            cout<<endl ;
            break ;
        }
        else
        {
            system ("CLS");
            cout<<"Invalid choice Try Again\n" ;
            cin>>choice ;
        }
    }

}
//============================== End Of User Functions =============================================//

// --------------------  Questions Functions  ---------------------------------- //

// Adding Questions Functions.
void AddingNewQuestions()
{
    system("CLS");

    char RepeatQuestion;
    int AddRepeat=1;

    while (AddRepeat==1)
    {
        string type ;
        cout<<"Please Input The Type of the Question: 1)MCQ 2)TF 3)Complete \n"<<"\t type: " ;
        cin >> type;
        transform(type.begin(), type.end(), type.begin(), ::toupper);
        if(type=="MCQ")
        {
            string quest1,choice1,choice2,choice3,choice4 ;
            int loop=1;
            AddRepeat=0;

            cout << "Please add your question :-\n";
            cin.ignore(256, '\n');
            getline(cin,quest1);

            if(questionExist(quest1,"MCQ"))
            {
                cout<<"The Question Exist \n" ;
                system("PAUSE") ;
                break ;
            }

            cout << "Please enter the Correct answer :-\n";
            getline(cin,choice1);

            cout << "Please enter the second choice:-\n";
            getline(cin,choice2);

            cout << "Please enter the third choice :-\n";
            getline(cin,choice3);

            cout << "Please enter the fourth choice :-\n";
            getline(cin,choice4);

            allMCQ.push_back(MCQ(quest1,choice1,choice2,choice3,choice4)) ;

            while (loop==1)
            {
                loop=0;
                cout << "Do you want to add another question\t (answer with Y/N)\n";
                cin  >> RepeatQuestion;

                switch (RepeatQuestion)
                {
                case 'y':
                case 'Y':
                    AddRepeat=1;
                    system ("CLS");
                    break;

                case 'n':
                case 'N':
                    break;

                default:
                    loop=1;
                    system ("CLS");
                }

            }
        }
        else if(type=="TF")
        {
            string quest1,choice1;
            int loop=1;
            AddRepeat=0;

            cout << "Please add your question :-\n";
            getline(cin,quest1);

            if(questionExist(quest1,"TF"))
            {
                cout<<"The Question Exist \n" ;
                system("PAUSE") ;
                break ;
            }

            cout << "Please enter the Correct answer :-\n"<<"\tTrue or False : " ;
            getline(cin,choice1);
            Temp1 = choice1 ;
            transform(Temp1.begin(), Temp1.end(), Temp1.begin(), ::toupper);
            if(Temp1=="TRUE"||Temp1=="FALSE")
            {
                allTOF.push_back(TOF(quest1,choice1)) ;
            }
            else
            {
                cout<<"Invalid Answer\n" ;
            }
            while (loop==1)
            {
                loop=0;
                cout << "Do you want to add another question\t (answer with Y/N)\n";
                cin  >> RepeatQuestion;

                switch (RepeatQuestion)
                {
                case 'y':
                case 'Y':
                    AddRepeat=1;
                    system ("CLS");
                    break;

                case 'n':
                case 'N':
                    break;

                default:
                    loop=1;
                    system ("CLS");
                }

            }
        }
        else if(type=="COMPLETE")
        {
            string quest1,choice1;
            int loop=1;
            AddRepeat=0;

            cout << "Please add your question :-\n";
            getline(cin,quest1);
            if(questionExist(quest1,"Complete"))
            {
                cout<<"The Question Exist \n" ;
                system("PAUSE") ;
                break ;
            }
            cout << "Please enter the Correct answer :-\n" ;
            getline(cin,choice1);
            allCQ.push_back(CompleteQuestion(quest1,choice1)) ;


            while (loop==1)
            {
                loop=0;
                cout << "Do you want to add another question\t (answer with Y/N)\n";
                cin  >> RepeatQuestion;

                switch (RepeatQuestion)
                {
                case 'y':
                case 'Y':
                    AddRepeat=1;
                    system ("CLS");
                    break;

                case 'n':
                case 'N':
                    break;

                default:
                    loop=1;
                    system ("CLS");
                }

            }
        }
        else
        {
            cout<<"Invalid Type \n\n" ;
        }
    }

}
//______________________________________________________________________________//

// to check if Question exist or not //
bool questionExist(string quest,string type)
{
    bool exist=false ;
    if(type=="MCQ")
    {
        for(int i=0; i<allMCQ.size(); i++)
        {
            if(allMCQ[i].QuestGetter()==quest)
            {
                exist=true ;
                break ;
            }
        }
    }
    else if(type=="TF")
    {
        for(int i=0; i<allTOF.size(); i++)
        {
            if(allTOF[i].QuestGetter()==quest)
            {
                exist=true ;
                break ;
            }
        }
    }
    else if(type=="Complete")
    {
        for(int i=0; i<allCQ.size(); i++)
        {
            if(allCQ[i].QuestGetter()==quest)
            {
                exist=true ;
                break ;
            }
        }
    }


    return exist ;
}
//_________________________________________________________________//

// Deleting Questions.
void DelQuestion(int delID)
{
    for(int i=0; i<allCQ.size(); i++)
    {
        if(allCQ[i].cqIDGetter()==delID)
        {
            allCQ.erase(allCQ.begin()+(i));
            QuestionsAvailable-- ;
        }
    }
    for(int i=0; i<allMCQ.size(); i++)
    {
        if(allMCQ[i].mcqIDGetter()==delID)
        {
            allMCQ.erase(allMCQ.begin()+(i));
            QuestionsAvailable-- ;
        }
    }
    for(int i=0; i<allTOF.size(); i++)
    {
        if(allTOF[i].tofIDGetter()==delID)
        {
            allTOF.erase(allTOF.begin()+(i));
            QuestionsAvailable-- ;
        }
    }
}
//______________________________________________________________________________//

// Loading From Your File.
void LoadQuestionsFromFile()
{
    bool DeleteOrNot = false ;
    char name[30];
    int typeChecker= 0, i=-1,repeat=1;
    cin.ignore(256, '\n');
    ifstream files;
    while (repeat==1)
    {
        repeat=0;
        cout << "Please enter the name of the file followed by (.txt)\n";
        cin.getline(name, 50, '\n');
        files.open(name);
        if (files.is_open())
        {
            string line;
            while (getline(files, line))
            {
                i++ ;
                if(typeChecker==0)
                {
                    if(line=="MCQ")
                    {
                        allMCQ.push_back(MCQ("1","2","3","4","5")) ;
                        allMCQ[(allMCQ.size()-1)].ClearChoices();
                        typeChecker=1 ;
                    }
                    else if(line=="TF")
                    {
                        allTOF.push_back(TOF("1","2")) ;
                        allTOF[(allTOF.size()-1)].ClearChoices();
                        typeChecker=2 ;
                    }
                    else if(line=="COMPLETE")
                    {
                        allCQ.push_back(CompleteQuestion("1","2")) ;
                        allCQ[(allCQ.size()-1)].ClearChoices();
                        typeChecker=3;
                    }
                    else
                    {
                        files.close();
                    }
                }
                if(typeChecker==1)
                {
                    switch (i)
                    {
                    case 1:
                        if(questionExist(line,"MCQ"))
                        {
                            //cout<<"The Question Exist \n" ;
                            DeleteOrNot = true ;
                            break ;
                        }
                        allMCQ[(allMCQ.size()-1)].QuestSetter(line);
                        break;
                    case 2:
                        allMCQ[(allMCQ.size()-1)].choicesPushBack(line);
                        break;
                    case 3:
                        allMCQ[(allMCQ.size()-1)].choicesPushBack(line);
                        break;
                    case 4:
                        allMCQ[(allMCQ.size()-1)].choicesPushBack(line);
                        break;
                    case 5:
                        allMCQ[(allMCQ.size()-1)].choicesPushBack(line);
                        i-=6;
                        if(DeleteOrNot==true)
                        {
                            allMCQ.erase(allMCQ.begin()+(allMCQ.size()-1));
                            QuestionsAvailable-=1 ;
                            Question::QuestionID -=1 ;
                            DeleteOrNot = false ;
                        }
                        typeChecker=0 ;
                        break;
                    }
                }
                else if(typeChecker==2)
                {
                    switch (i)
                    {
                    case 1:
                        if(questionExist(line,"TF"))
                        {
                            //cout<<"The Question Exist \n" ;
                            DeleteOrNot = true ;
                            break ;
                        }
                        allTOF[(allTOF.size()-1)].QuestSetter(line);
                        break;
                    case 2:
                        if(line=="true"||line=="false")
                        {
                            allTOF[(allTOF.size()-1)].choicesPushBack(line);
                            i-=3;
                            if(DeleteOrNot==true)
                            {
                                allTOF.erase(allTOF.begin()+(allTOF.size()-1));
                                QuestionsAvailable-=1 ;
                                Question::QuestionID -=1 ;
                                DeleteOrNot = false ;
                            }
                            typeChecker=0 ;
                            break;
                        }
                        else
                        {
                            cout<<"Invalid Answer\n The End of The file*\n"  ;
                            allTOF.erase(allTOF.begin()+(allTOF.size()-1));
                            files.close();
                            break ;
                        }

                    }
                }
                else if(typeChecker==3)
                {
                    switch (i)
                    {
                    case 1:
                        if(questionExist(line,"Complete"))
                        {
                            //cout<<"The Question Exist \n" ;
                            DeleteOrNot = true ;
                            break ;
                        }
                        allCQ[(allCQ.size()-1)].QuestSetter(line);
                        break;
                    case 2:
                        if(line!=" "||line!="\0")
                        {
                            allCQ[(allCQ.size()-1)].choicesPushBack(line);
                            i-=3;
                            if(DeleteOrNot==true)
                            {
                                allCQ.erase(allCQ.begin()+(allCQ.size()-1));
                                QuestionsAvailable-=1 ;
                                Question::QuestionID -=1 ;
                                DeleteOrNot = false ;
                            }
                            typeChecker=0 ;
                            break;
                        }
                        else
                        {
                            cout<<"The Answer Is Empty\n The End of The file*\n"  ;
                            allCQ.erase(allCQ.begin()+(allCQ.size()-1));
                            files.close();
                            break ;
                        }

                    }
                }

            }
        }
        else
        {
            system("CLS");
            cout << "invalid name \n";
            repeat=1;
        }
        files.close();
        cout << "done\n" << flush;
        system("PAUSE");
    }

}
//============================== End Of Question Functions =============================================//

// --------------------  Randomize Functions  ---------------------------------- //

//Randomize Your Questions For Quiz.
void RandomizeQuestions(int ourArrai[],int domain,int mysize)
{
    srand(time(0)) ;
    bool flag = false ;
    int arr[mysize];
    arr[0]=rand()%domain ;
    int init= 0 ;
    if(mysize!=1)
    {
        while(init!=mysize)
        {
            arr[init]=rand()%domain ;
            for(int i=0; i<mysize; i++)
            {
                if(init!=i)
                {
                    if(arr[init]==arr[i])
                    {
                        flag = false ;
                        break;
                    }
                    else
                    {
                        flag =true ;
                    }
                }
            }
            if(flag==true)
            {
                init +=1 ;
            }
        }
    }
    for(int i =0 ; i<mysize ; i++)
    {
        ourArrai[i]=arr[i];
    }

}
//______________________________________________________________________________//

// Randomizing Your Choices For MCQ Questions.
void RandomChoices (int arr[4])
{
    srand(time(0)) ;
    int number  = rand()%4,firstNumber = rand()%4,secondNumber = rand()%4,thirdNumber = rand()%4 ;
    while(firstNumber==number)
    {
        firstNumber = rand()%4 ;
    }
    while(secondNumber==number||secondNumber==firstNumber)
    {
        secondNumber = rand()%4 ;
    }
    while(thirdNumber==number || thirdNumber==firstNumber || thirdNumber==secondNumber)
    {
        thirdNumber = rand()%4 ;
    }
    arr[0]=number ;
    arr[1]=firstNumber;
    arr[2]=secondNumber;
    arr[3]=thirdNumber ;
}
//______________________________________________________________________________//

// Pushing And Organizing Types Of Question For Your Quiz.

void RandomTypesPushBack()
{
    RandomTypes.push_back(1);
    RandomTypes.push_back(1);
    RandomTypes.push_back(1);
    RandomTypes.push_back(2);
    RandomTypes.push_back(3);

}

//______________________________________________________________________________//

//============================== End Of Randomize Functions =============================================//

// --------------------  Quizzes Functions  ---------------------------------- //

// Case 5 For Player.
void DisplayScoreStat()
{
    cout<<"\n Your score statistics per quiz:\n"
        <<"\t- Number of Quizzes taken: "<<LastTwoQuizzes.size()<<endl
        <<"\t- Highest quiz score: "<<highest<<"/10\n"
        <<"\t- Lowest quiz score: "<<lowest<<"/10\n"
        <<"\t- Average quiz score: "<<calcAverage()<<"/10\n\n\n"
        <<" Your score statistics per question type: \n"
        <<"\t- Number of MC questions: "<<LastTwoQuizzes.size()*3<<endl
        <<"\t- Number of Complete questions: "<<LastTwoQuizzes.size()<<"\n"
        <<"\t- Number of T/F questions: "<<LastTwoQuizzes.size()<<"\n"
        <<"\t- Average grade for MC questions: "<<(MCQRight/(LastTwoQuizzes.size()*3))*2<<"/2\n"
        <<"\t- Average grade for Complete questions: "<<(CQRight/(LastTwoQuizzes.size()))*3<<"/3\n"
        <<"\t- Average grade for T/F questions: "<<(TFRight/(LastTwoQuizzes.size()))*1<<"/1\n\n"
        <<"Press [b] if you want to go back to the main menu or [e] to exit\n"
        <<"My Choice: " ;

}
//______________________________________________________________________________//

// Calculating The Average For Case 5.
double calcAverage()
{
    double sum = 0,average ;
    for(int i=0; i<LastTwoQuizzes.size(); i++)
    {
        sum += LastTwoQuizzes[i].total ;
    }

    average = sum / LastTwoQuizzes.size() ;

    return average;

}
//______________________________________________________________________________//

// Case 6 For The Player.
void PrintingAllScores()
{
    system("CLS") ;
    cout<<endl;
    cout<<"Number of Quizzes taken: "<<LastTwoQuizzes.size()<<endl ;
    for(int i=0; i<LastTwoQuizzes.size(); i++)
    {
        cout<<"\n\t Quiz "<<i+1<<" :\n\n" ;
        cout<<"\t The Number Of Right Answers: "<<LastTwoQuizzes[i].RWAnswers<<"/5"<<endl ;
        cout<<"\t The Number Of Wrong Answers: "<<5-LastTwoQuizzes[i].RWAnswers<<"/5"<<endl ;
        cout<<"\t The Score Of This Quiz: "<<LastTwoQuizzes[i].total<<"/10" ;
        cout<<"\n\n" ;
    }
}
//______________________________________________________________________________//

// Print Last 2 Quizzes Or Any Quiz You Want To Print.
void PrintingLastTwoQuizzes()
{
    system("ClS") ;
    int number = 1 ;
    int t2 ;
    int i=(LastTwoQuizzes.size()-2) ;

    if(LastTwoQuizzes.size()==1)
        i=0 ;

    for(i; i<LastTwoQuizzes.size(); i++)
    {
        cout<<"\n Quiz "<<number<<" :\n\n" ;
        for(int x=0; x<5; x++)
        {
            t2 = LastTwoQuizzes[i].thisType[x] ;
            switch(t2)
            {
            case 1:
                cout<<"\t[ " << x+1 << " ]" << LastTwoQuizzes[i].thisQuestion[x] <<endl;
                cout<<"\t\t[a]"<<LastTwoQuizzes[i].thisChoices[x][0]
                    <<"\t[b]"<<LastTwoQuizzes[i].thisChoices[x][1]
                    <<"\t[c]"<<LastTwoQuizzes[i].thisChoices[x][2]
                    <<"\t[d]"<<LastTwoQuizzes[i].thisChoices[x][3]<<endl
                    <<"\tYour Answer is: "<<LastTwoQuizzes[i].thisAnswer[x][0]<<endl
                    <<"\tThe Right Answer IS: "<<LastTwoQuizzes[i].RightAnswers[x]<<endl
                    <<"\t The Score For This Question: "<<LastTwoQuizzes[i].RightOrWrong[x]
                    <<endl<<endl ;

                break ;
            case 2:
                cout<<"\t [ " << x+1 << " ]" << LastTwoQuizzes[i].thisQuestion[x] <<endl;
                cout<<"\t Your Answer is: "<<LastTwoQuizzes[i].thisAnswer[x]<<endl
                    <<"\t The Right Answer IS: "<<LastTwoQuizzes[i].RightAnswers[x]<<endl
                    <<"\t The Score For This Question: "<<LastTwoQuizzes[i].RightOrWrong[x]
                    <<endl<<endl ;
                break ;
            case 3:
                cout<<"\t[ " << x+1 << " ]" << LastTwoQuizzes[i].thisQuestion[x] <<endl
                    <<"\t Your Answer is: "<<LastTwoQuizzes[i].thisAnswer[x]<<endl
                    <<"\t The Right Answer IS: "<<LastTwoQuizzes[i].RightAnswers[x]<<endl
                    <<"\t The Score For This Question: "<<LastTwoQuizzes[i].RightOrWrong[x]
                    <<endl<<endl  ;
                break ;
            }
        }

        cout<<"The Total Score For This Quiz: "<<LastTwoQuizzes[i].total<<endl ;
        cout<<"-------------------------------------------------";
        cout<<"\n\n" ;

        number++ ;
    }
}
//============================== End Of Quiz Functions =============================================//
