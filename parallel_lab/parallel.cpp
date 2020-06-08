#include "parallel.h"

vector<int> parallelClass::parallel(vector<int> a, vector<int> b, vector<int> c)
{
	vector<int> res;

	if ((!a.empty()) && (!b.empty()) && (!c.empty())) {

		//omp_set_num_threads(1000);
#pragma omp parallel sections
		{
#pragma omp section
			{
				sort(a.begin(), a.end());
			}
#pragma omp section
			{
				sort(b.begin(), b.end());
			}
#pragma omp section
			{
				sort(c.begin(), c.end());
			}
		}
#pragma omp parallel for
		for (size_t i = 0; i < a.size(); i++)
		{
			if (binary_search(b.begin(), b.end(), a[i]))
			{
				if (binary_search(c.begin(), c.end(), a[i]))
				{
#pragma omp critical
					res.push_back(a[i]);
				}
			}
		}
	}
	return res;
}