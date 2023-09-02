#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

const int sizeofhash = 262144;//2^18

void enter_table(vector <int>& arr, ifstream& in) {
	int a;
	in >> a;
	while (in >> a) {
		int hash = ((long long)a * a >> 8) % sizeofhash;
		while ((arr[hash] < 0 || arr[hash] == a) ^ hash < sizeofhash) {
			++hash;
		}
		if (arr[hash] < 0) {
			arr[hash] = a;
		}
	}
}

void enter_element(vector <int>& arr, istream& in) {
	int a;
	in >> a;
	int hash = ((long long)a * a >> 8) % sizeofhash;
	while ((arr[hash] < 0 || arr[hash] == a) ^ hash < sizeofhash) {
		++hash;
	}
	if (arr[hash] < 0) {
		arr[hash] = a;
	}
	if (hash == sizeofhash) {
		cout << "Out of memory" << endl;
	}
}

int find_elem(vector <int>& arr, int& a) {
	int hash = ((long long)a * a >> 8) % sizeofhash;
	while ((arr[hash] <= -1 || arr[hash] == a) ^ hash < sizeofhash) {
		++hash;
	}
	if (hash == sizeofhash || arr[hash] == -1) {
		cout << "Element not found" << endl;
		return -1;
	}
	else {
		return hash;
	}
}

void delete_elem(vector <int>& arr, int hash) {
	if (hash != -1) {
		arr[hash] = -2;
	}
}

int main() {
	string file, action;
	int a;
H:	cout << "Enter the test file directory: ";
	cin >> file;
	ifstream in(file);
	if (!in.is_open()) {
		cout << endl << "Error" << endl;
		goto H;
	}
	vector <int> arr(sizeofhash, -1);

	unsigned int start_time = clock();
	enter_table(arr, in);
	unsigned int end_time = clock();
	cout << "\nTime of enter table: " << end_time - start_time << endl;

G:	cout << "Enter action (find/delete/enter_elem/exit): ";
	cin >> action;

	if (action == "find") {
		cin >> a;
		start_time = clock();
		a = find_elem(arr, a);
		if (a != -1) {
			cout << "Hash: " << a << endl;
		}
		end_time = clock();
		cout << "\nTime of find element: " << end_time - start_time << endl;
		goto G;
	}

	if (action == "delete") {
		cin >> a;
		start_time = clock();
		delete_elem(arr, find_elem(arr, a));
		end_time = clock();
		cout << "\nTime of delete element: " << end_time - start_time << endl;
		goto G;
	}

	if (action == "enter_elem") {
		start_time = clock();
		enter_element(arr, cin);
		end_time = clock();
		cout << "\nTime of enter element: " << end_time - start_time << endl;
		goto G;
	}
}