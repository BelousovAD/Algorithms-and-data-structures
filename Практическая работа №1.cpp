#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

/*unsigned long long a(const int& i)
{
    unsigned long long ai = 0;
    for (int j = 1; j <= i; ++j)
        ai += j;
    return ai;
}

int main()
{
    int N;
    cout << "Enter N: ";
    cin >> N;
    unsigned int start_time = clock();
    vector <unsigned long long> K(N);
    K[0] = 0;

    for (int i = 1; i < N; ++i)
    {
        K[i] = K[i - 1] + a(i);
        cout << endl << "K[" << i << "] = " << K[i];
    }

    unsigned int end_time = clock();
    cout << endl << end_time - start_time;
}*/

int main()
{
    int N;
    cout << "Enter N: ";
    cin >> N;
    unsigned int start_time = clock();
    vector <unsigned long long> K(N);
    vector <unsigned long long> a(N);
    K[0] = 0;
    a[0] = 0;

    for (int i = 1; i < N; ++i)
    {
        a[i] = a[i - 1] + i;
        K[i] = K[i - 1] + a[i];
        cout << endl << "K[" << i << "] = " << K[i];
    }

    unsigned int end_time = clock();
    cout << endl << end_time - start_time;
}