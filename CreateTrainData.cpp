//
//  CreateTrainData.cpp
//  Smart_Park2
//
//  Created by Travis Miller on 4/7/14.
//  Copyright (c) 2014 NA. All rights reserved.
//

#include "CreateTrainData.h"

// Creates a SVM File
void CreateTrainData(HoGParam cHoGPar, int nPosFiles)
{
    using namespace std;
    using namespace cv;

    Mat frame, gray_image;
    string strName = "training_data2/";
    string line;
    int nCount=0;
    int nLabel, nAtt;
    double train_hog[cHoGPar.GetDesSize()];

    // Set-up training data
    ifstream InFile ("training_data2/training_file.txt");
    ofstream OutFile;
    OutFile.open("SVMData.txt");
    if (InFile.is_open())
    {
        while ( getline (InFile,line) )
        {
            nAtt = 1;

            frame = imread( (strName+line), 1 );
            cvtColor(frame, gray_image, CV_BGR2GRAY);

            cHoGPar.SetDesSize(gray_image.rows, gray_image.cols);

            find_gradient(gray_image, cHoGPar, train_hog);

            if (nCount < nPosFiles)
                nLabel = 1.0;
            else
                nLabel = -1.0;

            OutFile << nLabel << " ";

            for(int i = 0; i < cHoGPar.GetDesSize(); i++)
            {
                if(train_hog[i] > 0.0001)
                    OutFile << nAtt << ":" << train_hog[i] << " ";
                nAtt++;
            }

            OutFile << endl;

            nCount++;

            cout << strName+line << " " << nCount << " " << endl;
        }
        OutFile.close();
        InFile.close();
    }
    else cout << "Unable to open file";
}
