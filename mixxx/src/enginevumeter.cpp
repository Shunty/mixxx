/***************************************************************************
                          enginevumeter.cpp  -  description
                             -------------------
    copyright            : (C) 2002 by Tue and Ken Haste Andersen
    email                :
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "enginevumeter.h"
#include "controlpotmeter.h"

EngineVuMeter::EngineVuMeter(const char *group)
{
    // The VUmeter widget is controlled via a controlpotmeter, which means
    // that it should react on the setValue(int) signal.
    m_ctrlVuMeter = new ControlPotmeter(ConfigKey(group, "VuMeter"), 0., 1.);
    m_ctrlVuMeter->set(0);

    // Initialize the calculation:
    m_iSamplesCalculated = 0;
    m_fRMSvolume = 0;
}

EngineVuMeter::~EngineVuMeter()
{
    delete m_ctrlVuMeter;
}

void EngineVuMeter::process(const CSAMPLE *pIn, const CSAMPLE *, const int iBufferSize)
{
    // Calculate the summed absolute volume
    for (int i=0; i<iBufferSize; ++i)
        m_fRMSvolume += fabs(pIn[i]);
    
    m_iSamplesCalculated += iBufferSize;

    // Are we ready to update the VU meter?:
    if (m_iSamplesCalculated > (44100/UPDATE_RATE) )
    {
        m_fRMSvolume = log10(m_fRMSvolume/(m_iSamplesCalculated*1000)+1);
        m_ctrlVuMeter->set( min(1.0, max(0.0, m_fRMSvolume)) ); 
        // Reset calculation:
        m_iSamplesCalculated = 0;
        m_fRMSvolume = 0;
    }
}
