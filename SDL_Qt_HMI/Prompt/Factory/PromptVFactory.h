#ifndef PROMPTVFACTORY_H
#define PROMPTVFACTORY_H

#include "HMIFrameWork/ViewFactory.h"

class PromptVFactory : public ViewFactory
{
public:
    PromptVFactory();

    static PromptVFactory* Inst();
    void *CreateProduct(int viewId);
private:
    static PromptVFactory *m_pInst;
};

#endif // PROMPTVFACTORY_H
