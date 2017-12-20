#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace test
{
using namespace std;

template <typename T>
void draw(const T& x, ostream& out, size_t position)
{
	out << string(position, ' ') << x << endl;
}

class object_t
{
public:
	template <typename T>
	object_t(T x)
	    : self_(make_unique<model<T>>(move(x)))
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
	template <typename T>
	struct model final : concept_t
	{
		model(T x)
		    : data_(move(x))
		{}

		unique_ptr<concept_t> copy_() const override
		{
			return make_unique<model>(*this);	
		}

		void draw_(ostream& out, size_t position) const override
		{
			draw(data_, out, position);
		}

		T data_;
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
