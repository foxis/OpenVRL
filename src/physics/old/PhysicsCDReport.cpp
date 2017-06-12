#include "stdafx.h"

#include "physics/PhysicsCDReport.h"

namespace openvrl {


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPhysicsCDReport::CPhysicsCDReport()
{

}

CPhysicsCDReport::~CPhysicsCDReport()
{
	m_entries.Destroy();
}

void CPhysicsCDReport::copy(ulong ti, ulong tj, const CPhysicsCDReport& rp)
{
	CPhysicsCDReport::Report* pr=&m_entries;
	const CPhysicsCDReport::Report* prp=rp.report();
	while ( pr&&pr->next() ) pr = pr->next();
	while ( prp && pr )
	{
		pr->Add(new CPhysicsCDReport::Report(*prp));
		if ( pr->id()==tj ) pr->id() = ti;
		prp = prp->next();
		pr = pr->next();
	}
}
void CPhysicsCDReport::copy_last(ulong ti, ulong tj, const CPhysicsCDReport& rp)
{
	CPhysicsCDReport::Report* pr=&m_entries;
	const CPhysicsCDReport::Report* prp=rp.report();
	while ( pr&&pr->next() ) pr = pr->next();
	while ( prp&&prp->next() ) prp = prp->next();

	if ( prp==0 || pr==0 ) return ;
	pr->Add(new CPhysicsCDReport::Report(*prp));
	pr = pr->next();
	if ( pr->id()==tj ) 
	{
		pr->id() = ti;
		for ( ulong i=0;i<pr->num_points();i++ )
		{
			pr->points()[i].origin() *= -1;
			pr->points()[i].normal().neg();
		}
	}
	prp = prp->next();
}


////////////////////////////
//	Collision Report
////////////////////////////
CPhysicsCDReport::Report::Report()
{ 
	m_id = 0;
	m_next = 0;
	m_SP = 0;
	m_data = 0;
}

CPhysicsCDReport::Report::Report(ulong id, const CPhysicsCDReport::CollisionPoint* SP, ulong n, void *data)
{ 
	m_next = 0; 
	m_id= id;
	m_SP = new CPhysicsCDReport::CollisionPoint[n];
	memcpy(m_SP, SP, sizeof(m_SP[0])*n);
	m_points = n;
	m_data = data;
}


CPhysicsCDReport::Report::~Report()
{
	if ( m_SP ) delete[] m_SP;
}

void CPhysicsCDReport::Report::Add(CPhysicsCDReport::Report * rp)
{
	if ( m_next ) 
	{
		if ( m_next->points()[0].time() > rp->points()[0].time() )
		{
			CPhysicsCDReport::Report* tmp = m_next->next();
			m_next->next() = 0;
			m_next->Destroy();
			delete m_next;
			m_next = tmp;
			if ( m_next )	m_next->Add(rp);
			else
				m_next = rp;
		} 
		else
			if ( m_next->points()[0].time() == rp->points()[0].time() )
				m_next->Add(rp);
	} else
		m_next = rp;
}

CPhysicsCDReport::Report* CPhysicsCDReport::Report::Find(ulong id)
{
	// @todo replace by iterative algorithm
	if ( m_id!=id && m_next ) m_next->Find(id);
	if ( m_id!=id ) 
		return 0;
	else
		return this;
}

void CPhysicsCDReport::Report::dump(ulong Id, bool b)
{
	static char str[4096];
	
	if ( b )
	{
		sprintf(str, "Report for object id %i:\n", Id);
//		_LOG("report_dump",str);
		if ( m_next ) m_next->dump(Id, false);
	}
	else
	{
		sprintf(str, " id = %i\n"
			" points = %i\n", 
			id(), num_points());
//		_LOG("report_dump", str);
		for ( ulong i=0;i<num_points();i++ )
		{
			sprintf(str, "  time[%i] = %.20f\n"
				"  origin[%i] = {%20f, %20f, %20f}\n" 
				"  normal[%i] = {%1.20f, %1.20f, %1.20f}\n", 
				i, points()[i].time(), 
				i, points()[i].origin().x(), points()[i].origin().y(), points()[i].origin().z(),
				i, points()[i].normal().x(), points()[i].normal().y(), points()[i].normal().z());
//			_LOG("report_dump", str);
		}

		if ( m_next ) m_next->dump(Id, false);
	}
}

void CPhysicsCDReport::Report::Destroy()
{
	if ( m_next ) 
	{
		m_next->Destroy();
		delete m_next;
	}
	m_next = 0;
}

void CPhysicsCDReport::Report::set_last_id(ulong id)
{
	if ( m_next ) m_next->set_last_id(id);
	m_id = id;
}

}