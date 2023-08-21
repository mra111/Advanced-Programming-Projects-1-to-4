#include <iostream>
#include <string>
using namespace std;


bool check_word (string word1, string word2, string subword);
bool is_sub (string word1, string word2, string subword);


bool check_word (string word1, string word2, string subword) {
    if (is_sub (word1, word2, subword) == true) {
        return true;
    }
    else if (is_sub (word2, word1, subword) == true) {
        return true;
    }
    else {
        return false;
    }
}

bool is_sub (string word1, string word2, string subword) {
    if (word1 == "" && word2 == "" && subword == "") {
        return true;
    }
    if (word1[0] == subword[0]) {
        word1 = word1.substr (1);
        subword = subword.substr (1);
        return check_word (word1, word2, subword);
    }
    else if (word2[0] == subword[0]) {
        word2 = word2.substr (1);
        subword = subword.substr (1);
        return check_word (word1, word2, subword);
    }
    else {
        return false;
    }
}

void print_result (bool result) {
    if (result == true) {
        cout << "Interleaving" << endl;
    }
    else {
        cout << "Not Interleaving" << endl;
    }
}


int main () {
    bool result;
    string word1;
    string word2;
    string subword;
    cin >> word1;
    cin >> word2;
    cin >> subword;

    result = check_word (word1, word2, subword);

    print_result (result);

    return 0;
}