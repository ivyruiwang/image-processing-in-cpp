#include <iostream>
#include "vector_week2.hpp"

// put your implementation of the class here, in lecture this is what was put in mvector3.cpp file
// this file is thus a combination of mvector3.cpp and main.cpp
vector::vector(double xx, double yy, double zz){
    x = xx;
    y = yy;
    z = zz;
    }
    
vector::vector(const vector& v){
    x = v.x;
    y = v.y;
    z = v.z;
    }

vector vector::operator+(const vector& v)const{
    return vector(x+v.x, y+v.y, z+v.z);
    }

std::ostream& operator<<(std::ostream& out, const vector& v){
    return out<<'('<<v.x<<','<<v.y<<','<<v.z<<')';
    }

std::istream& operator<<(std::istream& in, vector& v){
    return in>>v.x>>v.y>>v.z;
    }
// use your new class code in the main function below, and solve the question as given in the exercise description

int main()
{
    vector v1(0.,1.,2.);
    vector v2(-1.,2.,4.);
    vector vsum = v1.operator+(v2);
    
    std::cout<<vsum<<std::endl;
    
    return 0;
}
