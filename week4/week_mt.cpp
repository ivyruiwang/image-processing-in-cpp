#include <filesystem>
#include <iostream>
#include <utility>
#include <queue>
#include <regex>

// our own image class
#include "image.hpp"

typedef int num;

int main ( int argc, char *argv[] ) {

	auto
//		uber_parent_path = std::filesystem::path(argv[0]).parent_path().parent_path().parent_path().parent_path(); // with codelite
        uber_parent_path = std::filesystem::current_path().parent_path(); // for my macbook
		//uber_parent_path = std::filesystem::current_path().parent_path().parent_path(); // with cmake
	vector <string> allfiles {
		std::string ( uber_parent_path.string() ) + "/amipractical_data/brainT1.nii.gz" };
	
    // Gaussian kernel with width sigma
    double
        sigma = 1.05;
    auto
        gk = aip::gausskernel ( sigma );

    for ( unsigned i=0; i<allfiles.size(); i++ )
        std::cout << "file " << i << " is " << allfiles[i] << "\n" << std::flush;

    // read a 3D image
	unsigned i=0;
    std::cout << "reading image " << allfiles[i] << " ... ";
    aip::imageNd<num> inputImage ( allfiles[i] );
    std::cout << "done\n";

    // Print some slices in BMP format
    inputImage.getSlice( 0,  90, std::string ( uber_parent_path.string() ) + "/amipractical_data/test_sliceX.bmp" );
    inputImage.getSlice( 1, 128, std::string ( uber_parent_path.string() ) + "/amipractical_data/test_sliceY.bmp" );
    inputImage.getSlice( 2, 128, std::string ( uber_parent_path.string() ) + "/amipractical_data/test_sliceZ.bmp" );

    bool
            doFilter = false;

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

    // compute maxtree components
    std::cout << "computing Maxtree ... ";
    inputImage.getMaxtree(	8,			// # levels
							6,			// connectivity ( 3d: 6 or 26, 2d: 4 or 8 )
							"Berger" );	// algorithm
    std::cout << "done\n";
	
	// we have put the peak component numbers in each voxel, see the hpp-file
	// now we want to store those in a different .nii
    inputImage.saveNII ( std::regex_replace( allfiles [ i ], std::regex ( ".nii" ), "_components.nii" ) );
    std::cout << "save components.nii ... done\n";

    std::cout << "filling component ... ";
	inputImage.setpoints ( 	0, 		// starting component
                              10033,			// maximum component label included
							true,		// sort collected points (for final set)
							true );	// set pixel values to level ( if false -> binary mask )
    std::cout << "done\n";

    // Print some slices in BMP format
    inputImage.getSlice( 0,  90, "../amipractical_data/testF_sliceX.bmp" );
    inputImage.getSlice( 1, 128, "../amipractical_data/testF_sliceY.bmp" );
    inputImage.getSlice( 2, 128, "../amipractical_data/testF_sliceZ.bmp" );

    // write output
    inputImage.saveNII ( std::regex_replace( allfiles [ i ], std::regex ( ".nii" ), "_output.nii" ) );

    return 0 ;

}













