//
// Configuration
//

// Include guard
#ifndef REQUESTCONTROLLER_H
#define REQUESTCONTROLLER_H

// Includes
#include <QDebug>
#include "ui/global.h"
#include "cachedapi.h"
#include "api/connectionrequest.h"
#include "requestview.h"
#include "connectioncontroller.h"
#include <QList>
#include <QMap>
#include "genericcontroller.h"


namespace iRail
{
    class RequestController : public GenericController
    {
    Q_OBJECT
    public:
        explicit RequestController(CachedAPI* iAPI, QWidget *parent = 0);
        ~RequestController();

        // Generic interface
        RequestView* view() const;
        void setView(GenericView*);
        void showView(GenericController* parent);
        void showView(GenericController* parent, ConnectionRequestPointer iInitialRequest);

        // View slots
    private slots:
        void _downloadStations();

        // Signals
    signals:
        void launchConnection(ConnectionRequestPointer iConnectionRequest);

        // Internal slots
    private slots:
        void gotStations(QMap<QString, StationPointer>* iStations, QDateTime iTimestamp);

        // Member data
    private:
        RequestView* mView;
    };
}

#endif // REQUESTCONTROLLER_H
