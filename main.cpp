#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class User {
public:
    string username;
    string password;

    User(string u, string p) : username(u), password(p) {}

    bool login(string uname, string pwd) {
        return uname == username && pwd == password;
    }

    static void signUp(string uname, string pwd) {
        ofstream userFile("users.txt", ios::app);
        if (userFile.is_open()) {
            userFile << uname << " " << pwd << endl;
            userFile.close();
        } else {
            cout << "Unable to open file to save user data." << endl;
        }
    }

    static bool authenticate(string uname, string pwd) {
        ifstream userFile("users.txt");
        string u, p;
        if (userFile.is_open()) {
            while (userFile >> u >> p) {
                if (u == uname && p == pwd) {
                    userFile.close();
                    return true;
                }
            }
            userFile.close();
        } else {
            cout << "Unable to open file for authentication." << endl;
        }
        return false;
    }
};

class Question {
public:
    string questionText;
    vector<string> options;
    int correctOption;

    Question(string q, vector<string> opts, int correct) : questionText(q), options(opts), correctOption(correct) {}

    void display() {
        cout << questionText << endl;
        for (int i = 0; i < options.size(); ++i) {
            cout << i + 1 << ". " << options[i] << endl;
        }
    }

    bool checkAnswer(int userAnswer) {
        return userAnswer == correctOption;
    }
};

class Quiz {
public:
    vector<Question> questions;

    void addQuestion(Question q) {
        questions.push_back(q);
    }

    int conductQuiz() {
        int score = 0;
        int answer;
        for (int i = 0; i < questions.size(); ++i) {
            questions[i].display();
            cout << "Your answer: ";
            cin >> answer;
            if (questions[i].checkAnswer(answer)) {
                score++;
            }
        }
        return score;
    }
};

void saveResult(string username, int score) {
    ofstream resultFile("results.txt", ios::app);
    if (resultFile.is_open()) {
        resultFile << username << " scored " << score << " out of " << 3 << endl;
        resultFile.close();
    } else {
        cout << "Unable to open file to save result." << endl;
    }
}

int main() {
    int choice;
    string username, password;

    cout << "Welcome to the Online Quiz System!" << endl;
    cout << "1. Sign Up" << endl;
    cout << "2. Log In" << endl;
    cout << "Choose an option: ";
    cin >> choice;

    if (choice == 1) {
        // Sign up process
        cout << "Enter a new username: ";
        cin >> username;
        cout << "Enter a new password: ";
        cin >> password;
        User::signUp(username, password);
        cout << "Sign-up successful! Please log in." << endl;
    }

    // Log in process
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (User::authenticate(username, password)) {
        cout << "Login successful!" << endl;

        Quiz quiz;

        // Adding questions to the quiz
        quiz.addQuestion(Question("What is the capital of France?", {"Paris", "Berlin", "Madrid", "Rome"}, 1));
        quiz.addQuestion(Question("What is 2 + 2?", {"3", "4", "5", "6"}, 2));
        quiz.addQuestion(Question("What is the largest planet in our solar system?", {"Earth", "Mars", "Jupiter", "Venus"}, 3));

        int score = quiz.conductQuiz();

        cout << "Quiz completed! Your score: " << score << " out of " << quiz.questions.size() << endl;

        saveResult(username, score);
    } else {
        cout << "Invalid username or password. Try again." << endl;
    }

    return 0;
}
