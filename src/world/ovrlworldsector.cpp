#include "physics/engine.h"
#include "world/worldsector.h"

namespace openvrl
{

CWorldSector::CWorldSector()
{
	m_Entities = new std::list<IBasicEntity*>;
	m_Base = 0;
}

CWorldSector::~CWorldSector()
{
	Release();
	delete m_Entities;
}

void CWorldSector::Add(IBasicEntity* e)
{
	OVRL_ASSERT(e);
	OVRL_ASSERT(m_Entities);
	OVRL_ASSERT(m_Base);

	e->onInsert(this);
	m_Entities->insert(m_Entities->end(), e);
	CPhysicsEngine::Add(e);
}

void CWorldSector::Remove(IBasicEntity* e)
{
	OVRL_ASSERT(e);
	OVRL_ASSERT(m_Entities);
	OVRL_ASSERT(m_Base);

	m_Entities->remove(e);
	CPhysicsEngine::Remove(e);
	e->onRemove(this);
}

void CWorldSector::Delete(IBasicEntity* e)
{
	OVRL_ASSERT(e);
	OVRL_ASSERT(m_Entities);
	OVRL_ASSERT(m_Base);

	m_Entities->remove(e);
	CPhysicsEngine::Remove(e);
	e->onRemove(this);
}

ulong CWorldSector::onInsert(IBasicWorldEntity* w)
{
	OVRL_ASSERT(w);
	OVRL_ASSERT(m_Base==0);
	OVRL_ASSERT(w->what()==ORW_WORLD || w->what()==ORW_WORLD_SECTOR );

	m_Base = w;

	return 0;
}

ulong CWorldSector::onRemove(IBasicWorldEntity* w)
{
	OVRL_ASSERT(w);
	OVRL_ASSERT(w==m_Base);

	m_Base = 0;
	return 0;
}

void CWorldSector::Release()
{
	std::list<IBasicEntity*>::iterator I;

	OVRL_ASSERT(m_Entities);


	I = m_Entities->begin();
	while ( I!=m_Entities->end() )
	{
		OVRL_ASSERT(*I);
		(*I)->Release();
		delete (*I);
		I++;
	}

	CPhysicsEngine::Release();
	IWorldSector::Release();
	m_Entities->clear();
}

int CWorldSector::Update(real time_step)
{
	std::list<IBasicEntity*>::iterator I;

	OVRL_ASSERT(m_Entities);

	I = m_Entities->begin();
	while ( I!=m_Entities->end() )
	{
		OVRL_ASSERT(*I);
		(*I)->Update(time_step);
		I++;
	}

	return CPhysicsEngine::Update(time_step);
}

void CWorldSector::Prepare()
{
	std::list<IBasicEntity*>::iterator I;

	OVRL_ASSERT(m_Entities);

	I = m_Entities->begin();
	while ( I!=m_Entities->end() )
	{
		OVRL_ASSERT(*I);
		(*I)->Prepare();
		I++;
	}

	return CPhysicsEngine::Prepare();
}

};
