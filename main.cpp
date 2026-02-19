#include <iostream>
#include <time.h>
using namespace std;

enum enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, mix = 4};

enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mix = 5};

enum enPassFail { Pass = 1, Fail = 2};

struct stQuiz {
    int Questions = 0;
    enQuestionsLevel QuestionLevel;
    enOperationType OperationType;
    int NumberOfRightAnswers = 0;
    int NumberOfWrongAnswers = 0;
    enPassFail Result;
};

struct stAnswers {
    int number1 = 0;
    int number2 = 0;
    int RightAnswer = 0;
    int UserAnswer = 0;
};

int GetRandomNumber(int from,int to) {

    int number = rand() % (to - from + 1) + from;
    return number;
}

short ReadNumber(string message) {
    short number;

    cout << message << endl;
    cin >> number;

    return number;
}

enQuestionsLevel GetQuestionLevel() {
    short number;
    do {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> number;
    } while (number < 1 || number > 4);

    return (enQuestionsLevel)number;
}

enOperationType GetOperationType() {
    
    short number = 0;
    do {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> number;
    } while(number < 1 || number > 5);

    return (enOperationType)number;
}

stAnswers GetNumbers(stQuiz quiz) {

    stAnswers answers;

    if(quiz.QuestionLevel == enQuestionsLevel::mix) {
        int temp = GetRandomNumber(1,3);
        quiz.QuestionLevel = (enQuestionsLevel)temp;
    }

    switch (quiz.QuestionLevel)
    {
    case enQuestionsLevel::Easy:
        answers.number1 = GetRandomNumber(1,9);
        answers.number2 = GetRandomNumber(1,9);
        break;
    case enQuestionsLevel::Med:
        answers.number1 = GetRandomNumber(10,25);
        answers.number2 = GetRandomNumber(10,25);
        break;
    case enQuestionsLevel::Hard:
        answers.number1 = GetRandomNumber(26,50);
        answers.number2 = GetRandomNumber(26,50);
        break;
    }
    return answers;
}

string ReturnResult(enPassFail result) {
    
    switch (result)
    {
    case enPassFail::Pass:
        return "Pass";
        break;
    case enPassFail::Fail:
        return "Fail";
        break;
    }
    return "";
}

string ReturnLevel(enQuestionsLevel level) {
    switch (level)
    {
    case enQuestionsLevel::Easy:
        return "Easy";
        break;
    case enQuestionsLevel::Med:
        return "Med";
        break;
    case enQuestionsLevel::Hard:
        return "Hard";
        break;
    case enQuestionsLevel::mix:
        return "Mix";
        break;
    }
    return "";
}

string ReturnOperationType(enOperationType Optype) {
    switch (Optype)
    {
    case enOperationType::Add:
        return "Add";
        break;
    case enOperationType::Sub:
        return "Sub";
        break;
    case enOperationType::Mul:
        return "Mul";
        break;
    case enOperationType::Div:
        return "Div";
        break;
    case enOperationType::Mix:
        return "Mix";
        break;
    }
    return "";
}

enPassFail HasPass(stQuiz quiz) {

    if(quiz.NumberOfRightAnswers > quiz.NumberOfWrongAnswers) {
        return enPassFail::Pass;
    } else {
        return enPassFail::Fail;
    }
}

void GetResult(stQuiz quiz) {

    cout << "------------------------------" << endl;
    cout << "Final Results is "<< ReturnResult(HasPass(quiz)) << endl;
    cout << "-------------------------------" << endl;
    cout << "Number Of Questions: " << quiz.Questions << endl;
    cout << "Questions Level: " << ReturnLevel(quiz.QuestionLevel) << endl;
    cout << "OpType: " << ReturnOperationType(quiz.OperationType) << endl;
    cout << "Number Of Right Answers: " << quiz.NumberOfRightAnswers << endl;
    cout << "Number Of Wrong Answers: " << quiz.NumberOfWrongAnswers << endl;
    cout << "--------------------------------" << endl;

}

void GetQuestion(stQuiz &quiz) {

    stAnswers answers = GetNumbers(quiz);

    switch (quiz.OperationType)
    {
    case enOperationType::Add:
        answers.RightAnswer = answers.number1 + answers.number2;
        break;
    case enOperationType::Sub:
        answers.RightAnswer = answers.number1 - answers.number2;
        break;
    case enOperationType::Mul:
        answers.RightAnswer = answers.number1 * answers.number2;
        break;
    case enOperationType::Div:
        answers.RightAnswer = answers.number1 / answers.number2;
        break;
    }

    cout << answers.number1 << endl;
    cout << answers.number2 << " " << ReturnOperationType(quiz.OperationType) << endl;
    cout << "---------------------" << endl;
    cin >> answers.UserAnswer;
        
    if(answers.UserAnswer == answers.RightAnswer) {
        cout << "Right Answer :-)" << endl;
        quiz.NumberOfRightAnswers++;
    } else {
        cout << "Wrong Answer :-(" << endl;
        cout << "The right answer is: " << answers.RightAnswer << endl;
        quiz.NumberOfWrongAnswers++;
    } 

}

void GetQuestions(stQuiz &quiz) {

    bool Mixed = false;

    for(short i = 1; i <= quiz.Questions; i++) {
        cout << "Question [" << i << "/" << quiz.Questions << "]" << endl;
        if(quiz.OperationType == enOperationType::Mix || Mixed) {
            int temp = GetRandomNumber(1,4);
            quiz.OperationType = (enOperationType)temp;
            Mixed = true;
        }
        GetQuestion(quiz);
    }
    if(Mixed) {
        quiz.OperationType = enOperationType::Mix;
    }
}

void ResetScreen() {
    system("cls");
    system("color 0F");
}

void StartQuiz() {

    stQuiz quiz;
    char PlayAgain;
    do {
        quiz.Questions = ReadNumber("How Many Questions do you want to answer ? ");
        quiz.QuestionLevel = GetQuestionLevel();
        quiz.OperationType = GetOperationType();
        GetQuestions(quiz);
        GetResult(quiz);
        cout << "Do you want to play again? Y/N ";
        cin >> PlayAgain;
    } while(PlayAgain == 'Y' || PlayAgain == 'y');

}

int main() {
    srand((unsigned)time(NULL)); 

    StartQuiz();

    return 0;
}