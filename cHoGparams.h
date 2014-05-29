//
//  sHoGparams.h
//  Smart_Park2
//
//  Created by Travis Miller on 4/6/14.
//  Copyright (c) 2014 NA. All rights reserved.
//

#ifndef __Smart_Park2__sHoGparams__
#define __Smart_Park2__sHoGparams__

class HoGParam
{
private:
    int m_nBins;
    int m_nCellSize;
    int m_nBlockSize;
    int m_nStride;
    int m_nWinHeight;
    int m_nWinWidth;
    int m_nDesSize;
    
public:
    HoGParam(int nBins, int nCellSize, int nBlockSize, int nStride);
    
    void SetDesSize(int nHeight, int nWidth);
    
    int GetBins(){return m_nBins;}
    int GetCellSize(){return m_nCellSize;}
    int GetBlockSize(){return m_nBlockSize;}
    int GetStride(){return m_nStride;}
    int GetWinHeight(){return m_nWinHeight;}
    int GetWinWidth(){return m_nWinWidth;}
    int GetDesSize(){return m_nDesSize;}
};

#endif /* defined(__Smart_Park2__cHoGparams__) */
