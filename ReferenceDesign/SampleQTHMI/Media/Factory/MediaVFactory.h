#ifndef MEDIAVFACTORY_H
#define MEDIAVFACTORY_H

#include "HMIFrameWork/ViewFactory.h"

class MediaVFactory : public ViewFactory
{
public:
    MediaVFactory();

    static MediaVFactory* Inst();
    void *CreateProduct(int viewId);
private:
    static MediaVFactory *m_pInst;
};

#endif // MEDIAVFACTORY_H
