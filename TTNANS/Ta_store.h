#ifndef TA_STORE
#define TA_STORE

#include "ttnerror.h"
#include "ttnui.h"

/**** Class CTa_stack_storage:							****/
/**** Stack-like storage class for use by ANSs			****/

template <class T>
class CTa_stack_storage
{
private:

struct _T_wrapper;
typedef struct _T_wrapper {T item ; _T_wrapper PTR  previous; _T_wrapper PTR  next; } T_wrapper;

T_wrapper PTR	m_first;
T_wrapper PTR	m_last;
T_wrapper PTR	m_current;
unsigned		m_number_of_items;
T				m_junk;

public:

CTa_stack_storage()
{
m_first=m_last=m_current=NULL;
m_number_of_items = 0;
}

~CTa_stack_storage()
{
unsigned c = 0;
T_wrapper PTR p = m_last;
while(p NEQL NULL)
 {
 UnstackLastItem();
 p=m_last;
 c++;
 }

#ifdef _DEBUG
mprintf("(CTa_stack_storage, removed a total of %d items.)\n",c);
#endif
}

bool StackItem(T REF item)
 {
 bool ok = true;
 T_wrapper PTR p_new_wrapper;

 ok=((p_new_wrapper = new T_wrapper)NEQL NULL);
 
 if(ok)
  {
  p_new_wrapper->item = item;
  m_number_of_items++;

  if(m_first EQL NULL)							// List empty?
   {
   p_new_wrapper->previous=NULL;
   p_new_wrapper->next=NULL;
   m_first = p_new_wrapper;
   m_last  = m_first;
   }  
  else
   {
   m_last->next=p_new_wrapper;
   p_new_wrapper->previous=m_last;
   p_new_wrapper->next=NULL;
   m_last=p_new_wrapper;
   }
  }
 return ok;
 }

bool StackItem()
 {
 bool ok = true;
 T_wrapper PTR p_new_wrapper;

 ok=((p_new_wrapper = new T_wrapper)NEQL NULL);
 
 if(ok)
  {
  m_number_of_items++;

  if(m_first EQL NULL)							// List empty?
   {
   p_new_wrapper->previous=NULL;
   p_new_wrapper->next=NULL;
   m_first = p_new_wrapper;
   m_last  = m_first;
   }  
  else
   {
   m_last->next=p_new_wrapper;
   p_new_wrapper->previous=m_last;
   p_new_wrapper->next=NULL;
   m_last=p_new_wrapper;
   }
  }
 return ok;
 }

bool UnstackLastItem()
 {
 T_wrapper PTR p = NULL;

 bool ok = true;
 if(m_last EQL NULL)
  {
  runerror(ANSINTERR,"CTa_stack_storage, can not unstack empty stack.");
  return false;
  }

 if(m_last->previous EQL NULL)				// is this the first item ?
  {
  if(m_first NEQL m_last) 
   {
   runerror(ANSINTERR,"CTa_stack_storage, stack inconsistent.");
   ok = false;
   delete m_first;
   m_number_of_items--;
   m_first=m_last;
   }  
  }
 else
  {
  p=m_last->previous;
  p->next=NULL;
  }

 if(m_first EQL m_last) m_first = m_last = NULL;

 delete m_last;
 m_last = p;
 m_number_of_items--;
 return ok;
 }

T REF Last()
{
if(m_last EQL NULL)
 {
  mprintf("CTa_stack_storage: Warning accessing last on empty stack.");
 return m_junk;
 }
return m_last->item;
}

unsigned Items () {return m_number_of_items;}

bool Contains (T REF item)
 {
 T_wrapper PTR p = m_first;
 bool found = false;
 while( (p NEQL NULL) AND (NOT found))
  {
  found = (p->item==item);
  p = p->next;
  }
 return found;
 }


T REF operator [] (unsigned item)
 {
 T_wrapper PTR p = m_first;
 if(item>=m_number_of_items)
  {
  runerror(ANSINTERR,"CTa_stack_storage, attempt to access non-existant item.");
  return m_junk;
  }
 
 for(unsigned i=0;i<item;i++)
  p=p->next;
 return p->item;
 }

};


/**** Class CTa_vector_storage:							****/
/**** Vector-like storage class for use by ANSs			****/


template <class T>
class CTa_vector_storage
{
private:

T PTR		m_storage;
unsigned	m_number_of_items;
T			m_junk;

protected:

public:

CTa_vector_storage ();
~CTa_vector_storage();

T REF operator [] (unsigned item);
bool Initialize(unsigned new_number_of_items);
unsigned Items ();
bool HasA (unsigned item_id);
bool Contains (T REF item);
};

/*- CTa_vector_storage implementation :		-*/

template <class T>
CTa_vector_storage<T>::CTa_vector_storage ()
 {
 m_storage = NULL;
 m_number_of_items = 0;
 }

template <class T>
CTa_vector_storage<T>::~CTa_vector_storage()
 {
 if((m_storage NEQL NULL) OR
	(m_number_of_items NEQL 0))
  {
  delete [m_number_of_items] m_storage;
  }
 m_storage = NULL;
 m_number_of_items = 0;
 }

template <class T>
T REF CTa_vector_storage<T>::operator [] (unsigned item)
 {
 if(item>=m_number_of_items)
  {
  runerror(ANSINTERR,"CTa_vector_storage, attempt to access non-existant item.");
  return m_junk;
  }
 return m_storage[item];
 };

template <class T>
bool CTa_vector_storage<T>::Initialize(unsigned new_number_of_items)
 {
 if(new_number_of_items EQL 0)
  mprintf("CTa_vector_storage: Warning. Initialize called for new item size = 0.\n");

 if(m_storage NEQL NULL)
  {
  mprintf("CTa_vector_storage: Warning. Initialize called on non-empty storage (deleting old).\n");
  delete [m_number_of_items] m_storage;
  m_number_of_items=0;
  }

 if(m_number_of_items NEQL 0)
  mprintf("CTa_vector_storage: Warning. Initialize called on non-zero old number of items.\n");

 m_storage = NULL;
 m_number_of_items = 0;

 m_storage = new T [new_number_of_items];

 if(m_storage NEQL NULL)
  {
  m_number_of_items = new_number_of_items;
  return true;
  }
 return false;
 }

template <class T>
unsigned CTa_vector_storage<T>::Items ()
 {return m_number_of_items;}

template <class T>
bool CTa_vector_storage<T>::HasA (unsigned item_id)
 {
 return(item_id<m_number_of_items);
 }

template <class T>
bool CTa_vector_storage<T>::Contains (T REF item)
 {
 unsigned i=0;
 bool found = false;
 while( (i<m_number_of_items) AND (NOT found) )
  {
  found=(m_storage[i] == item);
  i++;
  }
 return found;
 }

/*- end of CTa_vector_storage implementation :	-*/

/*
typedef CTa_vector_storage <extern class CTa_pe> PEs;
typedef CTa_vector_storage <extern class CTa_layer> LAYERs;
typedef CTa_stack_storage <extern class CTa_layer> CONNECTIONs;
*/

#endif // TA_STORE
