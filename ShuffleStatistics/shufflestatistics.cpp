#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

void initMap(map<string, int> &nStrings, string letters) {
	nStrings.clear();
	sort(letters.begin(), letters.end());
	nStrings[letters] = 1;
	while (next_permutation(letters.begin(), letters.end())) {
		nStrings[letters] += 0;
	}
}

void swapStringWithPosition(map<string, int> &oldNStrings, map<string, int> &newNStrings, string currentString, size_t position) {
	for (size_t i = 0; i < currentString.length(); ++i) {
		if (i == position) continue;
		string otherString = currentString;
		otherString[i] = currentString[position];
		otherString[position] = currentString[i];
#ifdef DEBUG
		cout << otherString << " ";
#endif // DEBUG
		newNStrings[otherString] += oldNStrings[currentString];
	}
#ifdef DEBUG
	cout << endl;
#endif // DEBUG
}

void swapAllWithPosition(map<string,int> &nOldStrings, map<string, int> &nNewStrings, size_t position) {
	map<string, int>::iterator it = nOldStrings.begin();
	for (; it != nOldStrings.end(); ++it) {
		if (it->second == 0) continue;
#ifdef DEBUG
		cout << it->first << " - ";
#endif // DEBUG
		swapStringWithPosition(nOldStrings, nNewStrings, it->first, position);
	}
}

void outputNStrings(ostream &stream, map<string, int> &nStrings) {
	map<string, int>::iterator it = nStrings.begin();
	for (; it != nStrings.end(); ++it) {
		stream << it->first << ": " << it->second << endl;
	}
}

void generateRandomShuffleStatistics(map<string, int> &nStrings, const string &letters) {
	initMap(nStrings, letters);
	map<string, int> nNewStrings = nStrings;
	for (size_t position = 0; position < letters.length(); ++position) {
#ifdef DEBUG
		outputNStrings(cout, nStrings);
		cout << endl;
#endif // DEBUG
		swapAllWithPosition(nStrings, nNewStrings, position);
		nStrings = nNewStrings;
	}
}

int main() {
	map<string, int> nStrings;
	generateRandomShuffleStatistics(nStrings, "abcdefghij");
	outputNStrings(cout, nStrings);
}