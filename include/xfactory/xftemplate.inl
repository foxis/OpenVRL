//
// xfactory list template
//
template <class TA, class Tthis>
inline TA* CxFactoryListTemplate<TA, Tthis>::create(const CString& name)
{
		return add(name, new TA(reinterpret_cast<Tthis*>(this)));
}

template <class TA, class Tthis>
inline int CxFactoryListTemplate<TA, Tthis>::release(TA* t)
{
	remove(t);
	t->free();
	t->release();
	return 0;
}

template <class TA, class Tthis>
inline TA* CxFactoryListTemplate<TA, Tthis>::add(const CString& name, TA* m)
{
	// @todo use named lists
	// @todo check for duplicate names
	m->name() = name;
	m_list->push_back(m);
	return m;
}

template <class TA, class Tthis>
inline TA* CxFactoryListTemplate<TA, Tthis>::remove(const CString& name)
{
	TA*	tmp = find(name);
	if ( tmp ) 
	{
		remove(tmp);
		return tmp;
	}
	else
		return 0;
}

template <class TA, class Tthis>
inline TA* CxFactoryListTemplate<TA, Tthis>::remove(TA* t)
{
	m_list->remove(t);
	return t;
}

template <class TA, class Tthis>
inline TA* CxFactoryListTemplate<TA, Tthis>::find(const CString& name)
{
	std::list<TA*>::iterator i(m_list->begin());
	while ( i!=m_list->end() && (*i)->name()!=name ) 
	{
		printf("searching: unmatched '%s'\n", (*i)->name().c_str());
		i++;
	}

	if ( i!=m_list->end() ) 
	{
		printf("searching: found '%s'\n", (*i)->name().c_str());
		return *i;
	}	
	else
	{
		printf("searching: not found '%s'\n", name.c_str());
		return 0;
	}
}

template <class TA, class Tthis>
CxFactoryListTemplate<TA, Tthis>::CxFactoryListTemplate(CxFactory* xf)
{
	m_xFactory = xf;
	m_list = new std::list<TA*>;
}

template <class TA, class Tthis>
CxFactoryListTemplate<TA, Tthis>::~CxFactoryListTemplate()
{
	std::list<TA*>::iterator i(m_list->begin());
	while ( i!=m_list->end() ) 
	{
		TA* tmp = *i;
//		OVRL_ASSERT(tmp);
		tmp->free();
		tmp->release();
		i++;
	}
	m_list->clear();
	delete m_list;
}

//
// xfactory template
//

template <class TA,class Tthis> 
CxFactoryTemplate<TA,Tthis>::CxFactoryTemplate(TA* xfl)
{
	m_xList = xfl;
	m_ref_count = 0;
}

template <class TA,class Tthis> 
CxFactoryTemplate<TA,Tthis>::~CxFactoryTemplate()
{
	printf("CxFactoryTemplate dtor\n");
	OVRL_ASSERT_EX(m_ref_count==0, GENERAL, "Deleting template that is still in use!");
	printf("CxFactoryTemplate dtor done\n");
}

template <class TA,class Tthis> 
inline int CxFactoryTemplate<TA,Tthis>::use()
{
	printf("CxFactoryTemplate: use('%s')\n", m_name.c_str());
	return m_ref_count++; 
}

template <class TA,class Tthis> 
inline int CxFactoryTemplate<TA,Tthis>::unuse() 
{ 
	printf("CxFactoryTemplate: unuse('%s')\n", m_name.c_str());
	OVRL_ASSERT_EX(m_ref_count>0, GENERAL, "Ref count == 0!");
	m_ref_count--;
	printf("CxFactoryTemplate: unuse('%s') done\n", m_name.c_str());
	return m_ref_count; 
}	

//template <class TA,class Tthis> 
//inline int CxFactoryTemplate<TA,Tthis>::free() 
//{
//	printf("CxFactoryTemplate: free('%s')  -- WTF?!?!?!?!\n", m_name.c_str());
//	return 1;
//}
