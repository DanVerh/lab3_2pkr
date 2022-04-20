#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int count = 1;
			int amSt = 2;
			double result = (count * 1.0 / amSt * 1.0) * 100.0;
			Assert::AreEqual(result, 50.0);
		}
	};
}
