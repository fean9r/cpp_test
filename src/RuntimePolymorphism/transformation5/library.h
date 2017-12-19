#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace test
{
using namespace std;

void draw(const int& x, ostream& out, size_t position)
{
	out << string(position, ' ') << x << endl;
}

void draw(const string& x, ostream& out, size_t position)
{
	out << string(position, ' ') << x << endl;
}

class object_t
{
public:
	object_t(string x)
	    : self_(make_unique<string_model_t>(move(x)))
	{
		cout << "ctor" << endl;
	}

	object_t(int x)
	    : self_(make_unique<int_model_t>(move(x)))
	{
		cout << "ctor" << endl;
	}

	// Our own copy constructor
	object_t(const object_t& x)
	    : self_(x.self_->copy_())
	{
		cout << "copy" << endl;
	}

	// Our move constructor (the && is R-value reference a temporary)
	// by beeing temporary we can steal the content of it without problem
	// we use the default one that just does: self_(move(x.self_))
	object_t(object_t&& x) noexcept = default;

	// Our own assignment operator
	object_t& operator=(object_t x) noexcept
	{
		// Passing the argument by value to exploit value return optimization
		// And steal the content of it to us
		self_ = move(x.self_);
		return *this;
	}

	friend void draw(const object_t& x, ostream& out, size_t position)
	{
		x.self_->draw_(out, position);
	}

private:
	struct concept_t
	{
		virtual ~concept_t()                        = default;
		virtual unique_ptr<concept_t> copy_() const = 0;
		virtual void  draw_(ostream&, size_t) const = 0;
	};

	struct string_model_t final : concept_t
	{
		string_model_t(string x)
		    : data_(move(x))
		{
		}

		unique_ptr<concept_t> copy_() const override
		{
			return make_unique<string_model_t>(*this);	
		}

		void draw_(ostream& out, size_t position) const
		{
			draw(data_, out, position);
		}
		string data_;
	};
	struct int_model_t final : concept_t
	{
		int_model_t(int x)
		    : data_(move(x))
		{
		}

		unique_ptr<concept_t> copy_() const override
		{
			return make_unique<int_model_t>(*this);	
		}

		void draw_(ostream& out, size_t position) const
		{
			draw(data_, out, position);
		}
		int data_;
	};
	unique_ptr<concept_t> self_;
};

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
