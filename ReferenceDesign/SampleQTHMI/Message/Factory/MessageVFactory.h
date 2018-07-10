#ifndef MESSAGEVFACTORY_H
#define MESSAGEVFACTORY_H
#include "HMIFrameWork/ViewFactory.h"
class MessageVFactory : public ViewFactory
{
public:
    MessageVFactory();

    static MessageVFactory* Inst();
    void *CreateProduct(int viewId);
private:
    static MessageVFactory *m_pInst;
};

#endif // MESSAGEVFACTORY_H
