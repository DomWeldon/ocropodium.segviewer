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


#ifndef OCROPUSTHREAD_H
#define OCROPUSTHREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QDebug>
#include <QImage>
#include <QColor>
#include <QString>
#include <QPainter>

#include <iulib.h>
#include <colib/colib.h>
#include <ocr-layout-rast.h>
#include <ocrinterfaces.h>



class OcropusThread : public QThread
{
Q_OBJECT
public:
    explicit OcropusThread(QObject *parent = 0);
    ~OcropusThread();

    void createGrouper(QImage image);
    void extractLineRects(colib::intarray& in, QImage* image);
    void extractParagraphRects(colib::intarray& in, QImage* image);
    void drawRectArray(colib::rectarray& rects, QImage* image, QColor color);

public slots:
    void segmentImage(QImage* image, const QString imagepath, const QString segtype);


protected:
    void run();    

signals:
    void workerStatus(const QString& status);
    void doneImage();


private:
    QString m_segtype;
    QString m_imagepath;


};

#endif // OCROPUSTHREAD_H
