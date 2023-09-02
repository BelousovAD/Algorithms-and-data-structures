#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

bool correct(vector <int>& vec) {
	int size = vec.size();
	while (--size > 0) {
		if (vec[size - 1] > vec[size]) {
			return false;
		}
	}
	return true;
}

void bogoSort(vector <int>& vec) {
	while (!correct(vec)) {
		int i = 0, size = vec.size();
		for (; i < size; ++i) {
			swap(vec[i], vec[(rand() % size)]);
		}
	}
}

void shellSort(vector <int>& vec) {
	for (int delta = vec.size() / 2; delta != 0; delta /= 2) {
		for (int i = 0; i != delta; ++i) {
			for (int j = i + delta; j < vec.size(); j += delta) {
				int save = j;
				while (j >= delta && vec[j - delta] > vec[j]) {
					swap(vec[j - delta], vec[j]);
					j -= delta;
				}
				j = save;
			}
		}
	}
}

int main() {
	unsigned int start_time, end_time;
	int s, size, action;
	vector<int> vec;
	string file;
	ifstream in;
	ofstream out("out.txt");
H:	cout << "Modes of work:" << endl
	<< "1) Input from console." << endl
	<< "2) Input from file." << endl
	<< "0) Exit." << endl
	<< "Enter your choose: ";
	cin >> action;
	cout << endl;
	switch (action)
	{
	case 0:
		return 0;
	case 1:
		cout << "Enter vector size: ";
		cin >> size;
		cout << "Enter vector: ";
		for (; size != 0; --size) {
			cin >> s;
			vec.push_back(s);
		}
		cout << endl;
		goto G;
	case 2:
		cout << "Enter the test file directory: ";
		cin >> file;
		in.open(file);
		if (!in.is_open()) {
			cout << endl << "Error of open file!" << endl;
			goto H;
		}
		while (in >> s) {
			vec.push_back(s);
		}
		goto G;
	default:
		cout << "Error action!" << endl;
		goto H;
	}

G:	cout << "Methodes of sort:" << endl
	<< "1) Bogosort." << endl
	<< "2) Shellsort." << endl
	<< "-------------" << endl
	<< "3) Go back to choice modes" << endl
	<< "0) Exit." << endl
	<< "Enter your chose: ";
	cin >> action;
	cout << endl;
	switch (action)
	{
	case 0:
		return 0;
	case 3:
		vec.clear();
		goto H;
	case 1:
		start_time = clock();
		bogoSort(vec);
		end_time = clock();
		cout << "\nTime of Bogosort table: " << end_time - start_time << endl;
		cout << "Result vector:" << endl;
		for (int i = 0; i != vec.size(); ++i) {
			cout << vec[i] << ' ' << endl;
		}
		goto H;
	case 2:
		start_time = clock();
		shellSort(vec);
		end_time = clock();
		cout << "\nTime of Shellsort table: " << end_time - start_time << endl;
		cout << "Result vector is located in \"out.txt\"" << endl;
		for (int i = 0; i < vec.size(); ++i) {
			out << vec[i] << ' ' << endl;
		}
		goto H;
	default:
		cout << "Error action!" << endl;
		goto G;
	}
}