#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;
const int redak = 20;
const int stupac = 40;

struct Tocka
{
	int Stupac;
	int Redak;
};

void print(char* polje, Tocka& a, Tocka& b, Tocka& x, Tocka& temp) {
	system("CLS");
	for (int i = 0; i < redak; i++)
	{
		for (int j = 0; j < stupac; j++)
		{
			cout << *((polje+i*stupac)+j);
		}
		cout << endl;
	}
	*((polje + a.Redak * stupac) + a.Stupac) = 'A';
	*((polje + b.Redak * stupac) + b.Stupac) = 'B';
	*((polje + temp.Redak * stupac) + temp.Stupac) = '-';
	*((polje + x.Redak * stupac) + x.Stupac) = 'X';
}

int main() {
	char polje[redak][stupac];
	fill(&polje[0][0], &polje[0][0] + 20 * 40, '-');
	int StupacDiff = 0, RedakDiff = 0;

	Tocka a, b, x, temp;
	cout << "A stupac: ";
	cin >> a.Stupac;
	cout << "A redak: ";
	cin >> a.Redak;
	cout << "B stupac: ";
	cin >> b.Stupac;
	cout << "B redak : ";
	cin >> b.Redak;

	a.Redak -= 1;
	a.Stupac -= 1;
	b.Redak -= 1;
	b.Stupac -= 1;

	x = a;

	if (a.Stupac<b.Stupac)
	{
		StupacDiff = 1;
	}
	else if (a.Stupac>b.Stupac)
	{

		StupacDiff = -1;
	}
	
	if (a.Redak<b.Redak)
	{
		RedakDiff = 1;
	}
	else if (a.Redak>b.Redak)
	{
		RedakDiff = -1;
	}

	do {
		temp = x;
		x.Stupac += StupacDiff;
		print(&polje[0][0], a, b, x, temp);
		this_thread::sleep_for(milliseconds(100));
	} while (x.Stupac != b.Stupac);
	
	do{
		temp = x;
		x.Redak += RedakDiff;
		print(&polje[0][0], a, b, x, temp);
		this_thread::sleep_for(milliseconds(100));
	} while (x.Redak != b.Redak);
	print(&polje[0][0], a, b, x, temp);
	return 0;
}