#ifndef HOMEVFACTORY_H
#define HOMEVFACTORY_H
#include "HMIFrameWork/ViewFactory.h"
class HomeVFactory : public ViewFactory
{
public:
    HomeVFactory();

    static HomeVFactory* Inst();
    void *CreateProduct(int viewId);
private:
    static HomeVFactory *m_pInst;
};

#endif // HOMEVFACTORY_H
