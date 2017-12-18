#include <iostream>
#include <string>
#include <vector>

namespace test
{
using namespace std;
using object_t = int;

void draw(const object_t& x, ostream& out, size_t position)
{
	out << string(position, ' ') << x << endl;
}

using document_t = vector<object_t>;

void draw(const document_t& x, ostream& out, size_t position)
{
	out << string(position, ' ') << "<document>" << endl;
	for (const auto& e : x)
	{
		draw(e, out, position + 2);
	}
	out << string(position, ' ') << "</document>" << endl;
}
}

int main()
{
	using namespace test;

	document_t document;
	document.emplace_back(0);
	document.emplace_back(1);
	document.emplace_back(2);
	document.emplace_back(3);

	draw(document, cout, 0);
}
