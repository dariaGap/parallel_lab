#include "pch.h"
#include "CppUnitTest.h"
#include "../parallel_lab/nonParallel.cpp"
#include "../parallel_lab/parallel.cpp"
#include <CppUnitTestAssert.h>
#include <algorithm>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<> inline std::wstring ToString<class std::vector<int, class std::allocator<int>>>(const class std::vector<int, class std::allocator<int>>& t) 
			{ 
				std::wstringstream ss;
				for (size_t i = 0; i < t.size(); i++) 
				{
					ss << t[i];
					if (i != t.size() - 1)
						ss << ",";
				}
				return ss.str(); 
			}
		}
	}
}

namespace parallellabtest
{
	TEST_CLASS(nonParallelTest)
	{
	public:
		vector<int> a;
		vector<int> b;
		vector<int> c;
		nonParallelClass np;

		nonParallelTest()
		{

			for (size_t i = 1; i <= 300000; i += 3)
			{
				a.push_back(i);
				b.push_back(i + 1);
				c.push_back(i + 2);
			}
		}

		TEST_METHOD(EmptyATest)
		{
			a.clear();

			vector<int> exp = {};

			vector<int> res = np.nonParallel(a, b, c);

			Assert::AreEqual(exp, res);
		}


		TEST_METHOD(EmptyBTest)
		{
			b.clear();
			vector<int> exp = {};

			vector<int> res = np.nonParallel(a, b, c);

			Assert::AreEqual(exp, res);
		}

		TEST_METHOD(EmptyCTest)
		{
			c.clear();
			vector<int> exp = {};

			vector<int> res = np.nonParallel(a, b, c);

			Assert::AreEqual(exp, res);
		}

		TEST_METHOD(AllMatchesTest)
		{
			b = a;
			c = a;

			vector<int> exp = a;

			vector<int> res = np.nonParallel(a, b, c);

			sort(res.begin(), res.end());
			sort(exp.begin(), exp.end());


			Assert::AreEqual(exp, res);
		}

		TEST_METHOD(SomeMatchesTest)
		{
			b.insert(b.begin() + 600, a[200]);
			b.insert(b.begin() + 800, a[1]);
			b.insert(b.begin() + 300, a[4000]);

			c.insert(c.begin() + 350, a[200]);
			c.insert(c.begin() + 150, a[1]);
			c.insert(c.begin() + 650, a[4000]);

			vector<int> exp = { a[1],a[200],a[4000] };

			vector<int> res = np.nonParallel(a, b, c);

			sort(res.begin(), res.end());
			sort(exp.begin(), exp.end());

			Assert::AreEqual(exp, res);
		}

		TEST_METHOD(DiffLengthTest)
		{
			for (size_t i = 0; i < 20; i+=2) {
				b.push_back(a[i]);
				c.push_back(a[i]);
				c.push_back(a[i + 1]);
				a.pop_back();
			}
			vector<int> exp = { a[0],a[2],a[4],a[6],a[8],a[10],a[12],a[14],a[16],a[18] };

			vector<int> res = np.nonParallel(a, b, c);

			sort(res.begin(), res.end());
			sort(exp.begin(), exp.end());

			Assert::AreEqual(exp, res);
		}

		TEST_METHOD(NoMatchesTest)
		{
			vector<int> exp = { };

			Assert::AreEqual(np.nonParallel(a, b, c),exp);
		}
	};

	TEST_CLASS(parallelTest)
	{
	public:
		vector<int> a;
		vector<int> b;
		vector<int> c;
		parallelClass np;

		parallelTest()
		{

			for (size_t i = 1; i <= 300000; i += 3)
			{
				a.push_back(i);
				b.push_back(i + 1);
				c.push_back(i + 2);
			}
		}

		TEST_METHOD(EmptyATest)
		{
			a.clear();

			vector<int> exp = {};

			vector<int> res = np.parallel(a, b, c);

			Assert::AreEqual(exp, res);
		}

		TEST_METHOD(EmptyBTest)
		{
			b.clear();
			vector<int> exp = {};

			vector<int> res = np.parallel(a, b, c);

			Assert::AreEqual(exp, res);
		}

		TEST_METHOD(EmptyCTest)
		{
			c.clear();
			vector<int> exp = {};

			vector<int> res = np.parallel(a, b, c);

			Assert::AreEqual(exp, res);
		}
	
		TEST_METHOD(AllMatchesTest)
		{
			b = a;
			c = a;

			vector<int> exp = a;

			vector<int> res = np.parallel(a, b, c);

			sort(res.begin(), res.end());
			sort(exp.begin(), exp.end());

			Assert::AreEqual(exp, res);
		}

		TEST_METHOD(SomeMatchesTest)
		{
			b.insert(b.begin() + 600, a[200]);
			b.insert(b.begin() + 800, a[1]);
			b.insert(b.begin() + 300, a[4000]);

			c.insert(c.begin() + 350, a[200]);
			c.insert(c.begin() + 150, a[1]);
			c.insert(c.begin() + 650, a[4000]);

			vector<int> exp = { a[1],a[200],a[4000] };

			vector<int> res = np.parallel(a, b, c);
			sort(res.begin(), res.end());
			sort(exp.begin(), exp.end());

			Assert::AreEqual(exp, res);
		}

		TEST_METHOD(DiffLengthTest)
		{
			for (size_t i = 0; i < 20; i += 2) {
				b.push_back(a[i]);
				c.push_back(a[i]);
				c.push_back(a[i + 1]);
				a.pop_back();
			}
			vector<int> exp = { a[0],a[2],a[4],a[6],a[8],a[10],a[12],a[14],a[16],a[18] };

			vector<int> res = np.parallel(a, b, c);

			sort(res.begin(), res.end());
			sort(exp.begin(), exp.end());

			Assert::AreEqual(exp, res);
		}
		
		TEST_METHOD(NoMatchesTest)
		{
			vector<int> exp = { };

			Assert::AreEqual(np.parallel(a, b, c), exp);
		}
	};
}
