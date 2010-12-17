//
// Configuration
//

// Include guard
#ifndef RequestDelegate_H
#define RequestDelegate_H

// Includes
#include <QObject>
#include <QPainter>
#include <QWidget>
#include <QModelIndex>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>
#include "api/liveboardrequest.h"
#include "api/connectionrequest.h"
#include "api/station.h"

namespace iRail
{
    class RequestDelegate : public QStyledItemDelegate
    {
        Q_OBJECT

    public:
        RequestDelegate(const QMap<QString, StationPointer>& iStations, QWidget *parent = 0) : QStyledItemDelegate(parent), mStations(iStations)
        {

        }

        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &iIndex, ConnectionRequestPointer iConnectionRequest) const;
        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &iIndex, LiveboardRequestPointer iLiveboardRequest) const;
    private:
        // Member data
        const QMap<QString, StationPointer>& mStations;
    };
}

#endif // RequestDelegate_H
