#pragma once

#include "setbase.hpp"

class Set : public SetBase {
private:
    SetBase set;
public:
    Set& operator+=(Set anotherSet);
    Set operator+(const Set &anotherSet);

    Set &operator*=(Set anotherSet);
    Set operator*(const Set &anotherSet);
    
    Set& operator-=(Set anotherSet);
    Set operator-(const Set &anotherSet);

    friend ostream& operator<<(ostream& outStream, const Set& set);
    friend Set& operator>>(Set& set, string setString);

    void generateSubsets(Set& currentSubset, int index, Set& result);
    Set powerSet();

    void pop();
};

Set parseSet(string setString);
void parseSet_closingBracket(string setString, Set& result, int index, int& elementStart, int& depth, int& subsetStart);
void parseSet_finishElement(string setString, Set& result, int index, int& elementStart, int& depth);

bool isSet(string element);
