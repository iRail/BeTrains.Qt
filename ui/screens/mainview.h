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
#include "ui/global.h"
#include <QObject>
#include <QScrollArea>
#include <QListView>
#include <QStandardItem>
#include <QModelIndex>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace iRail
{
    class MainView : public GenericView
    {

    Q_OBJECT
    public:
        MainView();

        // Controller actions
    public slots:
        void reset();
        void load();
        void load(const QMap<QString, StationPointer>& iStations);
        void load(const QList<QVariant>& iHistory, const QList<QVariant>& iFavourites);
        void setStations(QMap<QString, StationPointer>* iStations);

        // Controller signals
    signals:
        void downloadStations();
        void getHistoryFavourites();
        void launchLiveboard();
        void launchLiveboard(LiveboardRequestPointer iLiveboardRequest);
        void launchRequest();
        void launchConnection(ConnectionRequestPointer iConnectionRequest);
        void addFavourite(QVariant iRequest);
        void removeFavourite(QVariant iRequest);
        void clearHistory();

        // UI events
    private slots:
        void do_lstHistory_activated(QModelIndex iIndex);
        void do_actAbout_triggered();
        void do_lstHistory_contextMenu(const QPoint& iPosition);
        void do_actRemoveFavourite();
        void do_actAddFavourite();
        void do_actClearHistory_triggered();

    private:
        // Member data
        QMap<QString, StationPointer> mStations;

        // UI members
        QLabel *mViewDummy;
        QListView *mView;
        QWidget *mViewHeader;
        QStandardItemModel *mModel;

        // Initialization
        void init_ui();
        void init_menu();

        // Auxiliary
        void populateModel(const QList<QVariant>& iHistory, const QList<QVariant>& iFavourites);
    };
}

#endif // MAINVIEW_H
