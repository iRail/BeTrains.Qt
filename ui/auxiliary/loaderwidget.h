/*
 *
 *  Copyright (c) 2010 Zagaia (INdT - Instituto Nokia de Tecnologia/
 *       FUCAPI - Fundação Centro de Análise, Pesquisa e Inovação Tecnológica)
 *
 *  This file is part of TweeGo.
 *
 *  TweeGo is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  TweeGo is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with TweeGo. If not, see <http://www.gnu.org/licenses/>
 *
 */

#ifndef LOADER_H
#define LOADER_H

#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QParallelAnimationGroup>
#include <QtCore/QPropertyAnimation>

#include <QtGui/QPainter>
#include <QtGui/QGraphicsPixmapItem>
#include <QtGui/QGraphicsRectItem>


#include "ui/auxiliary/animationwidget.h"
#include "ui/auxiliary/animationrectitem.h"

/*!
 * \class LoaderWidget
 *
 * \brief A generic loader object to be displayed
 * whenever waiting for an event.
 */
class LoaderWidget : public AnimationWidget
{
    Q_OBJECT

public:
    LoaderWidget(QGraphicsWidget *parent = 0);
    ~LoaderWidget();

private:
    void setEntryAnimation(void);
    void setExitAnimation(void);

    QParallelAnimationGroup *_entryAnimation;
    QParallelAnimationGroup *_exitAnimation;
    QPropertyAnimation *_animRotate;
    QPropertyAnimation *_animPosition;
    QPropertyAnimation *_animOpacity;
    QPropertyAnimation *_animBackgroundOpacity;

signals:
    void finished(void);

public slots:
    void startEntryAnimation(void);
    void startExitAnimation(void);

private:
    AnimationRectItem *_background;
    AnimationWidget *_image;
};

#endif // LOADER_H
