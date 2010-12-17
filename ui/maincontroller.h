//
// Configuration
//

// Include guard
#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

// Includes
#include <QDebug>
#include "ui/global.h"
#include "cachedapi.h"
#include "api/connectionrequest.h"
#include "mainview.h"
#include <QList>
#include <QMap>
#include "genericcontroller.h"


namespace iRail
{
    class MainController : public GenericController
    {
    Q_OBJECT
    public:
        explicit MainController(CachedAPI* iAPI, QWidget *parent = 0);
        ~MainController();

        // Generic interface
        MainView* view() const;
        void setView(GenericView*);
        void showView(GenericController* parent = 0);
        void addHistory(QVariant iRequest);

        // View slots
    private slots:
        void _downloadStations();
        void _getHistoryFavourites();
        void _addFavourite(QVariant iRequest);
        void _removeFavourite(QVariant iRequest);
        void _clearHistory();

        // Internal slots
    private slots:
        void gotStations(QMap<QString, StationPointer>* iStations, QDateTime iTimestamp);

        // Signals
    signals:
        void launchLiveboard();
        void launchLiveboard(LiveboardRequestPointer iLiveboardRequest);
        void launchRequest();
        void launchConnection(ConnectionRequestPointer iConnectionRequest);

    private:
        // Member data
        MainView* mView;
        QList<QVariant> mHistory, mFavourites;
    };
}

#endif // MAINCONTROLLER_H
