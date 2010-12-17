//
// Configuration
//

// Includes
#include "maincontroller.h"
#include "application.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

MainController::MainController(CachedAPI* iAPI, QWidget* iParent) : GenericController(iAPI, iParent)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    setView(new MainView());
    connect(view(), SIGNAL(downloadStations()), this, SLOT(_downloadStations()));
    connect(view(), SIGNAL(getHistoryFavourites()), this, SLOT(_getHistoryFavourites()));
    connect(view(), SIGNAL(launchLiveboard()), this, SIGNAL(launchLiveboard()));
    connect(view(), SIGNAL(launchLiveboard(LiveboardRequestPointer)), this, SIGNAL(launchLiveboard(LiveboardRequestPointer)));
    connect(view(), SIGNAL(launchRequest()), this, SIGNAL(launchRequest()));
    connect(view(), SIGNAL(launchConnection(ConnectionRequestPointer)), this, SIGNAL(launchConnection(ConnectionRequestPointer)));
    connect(view(), SIGNAL(addFavourite(QVariant)), this, SLOT(_addFavourite(QVariant)));
    connect(view(), SIGNAL(removeFavourite(QVariant)), this, SLOT(_removeFavourite(QVariant)));
    connect(view(), SIGNAL(clearHistory()), this, SLOT(_clearHistory()));
}

MainController::~MainController()
{
    qDebug() << "~ " << Q_FUNC_INFO;

    delete view();
}


//
// Generic interface
//

MainView* MainController::view() const
{
    return mView;
}

void MainController::setView(GenericView* iView)
{
    mView = dynamic_cast<MainView*>(iView);
}

void MainController::showView(GenericController* parent)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    GenericController::showView(parent);
    view()->load();
}

void MainController::addHistory(QVariant iRequest)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    mHistory.push_front(iRequest);

    Application::storage()->setHistory(mHistory);

    view()->load(mHistory, mFavourites);
}


//
// View slots
//

void MainController::_downloadStations()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    connect(api(), SIGNAL(replyStations(QMap<QString, StationPointer>*, QDateTime)), this, SLOT(gotStations(QMap<QString, StationPointer>*, QDateTime)));

    bool tCached;
    api()->requestStations(tCached);
    if (!tCached)
        view()->showProgress();
}

void MainController::_getHistoryFavourites()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    mHistory = Application::storage()->history();
    mFavourites = Application::storage()->favourites();

    view()->load(mHistory, mFavourites);

}

void MainController::_addFavourite(QVariant iRequest)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    mFavourites.push_back(iRequest);
    mHistory.removeOne(iRequest);

    Application::storage()->setHistory(mHistory);
    Application::storage()->setFavourites(mFavourites);

    view()->load(mHistory, mFavourites);
}

void MainController::_removeFavourite(QVariant iRequest)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    mFavourites.removeOne(iRequest);

    Application::storage()->setFavourites(mFavourites);

    view()->load(mHistory, mFavourites);
}

void MainController::_clearHistory()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    mHistory.clear();

    Application::storage()->clearHistory();

    view()->load(mHistory, mFavourites);
}



//
// Internal slots
//

void MainController::gotStations(QMap<QString, StationPointer>* iStations, QDateTime iTimestamp)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    disconnect(api(), SIGNAL(replyStations(QMap<QString, StationPointer>*, QDateTime)), this, SLOT(gotStations(QMap<QString, StationPointer>*, QDateTime)));
    if (iStations != 0)
        view()->setStations(iStations);
    else
        view()->showError( api()->hasError() ? api()->errorString() : tr("unknown error") );
}
