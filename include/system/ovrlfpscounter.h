/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/system/ovrlfpscounter.h,v $
 * $Implementation: /include/fpscounter.cc $
 * $Revision: 1.4 $
 * $Author: foxis $
 * $Date: 2005/02/03 17:52:55 $
 * $Description: FPS manager $
 *
 * $Log: ovrlfpscounter.h,v $
 * Revision 1.4  2005/02/03 17:52:55  foxis
 * made IBasicGeom and it's derivatives to work.
 * now physics engine recognizes collisions.
 *
 * however geom management should be rethought.
 *
 * Revision 1.3  2005/02/03 16:50:30  foxis
 * stop_frame_measure divbyzero fixed
 * .hold() changed to .elapsed()
 *
 * Revision 1.2  2005/02/02 20:01:02  foxis
 * Basic ODE support - seems to work ok
 * basic CBody - seems to work
 * basic system overall - seems to work :)
 *
 * minor bugfixes, and changes in body managment code
 *
 * Revision 1.1.1.1  2005/02/02 15:39:21  foxis
 * sources import
 *
 * Revision 0.1  20020105  11:52:40 FoxiE
 *  :)
 *
 */


#if !defined(__ovrl_FPSCOUNTER_HPP)
#define __ovrl_FPSCOUNTER_HPP

#include "common/all.h"
#include "system/ovrlclock.h"

namespace openvrl {

class OVRLIBAPI CFPSCounter 
{
	ulong m_frames;
	ulong m_subframes;
	ulong m_accuracy;
	bool m_floating_accuracy;
	CClock m_frame;
	CClock m_subframe;
	CClock m_calculate;
	CClock m_render;
	CClock m_custom;
	CClock	m_clock;

	real m_FPS;
	real m_hold_FPS;
	real m_hold_FPS_time;
	real m_frame_time_delta;

public:
	CFPSCounter(ulong FPS, ulong accuracy=10, bool floating_accuracy=true): m_frames(0), m_subframes(0),
		m_accuracy(accuracy), m_floating_accuracy(floating_accuracy), m_FPS(0),
		m_hold_FPS(FPS)
	{	
		m_hold_FPS_time = 1/m_hold_FPS;
		if ( m_accuracy==0 ) m_accuracy = 1;
	}


	real FPS() const 
	{
		return m_FPS;
	}
	real frame_time() const 
	{
		return 0;
	}
	real frame_dx() const
	{
		return 0;
	}

	void start_frame_measure() 
	{  
		m_frames++;
		m_frame.reset();
		if ( m_subframes )
			m_subframes--;
		else
		{
			m_subframe.reset();
			m_subframes = m_accuracy;
		}
	}
	void stop_frame_measure()
	{
		ulong ms = m_frame.hold();
		if ( m_subframes==0 ) {
			m_subframes = m_accuracy;
			m_FPS = m_accuracy/m_subframe.elapsed();
		}
	}

	void start_calculate_measure()
	{
		m_calculate.reset();
	}
	void stop_calculate_measure()
	{
		m_calculate.hold();
	}

	void start_render_measure()
	{
		m_render.reset();
	}
	void stop_render_measure()
	{
		m_render.hold();
	}

	void start_custom_measure()
	{
		m_custom.reset();
	}
	void stop_custom_measure()
	{
		m_custom.hold();
	}

	void idle()
	{
		m_clock.reset();
		m_clock.noops(1);
	}

	void reset()
	{
		m_frames = 0;
		m_subframes = 0;
	}
};

};

#endif /* !defined(__ovrl_FPSCOUNTER_HPP) */
