/*****************************************
 * Lab 3: exercise 2                      *
 * Anagrams table                         *
 ******************************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <set>
#include <iterator>
#include <iomanip>

// By using set instead of vector we dont have to remove duplicates
using Table = std::map<std::string, std::vector<std::string>>;

// Definition of testing function
void test(const Table& T, const std::string& file_name);

struct insert_table {
	insert_table(Table& t) : T(t) { //Table constructor
	}

	void operator()(const std::string& word) {
		std::string subject{ word };
		std::sort(subject.begin(), subject.end());

		auto it = std::find(T[subject].begin(), T[subject].end(), word);

		if (it == T[subject].end()) {
			T[subject].push_back(word);
		};
		std::sort(T[subject].begin(), T[subject].end());
	}

private:
	Table& T;
};

struct print {
	void operator()(const std::pair<const std::string, const std::vector<std::string>>& T) {
		if (T.second.size() >= 2){
			std::for_each(T.second.begin(), T.second.end(), [](const std::string& w){
				std::cout << w << " ";
			});
			std::cout << " --> " << T.second.size()<<"\n";
		};
	};
};


/*******************************
 * Main function			   *
 *******************************/

int main() {
	std::string name;
	std::cout << "Text file: ";
	std::cin >> name;

	std::ifstream in_File{ "../code/" + name };

	if (!in_File) {
		std::cout << "Could not open input file!!\n";
		return 0;
	}

	std::vector<std::string> words_subject;

	// Reads every word in the file and copies them to words_key

	std::copy(std::istream_iterator<std::string>{in_File}, std::istream_iterator<std::string>{}, inserter(words_subject, words_subject.end()));

	Table anagram; // Create a table
	insert_table newTable(anagram); // Call the table constructor

	// Add the subject and word
	std::for_each(words_subject.begin(), words_subject.end(), newTable);
	std::cout << "Number of words = " << words_subject.size() << "\n\n" << "--ANAGRAMS--\n";

	// Sends every element into print()
	std::for_each(anagram.begin(), anagram.end(), print());

	//Necessary testing
	test(anagram, name);
}
void test(const Table& T, const std::string& file_name) {
	std::ifstream file{ "../code/" + file_name };

	//Test the file
	assert(bool(file) == true);

	Table result1;
	std::string out_anagram;

	while (file >> out_anagram) {
		std::string temp = out_anagram;

		// Sort alphabeticly
		std::sort(std::begin(temp), std::end(temp));

		auto it = std::find(result1[temp].begin(), result1[temp].end(), out_anagram);

		if (it == result1[temp].end()) {
			result1[temp].push_back(out_anagram);
		};

		std::sort(result1[temp].begin(), result1[temp].end());
	}

	assert(T == result1);

	std::cout << "\n SUCKESS B^)\n\n";
}