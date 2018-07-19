#ifndef PHONEVFACTORY_H
#define PHONEVFACTORY_H
#include "HMIFrameWork/ViewFactory.h"
class PhoneVFactory : public ViewFactory
{
public:
    PhoneVFactory();

    static PhoneVFactory* Inst();
    void *CreateProduct(int viewId);
private:
    static PhoneVFactory *m_pInst;
};

#endif // PHONEVFACTORY_H
