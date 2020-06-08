#pragma once
#include <vector>
#include <algorithm>
#include <omp.h>

using namespace std;

class parallelClass
{
public:
	vector<int> parallel(vector<int> a, vector<int> b, vector<int> c);
};