//
// Configuration
//

// Includes
#include "genericcontroller.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

GenericController::GenericController(CachedAPI* iAPI, QWidget* iParent) : mAPI(iAPI)
{
    qDebug() << "+ " << Q_FUNC_INFO;
}


//
// Application actions
//

void GenericController::showView(GenericController* parent)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    if (parent != 0)
    {
        view()->setParent(parent->view());
        view()->setWindowFlags(view()->windowFlags() | Qt::Window);
    }

    view()->reset();
    view()->show();
}


//
// Auxiliary
//

CachedAPI* GenericController::api() const
{
    return mAPI;
}
