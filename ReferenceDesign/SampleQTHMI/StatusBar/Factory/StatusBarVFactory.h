#ifndef STATUSBARVFACTORY_H
#define STATUSBARVFACTORY_H

#include "HMIFrameWork/ViewFactory.h"

class StatusBarVFactory : public ViewFactory
{
public:
    StatusBarVFactory();

    static StatusBarVFactory* Inst();
    void *CreateProduct(int viewId);
private:
    static StatusBarVFactory *m_pInst;
};

#endif // STATUSBARVFACTORY_H
