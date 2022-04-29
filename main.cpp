/*
Project 4: Part 5 / 9
 video: Chapter 5 Part 2
 Operator Overloading.

Do not delete your previous main.

 Create a branch named Part5

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.

 1) replace the add/subtract/multiply/etc functions in your UDTs with overloaded math operators
        e.g. add() would become operator+=() because it modifies the internal heap-allocated object.
        The easiest way to do this is to just rename your member functions.
        Do not: delete your member functions and add new ones.  Simply rename them
        You do not need to change the Point class's multiply() functions.
 
 2) Your overloaded operators should only take primitives, passed by value.
    since they are passed by value, they do not need to be const.
 
 3) don't delete your conversion functions.

 4) your main() function should be the same as Project 4 part 4,
    excluding the changes made due to 1)

 5) delete the example below after it makes sense how your code will change due to 1).
 */

//#include <iostream>
//namespace Example
//{
//    int main()
//    {
//        FloatType floatNum(4.3f);
//        IntType intNum(2);
//        IntType intNum2(6);
//
//        /*
//        if you previously had a line like this demonstrating chaining:
//
//            intNum.add(3).add(4.5f).divide(floatNum);
//
//        it should become:
//        */
//        intNum += 3;
//        intNum += 4.5f;
//        intNum /= floatNum;
//        std::cout << "intNum: " << intNum << std::endl;
//
//        return 0;
//    }
//}

 /*
 6) compile/link/run to make sure you don't have any errors or warnings.

 7) your program should produce the exact same output as Project 4 part 4, listed below.
    use https://www.diffchecker.com/diff to make sure it is the same.
 */

