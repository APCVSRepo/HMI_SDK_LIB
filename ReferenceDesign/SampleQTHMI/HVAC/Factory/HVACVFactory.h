#ifndef HVACVFACTORY_H
#define HVACVFACTORY_H
#include "HMIFrameWork/ViewFactory.h"
class HVACVFactory : public ViewFactory
{
public:
    HVACVFactory();

    static HVACVFactory* Inst();
    void *CreateProduct(int viewId);
private:
    static HVACVFactory *m_pInst;
};

#endif // HVACVFACTORY_H
