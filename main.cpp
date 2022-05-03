/*
Project 4: Part 8 / 9
 video: Chapter 5 Part 6 Task

Create a branch named Part8

 R-Values L-Values Move Semantics.

 This Task is going to demonstrate R-Values and writing Generic Code

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
    it's very easy to mess this task up.

 Your job is to replace the owned type (the primitive specified by your template argument) from the
     Templated Class you created in Ch5 p04 with a struct named Temporary that can behave ENTIRELY as a temporary object.

 That means you must use conversion functions to interact with what it owns.

 You need to figure out how to use conversion functions to be able to GET and SET the 'value' member variable.
    hint: conversion functions can return by value and also by ___...

 1) Here is a starting point for how to implement your Temporary struct.
 */

/*
 2) add the definition of Temporary::counter here, which is a static variable and must be defined outside of the class.
    Remember the rules about how to define a Template member variable/function outside of the class.
*/

/*
 3) You'll need to template your overloaded math operator functions in your Templated Class from Ch5 p04
    use static_cast to convert whatever type is passed in to your template's NumericType before performing the +=, -=, etc.  here's an example implementation:
 */
//namespace example
//{
//template<typename NumericType>
//struct Numeric
//{
//    //snip
//    template<typename OtherType>
//    Numeric& operator-=(const OtherType& o)
//    {
//        *value -= static_cast<NumericType>(o);
//        return *this;
//    }
//    //snip
//};
//}

/*
 4) remove your specialized <double> template of your Numeric<T> class from the previous task (ch5 p04)
    replace the 2 apply() functions in your Numeric<T> with the single templated apply() function from the specialized <double> template.
 */

/*
 5) Template your pow() function the same way you templated the overloaded math operators
    Remove the call to powInternal() and just call std::pow() directly.
    you'll need to static_cast<> the pow() argument the same way you did in the overloaded math operators, when you pass it to std::pow()
 */

/*
 6) Finally, your conversion function in your templated class is going to be returning this Temporary,
        so you should probably NOT return by copy if you want your templated class's owned object to be modified by any math operation.
    See the previous hint for implementing the conversion functions for the Temporary if you want to get the held value
*/


/*
 7) replace main() with the main below
        you can remove or fix all previous partX() functions if they cause compiler errors.
        you can leave them where they are if they don't produce any errors.

 If you did everything correctly, this is the output you should get:

I'm a Temporary<f> object, #0
I'm a Temporary<i> object, #0
I'm a Temporary<d> object, #0
f: -1.89
d: -3.024
i: -9
Point { x: -1.89, y: -9 }
d: 3.024
I'm a Temporary<d> object, #1
I'm a Temporary<d> object, #2
d: 1.49519e+08
Point { x: -2.82591e+08, y: -1.34567e+09 }
I'm a Temporary<f> object, #1
I'm a Temporary<i> object, #1
I'm a Temporary<i> object, #2
I'm a Temporary<i> object, #3
intNum: 5
I'm a Temporary<f> object, #2
f squared: 3.5721
I'm a Temporary<f> object, #3
f cubed: 45.5796
I'm a Temporary<d> object, #3
d squared: 2.2356e+16
I'm a Temporary<d> object, #4
d cubed: 1.11733e+49
I'm a Temporary<i> object, #4
i squared: 81
I'm a Temporary<i> object, #5
i cubed: 531441

Use a service like https://www.diffchecker.com/diff to compare your output.
*/


struct A {};

struct HeapA
{
    HeapA() : a(new A) {}
    ~HeapA()
    {
        delete a;
    }
    A* a = nullptr;
};

#include <iostream>
#include <cmath>
#include <memory>
#include <typeinfo>

template<typename NumericType>
struct Temporary
{
    Temporary(NumericType t) : v(t)
    {
        std::cout << "I'm a Temporary<" << typeid(v).name() << "> object, #"
                  << counter++ << std::endl;
    }
    /*
     revise these conversion functions to read/write to 'v' here
     hint: what qualifier do read-only functions usually have?
     */
    operator NumericType const () { return v; }
    operator NumericType&() { return v; }
private:
    static int counter;
    NumericType v;
};

template<typename NumericType>
int Temporary<NumericType>::counter = 0;

template<typename T>
struct Numeric
{
    using Type = T;

    explicit Numeric(Type lhs) : value(std::make_unique<Type>(lhs)) {}

    template<typename Param>
    Numeric<Type>& operator=( const Param& rhs )
    {
        *value = static_cast<Type>(rhs);
        return *this;
    }

    template<class Param>
    Numeric<Type>& operator+=(const Param& rhs)
    {
        *value += static_cast<Type>(rhs);
        return *this;
    }

