//
//  main.cpp
//  Smart_Park2
//
//  Created by Travis Miller on 4/5/14.
//  Copyright (c) 2014 NA. All rights reserved.
//

#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "cHoGparams.h"
#include "FindGradient.h"
#include "CreateTrainData.h"
#include "CreateTestData.h"
#include "TestHoG.h"
#include "HoGVisual.h"
#include "CarDetection.h"
#include "WebCarDetection.h"
#include "svm.h"
#include <cmath>
#include <time.h>
#include <iostream>
#include <fstream>

struct ImageParam
{
    const int nHeight;
    const int nWidth;
};

int main(int argc, char* argv[])
{

    using namespace cv;
    using namespace std;

    double dValue;
    Size winSize;
    Size winCell;
    CvSVM project_SVM;
    Mat frame, gray_image, grad_image;
    HoGParam cSP_HoGPar = {9, 64, 2, 64}; // Bins, cell size, block size, stride
    svm_model *SP_SVMmodel = svm_load_model("SVMData_64x64.model");
    winCell.width = cSP_HoGPar.GetCellSize(); // Sets cell size for HoG visualization
    winCell.height = cSP_HoGPar.GetCellSize(); // Sets cell size for HoG visualization
    winSize.width = 320;
    winSize.height = 320;
    cSP_HoGPar.SetDesSize(winSize.width, winSize.height);
    double dHoG[cSP_HoGPar.GetDesSize()]; // HoG Descriptor vector


    // Starts clock
    clock_t t;
    t = clock();



    //CarDetection(SP_SVMmodel, cSP_HoGPar);
    //WebCarDetection();

    // Reads in image and converts to grayscale
    //frame = imread( "car_test12.jpg", 1 );
    //cvtColor(frame, gray_image, CV_BGR2GRAY);
    //imwrite( "Gray_Image.jpg", gray_image );


    // Sets parameters for HoG Descriptor size and visualization window
    //ImageParam sHogImage = {gray_image.rows,  gray_image.cols};
    //winSize.width = sHogImage.nWidth;
    //winSize.height = sHogImage.nHeight;
    //cSP_HoGPar.SetDesSize(sHogImage.nHeight, sHogImage.nWidth);
    //dHoG[cSP_HoGPar.GetDesSize()];



    //find_gradient(gray_image, cSP_HoGPar, dHoG); // Generates HoG Descriptor
    //dValue = TestHoG(SP_SVMmodel, cSP_HoGPar, dHoG); // Tests HoG Descriptor with SVM

    // Ends Clock

    t = clock() - t;
    cout << "It took me " << t << " clicks ("<< ((float)t)/CLOCKS_PER_SEC << " seconds)." << endl;

    // Creates HoG visualization
    //grad_image = get_hogdescriptor_visual_image(frame, dHoG, winSize, winCell, 2, 1.5);
    //imwrite( "/Users/travismiller/Documents/C++/Smart_Park2/Smart_Park2/Gradient_Image.jpg", grad_image );


    //CreateTrainData(cSP_HoGPar, 344); // Creates SVM Training Data
    //CreateTestData(SP_SVMmodel, cSP_HoGPar, 118); // Creates Test Results Data

    return 0;
}
