//
// Configuration
//

// Include guard
#ifndef STATIONCHOOSER_H
#define STATIONCHOOSER_H

// Includes
#include <QDialog>
#include <QMap>
#include <QStandardItemModel>
#include <QListView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "api/station.h"
#include "ui/global.h"
#include "cachedapi.h"

namespace iRail
{
    class StationChooser : public QDialog
    {
    Q_OBJECT
    public:
        explicit StationChooser(const QMap<QString, StationPointer>& iStations, QWidget *iParent);
        QString getSelection();
        ~StationChooser();

        // UI events
    private slots:
        void do_txtFilter_textEdited(QString iText);
        void do_lstStations_activated(QModelIndex iIndex);

    private:
        const QMap<QString, StationPointer>& mStations;
        StationPointer mStation;

        // Initialization
        void init_ui();
        void init_children();

        // UI members
        QListView *mView;
        QLabel *mViewDummy;
        QStandardItemModel *mModel;
        QLineEdit* mFilter;

        // Auxiliary
        void populateModel(QString iPrefix);
    };
}

#endif // STATIONCHOOSER_H
