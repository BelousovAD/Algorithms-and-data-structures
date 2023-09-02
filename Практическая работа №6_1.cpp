#include <iostream>
#include <vector>
#include <set>

using namespace std;

//Не работает удаление. Запилить слияние деревьев

struct node {
	int data;
	node* left = NULL;
	node* right = NULL;
	node* parent = NULL;
};

struct BTree {
	node* addNode(node*, node*, int);
	bool findElement(node*, int);
	node* deleteNode(node*, node*, int);
	void treePrint(node*, int);
	node* tree;
	set<int> dataOfTree;
};

node* BTree::addNode (node* parent, node* tree, int info) {//О(1)-лучший, O(logN)-средний, О(N)-худший
	if (tree == NULL) {
		node* k = new node;
		k->data = info;
		k->parent = parent;
		tree = k;
	}
	else if (tree->data < info) {
		tree->right = addNode(tree, tree->right, info);
	}
	else if (tree->data > info){
		tree->left = addNode(tree, tree->left, info);
	}
		return tree;
}

node* findRightNode(node* tree) {//О(1)-лучший, О(logN)-средний, О(N)-худший
	if (tree != NULL) {
		while (tree->left != NULL) {
			tree = tree->left;
		}
	}
	return tree;
}

node* findLeftNode(node* tree) {//О(1)-лучший, О(logN)-средний, О(N)-худший
	if (tree != NULL) {
		while (tree->right != NULL) {
			tree = tree->right;
		}
	}
	return tree;
}

node* BTree::deleteNode(node* parent, node* tree, int info) {//О(1)-лучший, О(logN)-средний, О(N)-худший
	if (tree == NULL) {//узел пустой
	}
	else if (info != tree->data){//узел не пустой и не равен искомому
		tree->right = deleteNode(tree, tree->right, info);
		tree->left = deleteNode(tree, tree->left, info);
	}
	else if (info == tree->data) {//узел искомый. Начинается поиск и замена элементом элемента который нужно удалить
		node* leftNode = findLeftNode(tree->left);
		node* rightNode = findRightNode(tree->right);
		if (leftNode == NULL && rightNode == NULL) {
			delete tree;
			tree = NULL;
		}
		else if (leftNode == NULL) {//у искомого узла имеется только правый потомок
			tree->data = rightNode->data;
			if (rightNode->parent == tree) {
				tree->right = deleteNode(rightNode->parent, rightNode, rightNode->data);
			}
			else {
				rightNode->parent->left = deleteNode(rightNode->parent, rightNode, rightNode->data);
			}
		}
		else {//у искомого узла имеется левый потомок
			tree->data = leftNode->data;
			if (leftNode->parent == tree) {
				tree->left = deleteNode(leftNode->parent, leftNode, leftNode->data);
			}
			else {
				leftNode->parent->right = deleteNode(leftNode->parent, leftNode, leftNode->data);
			}
		}	  
	}
	return tree;
}

void BTree::treePrint(node* tree, int level)//О(N*logN)
{
	if (tree != NULL)
	{
		treePrint(tree->left, level + 1); // по левому указателю
		for (int i = 0; i < level; i++) cout << "-";
		cout << tree->data << endl;
		treePrint(tree->right, level + 1); // по правому указателю
	}
}

int main() {
	setlocale(LC_ALL, "");
	const int N = 4;
	int action, n, a;
	vector<BTree> btrees;
H:	cout << "(1) Построить деревья." << endl
		<< "(2) Добавить элемент в дерево." << endl
		<< "(3) Удалить элемент дерева." << endl
		<< "(4) Слить деревья." << endl
		<< "(5) Вывести деревья." << endl
		<< "(0) Выход." << endl
		<< "Введите действие: ";
	cin >> action;
	cout << endl;
	switch (action)
	{
	case 1://Построение деревьев. O(N)-лучший, О(N*logN)-средний, О(N^2)-худший
		btrees.clear();
		btrees.resize(N);
		for (int i = 0; i < N; i++) {

			cout << "Введите количество узлов в " << i << " дереве: ";
			cin >> n;
			cout << endl;
			cout << "Введите " << n << " чисел для дерева: ";
			for (int j = 0; j < n; j++) {
				cin >> a;
				btrees[i].dataOfTree.insert(a);
				btrees[i].tree = btrees[i].addNode(NULL, btrees[i].tree, a);
			}
		}
		cout << endl;
		goto H;
	case 2://Встава элемента в дерево. О(1)-лучший, O(logN)-средний, О(N)-худший
		do {
			cout << "Введите номер дерева: ";
			cin >> n;
			cout << endl;
			if (btrees[n].tree == NULL) {
				cout << "Неверный номер дерева" << endl;
			}
		} while (btrees[n].tree == NULL);
		cout << "Введите элемент: ";
		cin >> a;
		btrees[n].dataOfTree.insert(a);
		btrees[n].tree = btrees[n].addNode(NULL, btrees[n].tree, a);
		cout << "Элемент вставлен" << endl;
		goto H;
	case 3://Удаление элемента из дерева. О(1)-лучший, O(logN)-средний, О(N)-худший
		do {
			cout << "Введите номер дерева: ";
			cin >> n;
			cout << endl;
			if (btrees[n].tree == NULL) {
				cout << "Неверный номер дерева" << endl;
			}
		} while (btrees[n].tree == NULL);
		cout << "Введите элемент: ";
		cin >> a;
		btrees[n].dataOfTree.erase(a);
		btrees[n].tree = btrees[n].deleteNode(NULL, btrees[n].tree, a);
		cout << "Элемент удалён" << endl;
		goto H;
	case 4://Сливание деревьев. O(N)-лучший, О(N*logN)-средний, О(N^2)-худший
		for (int i = N - 1; i > 0; --i) {
			while (!btrees[i].dataOfTree.empty()) {
				auto it = btrees[i].dataOfTree.begin();
				btrees[0].dataOfTree.insert(*it);
				btrees[0].tree = btrees[0].addNode(NULL, btrees[0].tree, *it);
				btrees[i].dataOfTree.erase(*it);
			}
			btrees.pop_back();
		}
		btrees.resize(N);
		cout << "Деревья слиты" << endl;
		goto H;
	case 5://Вывод деревьев. О(N*logN)
		for (int i = 0; i < N; i++) {
			if (btrees[i].tree != NULL) {
				cout << "---------------Дерево " << i << " ----------------" << endl;
				btrees[i].treePrint(btrees[i].tree, 0);
				cout << "-------------------------------" << endl;
			}
		}
		goto H;
	case 0:
		return 0;
	default:
		cout << "Неверное действие!" << endl;
		goto H;
	}
}