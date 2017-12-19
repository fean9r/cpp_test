#include "library.h"
#include <algorithm>
#include <string>
using namespace test;

struct some_t
{
	object_t member_;
};

some_t func()
{
	return {5};
}

void document_work()
{
	document_t document;

	document.emplace_back(0);
	document.emplace_back(string("10-Hello"));
	document.emplace_back(20);
	document.emplace_back(30);

	draw(document, cout, 0);
}
int main()
{
	some_t x = {0};
	x        = func();

	document_work();
}
