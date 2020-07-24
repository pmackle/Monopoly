#include <iostream>
#include <memory>

class Class1
{
    public:
        
        Class1(int num1) : num1(num1)
        {
            
        }
        
        virtual int getNum1() const = 0;
        
        
    protected:
        
        int num1;
};

class Class2 : public Class1
{
    public:
    
        Class2(int num1, int num2) : Class1(num1), num2(num2)
        {
        
        }
        
        int num2 = 5;
        
        virtual int getNum1() const
        {
            return num2;
        }
};

int main(void)
{
    int num1 = 1, num2 = 2;
    
    std::vector<std::unique_ptr<Class1> > ptr = std::make_unique<Class2>();

    ptr.push_back(std::move(std::))
    
    ptr.push_back(class1Ptr);    
    std::cout << "num 2 is " <<  << std::endl;
}
    