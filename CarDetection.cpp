//
//  CarDetection.cpp
//  Smart_Park2
//
//  Created by Travis Miller on 4/19/14.
//  Copyright (c) 2014 NA. All rights reserved.
//

#include "CarDetection.h"

void CarDetection(svm_model* SP_SVMModel, HoGParam cDetect_HoGPar)
{
    using namespace cv;
    using namespace std;

    Mat Frame, Det_Image, Temp_Frame;
    Size imageSize;
    Rect box;
    int nCameraNum, nStep, nThreshold, nyStart, nyEnd;
    int nNumFrames = 0;
    double dFrameMean;
    double dDet_HoG[cDetect_HoGPar.GetDesSize()];
    double dResult = 0;
    Point tl, br;
    Scalar tempVal;


    VideoCapture SP_vid("test_video_pkg3.mp4");
    nCameraNum = 3;

  switch (nCameraNum)
    {
        case 1:
            nThreshold = 0;
            nyStart = 125;
            nyEnd = 180;
            nStep = 16;
            cout << 1 << endl;
            break;
        case 2:
            nThreshold = 0;
            nyStart = 200;
            nyEnd = 210;
            nStep = 2;
            cout << 2 << endl;
            break;
        case 3:
            nThreshold = 50;
            nyStart = 120;
            nyEnd = 200;
            nStep = 32;
            cout << 3 << endl;
            break;
        default:
            nThreshold = 0;
            nyStart = 100;
            nyEnd = 200;
            nStep = 16;
            cout << 4 << endl;
    }

    if ( !SP_vid.isOpened() )  // if not success, exit program
    {
        cout << "Video file cannot be opened" << endl;
        return;
    }
    double fps = SP_vid.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video

    cout << "Frame per seconds : " << fps << endl;

    fps = SP_vid.get(CV_CAP_PROP_FRAME_HEIGHT); //get the frames per seconds of the video

    cout << "Frame Height : " << fps << endl;

    fps = SP_vid.get(CV_CAP_PROP_FRAME_WIDTH); //get the frames per seconds of the video

    cout << "Frame Height : " << fps << endl;


    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

    while(1)
    {
        // Starts clock
        clock_t t;
        clock_t t_total = 0;

        //bool bSuccess = SP_vid.read(Frame); // read a new frame from video
        SP_vid >> Frame;
        if (!Frame.data) //if not success, break loop
        {
            cout << "Cannot read the frame from video file" << endl;
            cout << "Number of Frames: " << nNumFrames << endl;
            return;
        }

        //Frame = imread( "full_image6.jpg", 1 );

        cvtColor(Frame, Det_Image, CV_BGR2GRAY);

        imageSize.height = Det_Image.rows;
        imageSize.width = Det_Image.cols;

        tempVal = mean( Det_Image );
        dFrameMean = tempVal.val[0];

        nNumFrames++;

        if(dFrameMean > 50)
        {
            for(int x = 0; x < imageSize.width - cDetect_HoGPar.GetWinWidth(); x+=nStep)
            {
                for(int y = nyStart; y < nyEnd; y+=nStep)
                {

                    Mat Det_Region (Det_Image, Rect(x, y, cDetect_HoGPar.GetWinWidth() ,cDetect_HoGPar.GetWinHeight()));

                    t = clock();
                    find_gradient(Det_Region, cDetect_HoGPar, dDet_HoG);
                    t_total += clock() - t;
                    dResult = TestHoG(SP_SVMModel, cDetect_HoGPar, dDet_HoG);

                    if (dResult > nThreshold)
                    {
                        tl.x = x;
                        tl.y = y;

                        br.x = x + cDetect_HoGPar.GetWinWidth();
                        br.y = y + cDetect_HoGPar.GetWinHeight();
                        rectangle(Frame, tl, br, cv::Scalar(0,255,0), 2);
                        x += 160;
                        y += imageSize.height;
                    }
                }
            }
        }

        // Ends Clock


        cout << "It took me " << t_total << " clicks ("<< ((float)t_total)/CLOCKS_PER_SEC << " seconds)." << endl;

        imshow("MyVideo", Frame);
        //imwrite( "Detection_Image.jpg", Frame);

        if (waitKey(20) >= 0)
            return;

    }
    return;

}
