//
// Configuration
//

// Include guard
#ifndef MAINVIEW_H
#define MAINVIEW_H

// Inclused
#include <QDebug>
#include "api/connection.h"
#include "api/connectionrequest.h"
#include "api/vehicle.h"
#include "api/liveboard.h"
#include "api/liveboardrequest.h"
#include "genericview.h"

namespace iRail
{
    class MainView : public GenericView
    {
    Q_OBJECT
        // Controller actions
    public slots:
        virtual void reset() = 0;
        virtual void load() = 0;
        virtual void setHistoryFavourites(const QList<QVariant>& iHistory, const QList<QVariant>& iFavourites) = 0;
        virtual void setStations(QMap<QString, StationPointer>* iStations) = 0;

        // Controller signals
    signals:
        void downloadStations();
        void getHistoryFavourites();
        void launchLiveboard();
        void launchLiveboardWithRequest(LiveboardRequestPointer iLiveboardRequest);
        void launchRequest();
        void launchConnection(ConnectionRequestPointer iConnectionRequest);
        void addFavourite(QVariant iRequest);
        void removeFavourite(QVariant iRequest);
        void clearHistory();
    };
}

#endif // MAINVIEW_H
