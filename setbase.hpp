#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class SetBase {
private:
    vector<string> elementSet;
    vector<SetBase> setSet;
public:
    
    void addElement(string element);

    void removeElement(string element);

    int simpleElementsNumber();
    int setsNumber();
    string getElement(int index);

    int cardinality();

    string intoString();

    friend bool operator==(const SetBase& oneSet, const SetBase& anotherSet);
    friend bool operator!=(const SetBase& oneSet, const SetBase& anotherSet);

    bool operator[](const string& element) const;

    bool empty();
};


