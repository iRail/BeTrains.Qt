//
// Configuration
//

// Include guard
#ifndef CONNECTIONVIEW_H
#define CONNECTIONVIEW_H

// Inclused
#include <QDebug>
#include "api/connection.h"
#include "api/connectionrequest.h"
#include "genericview.h"
#include <QVBoxLayout>
#include <QModelIndex>
#include <QTreeView>
#include <QStandardItemModel>

namespace iRail
{
    class ConnectionView : public GenericView
    {

    Q_OBJECT
    public:
        ConnectionView();

        // Temporary data
        QList<ConnectionPointer>* tConnections;

        // UI events
    private slots:
        void do_lstConnections_activated(QModelIndex iIndex);

        // Controller actions
    public slots:
        void reset();
        void load(ConnectionRequestPointer iConnectionRequest);
        void setStations(QMap<QString, StationPointer>* iStations);
        void setConnections(QList<ConnectionPointer>* iConnections);

        // Controller signals
    signals:
        void downloadStations();
        void downloadConnections(ConnectionRequestPointer iConnectionRequest);
        void launchVehicle(Connection::Line iConnectionLine);

    private:
        // Member data
        QMap<QString, StationPointer> mStations;

        // Initialization
        void init_ui();

        // UI members
        QTreeView *mView;
        QStandardItemModel *mModel;

        // Auxiliary
        void populateModel(const QList<ConnectionPointer>& iConnections);
    };
}

#endif // CONNECTIONVIEW_H
