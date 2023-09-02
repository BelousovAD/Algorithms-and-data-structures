#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

/*int main() {
	string file;
H:	cout << "Enter the test file directory: ";
	cin >> file;
	ifstream in(file);
	if (!in.is_open()) {
		cout << endl << "Error" << endl;
		goto H;
	}
	int a;
	vector <int> arr;
	in >> a;
	while (in >> a) {
		arr.push_back(a);
	}
	cout << "Enter searching element: ";
	cin >> a;

	unsigned int start_time = clock();

	for (size_t i = 0; i < arr.size(); i++) {
		if (arr[i] == a) {
			cout << "Index of element: " << i << endl;
			unsigned int end_time = clock();
			cout << "\nTime: " << end_time - start_time;
			return 0;
		}
	}
	cout << "Element not fouded" << endl;

	unsigned int end_time = clock();
	cout << "\nTime: " << end_time - start_time;
}*/

int main() {
	string file;
H:	cout << "Enter the test file directory: ";
	cin >> file;
	ifstream in(file);
	if (!in.is_open()) {
		cout << endl << "Error" << endl;
		goto H;
	}
	int a;
	vector <pair<int, int>> arr;
	in >> a;
	for (int i = 0; in >> a;++i) {
		arr.push_back(pair<int, int>(a, i));
	}
	cout << "Enter searching element: ";
	cin >> a;

	unsigned int start_time = clock();

	sort(arr.begin(), arr.end(), [](pair <int, int> a, pair <int, int> b) {
		return a.first < b.first;
		});
	if (arr.begin()->first > a || (arr.end() - 1)->first < a) {
		cout << "Element not fouded" << endl;
		return 0;
	}
	int start = 0, finish = arr.size() - 1, mid = 0;
	while (start < finish) {
		mid = start + (finish - start) / 2;//start + (long long)(a - arr[start].first) * (finish - start) / (arr[finish].first - arr[start].first);
		if (a == arr[mid].first) {
			cout << "Index of element: " << arr[mid].second << endl;
			unsigned int end_time = clock();
			cout << "\nTime: " << end_time - start_time;
			return 0;
		}
		else {
			if (a < arr[mid].first) {
				finish = mid;
			}
			else
				start = mid;
		}
	}
	cout << "Element not fouded" << endl;

	unsigned int end_time = clock();
	cout << "\nTime: " << end_time - start_time;
}