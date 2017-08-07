#ifndef RING_H
#define RING_H

#include <boost/std.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/smart_ptr.hpp>
using namespace boost;


template<typename T>
struct min_element {
    typedef T result_type;

    template<typename InputIterator>
    T operator ()(InputIterator first, InputIterator last) const
    {
        return T(first, last);
    }
};




//////////////////////////////////////////

class sample
{
private:
	class impl;
	shared_ptr<impl> p;
public:
	sample();
	void print();
};

class sample::impl
{
public:
	void print()
	{
		std::cout << "impl print" << std::endl;
	}
};

sample::sample() :p(new impl) {}

void sample::print()
{
	p->print();
}

void case1()
{
	sample s;
	s.print();
}

//////////////////////////////////////////

class abstract
{
public:
	virtual void f() = 0;
	virtual void g() = 0;
protected:
	virtual ~abstract() = default;
};

class impl :public abstract
{
public:
	impl() = default;
	virtual ~impl() = default;
public:
	virtual void f()
	{
		std::cout << "class impl f" << std::endl;
	}
	virtual void g()
	{
		std::cout << "class impl g" << std::endl;
	}
};


#endif

