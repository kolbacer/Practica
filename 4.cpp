#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <initializer_list>
#include <ctime>
using namespace std;

class chip
{
public:
	chip() {};
	chip(initializer_list<int> list){
		auto begin = list.begin();
		auto end = list.end();
		for (auto it = begin; it != end; ++it)
		{
			if (it == begin) amount = *it;
			else cost = *it;
		}
		picked = 0;
		placed = 0;
		sum = 0;
	}

	bool has() { return picked > placed; }
	void place() { 
		++placed;
		sum += cost;
	}
	bool pick() {
		if (picked < amount)
		{
			++picked;
			return true;
		}
		return false;
	}
	bool used() { return (placed > 0); }
	void refresh() { 
		placed = 0; 
		sum = 0;
	}
	static int get_sum() { return sum; }

	int amount;
	int cost;
private:
	int picked;
	int placed;
	static int sum;
};
int chip::sum = 0;

map<char, chip> letter = { {'а',{10,1}}, {'б',{3,3}}, {'в',{5,2}}, {'г',{3,3}}, {'д',{5,2}},
{'е',{9,1}}, {'ж',{2,5}}, {'з',{2,5}}, {'и',{8,1}}, {'й',{4,2}}, {'к',{6,2}}, {'л',{4,2}},
{'м',{5,2}}, {'н',{8,1}}, {'о',{10,1}}, {'п',{6,2}}, {'р',{6,2}}, {'с',{6,2}}, {'т',{5,2}},
{'у',{3,3}}, {'ф',{1,10}}, {'х',{2,5}}, {'ц',{1,10}}, {'ч',{2,5}}, {'ш',{1,10}}, {'щ',{1,10}},
{'ъ',{1,10}}, {'ы',{2,5}}, {'ь',{2,5}}, {'э',{1,10}}, {'ю',{1,10}}, {'я',{3,3}}, {'*',{3,0}} };

void refresh_all()
{
	for (auto &chip : letter)
		chip.second.refresh();
}

char pick_up(int range)
{
	bool can_pick = false;
	char c;
	while (!can_pick) 
	{
		int x = rand() % range;
		if (x == 32) c = '*';
		else c = 'а' + x;
		can_pick = letter[c].pick();
	}
	return c;
}

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "russian");

	ifstream dict;
	dict.open("dictionary.txt");
	if (!dict.is_open())
	{
		cout << "Can't open dictionary!" << endl;
		return -1;
	}

	cout << "Взятые фишки: ";
	for (size_t i = 0; i < 7; ++i)
		cout << pick_up(33) << " ";
	char main_letter = pick_up(32);
	cout << main_letter << endl;
	cout << "Главная фишка: " << main_letter << endl;
	chip &main_chip = letter[main_letter];

	chip &asterisk_chip = letter['*'];
	int max_sum = 0;
	string maxword;
	while (!dict.eof())
	{
		refresh_all();
		bool good_word = true;
		string word;
		dict >> word;
		for (size_t i = 0; i < word.size(); ++i)
		{
			chip &current_chip = letter[word[i]];

			if (current_chip.has()) current_chip.place();
			else if (asterisk_chip.has()) asterisk_chip.place();
			else {
				good_word = false;
				break;
			}
		}

		if (!good_word || !main_chip.used()) continue;
		int sum = chip::get_sum();
		if (sum > max_sum) {
			max_sum = sum;
			maxword = word;
		}
	}
	dict.close();
	cout << endl;

	if (max_sum == 0)
	{
		cout << "Нельзя составить ни одного слова!" << endl;
		return 1;
	}

	cout << "Лучшее слово: " << maxword << " (сумма = " << max_sum << ")" << endl;
	return 0;
}
