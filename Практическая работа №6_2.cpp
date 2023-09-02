#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct node {
	int data, level = 1;
	node* left = NULL;
	node* right = NULL;
};

struct avl_tree {
	node* addNode(node*, int );
	node* deleteNode(node*, int);
	void treePrint(node*, int);
	node* tree;
	set<int> dataOfTree;
};

int height(node* a) {//Возврат высоты
	if (a != NULL) {
		return a->level;
	}
	return 0;
}

int bfactor(node* a) {//Разность высот поддеревьев
	return height(a->right) - height(a->left);
}

void fixheight(node* a) {//Запись высоты в узел
	int left = height(a->left);
	int right = height(a->right);
	if (left > right) {
		a->level = left + 1;
	}
	else {
		a->level = right + 1;
	}
}

node* minrotateright(node* a) {//малое правое вращение
	node* b = a->left;
	a->left = b->right;
	b->right = a;
	fixheight(a);
	fixheight(b);
	return b;
}

node* minrotateleft(node* a) {//малое левое вращение
	node* b = a->right;
	a->right = b->left;
	b->left = a;
	fixheight(a);
	fixheight(b);
	return b;
}

node* maxrotateright(node* a) {//большое правое вращение
	a->left = minrotateleft(a->left);
	return minrotateright(a);
}

node* maxrotateleft(node* a) {//большое левое вращение
		a->right = minrotateright(a->right);
		return minrotateleft(a);
}

node* balance(node* a) {//балансировка дерева
	fixheight(a);
	if (bfactor(a) == 2) {
		if (bfactor(a->right) < 0) {
			return maxrotateleft(a);
		}
		else {
			return minrotateleft(a);
		}
	}
	if (bfactor(a) == -2) {
		if (bfactor(a->left) > 0) {
			return maxrotateright(a);
		}
		else {
			return minrotateright(a);
		}
	}
	return a;
}

node* avl_tree::addNode(node* a, int info) {//Добавление узла
	if (a == NULL) {
		node* n = new node;
		n->data = info;
		return n;
	}
	if (info < a->data) {
		a->left = addNode(a->left, info);
	}
	else if (info > a->data) {
		a->right = addNode(a->right, info);
	}
	else {
		return a;
	}
	return balance(a);
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

node* avl_tree::deleteNode(node* tree, int info) {//О(1)-лучший, О(logN)-средний, О(N)-худший
	if (tree == NULL) {//узел пустой
		return tree;
	}
	else if (info != tree->data) {//узел не пустой и не равен искомому
		tree->right = deleteNode(tree->right, info);
		tree->left = deleteNode(tree->left, info);
	}
	else if (info == tree->data) {//узел искомый. Начинается поиск и замена элементом элемента который нужно удалить
		node* leftNode = findLeftNode(tree->left);
		node* rightNode = findRightNode(tree->right);
		if (leftNode == NULL && rightNode == NULL) {
			delete tree;
			tree = NULL;
			return tree;
		}
		else if (leftNode == NULL) {//у искомого узла имеется только правый потомок
			tree = rightNode;
		}
		else {//у искомого узла имеется левый потомок
			if (bfactor > 0) {
				tree->data = leftNode->data;
				tree->left = deleteNode(tree->left, leftNode->data);
			}
			else {
				tree->data = rightNode->data;
				tree->right = deleteNode(tree->right, rightNode->data);
			}
		}
	}
	return balance(tree);
}

void avl_tree::treePrint(node* tree, int level)//О(N*logN)
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
	vector<avl_tree> avl_trees;
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
		avl_trees.clear();
		avl_trees.resize(N);
		for (int i = 0; i < N; i++) {
			cout << "Введите количество узлов в " << i << " дереве: ";
			cin >> n;
			cout << endl;
			cout << "Введите " << n << " чисел для дерева: ";
			for (int j = 0; j < n; j++) {
				cin >> a;
				avl_trees[i].dataOfTree.insert(a);
				avl_trees[i].tree = avl_trees[i].addNode(avl_trees[i].tree, a);
			}
		}
		cout << endl;
		goto H;
	case 2://Встава элемента в дерево. О(1)-лучший, O(logN)-средний, О(N)-худший
		do {
			cout << "Введите номер дерева: ";
			cin >> n;
			cout << endl;
			if (avl_trees[n].tree == NULL) {
				cout << "Неверный номер дерева" << endl;
			}
		} while (avl_trees[n].tree == NULL);
		cout << "Введите элемент: ";
		cin >> a;
		avl_trees[n].dataOfTree.insert(a);
		avl_trees[n].tree = avl_trees[n].addNode(avl_trees[n].tree, a);
		cout << "Элемент вставлен" << endl;
		goto H;
	case 3://Удаление элемента из дерева. О(1)-лучший, O(logN)-средний, О(N)-худший
		do {
			cout << "Введите номер дерева: ";
			cin >> n;
			cout << endl;
			if (avl_trees[n].tree == NULL) {
				cout << "Неверный номер дерева" << endl;
			}
		} while (avl_trees[n].tree == NULL);
		cout << "Введите элемент: ";
		cin >> a;
		avl_trees[n].dataOfTree.erase(a);
		avl_trees[n].tree = avl_trees[n].deleteNode(avl_trees[n].tree, a);
		cout << "Элемент удалён" << endl;
		goto H;
	case 4://Сливание деревьев. O(N)-лучший, О(N*logN)-средний, О(N^2)-худший
		for (int i = N - 1; i > 0; --i) {
			while (!avl_trees[i].dataOfTree.empty()) {
				auto it = avl_trees[i].dataOfTree.begin();
				avl_trees[0].dataOfTree.insert(*it);
				avl_trees[0].tree = avl_trees[0].addNode(avl_trees[0].tree, *it);
				avl_trees[i].dataOfTree.erase(*it);
			}
			avl_trees.pop_back();
		}
		avl_trees.resize(N);
		cout << "Деревья слиты" << endl;
		goto H;
	case 5://Вывод деревьев. О(N*logN)
		for (int i = 0; i < N; i++) {
			if (avl_trees[i].tree != NULL) {
				cout << "---------------Дерево " << i << " ----------------" << endl;
				avl_trees[i].treePrint(avl_trees[i].tree, 0);
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