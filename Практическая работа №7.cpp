#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

void Simple_Merging_Sort(const char* name) {
	int a1, a2, k = 1, i, j, kol = 0;
	fstream f(name, ios::in), f1, f2;

	if (!f.is_open()) {
		cout << "\nИсходный файл не может быть прочитан";
	}
	else {
		while (!f.eof()) {//подсчёт количества элементов
			f >> a1;
			kol++;
		}
		f.close();
	}
	while (k < kol) {
		f.open(name, ios::in);
		f1.open("sort1.txt", ios::out);
		f2.open("sort2.txt", ios::out);
		if (!f.eof()) {
			f >> a1;
		}
		while (!f.eof()) {//разбиение файла на два
			for (i = 0; i < k && !f.eof(); i++) {
				f1 << a1 << ' ';
				f >> a1;
			}
			for (j = 0; j < k && !f.eof(); j++) {
				f2 << a1 << ' ';
				f >> a1;
			}
		}
		f2.close();
		f1.close();
		f.close();

		f.open(name, ios::out);
		f1.open("sort1.txt", ios::in);
		f2.open("sort2.txt", ios::in);
		if (!f1.eof()) {
			f1 >> a1;
		}
		if (!f2.eof()) {
			f2 >> a2;
		}
		while (!f1.eof() && !f2.eof()) {//слияние файлов
			i = 0;
			j = 0;
			while (i < k && j < k && !f1.eof() && !f2.eof()) {
				if (a1 < a2) {
					f << a1 << ' ';
					f1 >> a1;
					i++;
				}
				else {
					f << a2 << ' ';
					f2 >> a2;
					j++;
				}
			}//если одно подмножество закончилось раньше парного
			while (i < k && !f1.eof()) {
				f << a1 << ' ';
				f1 >> a1;
				i++;
			}
			while (j < k && !f2.eof()) {
				f << a2 << ' ';
				f2 >> a2;
				j++;
			}
		}//если подмножество изначально не имело пары
		while (!f1.eof()) {
			f << a1 << ' ';
			f1 >> a1;
		}
		while (!f2.eof()) {
			f << a2 << ' ';
			f2 >> a2;
		}
		f.close();
		f1.close();
		f2.close();
		k *= 2;
	}
	remove("sort1.txt");
	remove("sort2.txt");
	cout << endl << "Массив отсортирован" << endl;
}

int returnElement(const char* name, int index) {
	fstream f(name, ios::in);
	int a1 = 0;
	if (!f.is_open()) {
		cout << "\nИсходный файл не может быть прочитан";
		return -1;
	}
	else {
		for (int i = 1; i <= index; ++i) {
			f >> a1;
		}
		f.close();
		return a1;
	}
}

int main() {
	setlocale(LC_ALL, "");
	int action, index, element;
	unsigned int end_time, start_time;
H:	cout << endl << "Вернуть элемент по индексу (1)" << endl
<< "Отсортировать массив (2)" << endl
<< "Выход (0)" << endl
<< "Введите действие: ";
cin >> action;
switch (action) {
case 1:
	cout << endl << "Введите индекс элемента: ";
	cin >> index;
	element = returnElement("in.txt", index);
	if (element != -1) {
		cout << endl << element;
	}
	goto H;
case 2:
	start_time = clock();
	Simple_Merging_Sort("in.txt");
	end_time = clock();
	cout << "\nВремя сортировки: " << end_time - start_time << endl;
	goto H;
case 0:
	return 0;
default:
	cout << "Неверное действие!" << endl;
	goto H;
}
}