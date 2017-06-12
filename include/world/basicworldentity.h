/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/world/basicworldentity.h,v $
 * $Implementation: /src/ovrlobj.cc $
 * $Revision: 1.3 $
 * $Author: foxis $
 * $Date: 2005/02/23 12:30:57 $
 * $Description: Base class for all other classes :-) $
 *
 * $Log: basicworldentity.h,v $
 * Revision 1.3  2005/02/23 12:30:57  foxis
 * added light/camera/rendertarget
 * rearranged IBasic* stuff - more like COM now :)
 * fixed 3dvector, quaternion, misc fixes
 *
 * Revision 1.2  2005/02/02 20:05:03  foxis
 * Basic ODE support - seems to work ok
 * basic CBody - seems to work
 * basic system overall - seems to work :)
 *
 * minor bugfixes, and changes in body managment code
 *
 * Revision 1.1.1.1  2005/02/02 15:39:23  foxis
 * sources import
 *
 * Revision 0.2  20020105  17:55:10 FoxiE
 *  Pervardinau, portinau prie VC++ 6..
 *
 * Revision 0.1  20010411  20:30:00 FoxiE
 *  :)
 *
 */



#if !defined(__ovrl_OVRLOBJ_H)
#define __ovrl_OVRLOBJ_H

#include "common/all.h"

namespace openvrl {

class IPipeline;
class IWorld;
class OVRLIBAPI IBasicWorldEntity
{
public:
	IBasicWorldEntity();
	virtual ~IBasicWorldEntity();

	virtual ulong what() const = 0;
	virtual CHAR* get_name() const =0;
	virtual ulong caps() const = 0;

	virtual IBasicWorldEntity* GetBase() = 0;
	virtual IPipeline*	GetPipeline() = 0;
	virtual IWorld*	GetWorld() = 0;

	virtual bool canInsert() const	{	return false;	}
	virtual bool canSort() const	{	return false;	}
	virtual bool canRender() const	{	return false;	}
	virtual bool canCalculate() const	{	return false;	}

	bool isActive() const { return m_active; }
	void setActive(bool a) { m_active = a; }

	virtual int Update(real time_step) = 0;

	virtual void Prepare() = 0;

	virtual void Release() = 0;
	void AddRef();


protected:
	int DelRef();

	num_t m_RefCount;
	bool m_active;
};

class OVRLIBAPI IBasicEvent
{
public:
	virtual ~IBasicEvent() = 0 {}

	virtual uint What() const = 0;
	virtual uint GetSize() const = 0;
	virtual void GetData(void*dst, uint maxcb) = 0;
};

class OVRLIBAPI IListener
{
public:
	virtual ~IListener() = 0 {}

	virtual uint onEvent(const IBasicEvent& be) = 0;
	virtual bool onQueryEvent(uint what) = 0;
};

};

#endif /* !defined(__ovrl_OVRLOBJ_HPP) */
