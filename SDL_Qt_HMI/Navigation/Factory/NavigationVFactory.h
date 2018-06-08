#ifndef NAVIGATIONVFACTORY_H
#define NAVIGATIONVFACTORY_H

#include "HMIFrameWork/ViewFactory.h"

class NavigationVFactory : public ViewFactory
{
public:
    NavigationVFactory();

    static NavigationVFactory* Inst();
    void *CreateProduct(int viewId);
private:
    static NavigationVFactory *m_pInst;
};

#endif // NAVIGATIONVFACTORY_H
