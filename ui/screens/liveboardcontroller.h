//
// Configuration
//

// Include guard
#ifndef LIVEBOARDCONTROLLER_H
#define LIVEBOARDCONTROLLER_H

// Includes
#include <QDebug>
#include "ui/global.h"
#include "cachedapi.h"
#include "liveboardview.h"
#include "vehiclecontroller.h"
#include <QMap>
#include "genericcontroller.h"


namespace iRail
{
    class LiveboardController : public GenericController
    {
    Q_OBJECT
    public:
        explicit LiveboardController(CachedAPI* iAPI, QWidget *parent = 0);
        ~LiveboardController();

        // Generic interface
        LiveboardView* view() const;
        void setView(GenericView*);
        void showView(GenericController* parent);
        void showView(GenericController* parent, LiveboardRequestPointer iLiveboardRequest);

        // View slots
    private slots:
        void _downloadStations();
        void _downloadLiveboard(LiveboardRequestPointer iLiveboardRequest);

        // Signals
    signals:
        void launchVehicle(QString iStationId, Liveboard::Departure iLiveboardDeparture);
        void launchLiveboard(LiveboardRequestPointer);

        // Internal slots
    private slots:
        void gotStations(QMap<QString, StationPointer>* iStations, QDateTime iTimestamp);
        void gotLiveboard(LiveboardPointer* iLiveboard, QDateTime iTimestamp);

    private:
        // Member data
        LiveboardView* mView;
    };
}

#endif // LIVEBOARDCONTROLLER_H
