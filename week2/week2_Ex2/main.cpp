#include <iostream>
#include <utility>
#include <cmath>


// our own image class
#include "image.hpp"

int main() {
    std::cout <<"hello\n";
    
    // read slice 85
    // change your path accordingly to your installation (lines 14, 18 an 69)!!!!
    aip::image2d<float> my2dimageA ( "./data/brainT1.hdr", 85 );

    // read slice 95 of the same image and add it to slice 85 using operator+()
    //QUESTION 1: write one line of code to open the second image at slice 95
    aip::image2d<float> my2dimageB ( "./data/brainT1.hdr", 95 );
    my2dimageA += my2dimageB;

    // make the average by dividing by the appropriate number (slices you have used)
    my2dimageA /= 2;

    // make a square of white pixels (wit intensity 255)
    // of width 100 and the upper left corner at (77,77)
    // using the class's 2-dimensional brackets indexing
    size_t
        zz = 77,
        hz = zz + 100;

    // draw 4 lines in 1 for-loop
    // QUESTION 3: just one line is currently drawn add the other 3 lines for a complete rectangle
    for (size_t i = 0; i <= 100; i++) {
        my2dimageA[zz][zz + i] = 255.;
        my2dimageA[hz][zz + i] = 255.;
        my2dimageA[zz + i][zz] = 255.;
        my2dimageA[zz + i][hz] = 255.;
    }


    // draw a largest triangle ** possible inside the
    // square that shares at most one side with it
    //
    // ** there are more than 1 possibilities (right answers)
    // QUESTION 4: code here a few lines for draw a triangle
    for (size_t i = 0; i < 100; i++) {
        my2dimageA[zz][zz + i] = 255.;
        my2dimageA[zz + i][zz + i / 2] = 255.;
        my2dimageA[zz + i][hz - i / 2] = 255.;
    }

    // draw the largest circle possible inside the square

    int radius = 50;
    int centerX = zz + 50;
    int centerY = zz + 50;
    const int num_points = 360;

    for (int angle = 0; angle < num_points; angle++) {
        double theta = angle * (M_PI / 180.0);

        int x = centerX + static_cast<int>(radius * cos(theta));
        int y = centerY + static_cast<int>(radius * sin(theta));

        my2dimageA[y][x] = 255.;
    }

    // flip upside down so that the head is upright in the BMP
    for ( size_t i = 0; i < (my2dimageA.getwidth() / 2); i++ )
        for ( size_t j = 0; j < my2dimageA.getheight() ; j++ )
            std::swap ( my2dimageA[i][j], my2dimageA[my2dimageA.getwidth() -i -1][j] );

    // write to BMP
    my2dimageA.saveBMP ( "./data/brainT1_week2.bmp" );
    std::cout << "Ready" << std::endl;

    return ( 0 );

}
