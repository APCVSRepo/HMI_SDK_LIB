#ifndef VIEWFACTORY_H
#define VIEWFACTORY_H
#include "Interface.h"
class ViewFactory:public IViewFactory
{
public:
    ViewFactory();
    virtual void* CreateProduct(int viewId);
};

#endif // VIEWFACTORY_H
