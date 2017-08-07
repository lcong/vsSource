#pragma once
#ifndef BOOSTTEST_H

#include <string>
#include <iostream>

template<class T, class D>
class Member
{
public:
	Member(T t, D d) : name(t), sal(d) {	};
	void print();
private:
	T name;
	D sal;
};

template<class T, class D>
void Member<T , D>::print()
{
	cout << name << " : " << sal << endl;
}



#endif // !BOOSTTEST_H
