// Copyright 2010 King's College London
// or its licensors, as applicable.
//
// You may not use this file except under the terms of the accompanying license.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you
// may not use this file except in compliance with the License. You may
// obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "imageview.h"

ImageView::ImageView(QWidget *parent) :
    QWidget(parent),
    m_image(new QImage()),
    m_scale(1.0)
{
}

ImageView::~ImageView()
{
    delete m_image;
}

QImage* ImageView::image()
{
    return m_image;
}

qreal ImageView::scale()
{
    return m_scale;
}

void ImageView::setImage(QImage& image)
{    
    *m_image = image;
    updateSize();
}

void ImageView::setScale(qreal scale)
{
    m_scale = scale;
    updateSize();
}

void ImageView::updateSize()
{
    resize(m_image->size() * m_scale);
}

QSize ImageView::sizeHint()
{
    m_image->size() * m_scale;
}

void ImageView::paintEvent(QPaintEvent * event)
{
    QPainter painter;
    painter.begin(this);
    painter.scale(m_scale, m_scale);

    QRect exposedrect = painter.matrix()
                        .inverted()
                        .mapRect(event->rect())
                        .adjusted(-1, -1, 1, 1);
    painter.drawImage(exposedrect, *m_image, exposedrect);
    painter.end();
}
