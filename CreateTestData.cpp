//
//  CreateTestData.cpp
//  Smart_Park2
//
//  Created by Travis Miller on 4/18/14.
//  Copyright (c) 2014 NA. All rights reserved.
//

#include "CreateTestData.h"

void CreateTestData(svm_model* SP_SVMModel, HoGParam cTest_HoGPar, int nPosNum)
{
    
    using namespace cv;
    using namespace std;
    
    Mat frame, gray_image;
    string strName = "test_data/";
    string strLine;
    int nTestNum;
    int nLabel = 1;
    int nValue;
    double dResult;
    double dTest_HoG[cTest_HoGPar.GetDesSize()];
    
    nTestNum = 0;
    
    // Set-up training data
    ifstream InFile ("test_data/test_file1.txt");
    ofstream OutFile;
    OutFile.open("HoGResults.txt");
    if (InFile.is_open())
    {
        //OutFile << "Test Number\tLabel\tPredict\t\tValue";
        //OutFile << endl;
        
        while ( getline (InFile,strLine) )
        {
            cout << strName+strLine << endl;
            
            frame = imread( (strName+strLine), 1 );
            cvtColor(frame, gray_image, CV_BGR2GRAY);
            
            nTestNum++;
            
            //cTest_HoGPar.SetDesSize(gray_image.rows, gray_image.cols);
            
            find_gradient(gray_image, cTest_HoGPar, dTest_HoG);
            dResult = TestHoG(SP_SVMModel, cTest_HoGPar, dTest_HoG);
            
            if(nTestNum > nPosNum)
                nLabel = -1;
            
            if(dResult < 0)
                nValue = -1;
            else
                nValue = 1;
            
            OutFile << nLabel << " " << dResult << endl;
            //OutFile << "\t" << nTestNum << "\t    " << nLabel << "\t" << dResult << "  \t" <<  nValue << endl;
            //OutFile << endl;

            
        }
        OutFile.close();
        InFile.close();
    }
    else cout << "Unable to open file";
}