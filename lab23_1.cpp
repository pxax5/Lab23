#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream fin(filename);
    string line;
    while(getline(fin, line)){
        size_t loc = line.find_first_of(':');
        if(loc != string::npos){
            string name = line.substr(0, loc);
            string scoreStr = line.substr(loc + 1);
            int s1, s2, s3;
            stringstream ss(scoreStr);
            ss >> s1 >> s2 >> s3;
            int total = s1 + s2 + s3;
            names.push_back(name);
            scores.push_back(total);
            grades.push_back(score2grade(total));
        }
    }
}

void getCommand(string &cmd, string &key){
    cout << "Please input your command: \n";
    string input;
    getline(cin, input);
    size_t loc = input.find_first_of(' ');
    if(loc != string::npos){
        cmd = input.substr(0, loc);
        key = input.substr(loc + 1);
    }else{
        cmd = input;
        key = "";
    }
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            found = true;
        }
    }
    if(!found) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size(); i++){
        string gStr = "";
        gStr += grades[i];
        if(gStr == key){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if(!found) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades;
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}