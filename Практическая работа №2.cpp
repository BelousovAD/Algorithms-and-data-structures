#include <iostream>
#include <vector>
#include <ctime>
#include <queue>

/*struct Node
{
    long double val = 0;
    Node* left = NULL;
    Node* right = NULL;
};

int main()
{//Генерация последовательности
    int index, N;
    double factor;
    Node* head, * cur;
    std::cout << "\nEnter number of elements: ";
    std::cin >> N;
    std::cout << "\nEnter index of missing element or \"-1\" for enter sequence yourself: ";
    std::cin >> index;
    if (index != -1) {
        std::cout << "\nEnter geometric ratio: ";
        std::cin >> factor;
        std::cout << "\nEnter first element: ";
        head = new Node;
        cur = head;
        std::cin >> head->val;
        std::cout << "\nSource sequence\n" << head->val << "  ";

        for (int i = 1; i < N; ++i) {
            Node* node = new Node;
            if (i != index) {
                node->val = cur->val * factor;
                std::cout << node->val << "   ";
            }
            else {
                node->val = cur->val * factor * factor;
                std::cout << node->val << "   ";
            }

            cur->right = node;
            node->left = cur;
            cur = node;
        }
    }
    else {
        std::cout << "\nEnter sequence: ";
        head = new Node;
        cur = head;
        std::cin >> head->val;
        for (int i = 1; i < N; ++i) {
            Node* node = new Node;
            std::cin >> node->val;
            cur->right = node;
            node->left = cur;
            cur = node;
        }
    }

    //Тело алгоритма
    unsigned int start_time = clock();

    cur = head->right;
    Node* next = cur->right;
    double factor_1 = cur->val / head->val;

    if (factor_1 - (next->val / cur->val) > 0) {//если удалён первый элемент
        Node* node = new Node;
        node->val = head->val * factor_1;
        node->left = head;
        node->right = cur;
        head->right = node;
        cur->left = node;
    }
    else {
        while (next != NULL) {
            if (factor_1 != next->val / cur->val) {
                Node* node = new Node;
                node->val = cur->val * factor_1;
                node->left = cur;
                node->right = next;
                cur->right = node;
                next->left = node;
                break;
            }
            cur = next;
            next = next->right;
        }
    }

    unsigned int end_time = clock();
    
    cur = head;
    std::cout << "\nRestored sequence\n";
    while (cur != NULL) {
        std::cout << cur->val << "   ";
        cur = cur->right;
    }
    std::cout << "\nTime: " << end_time - start_time;
}*/

int main()
{//Генерация последовательности
    int index, N;
    double factor;
    std::cout << "\nEnter number of elements: ";
    std::cin >> N;
    std::vector <long double> arr(N);
    std::cout << "\nEnter index of missing element or \"-1\" for enter sequence yourself: ";
    std::cin >> index;
    if (index != -1) {
        std::cout << "\nEnter geometric ratio: ";
        std::cin >> factor;
        std::cout << "\nEnter first element: ";
        std::cin >> arr[0];
        std::cout << "\nSource sequence\n" << arr[0] << "   ";

        for (int i = 1; i < N; ++i) {
            if (i != index) {
                arr[i] = arr[i - 1] * factor;
                std::cout << arr[i] << "   ";
            }
            else {
                arr[i] = arr[i - 1] * factor * factor;
                std::cout << arr[i] << "   ";
            }
        }
    }
    else {
        std::cout << "\nEnter sequence: ";
        for (int i = 0; i < N; ++i) {
            std::cin >> arr[i];
        }
    }
    //Тело алгоритма
    unsigned int start_time = clock();

    double factor_1 = arr[1] / arr[0];

    if (factor_1 - (arr[2] / arr[1]) > 0) {//если удалён первый элемент
        arr.insert(arr.begin() + 1, arr[0] * factor_1);
    }
    else {
        for (int i = 1; i < N - 1; ++i) {
            if (factor_1 != arr[i + 1] / arr[i]) {
                arr.insert(arr.begin() + i + 1, arr[i] * factor_1);
                break;
            }
        }
    }

    unsigned int end_time = clock();

    std::cout << "\nRestored sequence\n";
    for (int i = 0; i <= N; ++i) {
        std::cout << arr[i] << "   ";
    }
    std::cout << "\nTime: " << end_time - start_time;
}

/*int main()
{//Генерация последовательности
    int index, N;
    double factor;
    long double num;
    std::queue <long double> q;
    std::cout << "\nEnter number of elements: ";
    std::cin >> N;
    std::cout << "\nEnter index of missing element or \"-1\" for enter sequence yourself: ";
    std::cin >> index;
    if (index != -1) {
        std::cout << "\nEnter geometric ratio: ";
        std::cin >> factor;
        std::cout << "\nEnter first element: ";
        std::cin >> num;
        q.push(num);
        std::cout << "\nSource sequence\n" << num << "   ";

        for (int i = 1; i < N; ++i) {
            if (i != index) {
                num *= factor;
                std::cout << num << "   ";
                q.push(num);
            }
            else {
                num *= factor * factor;
                std::cout << num << "   ";
                q.push(num);
            }
        }
    }
    else {
        std::cout << "\nEnter sequence: ";
        for (int i = 0; i < N; ++i) {
            std::cin >> num;
            q.push(num);
        }
    }
    //Тело алгоритма
    unsigned int start_time = clock();

    num = q.front();
    q.pop();
    double factor_1 = q.front() / num;
    std::cout << "\nRestored sequence\n";
    std::cout << num << "   ";
    num = q.front();
    q.pop();
    if (factor_1 - (q.front() / num) > 0) {//если удалён первый элемент
        std::cout << num / factor_1 << "   " << num << "   ";
    }
    else {
        while (!q.empty()) {
            std::cout << num << "   ";
            if (factor_1 != q.front() / num) {
                std::cout << num * factor_1 << "   ";
                break;
            }
            num = q.front();
            q.pop();
        }
    }
    while (!q.empty()) {
        std::cout << q.front() << "   ";
        q.pop();
    }

    unsigned int end_time = clock();
    std::cout << "\nTime: " << end_time - start_time;
}*/