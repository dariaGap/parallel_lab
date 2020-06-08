#include "nonParallel.h"

vector<int> nonParallelClass::nonParallel(vector<int> a, vector<int> b, vector<int> c)
{
	vector<int> res;
	if ((!a.empty()) && (!b.empty()) && (!c.empty())) {

		sort(a.begin(),a.end());
		sort(b.begin(), b.end());
		sort(c.begin(), c.end());
		size_t j = 0;
		for (size_t i = 0; i < a.size(); i++)
		{
			if (binary_search(b.begin(), b.end(), a[i]))
			{
				if(binary_search(c.begin(), c.end(), a[i]))
					res.push_back(a[i]);
			}
		}
	}
	return res;
}