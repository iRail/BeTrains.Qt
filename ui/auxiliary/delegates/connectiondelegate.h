//
// Configuration
//

// Include guard
#ifndef CONNECTIONDELEGATE_H
#define CONNECTIONDELEGATE_H

// Includes
#include <QObject>
#include <QPainter>
#include <QWidget>
#include <QModelIndex>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>
#include <QTreeView>
#include "api/station.h"
#include "api/connection.h"

namespace iRail
{
    class ConnectionDelegate : public QStyledItemDelegate
    {
        Q_OBJECT

    public:
        ConnectionDelegate(const QMap<QString, StationPointer>& iStations, QTreeView *iView, QWidget *parent = 0) : QStyledItemDelegate(parent), mView(iView), mStations(iStations)
        {

        }

        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &iIndex, ConnectionPointer connection) const;
        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &iIndex, Connection::Line line) const;

    private:
        // Member data
        const QMap<QString, StationPointer>& mStations;
        QTreeView* mView;
    };
}

#endif // CONNECTIONDELEGATE_H
