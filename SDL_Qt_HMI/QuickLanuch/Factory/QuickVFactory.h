#ifndef QUICKVFACTORY_H
#define QUICKVFACTORY_H
#include "HMIFrameWork/ViewFactory.h"
class QuickVFactory:public ViewFactory
{
public:
    QuickVFactory();
    static QuickVFactory* Inst();
    void *CreateProduct(int viewId);
private:
    static QuickVFactory *m_pInst;
};

#endif // QUICKVFACTORY_H
