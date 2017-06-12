//
//
//
template <class BasePool>
void CBasePoolEntry<BasePool>::clear(BasePool* p)
{
	hBase = 0;
	dwFormat = 0;
	ulIndex = 0;
	ulSize = 0;
	pLocked = 0;
	next = 0;
	prev = 0;
	pool = p;
}

//
//
//
template <class PoolEntry>
inline bool CplBasePool<PoolEntry>::add_entry(PoolEntry* hBase)
{
	if ( hBase==0 ) return true;

	hBase->next = m_Head;
	hBase->prev = 0;
	if ( m_Head ) m_Head->prev = hBase;
	m_Head = hBase;

	return false;
}

template <class PoolEntry>
inline bool CplBasePool<PoolEntry>::del_entry(PoolEntry *hBase)
{
	PoolEntry* tmp;
	if ( m_Head==0 || hBase==0 ) return true;

	if ( m_Head==hBase ) 
	{
		tmp = m_Head;
		m_Head = tmp->next;
		delete tmp;
		return true;
	}

	tmp = m_Head;
	while ( tmp!=hBase && tmp!=0 ) 
		tmp = tmp->next;
	if ( tmp && tmp->hBase ) 
		if ( tmp==m_Head ) {
			tmp = m_Head->next;
			tmp->prev = 0;
			m_Head->next = 0;
			m_Head = tmp;
			delete hBase;
		} else {
			if ( tmp->next ) tmp->next->prev = tmp->prev;
			if ( tmp->prev ) tmp->prev->next = tmp->next;
			delete hBase;
		}	

	return true;
}

template <class PoolEntry>
inline PoolEntry* CplBasePool<PoolEntry>::new_entry()
{
	PoolEntry *hBase = new PoolEntry();

	if ( add_entry(hBase) ) { delete hBase; return 0; }
	return hBase;
}

template <class PoolEntry>
inline bool CplBasePool<PoolEntry>::optimize()
{
	return false;
}

template <class PoolEntry>
inline bool CplBasePool<PoolEntry>::freeup()
{
	PoolEntry*	tmp, *tmpn;
	if ( m_Head==0 ) return true;
	tmp = m_Head;
	while ( tmp ) {
		freeup_entry(tmp);
		tmpn = tmp->next;
		delete tmp;
		tmp = tmpn;
	}
	m_Head = 0;
	return false;
}

