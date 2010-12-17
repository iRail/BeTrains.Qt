//
// Configuration
//

// Includes
#include "vehiclecontroller.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

VehicleController::VehicleController(CachedAPI* iAPI, QWidget* iParent) : GenericController(iAPI, iParent)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    setView(new VehicleView());
    connect(view(), SIGNAL(downloadStations()), this, SLOT(_downloadStations()));
    connect(view(), SIGNAL(downloadVehicle(QString)), this, SLOT(_downloadVehicle(QString)));
}

VehicleController::~VehicleController()
{
    qDebug() << "~ " << Q_FUNC_INFO;

    delete view();
}


//
// Generic interface
//

VehicleView* VehicleController::view() const
{
    return mView;
}

void VehicleController::setView(GenericView* iView)
{
    mView = dynamic_cast<VehicleView*>(iView);
}

void VehicleController::showView(GenericController* parent, Connection::Line iConnectionLine)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    GenericController::showView(parent);
    view()->load(iConnectionLine);
}


//
// View slots
//

void VehicleController::_downloadStations()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    connect(api(), SIGNAL(replyStations(QMap<QString, StationPointer>*, QDateTime)), this, SLOT(gotStations(QMap<QString, StationPointer>*, QDateTime)));

    bool tCached;
    api()->requestStations(tCached);
    if (!tCached)
        view()->showProgress();
}

void VehicleController::_downloadVehicle(QString iVehicleId)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    connect(api(), SIGNAL(replyVehicle(VehiclePointer*, QDateTime)), this, SLOT(gotVehicle(VehiclePointer*, QDateTime)));

    bool tCached;
    api()->requestVehicle(iVehicleId, tCached);
    if (!tCached)
        view()->showProgress();
}


//
// Internal slots
//

void VehicleController::gotStations(QMap<QString, StationPointer>* iStations, QDateTime iTimestamp)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    disconnect(api(), SIGNAL(replyStations(QMap<QString, StationPointer>*, QDateTime)), this, SLOT(gotStations(QMap<QString, StationPointer>*, QDateTime)));
    if (iStations != 0)
        view()->setStations(iStations);
    else
        view()->showError( api()->hasError() ? api()->errorString() : tr("unknown error") );
}

void VehicleController::gotVehicle(VehiclePointer* iVehicle, QDateTime iTimestamp)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    disconnect(api(), SIGNAL(replyVehicle(VehiclePointer*, QDateTime)), this, SLOT(gotVehicle(VehiclePointer*, QDateTime)));
    if (iVehicle != 0)
        view()->setVehicle(iVehicle);
    else
        view()->showError( api()->hasError() ? api()->errorString() : tr("unknown error") );
}