    template<class Param>
    Numeric<Type>& operator-=(const Param& rhs)
    {
        *value -= static_cast<Type>(rhs);
        return *this;
    }

    template<class Param>
    Numeric<Type>& operator*=(const Param& rhs)
    {
        *value *= static_cast<Type>(rhs);
        return *this;
    }

    template<typename Param>
    Numeric<Type>& operator/=(const Param& rhs )
    {
        if (std::is_same<Type, int>::value)
        {
            if (std::is_same<Param, int>::value)
            {
                if(std::abs(rhs) <= std::numeric_limits<Type>::epsilon())
                {
                    std::cout << "error: integer division by zero is an error and will crash the program!\n";
                    return *this;
                }
            }
            else if (std::abs(rhs) <= std::numeric_limits<Type>::epsilon())
            {
                std::cout << "can't divide integers by zero!\n";
                return *this;
            }
        }
        else if (std::abs(rhs) <= std::numeric_limits<Type>::epsilon())
        {
            std::cout << "warning: floating point division by zero!" << std::endl;
        }

        *value /= rhs;
        return *this;
    }

    operator Type() const
    {
        return static_cast<Type>(*value);
    }

    template<class Param>
    Numeric<Type>& pow(const Param& rhs)
    {
        *value = static_cast<Type>(std::pow(*value, static_cast<Type>(rhs)));
        return *this;
    }

    template<class Func>
    Numeric<Type>& apply(Func func)
    {
        func(*value);
        return *this;
    }

private:
    std::unique_ptr<Type> value;
};

struct Point
{
    Point(float x_, float y_) : x(x_), y(y_) { }

    template<typename Param>
    Point(const Param& x_, const Param& y_) : Point(static_cast<float>(x_), static_cast<float>(y_)) { }

    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }

    template<typename Param>
    Point& multiply(Numeric<Param>& rhs)
    {
        return multiply(static_cast<float>(rhs));
    }

    void toString() const
    {
        std::cout << "Point { x: " << x << ", y: " << y << " }" << std::endl;
    }

private:
    float x{0}, y{0};
};

void part3()
{
    Numeric<float> ft( 5.5f );
    Numeric<double> dt( 11.1 );
    Numeric<int> it ( 34 );
    Numeric<double> pi( 3.14 );

    ft *= ft;
    ft *= ft;
    ft /= it;
    std::cout << "The result of FloatType^4 divided by IntType is: " <<  ft << std::endl;
    dt *= 3;
    dt += it;
    std::cout << "The result of DoubleType times 3 plus IntType is : " <<  dt << std::endl;
    it /= pi;
    it *= dt;
    it -= ft;
    std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: " << static_cast<int>(it) << std::endl;
    std::cout << "An operation followed by attempts to divide by 0, which are ignored and warns user: " << std::endl;
    it *= it;
    it /= 0;
    it /= 0.0f;
    it /= 0.0;
    std::cout <<  it << std::endl;

    it *= ft;
    std::cout << "FloatType x IntType  =  " <<  it << std::endl;
    it += dt;
    it += ft;
    it *= 24;
    std::cout << "(IntType + DoubleType + FloatType) x 24 = " <<  it << std::endl;
}

