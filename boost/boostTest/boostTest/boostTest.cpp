#include <boost/array.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/progress.hpp>
#include <boost/thread.hpp> 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/asio.hpp> 
#include "boostTest.h"

using namespace std;
using namespace boost;

template<class T>
class Print
{
    public:
        void operator() (T&t)
        {
            cout << t << "";
        }
        
};


void handler1(const boost::system::error_code &ec)
{
	std::cout << "5 s." << std::endl;
}

void handler2(const boost::system::error_code &ec)
{
	std::cout << "10 s." << std::endl;
}

boost::asio::io_service io_service1;
boost::asio::io_service io_service2;

void run1()
{
	io_service1.run();
}

void run2()
{
	io_service2.run();
}


int main()
{

	boost::asio::deadline_timer timer1(io_service1, boost::posix_time::seconds(5));
	timer1.async_wait(handler1);
	boost::asio::deadline_timer timer2(io_service2, boost::posix_time::seconds(5));
	timer2.async_wait(handler2);
	boost::thread thread1(run1);
	boost::thread thread2(run2);
	thread1.join();
	thread2.join();

    typedef boost::array<std::string, 3> array;
    array a1;
    a1[0] = "Boris";
    a1.at (1) = "Anton";
    *a1.rbegin() = "Caesar";
    
    for (array::const_iterator it = a1.begin(); it != a1.end(); ++it)
    {
        cout << *it << endl;
    }
    
    std::sort (a1.begin(), a1.end());
    cout << "after sort" << endl;
    
    for (array::const_iterator it = a1.begin(); it != a1.end(); ++it)
    {
        cout << *it << endl;
    }
    
    cout << a1.size() << endl;
    cout << a1.max_size() << endl;
    array a2 = { "Boris", "Anton", "Caesar" };
    typedef boost::tuple<string, string, int> person;
    person p1 ("Boris", "Schaeling", 43);
    string s = "David";
    cout << boost::make_tuple (boost::ref (s), "Schaeling", 41) << endl;
    person p3 = boost::make_tuple ("Rockcong", "Schaeling", 43);
    p3.get<1>() = "Becker";
    cout << p3 << endl;
    person p4 = boost::make_tuple ("Boris", "Schaeling", 43);
    person p5 = boost::make_tuple ("Boris", "Becker", 43);
    cout << (p4 != p5) << endl;
    cout << p4 << endl;
    cout << p5 << endl;
    vector<string> vStr (100);
    progress_display pd (vStr.size());
    vector<string>::iterator pos;
    
    for (pos = vStr.begin(); pos != vStr.end(); ++pos)
    {
		boost::this_thread::sleep(boost::posix_time::seconds(2));
        ++pd;
    }
    
    vector<int> vInt (10);
    Print<int> print;
    fill (vInt.begin(), vInt.end(), 5);
    cout << "Vector vInt:";
    for_each (vInt.begin(), vInt.end(), print);
    cout << endl;
    cout << "Size of vInt= " << vInt.size() << endl;
    cout << "vInt.clear" << endl;
    vInt.clear();
    cout << "Vector vInt : ";
    for_each (vInt.begin(), vInt.end(), print);
    cout << endl;
    cout << "Size of vInt =" << vInt.size() << endl;
    cout << "Vector vInt is " ;
    vInt.empty() ? cout << "" : cout << "not";
    cout << "empty" << endl;
    typedef Member<string, double> M;
    vector<M> vM;
    vM.push_back (M ("Linda", 7500));
    vM.push_back (M ("Robot", 8500));
    vector<M>::iterator It = vM.begin();
    cout << "Entire vector: " << endl;
    
    while (It != vM.end())
    {
        (It++)->print();
    }
    
    cout << endl;
}
