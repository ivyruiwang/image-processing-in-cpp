#include <filesystem>
#include <iostream>
#include <utility>
#include <queue>
#include "image.hpp"


typedef int num;

int main(int argc, char *argv[]) {
    
    // NOTE: Adjust dataPath to your file location
    std::string dataPath = "C:/Users/25812/Desktop/C++/final/AMIPractical/AMIPractical/AMIPractical/amipractical_data/final/";

    // Load the original 3D image
    aip::imageNd<num> inputImage(dataPath + "Pat1.nii.gz");
    aip::imageNd<num> presegmentation(dataPath + "Pat1Brain.nii.gz"); // Presegmented brain data
   
    // Gaussian Filter Preprocessing
    double sigma = 1.05;
    auto gk = aip::gausskernel(sigma);
    bool doFilter = true;

    if (doFilter) {
        std::cout << "Smoothing image x, y, z ... " << std::flush;
        inputImage.filter(gk, 0); // x-direction
        inputImage.filter(gk, 1); // y-direction
        inputImage.filter(gk, 2); // z-direction
        std::cout << "done\n";
    }

    // Print some slices in BMP format
    inputImage.getSlice( 0,  90, "C:/Users/25812/Desktop/C++/test/Pat1_GS_sliceX_.bmp" );
    inputImage.getSlice( 1,  90, "C:/Users/25812/Desktop/C++/test/Pat1_GS_sliceY_.bmp" );
    inputImage.getSlice( 2,  90, "C:/Users/25812/Desktop/C++/test/Pat1_GS_sliceZ_.bmp" );

    auto tmp = 0;
    // Perform Watershed Segmentation
    bool test = inputImage.GetWatershedImage();
    std::cout << "Run OK? " << test << std::endl;

    // Save initial watershed output for reference
    inputImage.setNIIdatatype (NIFTI_TYPE_INT32); // set saving data type to int32, so all labels can be printed
    inputImage.saveNII("C:/Users/25812/Desktop/C++/test/Pat1_Watershed_Initial.nii.gz");

    // Histogram for voxel counts per watershed label
    auto Maxdata = *std::max_element(inputImage.getdata_ptr()->begin(), inputImage.getdata_ptr()->end());
    auto N_voxels = inputImage.getsize(0) * inputImage.getsize(1) * inputImage.getsize(2);
    
    std::cout<<"Number of voxels: " << N_voxels << std::endl;
    std::cout<<"Max data: " << Maxdata << std::endl;
    std::vector<int> numberVoxelsPerLabel(Maxdata+1);

    // set elements to zero
    for ( auto i=0; i<Maxdata+1; i++ )
        numberVoxelsPerLabel[i] = 0;

    // make histogram with number of voxel per watershed label
    for ( size_t i=0; i<inputImage.getsize(0); i++ ){
		for ( size_t j=0; j<inputImage.getsize(1); j++ ){
			for ( size_t k=0; k<inputImage.getsize(2); k++ ){
				tmp =  inputImage( { i, j, k } );
                //tmp = presegmentation( { i, j, k } );
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
    for ( size_t i=0; i<inputImage.getsize(0); i++ ){
		for ( size_t j=0; j<inputImage.getsize(1); j++ ){
			for ( size_t k=0; k<inputImage.getsize(2); k++ ){
				tmp =  inputImage( { i, j, k } );
                //tmp =  presegmentation( { i, j, k } );
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

    // Overlap Analysis with Presegmentation
   
    
    std::vector<int> N_basin(Maxdata + 1, 0);   // Total voxels per basin
    std::vector<int> N_overlap(Maxdata + 1, 0); // Overlapping voxels per basin
    
    // Count voxels and overlaps and assign dam voxels to nearby basins
    for (auto i = 0; i < int(inputImage.getsize(0)); i++) {
        for (auto j = 0; j < int(inputImage.getsize(1)); j++) {
            for (auto k = 0; k < int(inputImage.getsize(2)); k++) {
                int watershedLabel = inputImage({i, j, k}); // Current voxel's label
                int presegLabel = presegmentation({i, j, k}); // Presegmentation label

                if (watershedLabel > 0) {
                // Regular voxel: Increment counts for the current basin
                    N_basin[watershedLabel]++;
                    if (presegLabel > 0) {
                        N_overlap[watershedLabel]++;
                    }
                } 
                else {
                // pixel basin merging, count the voxel which doesn't belong to a basin
                // Dam voxel: Assign it to a nearby basin
                    for (int di = -1; di <= 1; di++) {
                        for (int dj = -1; dj <= 1; dj++) {
                            for (int dk = -1; dk <= 1; dk++) {
                                if (di == 0 && dj == 0 && dk == 0) continue; // Skip the voxel itself
                                int ni = i + di, nj = j + dj, nk = k + dk;

                            // Check if neighbor is within bounds
                                if (ni >= 0 && ni < int(inputImage.getsize(0)) &&
                                    nj >= 0 && nj < int(inputImage.getsize(1)) &&
                                    nk >= 0 && nk < int(inputImage.getsize(2))) {
                                    int neighborLabel = inputImage({ni, nj, nk});
                                    if (neighborLabel > 0) {
                                    // Assign the dam voxel to the nearby basin
                                        watershedLabel = neighborLabel;
                                        inputImage({i, j, k}) = watershedLabel; // Update voxel's label
                                        N_basin[watershedLabel]++;
                                        if (presegLabel > 0) {
                                            N_overlap[watershedLabel]++;
                                        }
                                        di = dj = dk = 2; // Break all loops
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Print the first 10 elements of N_basin and N_overlap
    std::cout << "First 10 elements of N_basin:" << std::endl;
    for (size_t i = 0; i < 10 && i < N_basin.size(); i++) {
        std::cout << "Label " << i << ": " << N_basin[i] << std::endl;
    }

    std::cout << "First 10 elements of N_overlap:" << std::endl;
    for (size_t i = 0; i < 10 && i < N_overlap.size(); i++) {
        std::cout << "Label " << i << ": " << N_overlap[i] << std::endl;
    }
    
    // Filter basins based on overlap ratio
    double overlapThreshold = 0.5; // Example threshold
    std::vector<bool> keepBasin(Maxdata + 1, false);

    for (int label = 1; label <= Maxdata; label++) {
        double overlapRatio = (double)N_overlap[label] / N_basin[label];
        if (overlapRatio >= overlapThreshold) {
            keepBasin[label] = true; // Keep basin if overlap ratio exceeds threshold
        }
    }
    
    aip::imageNd<num> inputImage_original ( dataPath + "Pat1.nii.gz" );
    // Remove basins that do not meet the threshold
    for (size_t i = 0; i < inputImage.getsize(0); i++) {
        for (size_t j = 0; j < inputImage.getsize(1); j++) {
            for (size_t k = 0; k < inputImage.getsize(2); k++) {
                int watershedLabel = inputImage({i, j, k});
                if (!keepBasin[watershedLabel]) {
                    inputImage({i, j, k}) = 0; // Remove basin
                    inputImage_original({i, j, k}) = 0; // Adjust original image
                }
            }
        }
    }

    // Save refined watershed output
    inputImage.saveNII("C:/Users/25812/Desktop/C++/test/Pat1_Watershed_Refined.nii.gz");
    inputImage_original.saveNII("C:/Users/25812/Desktop/C++/test/Pat1_Refined_T1MRI.nii.gz");

    // Print example slices for visualization
    inputImage_original.getSlice(0, 90, "C:/Users/25812/Desktop/C++/test/Pat1_Final_SliceX.bmp");
    inputImage_original.getSlice(1, 90, "C:/Users/25812/Desktop/C++/test/Pat1_Final_SliceY.bmp");
    inputImage_original.getSlice(2, 90, "C:/Users/25812/Desktop/C++/test/Pat1_Final_SliceZ.bmp");

    std::cout << "Segmentation process completed." << std::endl;
    return 0;
}







