//
//  CarDetection.h
//  Smart_Park2
//
//  Created by Travis Miller on 4/19/14.
//  Copyright (c) 2014 NA. All rights reserved.
//

#ifndef __Smart_Park2__CarDetection__
#define __Smart_Park2__CarDetection__

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
#include "TestHoG.h"
#include <iostream>
#include <time.h>


void CarDetection(svm_model* SP_SVMModel, HoGParam cDetect_HoGPar);

#endif /* defined(__Smart_Park2__CarDetection__) */
