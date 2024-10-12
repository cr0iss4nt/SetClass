#include "bset.hpp"
using namespace std;

bool isSet(string element) {
    return (element[0] == '{' && element[element.size() - 1] == '}');
}



void SetBase::addElement(string element) {
    if (isSet(element) && find(setSet.begin(), setSet.end(), parseSet(element)) == setSet.end()) {
        setSet.push_back(parseSet(element));
        for (int i = setSet.size() - 1; i > 0; i--)
        {
            if (setSet[i].intoString() < setSet[i - 1].intoString())
                swap(setSet[i], setSet[i - 1]);
            else
                break;
        }
    }
    else if (find(elementSet.begin(), elementSet.end(), element) == elementSet.end()) {
        elementSet.push_back(element);
        for (int i = elementSet.size() - 1; i > 0; i--)
        {
            if (elementSet[i] < elementSet[i - 1])
                swap(elementSet[i], elementSet[i - 1]);
            else
                break;
        }
    }
}

void SetBase::removeElement(string element) {
    if (isSet(element)) {
        auto it = find(setSet.begin(), setSet.end(), parseSet(element));
        if (it != setSet.end())
            setSet.erase(it);
    }
    else {
        auto it = find(elementSet.begin(), elementSet.end(), element);
        if (it != elementSet.end())
            elementSet.erase(it);
    }
}

int SetBase::simpleElementsNumber() {
    return elementSet.size();
}
int SetBase::setsNumber() {
    return setSet.size();
}

string SetBase::getElement(int index) {
    if (index < 0 || index >= cardinality())
        return "";
    if (index < elementSet.size() && index >= 0)
        return elementSet[index];
    return setSet[index - elementSet.size()].intoString();
}

int SetBase::cardinality() {
    return elementSet.size() + setSet.size();
}

string SetBase::intoString() {
    string stringOutput = "";
    stringOutput += "{";
    for (size_t i = 0; i < elementSet.size(); i++) {
        stringOutput += elementSet[i];
        if (i != elementSet.size() - 1 || !setSet.empty())
            stringOutput += ", ";
    }
    for (size_t i = 0; i < setSet.size(); i++) {
        stringOutput += setSet[i].intoString();
        if (i != setSet.size() - 1)
            stringOutput += ", ";
    }
    stringOutput += "}";
    return stringOutput;
}

bool operator==(const SetBase& oneSet, const SetBase& anotherSet) {
    return (oneSet.elementSet == anotherSet.elementSet) && (oneSet.setSet == anotherSet.setSet);
}
bool operator!=(const SetBase& oneSet, const SetBase& anotherSet) {
    return !(oneSet == anotherSet);
}

bool SetBase::operator[](const string& element) const {
    if (isSet(element))
        return (find(setSet.begin(), setSet.end(), parseSet(element)) != setSet.end());
    else
        return (find(elementSet.begin(), elementSet.end(), element) != elementSet.end());
}

bool SetBase::empty() {
    return (elementSet.empty() && setSet.empty());
}


    
Set& Set::operator+=(Set anotherSet) {
    for (int i = 0; i < anotherSet.cardinality(); i++)
        this->addElement(anotherSet.getElement(i));
    return *this;
}
Set Set::operator+(const Set& anotherSet) {
    Set result = *this;
    result += anotherSet;
    return result;
}

Set& Set::operator*=(Set anotherSet) {
    for (int i = 0; i < this->cardinality(); i++)
    {
        if (!anotherSet[this->getElement(i)]) {
            this->removeElement(this->getElement(i));
            i--;
        }
    }
    return *this;
}
Set Set::operator*(const Set& anotherSet) {
    Set result = *this;
    result *= anotherSet;
    return result;
}

Set& Set::operator-=(Set anotherSet) {
    for (int i = 0; i < this->cardinality(); i++)
    {
        if (anotherSet[this->getElement(i)]) {
            this->removeElement(this->getElement(i));
            i--;
        }
    }
    return *this;
}
Set Set::operator-(const Set& anotherSet) {
    Set result = *this;
    result -= anotherSet;
    return result;
}

Set& operator>>(Set& set, string setString) {
    set += parseSet(setString);
    return set;
}
ostream& operator<<(ostream& outStream, Set& set) {
    return (outStream << set.intoString());
}

void Set::generateSubsets(Set& currentSubset, int index, Set& result) {
    result.addElement(currentSubset.intoString());
    for (int i = index; i < this->cardinality(); i++) {
        currentSubset.addElement(this->getElement(i));
        generateSubsets(currentSubset, i + 1, result);
        currentSubset.pop();
    }
}
Set Set::powerSet() {
    Set result, currentSubset;
    generateSubsets(currentSubset, 0, result);
    return result;
}

void Set::pop() {
    if (!this->empty())
        this->removeElement(this->getElement(this->cardinality() - 1));
}

Set parseSet(string setString) {
    setString.erase(remove_if(setString.begin(), setString.end(), ::isspace), setString.end());
    
    Set result;
    if (setString == "{}")
        return {};

    int index = 1;
    int depth = 1;
    int subsetStart, elementStart = 0;
    for (index = 1; index < setString.length(); index++) {
        if (setString[index] == '{') {
            if (depth==1)
                subsetStart = index;
            depth++;
        }
        else if (setString[index] == '}') {
            if (elementStart && depth==1) {
                result.addElement(setString.substr(elementStart, index - elementStart));
                elementStart = 0;
            }

            depth--;
            if (depth == 1 && setString!=",{}") {
                result.addElement(setString.substr(subsetStart, index - subsetStart + 1));
                if (index != setString.length() - 2 && setString[index + 1] == ',')
                    index++;
            }
        }
        else if (setString[index] == ',' && depth == 1 && elementStart) {
            if (setString.substr(elementStart, index - elementStart)!=",{}")
                result.addElement(setString.substr(elementStart, index - elementStart));
            elementStart = 0;
        }
        else if (depth == 1 && !elementStart) {
            elementStart = index;
        }
    }
    return result;
}