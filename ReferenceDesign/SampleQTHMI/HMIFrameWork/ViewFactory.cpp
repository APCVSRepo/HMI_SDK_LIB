#include "ViewFactory.h"

ViewFactory::ViewFactory()
{
}

void* ViewFactory::CreateProduct(int viewId)
{
    C_CXX_UNUSED(viewId)
    return NULL;
}
