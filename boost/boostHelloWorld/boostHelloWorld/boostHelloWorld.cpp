#include <boost/scoped_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/make_shared.hpp>
#include <boost/exception/all.hpp>
#include <boost/exception/get_error_info.hpp>
#include <boost/array.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/unordered_map.hpp>
#include <boost/assign.hpp>
#include <iostream>
#include <string.h>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include "ring.h"

using namespace boost;

typedef boost::error_info<struct tag_err_no, int> err_no;
typedef boost::error_info<struct tag_err_str, std::string> err_str;


shared_ptr<abstract> create()
{
    return make_shared<impl>();
}


/*
入口函数
*/
int main()
{
    scoped_ptr<int> i (new int);
    *i = 1;
    std::cout << "i =" << *i.get() << std::endl;
    *i.get() = 2;
    std::cout << "i =" << *i.get() << std::endl;
    i.reset (new int);
    scoped_ptr<std::string> sp (new std::string ("text"));
    std::cout << *sp << std::endl;
    shared_ptr<abstract> p = create();
    p->f();
    p->g();
    
    try
    {
        try
        {
            throw my_exception() << err_no (10);
        }
        
        catch (my_exception& e)
        {
            std::cout << *get_error_info<err_no> (e) << std::endl;
            std::cout << e.what() << std::endl;
            e << err_str ("other info");
            throw;
        }
    }
    
    catch (my_exception& e)
    {
        std::cout << *get_error_info<err_str> (e) << std::endl;
    }
    
    array<int, 10> ar;
    ar[0] = 1;
    ar.back() = 100;
    assert (ar[ar.max_size() - 1] == 100);
    ar.assign (777);
    
    for (auto x : ar)
    {
        std::cout << x << std::endl;
    }
    
    int *ptemp = ar.c_array();
    * (ptemp + 5) = 253;
    std::cout << "ar[5]=" << ar[5] << std::endl;
    ar[6] = 666;
    ar.at (7) = 777;
    ar.at (8) = 888;
    ar.at (9) = 999;
    std::sort (ar.begin(), ar.end());
    
    for (auto y : ar)
    {
        std::cout << y << std::endl;
    }
    
    array <std::string, 3> ar1 = { "alice", "bob", "carl" };
    array <std::string, 3> ar2 = { "racer" };
    typedef boost::tuple<std::string, std::string, int> person;
    person pers1 = boost::make_tuple ("Boris", "Schaeling", 43);
    person pers2 = boost::make_tuple ("Boris", "Becker", 43);
    std::cout << pers1 << std::endl;
    std::cout << pers2 << std::endl;
    person pers3 ("Boris", "Schaeling", 43);
    std::cout << pers3 << std::endl;
    std::cout << pers3.get<0>() << std::endl;
    std::cout << boost::get<1> (pers3) << std::endl;
    std::cout << pers3.get<2>() << std::endl;
    pers3.get<1>() = "Becker";
    std::cout << pers3.get<0>() << std::endl;
    std::cout << boost::get<1> (pers3) << std::endl;
    std::cout << pers3.get<2>() << std::endl;
    std::vector<int>vi;
    int a;
    
    while (true)
    {
        std::cout << "输入一个整数，按0停止输入：";
        std::cin >> a;
        
        if (a == 0)
        {
            break;
        }
        
        vi.push_back (a);
        std::vector<int>::iterator iter;
        
        for (iter = vi.begin(); iter != vi.end(); ++iter)
        {
            std::cout << *iter;
        }
    }
    
    std::vector<int> ivec;
    std::cout << "ivec:size:" << ivec.size() << " capacity: " << ivec.capacity() << std::endl;
    
    for (int ix = 0; ix < 24; ++ix)
    {
        ivec.push_back (ix);
        std::cout << "ivec:size:" << ivec.size() << " capacity: " << ivec.capacity() << std::endl;
    }
    
    std::vector<std::string> svec;
    std::list<int>ilist;
    //std::string textword;
    //while (std::cin >>textword)
    {
        svec.push_back ("one");
    }
    svec.push_back ("one, two");
    svec.push_back ("one, two three");
    std::vector<std::string>::iterator iterv;
    
    for (iterv = svec.begin(); iterv != svec.end(); ++iterv)
    {
        std::cout << *iterv << std::endl;
    }
    
    int ia[4] = { 0, 1, 2, 3 };
    
    for (int ix = 0; ix < 4; ++ix)
    { ilist.push_back (ia[ix]); }
    
    for (int ix = 0; ix < 4; ++ix)
    { ilist.push_front (ia[ix]); }
    
    std::list<int>::iterator itor = ilist.begin();
    
    while (itor != ilist.end())
    {
        std::cout << *itor++ << std::endl;
    }
    
    return 0;
}