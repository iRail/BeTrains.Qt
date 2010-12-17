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
#include <QVBoxLayout>
#include <QModelIndex>
#include <QLineEdit>
#include <QLabel>
#include <QListView>
#include <QStandardItemModel>
#include <QPushButton>

namespace iRail
{
    class LiveboardView : public GenericView
    {

    Q_OBJECT
    public:
        LiveboardView();

        // UI events
    private slots:
        void do_btnStations_clicked();
        void do_lstDepartures_activated(QModelIndex iIndex);
        void do_btnMore_clicked();

        // Controller actions
    public slots:
        void reset();
        void load();
        void load(LiveboardRequestPointer iLiveboardRequest);
        void setStations(QMap<QString, StationPointer>* iStations);
        void setLiveboard(LiveboardPointer* iLiveboard);

        // Controller signals
    signals:
        void downloadStations();
        void downloadLiveboard(LiveboardRequestPointer iLiveboardRequest);
        void launchVehicle(QString iStationId, Liveboard::Departure iLiveboardDeparture);

    private:
        // Member data
        QMap<QString, StationPointer> mStations;
        QList<Liveboard::Departure> mDepartures;
        LiveboardRequestPointer tLiveboardRequest;

        // UI Members
        QLineEdit *mUIStationEdit;
        QPushButton *mUIStationButton;
        QLabel *mViewDummy;
        QWidget *mViewHeader;
        QListView *mView;
        QStandardItemModel *mModel;

        // Initialization
        void init_ui();

        // Auxiliary
        void populateModel();
    };
}

#endif // LIVEBOARDVIEW_H
