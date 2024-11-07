#ifndef _VECTOR3_INCLUDED     // include Guard: avoid multiple conclusions of this file
#define _VECTOR3_INCLUDED

#include <math.h>             // standard C maths functions like sqrt(), atan(), cos(), etc
#include <iostream>           // standard C++ include file for iostream (input / output streams)

// Start implementing your class ase give in the course here, this is the .hpp or .h file this just has the class declaration

class vector{
    friend std::ostream& operator<<(std::ostream& out, const vector& v);
    friend std::istream& operator<<(std::istream&, vector&);
    
    public:
        vector(double x, double y, double z);
        vector(const vector& v);
        vector operator+(const vector& v)const;
        
    private:
        double x;
        double y;
        double z;
    
    };

// do not change lines below this line

#endif// _VECTOR3_INCLUDED
