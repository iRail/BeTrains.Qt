//
// Configuration
//

// Includes
#include "liveboardcontroller.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

LiveboardController::LiveboardController(CachedAPI* iAPI, QWidget* iParent) : GenericController(iAPI, iParent)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    setView(new LiveboardView());
    connect(view(), SIGNAL(downloadStations()), this, SLOT(_downloadStations()));
    connect(view(), SIGNAL(downloadLiveboard(LiveboardRequestPointer)), this, SLOT(_downloadLiveboard(LiveboardRequestPointer)));
    connect(view(), SIGNAL(launchVehicle(QString,Liveboard::Departure)), this, SIGNAL(launchVehicle(QString,Liveboard::Departure)));
}

LiveboardController::~LiveboardController()
{
    qDebug() << "~ " << Q_FUNC_INFO;

    delete view();
}


//
// Generic interface
//

LiveboardView* LiveboardController::view() const
{
    return mView;
}

void LiveboardController::setView(GenericView* iView)
{
    mView = dynamic_cast<LiveboardView*>(iView);
}

void LiveboardController::showView(GenericController* parent)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    GenericController::showView(parent);
    view()->load();
}

void LiveboardController::showView(GenericController* parent, LiveboardRequestPointer iLiveboardRequest)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    GenericController::showView(parent);
    view()->load();
                    // This because the liveboard screen performs two tasks:
                    // forming the request and fetching its data. This means
                    // that using the secondary load bypasses the first
                    // stage, hence we call it manually here.
    view()->load(iLiveboardRequest);
}


//
// View slots
//

void LiveboardController::_downloadStations()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    connect(api(), SIGNAL(replyStations(QMap<QString, StationPointer>*, QDateTime)), this, SLOT(gotStations(QMap<QString, StationPointer>*, QDateTime)));

    bool tCached;
    api()->requestStations(tCached);
    if (!tCached)
        view()->showProgress();
}

void LiveboardController::_downloadLiveboard(LiveboardRequestPointer iLiveboardRequest)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    // Manage history (but skip timed requests, from the "More" button)
    if (! iLiveboardRequest->timed())
        emit launchLiveboard(iLiveboardRequest);

    connect(api(), SIGNAL(replyLiveboard(LiveboardPointer*, QDateTime)), this, SLOT(gotLiveboard(LiveboardPointer*, QDateTime)));

    bool tCached;
    api()->requestLiveboard(iLiveboardRequest, tCached);
    if (!tCached)
        view()->showProgress();
}


//
// Internal slots
//

void LiveboardController::gotStations(QMap<QString, StationPointer>* iStations, QDateTime iTimestamp)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    disconnect(api(), SIGNAL(replyStations(QMap<QString, StationPointer>*, QDateTime)), this, SLOT(gotStations(QMap<QString, StationPointer>*, QDateTime)));
    if (iStations != 0)
        view()->setStations(iStations);
    else
        view()->showError( api()->hasError() ? api()->errorString() : tr("unknown error") );
}

void LiveboardController::gotLiveboard(LiveboardPointer* iLiveboard, QDateTime iTimestamp)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    disconnect(api(), SIGNAL(replyLiveboard(LiveboardPointer*, QDateTime)), this, SLOT(gotLiveboard(LiveboardPointer*, QDateTime)));
    if (iLiveboard != 0)
        view()->setLiveboard(iLiveboard);
    else
        view()->showError( api()->hasError() ? api()->errorString() : tr("unknown error") );
}
