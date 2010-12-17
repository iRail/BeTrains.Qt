//
// Configuration
//

// Include guard
#ifndef REQUESTVIEW_H
#define REQUESTVIEW_H

// Inclused
#include <QDebug>
#include "api/connection.h"
#include "api/connectionrequest.h"
#include "api/vehicle.h"
#include "api/liveboard.h"
#include "ui/global.h"
#include "genericview.h"
#include <QScrollArea>
#include <QListView>
#include <QStandardItem>
#include <QModelIndex>
#include <QLabel>
#include <QRadioButton>
#include <QLineEdit>
#include <QButtonGroup>
#include <QtMaemo5/QMaemo5DatePickSelector>
#include <QtMaemo5/QMaemo5TimePickSelector>
#include <QtMaemo5/QMaemo5ValueButton>

namespace iRail
{
    class RequestView : public GenericView
    {

    Q_OBJECT
    public:
        RequestView();

        // UI events
    private slots:
        void do_btnDatetime_clicked(bool iUseDatetime);
        void do_btnSearch_clicked();
        void do_btnNow_clicked();
        void do_btnClear_clicked();
        void do_btnTo_clicked();
        void do_btnFrom_clicked();
        void do_btnSwap_clicked();

        // Controller actions
    public slots:
        void reset();
        void load();
        void load(ConnectionRequestPointer iConnectionRequest);
        void setStations(QMap<QString, StationPointer>* iStations);

        // Controller signals
    signals:
        void downloadStations();
        void launchConnection(ConnectionRequestPointer iConnectionRequest);

        // Member data
    private:
        QMap<QString, StationPointer> mStations;

        // Temporary data
        QLineEdit *tTarget;

        // Initialization
        void init_ui();

        // UI members
        QPushButton *mUIFromButton, *mUIToButton;
        QLineEdit *mUIFromLine, *mUIToLine;
        QMaemo5ValueButton *mUIDate, *mUITime;
        QMaemo5DatePickSelector *mUIDatePicker;
        QMaemo5TimePickSelector *mUITimePicker;
        QRadioButton *mUIUseTime, *mUITypeDeparture, *mUITypeArrival;
    };
}

#endif // REQUESTVIEW_H
