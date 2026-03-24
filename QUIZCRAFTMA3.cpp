#include <iostream>
#include <fstream>
#include <limits>
using namespace std;
	

void clearScreen() {
    system("cls");
}


void displayMenu() {
    clearScreen();
    cout <<"                          **************************" << endl;
    cout <<"                             Welcome to QuizCraft!!!" << endl;
    cout <<"                          **************************" << endl;
    cout << "Please enter your option: " << endl;
    cout << "1 - TEACHERS" << endl;
    cout << "2 - STUDENTS" << endl;
    cout << endl;
}

void displayTeacherMenu() {
    clearScreen();
    cout << "                          **************************" << endl;
    cout << "                           Welcome to the Teacher's menu!!!" << endl;
    cout << "                          **************************" << endl;
    cout << "1 - Create a quiz" << endl;
    cout << "2 - View students answer" << endl;
    cout << endl;
}

void displayStudentMenu() {
	clearScreen();
    cout << "Welcome to the Student's menu!!!" << endl;
    cout << "1 - Attempt a quiz" << endl;
    cout << "2 - View high scores" << endl;
    cout << endl;
}

void createQuiz() {
    
	ofstream dataFile("records.txt", ios::app);

    if (!dataFile) {
        cout << "Error opening file!" << endl;
        return;
    }
    
    int select;
   int numQuestions;

    cout << "Enter the number of questions: ";
    cin >> numQuestions;

    for (int i = 0; i < numQuestions; ++i) {
        int questionType;
        cout << "Select the question type for question #" << i + 1 << ": " << endl;
        cout << "1 - Identification" << endl;
        cout << "2 - Fill in the blanks" << endl;
        cout << "3 - True or False" << endl;
        cout << "4 - Multiple Choice" << endl;
        cin >> questionType;

        string question;
        cout << "Enter the question text for question #" << i + 1 << ": ";
        cin.ignore();
        getline(cin, question);

        if (questionType != 4) {
            string correctanswer;
            cout << "Enter the correct answer for question #" << i + 1 << ": ";
            getline(cin, correctanswer);

            dataFile << "Question #" << i + 1 << " Type: ";

            switch (questionType) {
                case 1:
                    dataFile << "Identification" << endl;
                    break;
                case 2:
                    dataFile << "Fill in the Blanks" << endl;
                    break;
                case 3:
                    dataFile << "True or False" << endl;
                    break;
                default:
                    dataFile << "Unknown" << endl;
                    break;
            }

            dataFile<<question<<endl;
            dataFile<<"Correct Answer: "<<correctanswer<<endl;
        } else {
            dataFile << "Question #" << i + 1 << " Type: Multiple Choice" << endl;
            dataFile << question << endl;

            string choices[4]={"A","B","C","D"};
            for (int j=0;j<4;++j){
                string choice;
                cout<<"Enter choice "<<choices[j]<<" for question #"<< i + 1 <<":";
                getline(cin,choice);
                dataFile<<choices[j]<<") "<< choice << endl;
            }

            char correctletter;
            cout << "Enter the correct letter for question #" << i + 1 << ": ";
            cin >> correctletter;
            dataFile<<"Correct Answer:"<<correctletter<<endl;
        }
    }

    dataFile.close();
}



