//
// Configuration
//

// Includes
#include "connectioncontroller.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

ConnectionController::ConnectionController(CachedAPI* iAPI, QWidget* iParent) : GenericController(iAPI, iParent)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    setView(new ConnectionView());
    connect(view(), SIGNAL(downloadStations()), this, SLOT(_downloadStations()));
    connect(view(), SIGNAL(downloadConnections(ConnectionRequestPointer)), this, SLOT(_downloadConnections(ConnectionRequestPointer)));
    connect(view(), SIGNAL(launchVehicle(Connection::Line)), this, SIGNAL(launchVehicle(Connection::Line)));
}

ConnectionController::~ConnectionController()
{
    qDebug() << "~ " << Q_FUNC_INFO;

    delete view();
}


//
// Generic interface
//

ConnectionView* ConnectionController::view() const
{
    return mView;
}

void ConnectionController::setView(GenericView* iView)
{
    mView = dynamic_cast<ConnectionView*>(iView);
}

void ConnectionController::showView(GenericController* parent, ConnectionRequestPointer iConnectionRequest)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    GenericController::showView(parent);
    view()->load(iConnectionRequest);
}


//
// View slots
//

void ConnectionController::_downloadStations()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    connect(api(), SIGNAL(replyStations(QMap<QString, StationPointer>*, QDateTime)), this, SLOT(gotStations(QMap<QString, StationPointer>*, QDateTime)));

    bool tCached;
    api()->requestStations(tCached);
    if (!tCached)
        view()->showProgress();
}

void ConnectionController::_downloadConnections(ConnectionRequestPointer iConnectionRequest)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    connect(api(), SIGNAL(replyConnections(QList<ConnectionPointer>*, QDateTime)), this, SLOT(gotConnections(QList<ConnectionPointer>*, QDateTime)));

    bool tCached;
    api()->requestConnections(iConnectionRequest, tCached);
    if (!tCached)
        view()->showProgress();
}


//
// Internal slots
//

void ConnectionController::gotStations(QMap<QString, StationPointer>* iStations, QDateTime iTimestamp)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    disconnect(api(), SIGNAL(replyStations(QMap<QString, StationPointer>*, QDateTime)), this, SLOT(gotStations(QMap<QString, StationPointer>*, QDateTime)));
    if (iStations != 0)
        view()->setStations(iStations);
    else
        view()->showError( api()->hasError() ? api()->errorString() : tr("unknown error") );
}

void ConnectionController::gotConnections(QList<ConnectionPointer>* iConnections, QDateTime iTimestamp)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    disconnect(api(), SIGNAL(replyConnections(QList<ConnectionPointer>*, QDateTime)), this, SLOT(gotConnections(QList<ConnectionPointer>*, QDateTime)));
    if (iConnections != 0)
        view()->setConnections(iConnections);
    else
        view()->showError( api()->hasError() ? api()->errorString() : tr("unknown error") );
}