/*
your program should generate the following output EXACTLY.
This includes any warnings included below.

The output should have zero warnings.


FloatType add result=4
FloatType subtract result=2
FloatType multiply result=4
FloatType divide result=0.25

DoubleType add result=4
DoubleType subtract result=2
DoubleType multiply result=4
DoubleType divide result=0.8

IntType add result=4
IntType subtract result=2
IntType multiply result=4
IntType divide result=1

Chain calculation = 590
New value of ft = (ft + 3.0f) * 1.5f / 5.0f = 0.975
---------------------

Initial value of dt: 0.8
Initial value of it: 590
Use of function concatenation (mixed type arguments) 
New value of dt = (dt * it) / 5.0f + ft = 95.375
---------------------

Intercept division by 0 
New value of it = it / 0 = error: integer division by zero is an error and will crash the program!
590
New value of ft = ft / 0 = warning: floating point division by zero!
inf
New value of dt = dt / 0 = warning: floating point division by zero!
inf
---------------------

The result of FloatType^4 divided by IntType is: 26.9136
The result of DoubleType times 3 plus IntType is : 67.3
The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: 711
An operation followed by attempts to divide by 0, which are ignored and warns user: 
error: integer division by zero is an error and will crash the program!
error: integer division by zero is an error and will crash the program!
error: integer division by zero is an error and will crash the program!
505521
FloatType x IntType  =  13143546
(IntType + DoubleType + FloatType) x 24 = 315447336
Power tests with FloatType
pow(ft1, floatExp) = 2^2 = 4
pow(ft1, itExp) = 4^2 = 16
pow(ft1, ftExp) = 16^2 = 256
pow(ft1, dtExp) = 256^2 = 65536
---------------------

Power tests with DoubleType
pow(dt1, doubleExp) = 2^2 = 4
pow(dt1, itExp) = 4^2 = 16
pow(dt1, ftExp) = 16^2 = 256
pow(dt1, dtExp) = 256^2 = 65536
---------------------

Power tests with IntType
pow(it1, intExp) = 2^2 = 4
pow(it1, itExp) = 4^2 = 16
pow(it1, ftExp) = 16^2 = 256
pow(it1, dtExp) = 256^2 = 65536
===============================

Point tests with float argument:
Point { x: 3, y: 6 }
Multiplication factor: 6
Point { x: 18, y: 36 }
---------------------

Point tests with FloatType argument:
Point { x: 3, y: 3 }
Multiplication factor: 3
Point { x: 9, y: 9 }
---------------------

Point tests with DoubleType argument:
Point { x: 3, y: 4 }
Multiplication factor: 4
Point { x: 12, y: 16 }
---------------------

Point tests with IntType argument:
Point { x: 3, y: 4 }
Multiplication factor: 5
Point { x: 15, y: 20 }
---------------------

good to go!

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

struct DoubleType;
struct IntType;

struct FloatType
{
    explicit FloatType(float lhs) : value(new float(lhs)) {}

    ~FloatType()
    {
        delete value;
    }

    FloatType& operator+=(float rhs);
    FloatType& operator-=(float rhs);
    FloatType& operator*=(float rhs);
    FloatType& operator/=(float rhs);

    operator float() const
    {
        return *value;
    }

    FloatType& pow(float rhs);
    FloatType& pow(const FloatType& rhs);
    FloatType& pow(const DoubleType& rhs);
    FloatType& pow(const IntType& rhs);

private:
    float* value;

    FloatType& powInternal(const float rhs);
};

struct DoubleType
{
    explicit DoubleType(double lhs) : value(new double(lhs)) {}

    ~DoubleType()
    {
        delete value;
    }

    DoubleType& operator+=(double rhs);
    DoubleType& operator-=(double rhs);
    DoubleType& operator*=(double rhs);
    DoubleType& operator/=(double rhs);

    operator double() const
    {
        return *value;
    }

    DoubleType& pow(double rhs);
    DoubleType& pow(const FloatType& rhs);
    DoubleType& pow(const DoubleType& rhs);
    DoubleType& pow(const IntType& rhs);

private:
    double* value;

    DoubleType& powInternal(const double rhs);
};

struct IntType
{
    explicit IntType(int lhs) : value(new int(lhs)) {}

    ~IntType()
    {
        delete value;
    }

    IntType& operator+=(int rhs);
    IntType& operator-=(int rhs);
    IntType& operator*=(int rhs);
    IntType& operator/=(int rhs);

    operator int() const
    {
        return *value;
    }

    IntType& pow(int rhs);
    IntType& pow(const FloatType& rhs);
    IntType& pow(const DoubleType& rhs);
    IntType& pow(const IntType& rhs);

private:
    int* value;

    IntType& powInternal(const int rhs);
};

FloatType& FloatType::operator+=(float rhs)
{
    *value += rhs;
    return *this;
}

FloatType& FloatType::operator-=(float rhs)
{
    *value -= rhs;
    return *this;
}

FloatType& FloatType::operator*=(float rhs)
{
    *value *= rhs;
    return *this;
}

FloatType& FloatType::operator/=(float rhs)
{
    if (rhs == 0.0f)
    {
        std::cout << "warning: floating point division by zero!" << std::endl;
    }
    *value /= rhs;
    return *this;
}

FloatType& FloatType::pow(float rhs)
{
    return powInternal(rhs);
}

FloatType& FloatType::pow(const FloatType& rhs)
{
    return powInternal(static_cast<float>(rhs));
}

FloatType& FloatType::pow(const DoubleType& rhs)
{
    return powInternal(static_cast<float>(rhs));
}

FloatType& FloatType::pow(const IntType& rhs)
{
    return powInternal(static_cast<float>(rhs));
}

FloatType& FloatType::powInternal(const float rhs)
{
    *value = static_cast<float>(std::pow(*value, rhs));
    return *this;
}

DoubleType& DoubleType::operator+=(double rhs)
{
    *value += rhs;
    return *this;
}

DoubleType& DoubleType::operator-=(double rhs)
{
    *value -= rhs;
    return *this;
}

DoubleType& DoubleType::operator*=(double rhs)
{
    *value *= rhs;
    return *this;
}

DoubleType& DoubleType::operator/=(double rhs)
{
    if (rhs == 0.0)
    {
        std::cout << "warning: floating point division by zero!" << std::endl;
    }
    *value /= rhs;
    return *this;
}

DoubleType& DoubleType::pow(double rhs)
{
    return powInternal(rhs);
}

DoubleType& DoubleType::pow(const FloatType& rhs)
{
    return powInternal(static_cast<double>(rhs));
}

DoubleType& DoubleType::pow(const DoubleType& rhs)
{
    return powInternal(static_cast<double>(rhs));
}

DoubleType& DoubleType::pow(const IntType& rhs)
{
    return powInternal(static_cast<double>(rhs));
}

DoubleType& DoubleType::powInternal(const double rhs)
{
    *value = static_cast<double>(std::pow(*value, rhs));
    return *this;
}

IntType& IntType::operator+=(int rhs)
{
    *value += rhs;
    return *this;
}

IntType& IntType::operator-=(int rhs)
{
    *value -= rhs;
    return *this;
}

IntType& IntType::operator*=(int rhs)
{
    *value *= rhs;
    return *this;
}

IntType& IntType::operator/=(int rhs)
{
    if (rhs == 0)
    {
        std::cout << "error: integer division by zero is an error and will crash the program!" << std::endl;
    }
    else
    {
        *value /= rhs;
    }
    return *this;
}

IntType& IntType::pow(int rhs)
{
    return powInternal(rhs);
}

IntType& IntType::pow(const FloatType& rhs)
{
    return powInternal(static_cast<int>(rhs));
}

IntType& IntType::pow(const DoubleType& rhs)
{
    return powInternal(static_cast<int>(rhs));
}

IntType& IntType::pow(const IntType& rhs)
{
    return powInternal(static_cast<int>(rhs));
}

IntType& IntType::powInternal(const int rhs)
{
    *value = static_cast<int>(std::pow(*value, rhs));
    return *this;
}

struct Point
{
    Point(float x_, float y_) : x(x_), y(y_) { }
    Point(FloatType& x_, FloatType& y_) : Point(static_cast<float>(x_), static_cast<float>(y_)) { }
    Point(DoubleType& x_, DoubleType& y_) : Point(static_cast<float>(x_), static_cast<float>(y_)) { }
    Point(IntType& x_, IntType& y_) : Point(static_cast<float>(x_), static_cast<float>(y_)) { }

    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }

    Point& multiply(FloatType& rhs)
    {
        return multiply(static_cast<float>(rhs));
    }

    Point& multiply(DoubleType& rhs)
    {
        return multiply(static_cast<float>(rhs));
    }

    Point& multiply(IntType& rhs)
    {
        return multiply(static_cast<float>(rhs));
    }

    void toString()
    {
        std::cout << "Point { x: " << x << ", y: " << y << " }" << std::endl;
    }

private:
    float x{0}, y{0};
};

void part3()
{
    FloatType ft( 5.5f );
    DoubleType dt( 11.1 );
    IntType it ( 34 );
    DoubleType pi( 3.14 );

    std::cout << "The result of FloatType^4 divided by IntType is: "
              << ((((ft *= ft) *= ft) *= ft) /= static_cast<float>(it)) << std::endl;
    std::cout << "The result of DoubleType times 3 plus IntType is : " << ((dt *= 3) += it) << std::endl;
    std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: "
              << (static_cast<int>(((it /= static_cast<int>(pi)) *= static_cast<int>(dt)) -= static_cast<int>(ft)))
              << std::endl;
    std::cout << "An operation followed by attempts to divide by 0, which are ignored and warns user: " << std::endl;
    std::cout << ((((it *= it) /= 0) /= 0.0f) /= 0.0) << std::endl;

    std::cout << "FloatType x IntType  =  " << (it *= static_cast<int>(ft)) << std::endl;
    std::cout << "(IntType + DoubleType + FloatType) x 24 = "
              << (((it += static_cast<int>(dt)) += static_cast<int>(ft)) *= 24) << std::endl;
}

void part4()
{
    // ------------------------------------------------------------
    //                          Power tests
    // ------------------------------------------------------------
    FloatType ft1(2);
    DoubleType dt1(2);
    IntType it1(2);
    float floatExp = 2.0f;
    double doubleExp = 2.0;
    int intExp = 2;
    IntType itExp(2);
    FloatType ftExp(2.0f);
    DoubleType dtExp(2.0);

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
    FloatType ft2(3.0f);
    DoubleType dt2(4.0);
    IntType it2(5);
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
    Point p2(ft2, static_cast<float>(dt2));
    p2.toString();
    std::cout << "Multiplication factor: " << dt2 << std::endl;
    p2.multiply(dt2);
    p2.toString();
    std::cout << "---------------------\n" << std::endl;

    // Point tests with IntType
    std::cout << "Point tests with IntType argument:" << std::endl;
    Point p3(ft2, static_cast<float>(dt2));
    p3.toString();
    std::cout << "Multiplication factor: " << it2 << std::endl;
    p3.multiply(it2);
    p3.toString();
    std::cout << "---------------------\n" << std::endl;
}

int main()
{   
    //testing instruction 0
    HeapA heapA; 

    //assign heap primitives
    FloatType ft ( 2.0f );
    DoubleType dt ( 2 );
    IntType it ( 2 ) ;

    std::cout << "FloatType add result=" << (ft += 2.0f) << std::endl;
    std::cout << "FloatType subtract result=" << (ft -= 2.0f) << std::endl;
    std::cout << "FloatType multiply result=" << (ft *= 2.0f) << std::endl;
    std::cout << "FloatType divide result=" << (ft /= 16.0f) << std::endl << std::endl;

    std::cout << "DoubleType add result=" << (dt += 2.0) << std::endl;
    std::cout << "DoubleType subtract result=" << (dt -= 2.0) << std::endl;
    std::cout << "DoubleType multiply result=" << (dt *= 2.0) << std::endl;
    std::cout << "DoubleType divide result=" << (dt /= 5.0) << std::endl << std::endl;

    std::cout << "IntType add result=" << (it += 2) << std::endl;
    std::cout << "IntType subtract result=" << (it -= 2) << std::endl;
    std::cout << "IntType multiply result=" << (it *= 2) << std::endl;
    std::cout << "IntType divide result=" << (it /= 3) << std::endl << std::endl;
    std::cout << "Chain calculation = " << (((((it *= 1000) /= 2) -= 10) += 100)) << std::endl;

        // FloatType object instanciation and method tests
    // --------
    std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << (((ft += 3.0f) *= 1.5f) /= 5.0f) << std::endl;
       
    std::cout << "---------------------\n" << std::endl; 
    
    // DoubleType/IntType object instanciation and method tests
    // --------
    std::cout << "Initial value of dt: " << dt << std::endl;
    std::cout << "Initial value of it: " << it << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments) " << std::endl;
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << ((((dt *= it) /= 5.0) += static_cast<double>(ft))) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    std::cout << "New value of it = it / 0 = " << (it /= 0) << std::endl;
    std::cout << "New value of ft = ft / 0 = " << (ft /= 0) << std::endl;
    std::cout << "New value of dt = dt / 0 = " << (dt /= 0) << std::endl;

    std::cout << "---------------------\n" << std::endl; 

    part3();
    part4();

    std::cout << "good to go!\n";

    return 0;
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
