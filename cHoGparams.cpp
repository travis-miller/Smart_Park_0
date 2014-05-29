//
//  sHoGparams.cpp
//  Smart_Park2
//
//  Created by Travis Miller on 4/6/14.
//  Copyright (c) 2014 NA. All rights reserved.
//

#include "cHoGparams.h"


HoGParam::HoGParam(int nBins, int nCellSize, int nBlockSize, int nStride)
{
    m_nBins = nBins;
    m_nCellSize = nCellSize;
    m_nBlockSize = nBlockSize;
    m_nStride = nStride;
}

void HoGParam::SetDesSize(int nHeight, int nWidth)
{
    m_nWinHeight = nHeight;
    m_nWinWidth = nWidth;
    m_nDesSize = ((nHeight - m_nCellSize * m_nBlockSize)/(m_nBlockSize * m_nCellSize - m_nStride) + 1)*((nWidth - m_nCellSize * m_nBlockSize)/(m_nBlockSize * m_nCellSize - m_nStride) + 1) * m_nBlockSize * m_nBlockSize*m_nBins;
}