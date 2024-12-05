#include <filesystem>
#include <iostream>
#include <utility>
#include <queue>
#include "image.hpp"

typedef int num;

int main ( int argc, char *argv[] ) {
    // NOTE 1 this is an example code for your final assignment, 
    // you could use it but it is not doing what you need for the final assignment
    
    // NOTE 2 change dataPath to where the files are located on your computer!!!
    std::string dataPath = "C:/Users/25812/Desktop/C++/final/AMIPractical/AMIPractical/AMIPractical/amipractical_data/final/";
    
    // read a 3D image
    aip::imageNd<num> inputImage ( dataPath + "Pat1.nii.gz" );
    
    // 1. First of all, split the data into 2 sets. (make a copy of the data above)
    //    Use the training set to optimize parameters 
    //    Evaluate the performance of the program using the testing set without parameter adjustments

    // Print some slices in BMP format
    inputImage.getSlice( 0,  90, dataPath + "Pat1_sliceX.bmp" );
    inputImage.getSlice( 1,  90, dataPath + "Pat1_sliceY.bmp" );
    inputImage.getSlice( 2,  90, dataPath + "Pat1_sliceZ.bmp" );

    // Gaussian Filter
    double sigma = 1.05;
    auto gk = aip::gausskernel ( sigma );

    bool 
        doFilter = true;
        
    if ( doFilter ) {

        // filter in x(0), y(1) and z(2) direction
        std::cout << "smoothing image x," << std::flush;
        inputImage.filter( gk, 0 );
        std::cout << " y," << std::flush;
        inputImage.filter( gk, 1 );
        std::cout << " z ... " << std::flush;
        inputImage.filter( gk, 2 );
        std::cout << "done\n";
        
    }

    // Print some slices in BMP format
    inputImage.getSlice( 0,  90, dataPath + "Pat1_GS_sliceX_.bmp" );
    inputImage.getSlice( 1,  90, dataPath + "Pat1_GS_sliceY_.bmp" );
    inputImage.getSlice( 2,  90, dataPath + "Pat1_GS_sliceZ_.bmp" );
    
    // 2. Input anisotropic diffusion image here, use getSlice to get bmp file (Slide 5)
    //    Make a comparasion with gaussian filter above
    //    Perform all of the operations in both image below.


   	auto tmp = 0;
    
    //perform watershed
    bool test = inputImage.GetWatershedImage();
    std::cout <<"Did it run ok?  "<< test <<std::endl;
    
    // 3. Refine the watershed output (See slide 9)
    //    For example, remove small basins (maybe it is just the noise)
    //    Merge small adjacent basins (especially when they have similar average intensity values)
    //    The output about the basins and voxel numbers below is useful for your refinement.
    //    Because it has helped you to sort the basins according to the number of pixels.
    //    You may perform 'saveNII' before and after refinement to see the difference

    //save resulting NII file
    inputImage.setNIIdatatype (NIFTI_TYPE_INT32); // set saving data type to int32, so all labels can be printed
    inputImage.saveNII(dataPath + "Pat1_GS_WS.nii.gz" );

    // Get the max value of the labels in the watershed image
    auto Maxdata = *std::max_element( inputImage.getdata_ptr()->begin(), inputImage.getdata_ptr()->end());
    auto N_voxels = inputImage.getsize(0)*inputImage.getsize(1)*inputImage.getsize(2);
    
    std::cout<<"Number of voxels: " << N_voxels << std::endl;
    std::cout<<"Max data: " << Maxdata << std::endl;
    
        
    std::vector<int> numberVoxelsPerLabel(Maxdata+1);
    
    
    // set elements to zero
    for ( auto i=0; i<Maxdata+1; i++ )
        numberVoxelsPerLabel[i] = 0;
	
    
    
    // make histogram with number of voxel per watershed label
    for ( auto i=0; i<inputImage.getsize(0); i++ ){
		for ( auto j=0; j<inputImage.getsize(1); j++ ){
			for ( auto k=0; k<inputImage.getsize(2); k++ ){
				tmp =  inputImage( { i, j, k } );
                numberVoxelsPerLabel[tmp]++;
			}
		}
	}
    
    // Sort the vector
    sort(numberVoxelsPerLabel.begin(), numberVoxelsPerLabel.end(), greater<>());

    for ( auto i=0; i<20; i++ )
        std::cout << "element number: " << i << ", items: " << numberVoxelsPerLabel[i] << "\n";

  
  
  // after sorting original index is lost so do it again with a vector pair

  std::vector<pair<int, int>> numberVoxelsPerLabel_new(Maxdata+1);
  
   // add elements initialized to zero
    for ( auto i=0; i<Maxdata+1; i++ ){
        numberVoxelsPerLabel_new[i].first=0;
        numberVoxelsPerLabel_new[i].second=0;
    }

    // make histogram with number of voxel per watershed label
    for ( auto i=0; i<inputImage.getsize(0); i++ ){
		for ( auto j=0; j<inputImage.getsize(1); j++ ){
			for ( auto k=0; k<inputImage.getsize(2); k++ ){
				tmp =  inputImage( { i, j, k } );
                numberVoxelsPerLabel_new[tmp].first++;
                numberVoxelsPerLabel_new[tmp].second=tmp;
			}
		}
	}

    std::cout << "\nBefore sorting pair vector\n";

    for ( auto i=0; i<20; i++ )
        std::cout << "element number: "<< i << ", label : " << numberVoxelsPerLabel_new[i].second << ", items: " << numberVoxelsPerLabel_new[i].first << "\n";

    std::cout << "after sorting\n";

    // Sort the vector
    sort(numberVoxelsPerLabel_new.begin(), numberVoxelsPerLabel_new.end(), greater<>());


    for ( auto i=0; i<20; i++ )
        std::cout << "element number: "<< i << ", label : " << numberVoxelsPerLabel_new[i].second << ", items: " << numberVoxelsPerLabel_new[i].first << "\n";


    // 4. Make sure to proceed only if you got a good watershed output.
    //    Input the presegmentation image here, prepare to do the overlap analysis.
    //    In a word, we need to determine if each basin is overlapped with the presegmentation.
    //    To be specfic, for each basin, count the number of pixels which are overlapped with the presegmentation.
    //    You can set a threshold to judge that, such as thr = 0.3/0.5/0.7 (flexible according to the final result)
    //    If the proportion of the pixels overlapped in a basin is larger than thr, then classify it in 'brain' part
    //    Otherwise, put it in the 'non-brain' part.
    //    Then the for loop below set all the basins which don't belong to brain to be 0
    
    
    bool outside = true;
	    // read a 3D image for segmentation of original image
    aip::imageNd<num> inputImage_original ( dataPath + "Pat1.nii.gz" );

    for ( auto i=0; i<inputImage.getsize(0); i++ ){
		for ( auto j=0; j<inputImage.getsize(1); j++ ){
			for ( auto k=0; k<inputImage.getsize(2); k++ ){
				tmp =  inputImage( { i, j, k } );
                outside = true;
                for(auto z=0; z<10; z++){
                    if(tmp==numberVoxelsPerLabel_new[z].second)
                        outside = false;
                    }

                if(outside){
                    inputImage( { i, j, k } ) = 0;
                    inputImage_original( { i, j, k } ) = 0;
                    }
			}
		}
	}

    // 5. Create a binary mask of the brain region (based on the for loop above)
    //    Extract the brain region from the original image using the mask
    //    Save resulting NII file below

    //save resulting NII file
    //inputImage.setNIIdatatype (NIFTI_TYPE_INT32); // set saving data type to int32, so all labels can be printen
    inputImage.saveNII(dataPath + "Pat1_segmented_WS.nii.gz" );
    inputImage_original.saveNII(dataPath + "Pat1_segmented_T1MRI.nii.gz" );

    // Print some slices in BMP format
    inputImage_original.getSlice( 0,  90, dataPath + "Pat1_segmented_WS_sliceX_.bmp" );
    inputImage_original.getSlice( 1,  90, dataPath + "Pat1_segmented_WS_sliceY_.bmp" );
    inputImage_original.getSlice( 2,  90, dataPath + "Pat1_segmented_WS_sliceZ_.bmp" );


    return 0 ;

}








