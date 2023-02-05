#include<iostream>
#include<string>
#include <sstream>
#include <cctype>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::istringstream;
using std::tolower;
using std::map;

string text = R"TEXT(
    Hello there. My name is Tarek, and I'd like to show you how to counts words in C++.
    To be honest, I'm not totally sure how I'll do it, since I'm not completely familiar
    with the C++ standard library. I'm thinking I'll use string stream and map, but 
    we'll see...
)TEXT";

void eraseChar(string& s, char c) {
    decltype(s.find("")) position = s.find(c);
    while (position != string::npos) {
        s.erase(position, 1);
        position = s.find(c);
    }
}

int main() {
    eraseChar(text, '.');
    eraseChar(text, ',');

    for (char &c : text) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }

    istringstream stream(text);
    map<string, unsigned int> counts;;
    
    string current;
    while (stream >> current) {
        ++counts[current];
    }

    for (auto pair : counts) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}