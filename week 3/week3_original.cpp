#include <iostream>
#include <utility>

// our own image class
#include "image.hpp"

int main() {

    // read a 3D image
    aip::imageNd<float> myNdimageA ( "../../data/brainT1.nii.gz" );

	// 3 A (there is no B)
    // make a sphere of radius 50 around voxel 91,128,128
    // by setting the intensities on its surface to 255
    
	// feel free to use sine / cosine, 
	// 3D distance from the centre, or
	// any other method to select the
	// surface of the sphere!

    // save as another image
    myNdimageA.saveNII( "../../data/football.nii.gz" );

    // get X slice 91  and write as BMP
    myNdimageA.getSlice( 0, 91,  "../../data/xslice.bmp" );
    // 4 A get Y slice 127 and write as BMP
    // 4 B get Z slice 160 and write as BMP

    return ( 0 );

}
