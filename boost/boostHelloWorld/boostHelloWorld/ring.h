#ifndef RING_H
#define RING_H

class abstract
{
    public:
        virtual void f() = 0;
        virtual void g() = 0;
    protected:
        virtual ~abstract() = default;
        
};

class impl : public abstract
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
    private:
    
};


struct my_exception :
    virtual std::exception,
    virtual boost::exception
{


};
#endif