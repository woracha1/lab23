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

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream source ;
    source.open(filename); 
    string textline ;
    while(getline(source,textline)){
        char format[] = "%[^:]:%d%d%d" ;
        char name[100] ;
        int a,b,c ;
        sscanf(textline.c_str(),format,name,&a,&b,&c);
        names.push_back(name) ;
        scores.push_back(a+b+c) ;
        grades.push_back(score2grade(a+b+c));
    }
}

void getCommand(string &command,string &key){
    string input ;
    cout << "Please input your command:" << endl;
    getline(cin,input);
    int x = input.find_first_of(" ");
    command = input.substr(0,x);
    key = input.substr(x+1);
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------" << endl ;
    bool x = false ;
    for(unsigned int i = 0 ; i < names.size() ; i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << endl ;
            cout << names[i] << "'s grade = " << grades[i] << endl ;
            x = true;
        }
    }
    if(!x) cout << "Cannot found.\n";
    cout << "---------------------------------" << endl ;
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------" << endl ;
    bool x = false ;
    char grade = key[0] ;
    for(unsigned int i = 0 ; i < grades.size() ; i++){
        if(grade == grades[i]){
            cout << names[i] << " (" << scores[i] << ")" << endl ;
            x = true ;
        }
    }
    if(!x) cout << "Cannot found." << endl ;
    cout << "---------------------------------" << endl ;
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
