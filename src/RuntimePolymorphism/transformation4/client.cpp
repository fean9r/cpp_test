#include "library.h"
#include <algorithm>
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
	document.reserve(5);

	document.emplace_back(0);
	document.emplace_back(10);
	document.emplace_back(20);
	document.emplace_back(30);
	document.emplace_back(40);

	reverse(document.begin(), document.end());

	draw(document, cout, 0);
}
int main()
{
	some_t x = {0};
	x        = func();

	document_work();
}
