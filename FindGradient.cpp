//
//  File.cpp
//  Smart_Park2
//
//  Created by Travis Miller on 4/6/14.
//  Copyright (c) 2014 NA. All rights reserved.
//

#include "FindGradient.h"


void find_gradient(cv::Mat image, HoGParam cGradParam, double * my_gradient)
{
    using namespace std;
    using namespace cv;
    
    int p0_v, p0_vpos, p0_vneg, p2_v, p2_vpos, p2_vneg, p0_h, p0_hpos, p0_hneg, p2_h, p2_hpos, p2_hneg;
    int hist_bin, bin_deg;
    int cell_height, cell_width;
    int height = cGradParam.GetWinHeight();
    int width = cGradParam.GetWinWidth();
    const int num_bins = cGradParam.GetBins();
    const int cell_size = cGradParam.GetCellSize();
    const int block_size = cGradParam.GetBlockSize();
    const int stride = cGradParam.GetStride();
    double hor_grad, vert_grad, grad_temp;
    double mag, dir, grad_norm;
    double im_grad[height][width][2];
    double im_grad_cells[(height)/cell_size][(width)/cell_size][num_bins];
    double im_grad_blocks[(height - cell_size*block_size)/(block_size*cell_size - stride) + 1][(width - cell_size*block_size)/(block_size*cell_size - stride) + 1][block_size*block_size][num_bins];
    const double pi = 3.1415926535897;
    
    int nCount = 0;
    
    
    // Finds magnitude and direction of gradients in an image
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0;x < width; ++x)
        {
            
            p0_v = 0;
            p2_v = 0;
            p0_h = 0;
            p2_h = 0;
            
            if (y != 0)
                p0_v = (int) image.at<uchar>(y-1, x);
            if (y != (height - 1))
                p2_v = (int) image.at<uchar>(y+1, x);
            
            vert_grad = p2_v - p0_v;
            
            if (x != 0)
                p0_h = (int) image.at<uchar>(y, x-1);
            if (x != (width - 1))
                p2_h = (int) image.at<uchar>(y, x+1);
            
            hor_grad = p2_h - p0_h;
            
            // Sobel/Prewitt method
            /*
            p0_v = 0;
            p0_vpos = 0;
            p0_vneg = 0;
            p2_v = 0;
            p2_vpos = 0;
            p2_vneg = 0;
            p0_h = 0;
            p0_hpos = 0;
            p0_hneg = 0;
            p2_h = 0;
            p2_hpos = 0;
            p2_hneg = 0;
            
            if (y != 0 || x != 0 || y != (height - 1) || x != (width -1) )
            {
                p0_v = (int) image.at<uchar>(y-1, x);
                p0_vneg = (int) image.at<uchar>(y-1, x-1);
                p0_vpos = (int) image.at<uchar>(y-1, x +1);

                p2_v = (int) image.at<uchar>(y+1, x);
                p2_vneg = (int) image.at<uchar>(y+1, x-1);
                p2_vpos = (int) image.at<uchar>(y+1, x+1);
                
                p0_h = (int) image.at<uchar>(y, x-1);
                p0_hneg = (int) image.at<uchar>(y-1, x-1);
                p0_hpos = (int) image.at<uchar>(y+1, x-1);
                
                p2_h = (int) image.at<uchar>(y, x+1);
                p2_hneg = (int) image.at<uchar>(y-1, x+1);
                p2_hpos = (int) image.at<uchar>(y+1, x+1);
            }
            
            vert_grad = 2*p2_v + p2_vneg + p2_vneg - 2*p0_v - p0_vneg - p0_vpos;
            hor_grad = 2*p2_h + p2_hneg + p2_hneg - 2*p0_h - p0_hneg - p0_hpos;
            */
            
            mag = pow(vert_grad, 2) + pow(hor_grad, 2);
            mag = sqrt(mag);
            
            dir = vert_grad/hor_grad;
            dir = atan(dir);
            dir = dir/pi * 180;
            
            if (dir < 0)
                dir += 180;
            
            if (y == 0 || x == 0 || y == (height - 1) || x == (width -1))
            {
                im_grad[y][x][0] = 0;
            }
            else
            {
                im_grad[y][x][0] = mag;
            }
            
            im_grad[y][x][1] = dir;
        }
    }


    // Creates a histogram of gradients
    bin_deg = 180/num_bins;
    
    for (int y = 0; y < height; y += cell_size)
    {
        cell_height = y/cell_size;
        for (int x = 0;x < width; x += cell_size)
        {
            cell_width = x/cell_size;
            for (int j = 0; j < num_bins; j++)
                im_grad_cells[cell_height][cell_width][j] = 0;
            
            for (int i = 0; i < cell_size; i++)
            {
                for (int j = 0; j < cell_size; j++)
                {
                    
                    hist_bin = 0;
                    grad_temp = 0;
                    
                    if (!isnan(im_grad[y+i][x+j][1]))
                        grad_temp = im_grad[y+i][x+j][1];
                    
                    hist_bin  = grad_temp/bin_deg;
                
                    
                    // Bilinear interplotation
                    if (grad_temp >= (double)(hist_bin*bin_deg + bin_deg/2))
                    {
                        im_grad_cells[cell_height][cell_width][hist_bin] += im_grad[y+i][x+j][0]*(1 - (grad_temp - (hist_bin*bin_deg + bin_deg/2))/20);
                        
                        if ((hist_bin+1) < num_bins)
                        {
                            im_grad_cells[cell_height][cell_width][hist_bin+1] += im_grad[y+i][x+j][0]*(grad_temp - (hist_bin*bin_deg + bin_deg/2))/20;
                        }
                    }
                    
                    else
                    {
                        im_grad_cells[cell_height][cell_width][hist_bin] += im_grad[y+i][x+j][0]*(grad_temp - hist_bin*bin_deg + bin_deg/2)/20;
                        
                        
                        if (hist_bin - 1 >= 0)
                        {
                            im_grad_cells[cell_height][cell_width][hist_bin-1] += im_grad[y+i][x+j][0]*((hist_bin*bin_deg + bin_deg/2)- grad_temp)/20;
                            nCount++;
                        }
                    }
                }
            }
        }
    }
    
    // Normalizes Cell Gradients
    for (int i = 0; i < ((height - cell_size*block_size)/(block_size*cell_size - stride) + 1); i++)
    {
        for (int j = 0; j < ((width - cell_size*block_size)/(block_size*cell_size - stride) + 1); j++){
            grad_norm = 0;
            for (int l = 0; l < num_bins; l++){
                grad_norm = grad_norm + im_grad_cells[i][j][l]*im_grad_cells[i][j][l] + im_grad_cells[i][j+1][l]*im_grad_cells[i][j+1][l] + im_grad_cells[i+1][j][l]*im_grad_cells[i+1][j][l] + im_grad_cells[i+1][j+1][l]*im_grad_cells[i+1][j+1][l];
            }
            grad_norm = sqrt(grad_norm);
            for (int l = 0; l < num_bins; l++){
                for (int k = 0; k < block_size; k ++){
                    for (int h = 0; h < block_size; h ++){
                        im_grad_blocks[i][j][2*k+h][l] = im_grad_cells[i+k][j+h][l]/grad_norm;
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < ((height - cell_size*block_size)/(block_size*cell_size - stride) + 1); i++)
    {
        for (int j = 0; j < ((width - cell_size*block_size)/(block_size*cell_size - stride) + 1); j++)
        {
            for (int k = 0; k < (block_size*block_size); k ++)
            {
                for (int l = 0; l < num_bins; l++)
                {
                    *my_gradient = im_grad_blocks[i][j][k][l];
                    ++my_gradient;
                }
            }
        }
    }
    
    return;
}