#include <iostream>
#include <vector>
using namespace std;

bool is_divided(int a, int b)
{
	if (a % b == 0) return true;
	return false;
}

int dividers(int x)
{
	if (x == 1) return 1;
	int k = 2;
	for (int i = 2; i <= sqrt(x); ++i)
		if (is_divided(x, i))
		{
			++k;
			if (i != sqrt(x)) ++k;
		}

	return k;
}

int main()
{
	int m, n;
	vector<int> mdiv;

	cout << "Enter M, N: ";
	cin >> m >> n;

	int kmax = 1;
	for (int i = m; i <= n; ++i)
	{
		int k = dividers(i);
		if (k == kmax) mdiv.push_back(i);
		else if (k > kmax)
		{
			kmax = k;
			mdiv.clear();
			mdiv.push_back(i);
		}
	}

	cout << endl << "Max dividers: ";
	for (auto x : mdiv)
		cout << x << " ";
	cout << endl;
}
