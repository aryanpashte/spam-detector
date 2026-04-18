#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<string> spamwords = {"free",  "win",     "offer",   "click",   "urgent", "money",
                            "prize", "lottery", "buy now", "limited", "bonus",  "gift",
                            "claim", "hurry",   "reward",  "now"};

void clrscr() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void addSpamWord() {
    int n;  // number of spam words;
    cout << "Enter the number Spam words You want add in the list: ";
    cin >> n;
    cout << "Enter all the spam words you want to add\n";
    for (int i = 0; i < n; i++) {
        string s;  // spam word user wants to add;
        cin >> s;
        spamwords.emplace_back(s);
    }
}

void displaySpamwords(string message) {
    map<string, int> freq;
    for (string word : spamwords) {
        size_t pos = message.find(word);
        while (pos != string::npos) {
            freq[word]++;
            pos = message.find(word, pos + 1);
        }
    }
    cout << "\n\tSpam words  -  frequency\n";
    for (auto x : freq) cout << "\t" << x.first << "  -  " << x.second << "\n";
}

void checkSpam(string message) {
    int score = 0;
    for (string word : spamwords) {
        size_t pos = message.find(word);
        while (pos != string::npos) {
            score++;
            pos = message.find(word, pos + 1);
        }
    }
    stringstream ss(message);
    string temp;
    int totalWords = 0;
    while (ss >> temp) totalWords++;
    double probability = (double)score / totalWords * 100;
    cout << "Spam probability: " << probability << "\n";
    if (probability <= 10)
        cout << "NOT SPAM\n";
    else if (probability <= 30)
        cout << "LIKELY SPAM\n";
    else
        cout << "SPAM CONFIRMED\n";
}

string getMessage() {
    string message, line;
    cout << "Enter message (PRESS Enter and type END after writing the entire message): \n";
    cin.ignore();
    while (true) {
        getline(cin, line);
        if (line == "END") break;
        message += line + " ";
    }
    transform(message.begin(), message.end(), message.begin(), ::tolower);
    return message;
}

int main() {
    cout << "\t\tWelcome to spamchecker\n";
    cout << "\n";
    cout << "\n";
    char ch;
    string message = getMessage();
    do {
        clrscr();
        cout << "Choose avaliable options\n";
        cout << "1. ADD SPAMWORDS\n";
        cout << "2. DISPLAY SPAMWORDS\n";
        cout << "3. CHECK SPAM\n";
        cout << "4. ENTER NEW MESSAGE\n";
        cout << "5. EXIT\n";
        int choice;
        cout << "ENTER YOUR CHOICE: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addSpamWord();
                break;
            case 2:
                displaySpamwords(message);
                break;
            case 3:
                checkSpam(message);
                break;
            case 4:
                message = getMessage();
                break;
            case 5:
                exit(0);
                break;
            default:
                cout << "Invalid Choice\n";
        }
        cout << "Do you want to continue(yes == y/Y or no == n/N): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    return 0;
}
