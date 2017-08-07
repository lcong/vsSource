// helloException.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class Expt
{
    public:
        Expt() {};
        ~Expt() {};
        const char *ShowReason() const
        {
            return "Except 异常";
        }
        
        
};

class Demo
{
    public:
        Demo() ;
        ~Demo();
};

Demo::Demo()
{
    cout << "构造Demo" << endl;
}

Demo::~Demo()
{
    cout << "析构Demo" << endl;
}

void MyFunc()
{
    Demo D;
    cout << "在MyFunc()抛出Expt类异常" << endl;
    throw Expt();
}

class Point
{
    public:
        Point();
        ~Point();
        void InitP (float xx = 0, float yy = 0)
        {
            X = xx;
            Y = yy;
        };
        void Move (float xOff, float yOff)
        {
            X += xOff;
            Y += yOff;
        };
        float GetX()
        {
            return X;
        };
        float GetY()
        {
            return Y;
        };
        
        
    private:
        float X;
        float Y;
};



template <class T>
class Store
{
    private:
        T item;
        int haveValue;
        
    public:
        Store (void);
        T GetElem (void);
        void PutElem (T x);
        
};


template <class T>
Store<T>::Store (void) : haveValue (0)
{}

template <class T>
T Store<T>::GetElem (void)
{
    if (0 == haveValue)
    {
        cout << "no item present" << endl;
        exit (1);
    }
    
    return item;
}

template <class T>
void Store<T>::PutElem (T x)
{
        haveValue++;
        item = x;
}

int main()
{
    cout << "在Main函数中" << endl;
    
    try
    {
        cout << "在try块中，调用MyFunc()" << endl;
        MyFunc();
    }
    
    catch (Expt E)
    {
        cout << "在try块中，调用MyFunc()" << endl;
        cout << "捕获到Expt类型异常" << endl;
        cout << E.ShowReason() << endl;
    }
    
    catch (char* str)
    {
        cout << "捕获到其他的异常" << endl;
    }
    
    cout << "回到Main函数，从这里恢复执行" << endl;
    return 0;
}