void answerQuiz() {
    ifstream questionsFile("records.txt");
    ofstream answersFile("studentsAnswer.txt");

    if (!questionsFile || !answersFile) {
        cout << "Error opening files!" << endl;
        return;
    }

    clearScreen();
    string line;
    int questionCount = 0;
    string firstName;
    string timeStarted;

    cout << "Enter your FIRST NAME: ";
    cin >> ws; 
    getline(cin, firstName);
    cout << "Enter TIME STARTED (__:__PM/AM): ";
    getline(cin, timeStarted);
    answersFile<<"Student Name: "<<firstName<<endl;
    answersFile<<"Time Started: "<<timeStarted<<endl;
    answersFile<<endl;
  while(getline(questionsFile,line)) {
        if(line.find("Question #")!=string::npos) {
            questionCount++;
            cout<<line<<endl;
            answersFile<<"Question #"<<questionCount<<":"<<endl;
            answersFile<<line<<endl;
            while(getline(questionsFile,line)&&line.find("Correct Answer:")==string::npos){
                cout<<line<<endl;
                answersFile<<line<<endl;
            }
            cout<<"Enter your answer for question #"<<questionCount<<": ";
            string studentAnswer;
            getline(cin >>ws, studentAnswer);

            answersFile << "Student's Answer for #" << questionCount << ": " << studentAnswer << std::endl;
            clearScreen();
        }
    }

    clearScreen();
    cout << "Quiz completed. Your answers have been saved in 'studentsAnswer.txt'." << endl;

   
    questionsFile.clear(); 
    questionsFile.seekg(0); 

    cout << "Correct Answers:" << endl;
    while (getline(questionsFile, line)) {
        if (line.find("Correct Answer:") != string::npos) {
            cout << line << endl;
        }
    }
}
void viewStudentAnswers() {
    ifstream answersFile("studentsAnswer.txt");
    ifstream correctAnswersFile("records.txt");

    if (!answersFile || !correctAnswersFile) {
        cout << "Error opening files!" << endl;
        return;
    }

    clearScreen();
    string studentLine, correctLine;
    cout << "Student Answers vs Correct Answers:" << endl;
    
    while (getline(answersFile, studentLine) && getline(correctAnswersFile, correctLine)) {
        if (studentLine.find("Student's Answer for #") != string::npos) {
            string studentAnswer = studentLine.substr(studentLine.find(":") + 2);
            string correctAnswer = correctLine.substr(correctLine.find(":") + 2);

            cout << "Your Answer:    " << studentAnswer << endl;
            cout << "Correct Answer: " << correctAnswer << endl;
            cout << "Result: " << (studentAnswer == correctAnswer ? "Correct" : "Incorrect") << endl;
            cout << endl;
        }
    }

    answersFile.close();
    correctAnswersFile.close();

    cout << "\nPress Enter to return to the menu";
    answersFile.clear(); 
answersFile.seekg(0); 

correctAnswersFile.clear(); 
correctAnswersFile.seekg(0);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    clearScreen();
}



void viewFiles(){}

void checkUserSelection(int select){
    if (select==1){
        string teacherPass,selection,teacherUser;
        cout<<"Please eneter your username:";
        cin>>teacherUser;
        cout<<"Please enter your password: ";
        cin>>teacherPass;
        if(teacherPass =="2024"&&teacherUser=="DLSLTeacher"){
            displayTeacherMenu();
            int selection;
            cout<<"Please enter your option: ";
            cin>> selection;
            cout<<endl;
            if(selection==1){
                createQuiz();
            } else if(selection==2) {
                viewStudentAnswers();
            } else{
                cout<<"Invalid option. Please try again."<<endl;
                checkUserSelection(select);
            }
        }else{
            cout<<"Wrong password. Please try again."<<endl;
            checkUserSelection(select);
        }
    }else if(select==2){
        string studentUsername,studentPassword;
        cout<<"Please enter your username: ";
        cin>>studentUsername;
        cout<<"Please enter your password: ";
        cin>>studentPassword;
        if (studentUsername =="DLSLStudent"&&studentPassword =="2024") {
            displayStudentMenu();
            int studentOption;
            cout<<"Please enter your option: ";
            cin>>studentOption;
            cout<<endl;

            if(studentOption==1){
                answerQuiz();
            }else if(studentOption==2){
         	 viewStudentAnswers();
            }
        } else{
            cout<<"Invalid username or password. Please try again." << endl;
            checkUserSelection(select);
        }
    } else{
        cout<<"Invalid option. Please try again."<<endl;
        checkUserSelection(select);
    }
}


int main() {
    displayMenu();
    int select;
    cout << "Please enter your option: ";
    cin >> select;
    cout << endl;
    checkUserSelection(select);
    return 0;
}