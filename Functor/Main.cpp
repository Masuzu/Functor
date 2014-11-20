#include "Functor.h"
#include "SmartFunctor.h"

#include <functional>
#include <iostream>

class A
{
public:
	int foo(double d, char c)
	{
		std::cout << "d=" << d << " c=" << c << std::endl;
		return 0;
	}

	int foo2(double **d, char **c)
	{
		*d = new double(3.14);
		*c = new char[5];
		strcpy_s(*c, 5, "test");
		return 0;
	}
};

void foo3(double **d, char **c)
{
	*d = new double(3.14);
	*c = new char[5];
	strcpy_s(*c, 5, "test");
}

int main()
{
	A a;
	Functor<int (A::*)(double, char), &A::foo> test(a);
	test(3.14, 'c');

	// Now do the same thing with std::function
	std::function<int(double, char)> test2 = std::bind(&A::foo, &a, std::placeholders::_1, std::placeholders::_2);
	test2(3.14, 'c');

	// Resolving the function type automatically
	SmartFunctor<int> test3(&A::foo, a);
	test3(3.14, 'c');

	double *d = nullptr;
	char *c = nullptr;
	SmartFunctor<int> test4(&A::foo2, a);
	test4(&d, &c);

	double *d2 = nullptr;
	char *c2 = nullptr;
	SmartFunctor<void> test5(&foo3);
	test5(&d2, &c2);

	system("pause");
}