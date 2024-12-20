#include <filesystem>
#include <iostream>
#include <utility>
#include <queue>
#include "image.hpp"

typedef int num;

aip::imageNd<num>* processImage(const std::string& dataPath, const std::string& filename1, const std::string& filename2,
                                double sigma, double overlapThreshold) {

    // Load the original 3D image
    std::cout << "Input file: " << filename1 << "\n";
    auto inputImage = new aip::imageNd<num>(dataPath + filename1);
    aip::imageNd<num> inputImage_original(dataPath + filename1);

    aip::imageNd<num> presegmentation(dataPath + filename2);


    // Gaussian Filter Preprocessing
    auto gk = aip::gausskernel(sigma);
    bool doFilter = true;

    // When sigma = 0, we use anisotropic diffusion.
    if (sigma < 1e-6){
        doFilter = false;
        std::cout << "Anistropic diffusion done\n";
    }

    if (doFilter) {
        std::cout << "Smoothing image x, y, z ... " << std::flush;
        inputImage->filter(gk, 0); // x-direction
        inputImage->filter(gk, 1); // y-direction
        inputImage->filter(gk, 2); // z-direction
        std::cout << "Gaussian filter done\n";
    }


    // Perform Watershed Segmentation
    bool test = inputImage->GetWatershedImage();
    std::cout << "Watershed segmentation completed: " << test << std::endl;

    // Compute histogram for voxel counts per watershed label
    auto Maxdata = *std::max_element(inputImage->getdata_ptr()->begin(), inputImage->getdata_ptr()->end());
    std::vector<int> N_basin(Maxdata + 1, 0);   // Total voxels per basin
    std::vector<int> N_overlap(Maxdata + 1, 0); // Overlapping voxels per basin

    // Count voxels and overlaps
    for (size_t i = 0; i < inputImage->getsize(0); i++) {
        for (size_t j = 0; j < inputImage->getsize(1); j++) {
            for (size_t k = 0; k < inputImage->getsize(2); k++) {
                int watershedLabel = (*inputImage)({i, j, k});
                int presegLabel = presegmentation({i, j, k});

                if (watershedLabel > 0) {
                    N_basin[watershedLabel]++;
                    if (presegLabel > 0) {
                        N_overlap[watershedLabel]++;
                    }
                } else {
                    // Assign dam voxel to a nearby basin
                    for (int di = -1; di <= 1; di++) {
                        for (int dj = -1; dj <= 1; dj++) {
                            for (int dk = -1; dk <= 1; dk++) {
                                if (di == 0 && dj == 0 && dk == 0) continue; // Skip itself
                                int ni = i + di, nj = j + dj, nk = k + dk;

                                if (ni >= 0 && ni < int(inputImage->getsize(0)) &&
                                    nj >= 0 && nj < int(inputImage->getsize(1)) &&
                                    nk >= 0 && nk < int(inputImage->getsize(2))) {
                                    int neighborLabel = (*inputImage)({static_cast<size_t >(ni), static_cast<size_t>(nj), static_cast<size_t>(nk)});
                                    if (neighborLabel > 0) {
                                        watershedLabel = neighborLabel;
                                        (*inputImage)({i, j, k}) = watershedLabel;
                                        N_basin[watershedLabel]++;
                                        if (presegLabel > 0) {
                                            N_overlap[watershedLabel]++;
                                        }
                                        di = dj = dk = 2; // Exit loop
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Filter basins based on overlap ratio
    std::vector<bool> keepBasin(Maxdata + 1, false);
    for (int label = 1; label <= Maxdata; label++) {
        double overlapRatio = (double)N_overlap[label] / N_basin[label];
        if (overlapRatio >= overlapThreshold) {
            keepBasin[label] = true;
        }
    }

    // Remove basins that do not meet the threshold
    for (size_t i = 0; i < inputImage->getsize(0); i++) {
        for (size_t j = 0; j < inputImage->getsize(1); j++) {
            for (size_t k = 0; k < inputImage->getsize(2); k++) {
                int watershedLabel = (*inputImage)({i, j, k});
                if (!keepBasin[watershedLabel]) {
                    (*inputImage)({i, j, k}) = 0;
                    inputImage_original({i, j, k}) = 0;
                }
            }
        }
    }

    // Save refined outputs
    inputImage->saveNII(dataPath + "Watershed_Refined_" + filename1);
    inputImage_original.saveNII(dataPath + "Refined_T1MRI_" + filename1);

    std::cout << "Refined outputs saved.\n\n" << std::endl;

    return inputImage;
    // Return pointer to refined image
}




int main(int argc, char *argv[]) {

    // NOTE: Adjust dataPath to your file location
    std::string dataPath = "/Users/rr/AMIP/AssignmentGit/final assignment/amipractical_data/";

    //Parameters we need to play with, if you use AD file, set sigma = 0, do not let sigma less than 1e-6
//    double sigma = 2.05; //  0.55 1.05 2.05
    double overlapThreshold = 0.7; // 0.3 0.5 0.7

    // filename1: original file; filename2: presegmentation
//    aip::imageNd<num>* Sub1_gau = processImage(dataPath, "Subj1.nii.gz", "Subj1Brain.nii.gz",sigma, overlapThreshold);
//    aip::imageNd<num>* Sub1_ad = processImage(dataPath, "Subj1_AD.nii.gz", "Subj1Brain.nii.gz",0, overlapThreshold);

//    aip::imageNd<num>* Sub2_gau = processImage(dataPath, "Subj2.nii.gz", "Subj2Brain.nii.gz",sigma, overlapThreshold);
//    aip::imageNd<num>* Sub2_ad = processImage(dataPath, "Subj2_AD.nii.gz", "Subj2Brain.nii.gz",0, overlapThreshold);

//    aip::imageNd<num>* Sub3_gau = processImage(dataPath, "Subj3.nii.gz", "Subj3Brain.nii.gz",sigma, overlapThreshold);
//    aip::imageNd<num>* Sub3_ad = processImage(dataPath, "Subj3_AD.nii.gz", "Subj3Brain.nii.gz",0, overlapThreshold);

//    aip::imageNd<num>* Sub4_gau = processImage(dataPath, "Subj4.nii.gz", "Subj4Brain.nii.gz",sigma, overlapThreshold);
//    aip::imageNd<num>* Sub4_ad = processImage(dataPath, "Subj4_AD.nii.gz", "Subj4Brain.nii.gz",0, overlapThreshold);

//    aip::imageNd<num>* Pat1_gau = processImage(dataPath, "Pat1.nii.gz", "Pat1Brain.nii.gz",sigma, overlapThreshold);
    aip::imageNd<num>* Pat1_ad = processImage(dataPath, "Pat1_AD.nii.gz", "Pat1Brain.nii.gz",0, overlapThreshold);

//    aip::imageNd<num>* Pat2_gau = processImage(dataPath, "Pat2.nii.gz", "Pat2Brain.nii.gz",sigma, overlapThreshold);
    aip::imageNd<num>* Pat2_ad = processImage(dataPath, "Pat2_AD.nii.gz", "Pat2Brain.nii.gz",0, overlapThreshold);

    // Clean up the dynamically allocated image
//    delete Sub1_gau;
//    delete Sub1_ad;
//    delete Sub2_gau;
//    delete Sub2_ad;
//    delete Sub3_gau;
//    delete Sub3_ad;
//    delete Sub4_gau;
//    delete Sub4_ad;

//    delete Pat1_gau;
//    delete Pat2_gau;
      delete Pat1_ad;
      delete Pat2_ad;
    return 0;
}