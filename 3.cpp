#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n;
	cout << "Enter N: ";
	cin >> n;

	vector<int> rock;
	rock.reserve(n + 1);
	rock.resize(n + 1, 0);

	cout << endl << "Masses of rocks: ";
	for (int i = 1; i <= n; ++i)
	{
		cin >> rock[i];
	}
	
	int sum = 0;

	for (auto x : rock)
	{
		sum += x;
	}

	if ((sum % 2) != 0)
	{
		cout << endl << "NO" << endl;
		return 0;
	}

	int m = sum / 2;

	vector<vector<bool>> heap(n+1);
	for (int i = 0; i <= n; ++i)
	{
		heap[i].reserve(m + 1);
		heap[i].resize(m + 1, false);
	}
	heap[0][0] = true;

	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= m; ++j)
			heap[i][j] = (heap[i - 1][j] || ([=]() {if (j >= rock[i]) return (heap[i - 1][j - rock[i]]); else return false; })());

	cout << endl;
	cout << (heap[n][m] ? "YES" : "NO");
	cout << endl;
}
