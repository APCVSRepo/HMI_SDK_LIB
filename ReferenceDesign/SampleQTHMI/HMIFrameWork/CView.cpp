#include "CView.h"

CView::CView(int viewId)
    :m_iViewId(viewId)
    ,m_pView(NULL)
    ,m_state(eViewStatus_Inactive)

{

}

CView::~CView()
{

}


void CView::setView(void *view)
{
    m_pView = view;
}

int CView::getViewId()
{
    return m_iViewId;
}

void CView::viewAction(int state)
{
    C_CXX_UNUSED(state)
}

void *CView::getView()
{
    return m_pView;
}

void CView::setState(int state)
{
    m_state = state;
}

int CView::getState()
{
    return m_state;
}
