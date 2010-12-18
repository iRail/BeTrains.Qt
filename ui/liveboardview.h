//
// Configuration
//

// Include guard
#ifndef LIVEBOARDVIEW_H
#define LIVEBOARDVIEW_H

// Inclused
#include <QDebug>
#include "genericview.h"
#include "api/vehicle.h"
#include "api/liveboardrequest.h"
#include "api/liveboard.h"

namespace iRail
{
    class LiveboardView : public GenericView
    {
    Q_OBJECT
        // Controller actions
    public slots:
        virtual void reset() = 0;
        virtual void load() = 0;
        virtual void load(LiveboardRequestPointer iLiveboardRequest) = 0;
        virtual void setStations(QMap<QString, StationPointer>* iStations) = 0;
        virtual void setLiveboard(LiveboardPointer* iLiveboard) = 0;

        // Controller signals
    signals:
        void downloadStations();
        void downloadLiveboard(LiveboardRequestPointer iLiveboardRequest);
        void launchVehicle(QString iStationId, Liveboard::Departure iLiveboardDeparture);
    };
}

#endif // LIVEBOARDVIEW_H
