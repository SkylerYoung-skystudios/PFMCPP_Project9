/*
 Project 9: Part 1/1
 Chapter 5 Part 7 Task

 Create a branch named Part1

Purpose:  This project will teach you about variadic templates and recursive templates, one of the last areas needing discussion while learning C++

 
1) read Instructions.cpp

Make the following program work, which makes use of Variadic templates and Recursion

2) You need to implement a RECURSIVE variadicHelper Function and a Wrapper class.

Here is an example of a non-templated recursive function so you know generally how recursive functions work:

#include <iostream>
namespace RecursiveExample
{
    void func(int i)
    {
        std::cout << "i: " << i << std::endl;
        
        if( i > 0 )
        {
            func(i-1); //calling itself with an updated value based on the input
        }
        
        std::cout << "done!" << std::endl;
    }
    
    int main()
    {
        func(5);
        return 0;
    }
}


 3) your variadicHelper function needs to be a Recursive Variadic Template Function.
    The recursion works by removing the first element from the Variadic Template Parameter Pack, doing something with it, and calling VariadicHelper with the rest of the Pack.
 
 the general format of a recursive variadic templated function is:


template<typename T, typename ...Args>
void funcName(T first, Args ... everythingElse)
{
    funcName( everythingElse... ); //recursive call
}


 T is the first element removed from the Args parameter pack when the template is called from inside it's own function body.
 
 In the body of the function, you'll do something with 'first', before recursing with the remaining template arguments
 
 When the function is called with only one parameter in the parameter pack, the compiler will look for a version of the function that has 1 template parameter.  The variadic function template above takes a minimum of 2 parameters.
 
 4) You'll need to write this single-template-parameter version of variadicHelper along with the variadic-template version of VariadicHelper.
 */

/*
 5) add a print() function to the Wrapper stub.
    if the first parameter of variadicHelper is a double with a value of 3.5, the print() function should print out: 
    "Wrapper::print(3.5)"
 
 6) make the body of both variadicHelper functions instantiate a Wrapper instance, which wraps the first function argument, and call the 'print()' member function of the Wrapper class:
 */

 // Wrapper(first).print();

/*
 7) Then, recursively call VariadicHelper
 
 8) You will need to specialize the Wrapper class template to work with the Point class.
 
 9) be sure to forward your variadicHelper function arguments correctly and use Forwarding/R-Value references, as opposed to passing by const-ref or by copy.
 */


#include <iostream>
#include <string>
#include <typeinfo>

struct Point
{
    Point(float _x, float _y) : x(_x), y(_y) { }
    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
    std::string toString() const
    {
        std::string str;
        str +="Point { x: ";
        str += std::to_string(x);
        str += ", y: ";
        str += std::to_string(y);
        str += " }";
        return str;
    }
private:
    float x{0}, y{0};
};

template<typename Type>
struct Wrapper
{
    Wrapper(Type&& t) : val(std::move(t)) 
    { 
        std::cout << "Wrapper(" << typeid(val).name() << ")" << std::endl; 
    }

    void print()
    {
        std::cout << "Wrapper::print(" << val << ")" << std::endl;
    }

private:
    Type val;
};

template<>
struct Wrapper <Point>
{
    Wrapper(Point&& t) : val(std::move(t)) 
    { 
        std::cout << "Wrapper(" << typeid(val).name() << ")" << std::endl; 
    }

    void print()
    {
        std::cout << "Wrapper::print(" << val.toString() << ")" << std::endl;    
    }

private:
    Point val;
};

template<typename T, typename ...Args>
void variadicHelper(T&& first, Args&& ... everythingElse)
{
    Wrapper wrapper ( std::forward<T>(first));
    wrapper.print();
    variadicHelper(std::forward<Args>( everythingElse)...); 
}

template<typename T>
void variadicHelper(T&& first)
{
    Wrapper wrapper ( std::forward<T>(first));
    wrapper.print(); 
}

/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

int main()
{
    variadicHelper( 3, std::string("burgers"), 2.5, Point{3.f, 0.14f} );
}


