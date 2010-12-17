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

#include "loaderwidget.h"
#include "ui/auxiliary/graphicsrectobject.h"

/*!
 * \brief Loader constructor.
 */
LoaderWidget::LoaderWidget(QGraphicsWidget *parent)
        : AnimationWidget(parent)
{
    _background = new AnimationRectItem(QRect(0, 0, 800, 420), this);
    _background->setBrush(Qt::black);
    _background->setOpacity(0.0);

    _image = new AnimationWidget(this);
    _image->setZValue(1.0);
    // This is necessary to set loader image center used by rotate function
    _image->setTransformOriginPoint(QPointF(18, 18));

    QGraphicsPixmapItem *img = new QGraphicsPixmapItem(_image);
    img->setPixmap(QPixmap(":ui/assets/loader.png"));
    img->setCacheMode(DeviceCoordinateCache);
    img->setTransformationMode(Qt::SmoothTransformation);

    _entryAnimation = 0;
    _exitAnimation = 0;
}

/*!
 * \brief Loader destructor.
 */
LoaderWidget::~LoaderWidget()
{
    if (_entryAnimation) {
        delete _entryAnimation;
    }
    if (_exitAnimation) {
        delete _exitAnimation;
    }
    if (_image) {
        delete _image;
    }
    qDebug() << "~ " << Q_FUNC_INFO;
}

/*!
 * \brief Starts the Entry animation. Loader image
 * is shown going UP.
 */
void LoaderWidget::startEntryAnimation(void)
{
    qDebug() << "+ " << Q_FUNC_INFO;
    if (_entryAnimation && _entryAnimation->state() == QPropertyAnimation::Running)
        return;

    setEntryAnimation();
    _entryAnimation->start();
}

/*!
 * \brief Creates the Entry animation group.
 */
void LoaderWidget::setEntryAnimation(void)
{
    /* Rotation */
    _animRotate = new QPropertyAnimation();
    _animRotate->setTargetObject(_image);
    _animRotate->setPropertyName("rotation");
    _animRotate->setStartValue(0.0);
    _animRotate->setEndValue(360.0);
    _animRotate->setDuration(400);
    _animRotate->setEasingCurve(QEasingCurve::Linear);
    _animRotate->setLoopCount(-1);  // Loop until stopped

    /* Position */
    _animPosition = new QPropertyAnimation();
    _animPosition->setTargetObject(_image);
    _animPosition->setPropertyName("pos");
    _animPosition->setStartValue(QPointF(400, 421));
    _animPosition->setEndValue(QPointF(400, 325));
    _animPosition->setDuration(500);
    _animPosition->setEasingCurve(QEasingCurve::Linear);

    /* Opacity */
    _animOpacity = new QPropertyAnimation();
    _animOpacity->setTargetObject(_image);
    _animOpacity->setPropertyName("opacity");
    _animOpacity->setStartValue(0.0);
    _animOpacity->setEndValue(1.0);
    _animOpacity->setDuration(500);
    _animOpacity->setEasingCurve(QEasingCurve::Linear);

    /* Background opacity */
    _animBackgroundOpacity = new QPropertyAnimation();
    _animBackgroundOpacity->setTargetObject(_background);
    _animBackgroundOpacity->setPropertyName("opacity");
    _animBackgroundOpacity->setStartValue(0.0);
    _animBackgroundOpacity->setEndValue(0.6);
    _animBackgroundOpacity->setDuration(500);
    _animBackgroundOpacity->setEasingCurve(QEasingCurve::Linear);

    /* Adding the animations to the group */
    _entryAnimation = new QParallelAnimationGroup(this);
    _entryAnimation->addAnimation(_animRotate);
    _entryAnimation->addAnimation(_animPosition);
    _entryAnimation->addAnimation(_animOpacity);
    _entryAnimation->addAnimation(_animBackgroundOpacity);
}

/*!
 * \brief Starts the Exit animation. Loader image
 * is shown going DOWN.
 */
void LoaderWidget::startExitAnimation(void)
{
    qDebug() << "+ " << Q_FUNC_INFO;
    if (_exitAnimation && _exitAnimation->state() == QPropertyAnimation::Running)
        return;

    setExitAnimation();

    /* When the Exit animation stops,
     * the Entry animation also stops. */
    connect(_exitAnimation, SIGNAL(finished()),
            _entryAnimation, SLOT(stop()));

    /* When the Exit animation stops,
     * a finished() signal is emitted. */
    connect(_exitAnimation, SIGNAL(finished()),
            this, SIGNAL(finished()));

    _exitAnimation->start();
}

/*!
 * \brief Creates the Exit animation group.
 */
void LoaderWidget::setExitAnimation(void)
{
    /* Position */
    _animPosition->stop();
    _animPosition->setTargetObject(_image);
    _animPosition->setPropertyName("pos");
    _animPosition->setStartValue(QPointF(400, 325));
    _animPosition->setEndValue(QPointF(400, 221));
    _animPosition->setDuration(500);
    _animPosition->setEasingCurve(QEasingCurve::Linear);

    /* Opacity */
    _animOpacity->stop();
    _animOpacity->setTargetObject(_image);
    _animOpacity->setPropertyName("opacity");
    _animOpacity->setStartValue(1.0);
    _animOpacity->setEndValue(0.0);
    _animOpacity->setDuration(500);
    _animOpacity->setEasingCurve(QEasingCurve::Linear);

    /* Background opacity */
    _animBackgroundOpacity->stop();
    _animBackgroundOpacity->setTargetObject(_background);
    _animBackgroundOpacity->setPropertyName("opacity");
    _animBackgroundOpacity->setStartValue(0.6);
    _animBackgroundOpacity->setEndValue(0.0);
    _animBackgroundOpacity->setDuration(500);
    _animBackgroundOpacity->setEasingCurve(QEasingCurve::Linear);

    _exitAnimation = new QParallelAnimationGroup(this);
    _exitAnimation->addAnimation(_animPosition);
    _exitAnimation->addAnimation(_animOpacity);
    _exitAnimation->addAnimation(_animBackgroundOpacity);
}


