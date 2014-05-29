//
//  File.h
//  Smart_Park2
//
//  Created by Travis Miller on 4/6/14.
//  Copyright (c) 2014 NA. All rights reserved.
//

#ifndef __Smart_Park2__File__
#define __Smart_Park2__File__

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
#include <cmath>
#include <iostream>

void find_gradient(cv::Mat image, HoGParam cGradParam, double * my_gradient);

#endif /* defined(__Smart_Park2__File__) */
