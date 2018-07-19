#ifndef POPUPVFACTORY_H
#define POPUPVFACTORY_H

#include "HMIFrameWork/ViewFactory.h"

class PopUpVFactory : public ViewFactory
{
public:
    PopUpVFactory();

    static PopUpVFactory* Inst();
    void *CreateProduct(int viewId);
private:
    static PopUpVFactory *m_pInst;
};

#endif // POPUPVFACTORY_H
