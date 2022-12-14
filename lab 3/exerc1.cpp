/*******************************
 * Lab 3: exercise 1            *
 * Frequency table of words     *
 *******************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>   //std::pair
#include <fstream>
#include <cassert>
#include <algorithm>

/*******************************
 * 1. Declarations              *
 ********************************/

 // Pair for every element
using pair = std::pair<std::string, int>;

// A function to test the tables created by the program
void test(const std::map<std::string, int>& t, const std::vector<std::pair<std::string, int>>& v,
          const std::string& file_name, int n);

// To lowercase
void lowerCase(std::string& word) {
    std::transform(word.begin(), word.end(), word.begin(), tolower);
}

// Check if c is a punctuation
bool isPunc(const char& c) {
    // List of punctuations that will be removed
    std::string puncts = ".,!?:();\"";
    return puncts.find(c) != std::string::npos;
}

// Remove specific chars from refrenced string
void removeChar(std::string& word) {
    word.erase(remove_if(word.begin(), word.end(), isPunc), word.end());
}

// Sort by frequency
bool sortBy(const pair& p1, const pair& p2) {
    if (p1.second == p2.second) { // If the frequency is the same sort alphembeticly
        return(p1.first < p2.first);
    }
    return (p1.second > p2.second); // Else sort by frequency
}

/*******************************
 * 2. Main function             *
 *******************************/

int main() {
    std::string name;
    std::cout << "Text file: ";
    std::cin >> name;

    std::ifstream in_File{"../code/" + name};

    if (!in_File) {
        std::cout << "Could not open input file!!\n";
        return 0;
    }


    std::map<std::string, int> table; // Creates map which will store the pairs
    int counter{0};  // to count total number of words read from the input file

    std::string incomingWord;

    while (in_File >> incomingWord) {
        removeChar(incomingWord); // Remove punctuations
        lowerCase(incomingWord);
        table[incomingWord]++; // Add word to the table
        counter++; // Change total amount of words
    }

    std::vector<std::pair<std::string, int>> freq;

    std::copy(table.begin(), table.end(), std::back_inserter(freq));

    std::sort(freq.begin(), freq.end(), sortBy);

    /* ************** Testing **************** */

    test(table, freq, name, counter);
}


/*******************************
 * 2. Test implementation      *
 * Do not modify               *
 *******************************/

void test(const std::map<std::string, int>& t, const std::vector<std::pair<std::string, int>>& v,
          const std::string& file_name, int n) {

    std::ifstream file{"../code/out_" + file_name};

    // Test if stream is in good state
    assert(bool(file) == true);

    std::map<std::string, int> result1;
    std::string word;
    int counter{0};
    int total{0};

    // load expected frequency table sorted alphabetically
    while (file >> word >> counter && counter > 0) {
        result1[word] = counter;
        total += counter;
    }
	
	/*
    * uppgift1_kort: 69 words
    * uppgift1.txt: 1063 words
    */

    assert(total == n);  // test if total number of words is correct
    assert(t == result1);

    std::vector<std::pair<std::string, int>> result2;

    // load expected frequency table sorted by frequence
    while (file >> word >> counter) {
        result2.push_back(std::pair{word, counter});
    }

    assert(v == result2);

    std::cout << "\nPassed all tests successfully!!\n";
}
