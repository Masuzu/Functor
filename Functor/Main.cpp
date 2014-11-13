#include "Functor.h"
#include "FunctorSlot.h"

#include <functional>

class A
{
public:
	int foo(double, char)
	{
		return 0;
	}

	int foo2(double *, char *)
	{
		return 0;
	}
};

int main()
{
	A a;
	FunctorClass<int (A::*)(double, char), &A::foo> test(a);
	test(3.14, 'c');

	// Now do the same thing with std::function
	std::function<int(double, char)> test2 = std::bind(&A::foo, &a, std::placeholders::_1, std::placeholders::_2);
	test2(3.14, 'c');

	Functor<int> test3(&A::foo2, &a);
	test3(nullptr, nullptr);	// Will not work with non pointer arguments
}