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

class my_class_t {};

void draw(const my_class_t&, ostream& out, size_t position)
{
	out << string(position, ' ') <<"my_class_t"<<endl;
}

void document_work()
{
	document_t document;

	document.emplace_back(0);
	document.emplace_back(string("10-Hello"));
	document.emplace_back(document);
	document.emplace_back(my_class_t());

	draw(document, cout, 0);
}
int main()
{
	some_t x = {0};
	x        = func();

	document_work();
}
