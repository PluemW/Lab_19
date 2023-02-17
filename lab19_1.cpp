#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

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
    ifstream file(filename);
    string text;
    char n[100];
    while(getline(file, text)){
        int score1, score2, score3, sums=0;
        sscanf(text.c_str(), "%[^:]: %d %d %d", n, &score1, &score2, &score3);
        names.push_back(n);
        sums = score1+score2+score3;
        scores.push_back(sums);
        grades.push_back(score2grade(sums));
    }
}

void getCommand(string &command, string &key){
    string ser;
    cout << "Please input your command: ";
    getline(cin, ser);
    int start = 0; int end = ser.find_first_of(" ");
    command = ser.substr(start, end-start);
    start = end+1;
    key = ser.substr(start, ser.size()-start);
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";
    string check;
    bool c = true;
    for(unsigned int i=0; i<names.size(); i++){
        check = toUpperStr(names[i]);
        if(key==check){
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            c = false;
        }
    }
    if(c==1) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";
    bool c = true;
    for(unsigned int i=0; i<names.size(); i++){
        string check;
        check += grades[i];
        if(toUpperStr(key)==toUpperStr(check)){
            cout << names[i] << " (" << scores[i] << ")\n";
            c = false;
        }
    }
    if(c==1) cout << "Cannot found.\n";
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
