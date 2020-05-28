#include <iostream>
#include <ctime>
using namespace std;

int main()
{
	int n, x = 101;

	srand(time(0));
	n = rand() % 101;
	cout << "Guess the number: ";
	while (x != n)
	{
		cin >> x;
		if (n > x) cout << "Number > " << x << endl << endl << "Try again: ";
		else if (n < x) cout << "Number < " << x << endl << endl << "Try again: ";
	}
	cout << "Bingo!" << endl;
}
