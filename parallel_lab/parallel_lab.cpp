#include <iostream>
#include <vector>
#include "nonParallel.h"
#include "parallel.h"

using namespace std;

void print_vector(vector<int> vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (i != 0)
			cout << ", ";
		cout << vec[i];
	};
	cout << endl;
}

int main(int argc, char **argv)
{
	vector<int> a, b, c;
	int num;
	cout << "Enter a" << endl;
	while (cin >> num)
	{
		a.push_back(num);
		if (cin.peek() == '\n')
			break;
	}
	cout << "Enter b" << endl;
	while (cin >> num)
	{
		b.push_back(num);
		if (cin.peek() == '\n')
			break;
	}
	cout << "Enter c" << endl;
	while (cin >> num)
	{
		c.push_back(num);
		if (cin.peek() == '\n')
			break;
	}

	nonParallelClass np;
	parallelClass p;

	vector <int> npres = np.nonParallel(a, b, c);

	vector <int> pres = p.parallel(a, b, c);

	cout << "Nonparallel result:" << endl;
	print_vector(npres);
	cout << "Prallel result:" << endl;
	print_vector(pres);
	
	return EXIT_SUCCESS;
}