void part4()
{
    // ------------------------------------------------------------
    //                          Power tests
    // ------------------------------------------------------------
    Numeric<float> ft1(2);
    Numeric<double> dt1(2);
    Numeric<int> it1(2);
    float floatExp = 2.0f;
    double doubleExp = 2.0;
    int intExp = 2;
    Numeric<int> itExp(2);
    Numeric<float> ftExp(2.0f);
    Numeric<double> dtExp(2.0);

    // Power tests with FloatType
    std::cout << "Power tests with FloatType" << std::endl;
    std::cout << "pow(ft1, floatExp) = " << ft1 << "^" << floatExp << " = " << ft1.pow(floatExp)  << std::endl;
    std::cout << "pow(ft1, itExp) = " << ft1 << "^" << itExp << " = " << ft1.pow(itExp)  << std::endl;
    std::cout << "pow(ft1, ftExp) = " << ft1 << "^" << ftExp << " = " << ft1.pow(ftExp)  << std::endl;
    std::cout << "pow(ft1, dtExp) = " << ft1 << "^" << dtExp << " = " << ft1.pow(dtExp)  << std::endl;
    std::cout << "---------------------\n" << std::endl;

    // Power tests with DoubleType
    std::cout << "Power tests with DoubleType" << std::endl;
    std::cout << "pow(dt1, doubleExp) = " << dt1 << "^" << doubleExp << " = " << dt1.pow(intExp)  << std::endl;
    std::cout << "pow(dt1, itExp) = " << dt1 << "^" << itExp << " = " << dt1.pow(itExp)  << std::endl;
    std::cout << "pow(dt1, ftExp) = " << dt1 << "^" << ftExp << " = " << dt1.pow(ftExp)  << std::endl;
    std::cout << "pow(dt1, dtExp) = " << dt1 << "^" << dtExp << " = " << dt1.pow(dtExp)  << std::endl;
    std::cout << "---------------------\n" << std::endl;

    // Power tests with IntType
    std::cout << "Power tests with IntType" << std::endl;
    std::cout << "pow(it1, intExp) = " << it1 << "^" << intExp << " = " << it1.pow(intExp)  << std::endl;
    std::cout << "pow(it1, itExp) = " << it1 << "^" << itExp << " = " << it1.pow(itExp)  << std::endl;
    std::cout << "pow(it1, ftExp) = " << it1 << "^" << ftExp << " = " << it1.pow(ftExp)  << std::endl;
    std::cout << "pow(it1, dtExp) = " << it1 << "^" << dtExp << " = " << it1.pow(dtExp)  << std::endl;
    std::cout << "===============================\n" << std::endl;

    // ------------------------------------------------------------
    //                          Point tests
    // ------------------------------------------------------------
    Numeric<float> ft2(3.0f);
    Numeric<double> dt2(4.0);
    Numeric<int> it2(5);
    float floatMul = 6.0f;

    // Point tests with float
    std::cout << "Point tests with float argument:" << std::endl;
    Point p0(ft2, floatMul);
    p0.toString();
    std::cout << "Multiplication factor: " << floatMul << std::endl;
    p0.multiply(floatMul);
    p0.toString();
    std::cout << "---------------------\n" << std::endl;

    // Point tests with FloatType
    std::cout << "Point tests with FloatType argument:" << std::endl;
    Point p1(ft2, ft2);
    p1.toString();
    std::cout << "Multiplication factor: " << ft2 << std::endl;
    p1.multiply(ft2);
    p1.toString();
    std::cout << "---------------------\n" << std::endl;

    // Point tests with DoubleType
    std::cout << "Point tests with DoubleType argument:" << std::endl;
    Point p2(ft2, dt2);
    p2.toString();
    std::cout << "Multiplication factor: " << dt2 << std::endl;
    p2.multiply(dt2);
    p2.toString();
    std::cout << "---------------------\n" << std::endl;

    // Point tests with IntType
    std::cout << "Point tests with IntType argument:" << std::endl;
    Point p3(ft2, dt2);
    p3.toString();
    std::cout << "Multiplication factor: " << it2 << std::endl;
    p3.multiply(it2);
    p3.toString();
    std::cout << "---------------------\n" << std::endl;
}

template<typename Type>
void cube(Type& t)
{
    t *= t * t;
}

int main()
{
    Numeric<float> f(0.1f);
    Numeric<int> i(3);
    Numeric<double> d(4.2);

    f += 2.f;
    f -= i;
    f *= d;
    f /= 2.f;
    std::cout << "f: " << f << std::endl;

    d += 2.f;
    d -= i;
    d *= f;
    d /= 2.f;
    std::cout << "d: " << d << std::endl;

    i += 2.f; i -= f; i *= d; i /= 2.f;
    std::cout << "i: "<< i << std::endl;

    Point p(f, i);
    p.toString();

    d *= -1;
    std::cout << "d: " << d << std::endl;

    p.multiply(d.pow(f).pow(i));
    std::cout << "d: " << d << std::endl;

    p.toString();

    Numeric<float> floatNum(4.3f);
    Numeric<int> intNum(2);
    Numeric<int> intNum2(6);
    intNum = 2 + (intNum2 - 4) + static_cast<double>(floatNum) / 2.3;
    std::cout << "intNum: " << intNum << std::endl;

    {
        using Type = decltype(f)::Type;
        f.apply([&f](std::unique_ptr<Type>&value) -> decltype(f)&
                {
                    auto& v = *value;
                    v = v * v;
                    return f;
                });
        std::cout << "f squared: " << f << std::endl;

        f.apply( cube<Type> );
        std::cout << "f cubed: " << f << std::endl;
    }

    {
        using Type = decltype(d)::Type;
        d.apply([&d](std::unique_ptr<Type>&value) -> decltype(d)&
                {
                    auto& v = *value;
                    v = v * v;
                    return d;
                });
        std::cout << "d squared: " << d << std::endl;

        d.apply( cube<Type> );
        std::cout << "d cubed: " << d << std::endl;
    }

    {
        using Type = decltype(i)::Type;
        i.apply([&i](std::unique_ptr<Type>&value) -> decltype(i)&
                {
                    auto& v = *value;
                    v = v * v;
                    return i;
                });
        std::cout << "i squared: " << i << std::endl;

        i.apply( cube<Type> );
        std::cout << "i cubed: " << i << std::endl;
    }
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
