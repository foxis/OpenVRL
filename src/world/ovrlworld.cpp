#include "system/ovrlsystem.h"
#include "world/world.h"

namespace openvrl {

IBasicWorldEntity::IBasicWorldEntity()
{
	m_RefCount = 0;
	m_active = true;
	AddRef();
}

IBasicWorldEntity::~IBasicWorldEntity()
{
	DelRef();
}

void IBasicWorldEntity::Release()
{
	DelRef();
}

void IBasicWorldEntity::AddRef()
{
	m_RefCount++;
}

int IBasicWorldEntity::DelRef()
{
	return --m_RefCount == 0;
}


CWorld::CWorld(CSystem* sys)
{
	OVRL_ASSERT(sys);
	m_Sectors = new std::list<IWorldSector*>;
	m_System = sys;
}

CWorld::~CWorld()
{
	Release();

	delete m_Sectors;
}

void CWorld::Release()
{
	std::list<IWorldSector*>::iterator I;

	OVRL_ASSERT(m_Sectors);

	I = m_Sectors->begin();
	while ( I!=m_Sectors->end() )
	{
		OVRL_ASSERT(*I);
		(*I)->Release();
		delete (*I);
		I++;
	}

	m_Sectors->clear();

	IBasicWorldEntity::Release();
}

void CWorld::AddSector(IWorldSector* s)
{
	OVRL_ASSERT(m_Sectors);
	OVRL_ASSERT(s);

	s->onInsert(this);
	m_Sectors->insert(m_Sectors->end(), s);
}

void CWorld::RemoveSector(IWorldSector* s)	
{
	OVRL_ASSERT(m_Sectors);
	OVRL_ASSERT(s);

	s->onRemove(this);
	m_Sectors->remove(s);
}

void CWorld::DeleteSector(IWorldSector* s)	
{
	OVRL_ASSERT(s);
	OVRL_ASSERT(m_Sectors);

	s->onRemove(this);
	m_Sectors->remove(s);
	s->Release();
}

IPipeline*	CWorld::GetPipeline() 
{ 
	return m_System->Pipeline(); 
}

int CWorld::Load(const CString& out)
{
	return 0;
}

int CWorld::Save(const CString& out)
{
	return 0;
}

int CWorld::Update(real time_step)
{
	std::list<IWorldSector*>::iterator I;

	OVRL_ASSERT_EX(time_step>0, DIVBYZERO, "Simulation time step cannot be less or equal 0");
	OVRL_ASSERT(m_Sectors);

	I = m_Sectors->begin();
	while ( I!=m_Sectors->end() )
	{
		OVRL_ASSERT(*I);
		(*I)->Update(time_step);
		I++;
	}

	return 0;
}

void CWorld::Prepare()
{
	std::list<IWorldSector*>::iterator I;

	OVRL_ASSERT(m_Sectors);

	I = m_Sectors->begin();
	while ( I!=m_Sectors->end() )
	{
		OVRL_ASSERT(*I);
		(*I)->Prepare();
		I++;
	}
}

};
