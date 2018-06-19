#ifndef VRVFACTORY_H
#define VRVFACTORY_H

#include "HMIFrameWork/ViewFactory.h"

class VRVFactory : public ViewFactory
{
public:
    VRVFactory();

    static VRVFactory* Inst();
    void *CreateProduct(int viewId);
private:
    static VRVFactory *m_pInst;
};

#endif // VRVFACTORY_H
