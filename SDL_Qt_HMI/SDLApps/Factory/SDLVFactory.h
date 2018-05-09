#ifndef SDLVFACTORY_H
#define SDLVFACTORY_H
#include "HMIFrameWork/ViewFactory.h"
class SDLVFactory:public ViewFactory
{
public:
    SDLVFactory();

    static SDLVFactory* Inst();
    void *CreateProduct(int viewId);
private:
    static SDLVFactory *m_pInst;
};

#endif // SDLVFACTORY_H
