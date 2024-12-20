#include <filesystem>
#include <iostream>
#include <utility>
#include <queue>
#include "image.hpp"


typedef int num;

int main(int argc, char *argv[]) {
    // NOTE: Adjust dataPath to your file location

    //    std::string dataPath = "C:/Users/25812/Desktop/C++/final/AMIPractical/AMIPractical/AMIPractical/amipractical_data/final/";

    // In my Macbook
    std::string dataPath = "/Users/rr/AMIP/AssignmentGit/final assignment/amipractical_data/";

    // Load the original 3D image
    aip::imageNd<num> inputImage(dataPath + "Pat1.nii.gz");
    aip::imageNd<num> inputImage_original(dataPath + "Pat1.nii.gz");
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

    // Perform Watershed Segmentation
    bool test = inputImage.GetWatershedImage();
    std::cout << "Watershed segmentation completed: " << test << std::endl;

    // Save initial watershed output for reference
    inputImage.saveNII(dataPath + "Pat1_Watershed_Initial.nii.gz");

    // Histogram for voxel counts per watershed label
    auto Maxdata = *std::max_element(inputImage.getdata_ptr()->begin(), inputImage.getdata_ptr()->end());
    auto N_voxels = inputImage.getsize(0) * inputImage.getsize(1) * inputImage.getsize(2);
    std::vector<int> numberVoxelsPerLabel(Maxdata + 1, 0);

    for (size_t i = 0; i < inputImage.getsize(0); ++i)
        for (size_t j = 0; j < inputImage.getsize(1); ++j)
            for (size_t k = 0; k < inputImage.getsize(2); ++k)
                numberVoxelsPerLabel[inputImage({i, j, k})]++;

    // Sorting by voxel count
    std::vector<std::pair<int, int>> numberVoxelsPerLabel_sorted(Maxdata + 1);
    for (int i = 0; i <= Maxdata; ++i)
        numberVoxelsPerLabel_sorted[i] = {numberVoxelsPerLabel[i], i};
    std::sort(numberVoxelsPerLabel_sorted.begin(), numberVoxelsPerLabel_sorted.end(), std::greater<>());

    // Overlap Analysis with Presegmentation
    for (size_t i = 0; i < inputImage.getsize(0); ++i) {
        for (size_t j = 0; j < inputImage.getsize(1); ++j) {
            for (size_t k = 0; k < inputImage.getsize(2); ++k) {
                int watershedLabel = inputImage({i, j, k});
                int presegLabel = presegmentation({i, j, k});
                // Remove basins not overlapping significantly with presegmentation
                if (presegLabel == 0 || watershedLabel == 0) {
                    inputImage({i, j, k}) = 0;
                    inputImage_original({i, j, k}) = 0;
                }
            }
        }
    }

    // Save refined watershed output
    inputImage.saveNII(dataPath + "Pat1_Watershed_Refined.nii.gz");
    inputImage_original.saveNII(dataPath + "Pat1_Refined_T1MRI.nii.gz");

    // Print example slices for visualization
    inputImage_original.getSlice(0, 90, dataPath + "Pat1_Final_SliceX.bmp");
    inputImage_original.getSlice(1, 90, dataPath + "Pat1_Final_SliceY.bmp");
    inputImage_original.getSlice(2, 90, dataPath + "Pat1_Final_SliceZ.bmp");

    std::cout << "Segmentation process completed." << std::endl;
    return 0;
}

