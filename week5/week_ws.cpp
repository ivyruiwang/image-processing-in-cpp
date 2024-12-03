#include <filesystem>
#include <iostream>
#include <utility>
#include <queue>
#include <set>
#include <algorithm>

// our own image class
#include "image.hpp"

typedef unsigned int num;

int main ( int argc, char *argv[] ) {

	    // read a 3D image
    aip::imageNd<num> inputImage ( "/Users/rr/AMIP/AssignmentGit/week5/amipractical_data/brainT1.nii.gz" );

    // keep original intensity data
    aip::imageNd<num> outputImage = inputImage;

    // Gaussian kernel with width sigma
    double sigma = 1.05;
    auto gk = aip::gausskernel ( sigma );

    bool doFilter = true;

    if(doFilter){
        inputImage.filter(gk,0);
        inputImage.filter(gk,1);
        inputImage.filter(gk,2);
        std::cout<<"Gaussian Filter Done"<<std::endl;
    }

    //perform watershed
    bool test = inputImage.GetWatershedImage();
    std::cout <<"Did it run ok?  "<< test <<"\n";


    // get the max intensity
    auto Maxdata = *std::max_element(inputImage.getdata_ptr()->begin(), inputImage.getdata_ptr()->end());
    cout<<"Maxdata: "<< Maxdata <<endl;

    // make a vector to store the data
    std::vector<int> datavector(Maxdata+1);

    // count pixel values per watershed
    for (size_t i = 0; i < inputImage.getsize(0); i++) {
        for (size_t j = 0; j < inputImage.getsize(1); j++) {
            for (size_t k = 0; k < inputImage.getsize(2); k++) {
                int label = inputImage({i, j, k});
                datavector[label]++;
//                cout<<"inputImage{" << i << ", " << j << ", " << k << "}: datavector[" << label <<"]: "<< datavector[label] <<endl;
            }
        }
    }

    // get 10 largest watershed
    std::vector<std::pair<int, int>> label_sizes; // {label, size}
    for (size_t i = 0; i < datavector.size(); i++) {
        if (datavector[i] > 0) {
            label_sizes.emplace_back(i, datavector[i]);
        }
    }
    std::sort(label_sizes.begin(), label_sizes.end(), [](auto &a, auto &b) {
        return b.second < a.second; // descending order
    });

    std::set<int> top10_labels;
    for (size_t i = 0; i < 10 && i < label_sizes.size(); i++) {
        top10_labels.insert(label_sizes[i].first);
        std::cout << "Watershed " << i + 1 << ": Label = " << label_sizes[i].first
                  << ", Pixels = " << label_sizes[i].second << "\n";
    }

//    // Map top10 labels to colors (0-255 range, 10 unique values)
//    std::map<int, int> label_to_color;
//    int color_step = 255 / 10; // Step for assigning unique colors
//    int color = color_step;
//    for (const int &label : top10_labels) {
//        label_to_color[label] = color;
//        color += color_step;
//    }

    // assign non-top 10 as value 0
    for (size_t i = 0; i < inputImage.getsize(0); i++) {
        for (size_t j = 0; j < inputImage.getsize(1); j++) {
            for (size_t k = 0; k < inputImage.getsize(2); k++) {
                int label = inputImage({i, j, k});
                if (top10_labels.find(label) == top10_labels.end()) {
                    inputImage({i, j, k}) = 0;
                } else {
//                        inputImage({i, j, k}) = 255;
                    inputImage({i, j, k}) = outputImage({i, j, k});
                }
            }
        }
    }

    //save resulting NII file
    inputImage.saveNII("/Users/rr/AMIP/AssignmentGit/week5/amipractical_data/Output_WS.nii.gz" );

    // Print some slices in BMP format
    inputImage.getSlice( 0,  90, "/Users/rr/AMIP/AssignmentGit/week5/amipractical_data/testF_sliceX.bmp" );
    inputImage.getSlice( 1,  128, "/Users/rr/AMIP/AssignmentGit/week5/amipractical_data/testF_sliceY.bmp" );
    inputImage.getSlice( 2,  128, "/Users/rr/AMIP/AssignmentGit/week5/amipractical_data/testF_sliceZ.bmp" );

    return 0 ;

}













