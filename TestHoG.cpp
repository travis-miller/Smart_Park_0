//
//  TestHoG.cpp
//  Smart_Park2
//
//  Created by Travis Miller on 4/18/14.
//  Copyright (c) 2014 NA. All rights reserved.
//

#include "TestHoG.h"

double TestHoG(svm_model* SP_SVMModel, HoGParam cTest_HoGPar, double * dTest_HoG)
{
    
    using namespace cv;
    using namespace std;

    
    int nCount = 0;
    double dResult, dValue;
    //svm_model *SP_SVMmodel = svm_load_model("SVMData.model");

    svm_node my_node[cTest_HoGPar.GetDesSize() + 1];
            
    for(int i = 0; i < cTest_HoGPar.GetDesSize(); i++)
    {
       // if (dTest_HoG[i] > 0.0001)
       // {
            my_node[nCount].index = i + 1;
            my_node[nCount].value = dTest_HoG[i];
            nCount++;
       // }
    }
            
    my_node[nCount].index = -1;
    my_node[nCount].value = '?';
    
    dResult = svm_predict_values(SP_SVMModel, my_node, &dValue);
    
    //cout << dResult << " " << dValue << endl;
    return dValue;
}