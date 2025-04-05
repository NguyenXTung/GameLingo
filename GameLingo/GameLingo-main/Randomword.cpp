#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Randomword.h"
using namespace std;
// chon ngau nhien 1 tu trong kho tu khoa
string randomkeyword(int ROW){
    string result;
    srand(time(0));
    ifstream file("words3.txt");
    if (!file.is_open()) {
        cerr << "Không thể mở file từ điển!" << endl;
    }
    vector<string> words;
    string word;
    while (getline(file, word)) {
        words.push_back(word);
    }
    file.close();
    //chọn ngẫu nhiên 1 từ
    bool valid = true;
    while(valid){
    valid = false;
    string a;
    for(int j = 0; j < 6; j++){
        int ran = rand() % 10;
        a+= to_string(ran);
    }
    int randomIndex = stoi(a) % words.size();
    string randomWord = words[randomIndex];
    int n = randomWord.size();
    bool checkviettat = true;
    for(int i = 0; i < n; i++){
        if(randomWord[i] >= 'a' && randomWord[i] <= 'z'){
            randomWord[i] = char(randomWord[i]-32);
            checkviettat = false;
        }
        if(checkviettat) valid = true;
        if(!(randomWord[i] >= 'A' && randomWord[i] <= 'Z')){
            valid = true;
        }
    }
    if(n != ROW) valid = true;
    result = randomWord;
    }
    return result;
}
