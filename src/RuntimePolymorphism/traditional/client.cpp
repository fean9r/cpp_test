#include "library.h"
#include <iostream>
#include <string>

namespace test
{
using namespace std;

class my_class_t final : public object_t
{
public:
	void draw(ostream& out, size_t position) const override
	{
		out << string(position, ' ') << "my_class_t" << endl;
	}
};
}

int main()
{
	using namespace test;

	document_t document;
	document.emplace_back(make_shared<my_class_t>());
	draw(document, cout, 0);
}
