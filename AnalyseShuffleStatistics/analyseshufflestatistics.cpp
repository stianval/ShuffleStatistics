#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct PermutationFrequency {
	string permutation;
	int frequency;
	PermutationFrequency(const string &permutation, int frequency) :
		permutation{ permutation }, frequency{ frequency } {
		;
	}
};

ostream &operator<<(ostream &stream, const PermutationFrequency &frequency) {
	return stream << frequency.permutation << " - " << frequency.frequency;
}

bool greaterFrequency(const PermutationFrequency &lhs, const PermutationFrequency &rhs) {
	return lhs.frequency > rhs.frequency;
}

void loadFrequencies(vector<PermutationFrequency> &frequencies) {
	ifstream datafile("../Release/stats.log");
	string permutation;
	int frequency;
	while (datafile >> permutation >> frequency, !datafile.eof()) {
		permutation.pop_back();
#ifdef _DEBUG
		cout << permutation << " - " << frequency << endl;
#endif // _DEBUG
		frequencies.emplace_back(PermutationFrequency(permutation, frequency));
	}
}

void outputHighestFrequencies(ostream &stream, const vector<PermutationFrequency> &frequencies, int n) {
	for_each(frequencies.begin(), frequencies.begin() + n, [&stream](const PermutationFrequency &frequency) {
		stream << frequency << endl;
	});
}

void outputLowestFrequencies(ostream &stream, const vector<PermutationFrequency> &frequencies, int n) {
	for_each(frequencies.end() - n, frequencies.end(), [&stream](const PermutationFrequency &frequency) {
		stream << frequency << endl;
	});
}


int roundDownToMultiplier(const int number, const int multiplier) {
	return (number / multiplier)*multiplier;
}

void outputFrequencyHistogram(ostream &stream, const vector<PermutationFrequency> &frequencies, int step) {
	int highestFrequency = frequencies.front().frequency;
	int currentStep = roundDownToMultiplier(highestFrequency, step);
	int nStringsInInterval = 0;
	for (const PermutationFrequency &pf : frequencies) {
		while (pf.frequency < currentStep) {
			stream << currentStep << " - " << nStringsInInterval << endl;
			currentStep -= step;
			nStringsInInterval = 0;
		}
		nStringsInInterval++;
	}
	stream << currentStep << " - " << nStringsInInterval << endl;
}

template <int num>
struct Faculty {
	static const int value = num*Faculty<num - 1>::value;
};

template <> struct Faculty<0> {
	static const int value = 1;
};

double frequencySum(const vector<PermutationFrequency> &frequencies) {
	double sum = 0;
	for (const PermutationFrequency &pf : frequencies) {
		sum += pf.frequency;
	}
	return sum;
}

int main() {
	vector<PermutationFrequency> frequencies;
	loadFrequencies(frequencies);
	
	cout << "Size:" << frequencies.size() << endl;
	cout << "Expected:" << Faculty<10>::value << endl;
	cout << endl;
	
	sort(frequencies.begin(), frequencies.end(), greaterFrequency);

	cout << "Permutations with highest frequency: " << endl;
	outputHighestFrequencies(cout, frequencies, 10);
	cout << endl;

	cout << "Permutations with lowest frequency: " << endl;
	outputLowestFrequencies(cout, frequencies, 10);
	cout << endl;

	cout << "Number of permutations in given frequency ranges: " << endl;
	outputFrequencyHistogram(cout, frequencies, 500);
	cout << endl;

	double totalFrequencies = frequencySum(frequencies);
	cout << "Total frequencies: " << (long long) totalFrequencies << endl;
	cout << "Mean frequency: " << totalFrequencies / frequencies.size() << endl;
}