#include "system/ovrlsystem.h"
#include "pipeline/basicmesh.h"
#include "world/world.h"
#include "pipeline/pipeline.h"
#include "pipeline/basicshadowvolume.h"

namespace openvrl {

IPipeline*		IPipeline::s_THIS = 0;
ulong		IPipeline::s_THIS_count = 0;

/**
 *
 */
IPipeline::IPipeline(CSystem* system)
	:CxFactory(system),
	m_VBPool(0),
	m_IBPool(0),
	m_TXPool(0),
	m_VSPool(0)
{
	if ( s_THIS==0 ) s_THIS = this;
	s_THIS_count++;

	m_Renderables = new std::vector<IBasicMesh*>;
	m_Cameras = new std::vector<IBasicCamera*>;
	m_Lights = new std::vector<IBasicLight*>;
}

IPipeline::~IPipeline()
{
	if ( s_THIS_count==1 ) s_THIS = 0;
	s_THIS_count--;

	delete m_Renderables;
	delete m_Cameras;
	delete m_Lights;
}


bool IPipeline::Initialize()
{
	CxFactory::Initialize();
	m_VBPool = create_VBPool();
	m_IBPool = create_IBPool();
	m_VSPool = create_VSPool();
	m_TXPool = create_TXPool();
	SetStates();
	return false;
}

bool IPipeline::CreateDevice()
{
	return false;
}

bool IPipeline::CleanupDevices()
{
	return false;
}

bool IPipeline::Cleanup()
{
	CxFactory::Cleanup();
	if ( m_VBPool ) { 
		printf("pipeline: release vb\n");
		m_VBPool->freeup();
		printf("pipeline: delete vb\n");
		delete_VBPool(m_VBPool);
		m_VBPool = 0;
	}
	if ( m_IBPool ) { 
		printf("pipeline: release ib\n");
		m_IBPool->freeup();
		printf("pipeline: delete ib\n");
		delete_IBPool(m_IBPool);
		m_IBPool = 0;
	}
	if ( m_VSPool ) { 
		printf("pipeline: release vs\n");
		m_VSPool->freeup();
		printf("pipeline: delete vs\n");
		delete_VSPool(m_VSPool);
		m_VSPool = 0;
	}
	if ( m_TXPool ) { 
		printf("pipeline: release tx\n");
		m_TXPool->freeup();
		printf("pipeline: delete tx\n");
		delete_TXPool(m_TXPool);
		m_TXPool = 0;
	}
	printf("pipeline: ::release\n");
	return 0;
}

int IPipeline::UpdateLightList(real time_step, IWorld* w)
{
	return 0;
}

int IPipeline::UpdateCameraList(real time_step, IWorld* w)
{
	return 0;
}

int IPipeline::UpdateRenderableList(real time_step, IWorld* w)
{
	return 0;
}

int IPipeline::Update(real time_step, IWorld* w)
{
	std::list<IBasicEntity*>* roote;
	std::list<IWorldSector*>* root;
	std::list<IWorldSector*>::iterator I;
	std::list<IBasicEntity*>::iterator J;
	OVRL_ASSERT(w);

	w->Update(time_step);

	// sort meshes
	// @todo make it fast and deeper 
	root = w->GetSectorList();
	OVRL_ASSERT(root);
	I = root->begin();
	m_Renderables->clear();
	m_Cameras->clear();
	m_Lights->clear();
	while ( I!=root->end() )
	{
		OVRL_ASSERT((*I)->what()==ORW_WORLD_SECTOR);
		roote = (*I)->GetEntityList();
		OVRL_ASSERT(roote);
		J = roote->begin();
		while ( J!=roote->end() )
		{
			ulong what = (*J)->caps();

//			printf("Render: %08x, '%s' '%s' [%08x,%08x,%08x]\n", what, (*J)->get_name(), (*J)->isActive()?"active":"inactive",
//				OVRL_CAPS_MESH, OVRL_CAPS_CAMERA, OVRL_CAPS_LIGHT);

			if ( (*J)->isActive() ) {
				if ( what&OVRL_CAPS_MESH )
					m_Renderables->push_back((IBasicMesh*)((*J)->GetPipelineEntity(OVRL_CAPS_MESH)));
				if ( what&OVRL_CAPS_CAMERA )
				{
					IBasicCamera* we = (IBasicCamera*)((*J)->GetPipelineEntity(OVRL_CAPS_CAMERA));
//					printf("Render: Add camera %p\n", we);
					m_Cameras->push_back(we);
				}
				if ( what&OVRL_CAPS_LIGHT )
					m_Lights->push_back((IBasicLight*)((*J)->GetPipelineEntity(OVRL_CAPS_LIGHT)));
			}
			// @todo: add particle group, effect group and so on..
			J++;
		}
		I++;
	}

	UpdateLightList(time_step, w);
	UpdateCameraList(time_step, w);
	UpdateRenderableList(time_step, w);

	std::vector<IBasicCamera*>::iterator K;

	K = m_Cameras->begin();
	if ( K==m_Cameras->end() )
		ProcessRenderables(0);	// if no camera - assume default one
	else while ( K!=m_Cameras->end() )
	{
		ProcessRenderables(*K);
		K++;
	}

	return 0;
}


}
