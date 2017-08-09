#include <boost/array.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/progress.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "boostTest.h"

using namespace std;
using namespace boost;

template<class T>
class Print
{
public:
	void operator()(T&t)
	{
		cout << t << "";

	}

};


int main()
{
    typedef boost::array<std::string, 3> array;
    array a;
    a[0] = "Boris";
    a.at (1) = "Anton";
    *a.rbegin() = "Caesar";

	for (array::const_iterator it = a.begin(); it != a.end(); ++it)
	{
		cout << *it << endl;
	}

	std::sort (a.begin(), a.end());

	cout <<"after sort" << endl;

    for (array::const_iterator it = a.begin(); it != a.end(); ++it)
    {
        cout << *it << endl;
    }
    
    cout << a.size() << endl;
    cout << a.max_size() << endl;
    
	
	typedef boost::array<string, 3> array2;
    array2 a2 = { "Boris", "Anton", "Caesar" };
    
	typedef boost::tuple<string, string, int> person1;
    person1 p1 ("Boris", "Schaeling", 43);
    std::cout << p1 << std::endl;
    
	typedef boost::tuple<string, string> person2;
    person2 p2 ("Boris", "Schaeling");
    cout << p2 << endl;
    string s = "David";
    cout << boost::make_tuple (boost::ref (s), "Schaeling", 41) << endl;
    
    person1 p3 = boost::make_tuple ("Rockcong", "Schaeling", 43);
    p3.get<1>() = "Becker";
    cout << p3 << endl;
    person1 p4 = boost::make_tuple ("Boris", "Schaeling", 43);
    person1 p5 = boost::make_tuple ("Boris", "Becker", 43);
    cout << (p4 != p5) << endl;
    
	vector<string> vStr (100);
    progress_display pd (vStr.size());
    vector<string>::iterator pos;
    
	cout << "Vector vStr:";

    for (pos = vStr.begin(); pos != vStr.end(); ++pos)
    {
        cout << *pos << endl;
        ++pd;
    }

	vector<int> vInt(10);
	Print<int> print;
	fill(vInt.begin(), vInt.end(), 5);

	cout << "Vector vInt:";
	for_each(vInt.begin(), vInt.end(), print);
	cout << endl;

	cout << "Size of vInt= " << vInt.size() << endl;

	cout << "vInt.clear" << endl;

	vInt.clear();

	cout << "Vector vInt : ";

	for_each(vInt.begin(), vInt.end(), print);

	cout << endl;

	cout << "Size of vInt =" << vInt.size() << endl;

	cout << "Vector vInt is " ;

	vInt.empty() ? cout << "" : cout << "not";

	cout << "empty" << endl;

	typedef Member<string, double> M;
	vector<M> vM;
	vM.push_back(M("Linda", 7500));
	vM.push_back(M("Robot", 8500));

	vector<M>::iterator It = vM.begin();
	cout << "Entire vector: " << endl;
	
	while (It !=vM.end())
	{
		(It++)->print();

	}

	cout << endl;

}
