#include <iostream>
#include <utility>

// our own image class
#include "image.hpp"

int main() {

    // read a 3D image
    aip::imageNd<float> myNdimageA ( "../amipractical_data/brainT1.nii.gz" );
    
    
    size_t xl = myNdimageA.getsize(0);  
    size_t yl = myNdimageA.getsize(1);  
    size_t zl = myNdimageA.getsize(2);  

    //std::cout << xl <<","<< yl <<","<< zl << std::endl; //check the dimensions
              
    float center[3] = {91.,128.,128.};
    float radius = 50.;
    //int count = 0; //for debug only, check how many points are selected
    
    for(size_t x = 0; x < xl; x++){
        for(size_t y = 0; y <yl; y++){
            for(size_t z = 0; z < zl; z++){
                float dx = float(x) - center[0];
                float dy = float(y) - center[1];
                float dz = float(z) - center[2];
                if(fabs(sqrt(dx*dx + dy*dy + dz*dz) - radius) < 0.5){
                    //count++;
                    myNdimageA({x,y,z}) = 0;
                    }
                }
            }
        }
    //std::cout << count << std::endl;

	// 3 A (there is no B)
    // make a sphere of radius 50 around voxel 91,128,128
    // by setting the intensities on its surface to 255
    // save as another image
    myNdimageA.saveNII( "../amipractical_data/football.nii.gz" );

    // get X slice 91  and write as BMP
    myNdimageA.getSlice( 0, 91,  "../amipractical_data/xslice.bmp" );
    myNdimageA.getSlice( 1, 128,  "../amipractical_data/yslice.bmp" );
    myNdimageA.getSlice( 2, 128,  "../amipractical_data/zslice.bmp" );
    // 4 A get Y slice 128 and write as BMP
    // 4 B get Z slice 128 and write as BMP
    return ( 0 );

}
