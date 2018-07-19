#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H
#include "Interface.h"
class CView:IView
{
public:
    CView(int viewId);
    virtual ~CView();
    virtual void setView(void* view);
    virtual int getViewId();
    virtual void viewAction(int state);
    virtual void* getView();
    virtual void setState(int state);
    virtual int getState();
private:
    int m_iViewId;
    void* m_pView;
    int m_state;

};

#endif // VIEWMANAGER_H
