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

#include "proxythread.h"

ProxyThread::ProxyThread(QObject *parent) :
    QThread(parent)
{
}

ProxyThread::~ProxyThread()
{
    qDebug() << "Deleting Ocropus worker thread...";
    delete m_worker;
}

void ProxyThread::run()
{
    m_worker = new OcropusThread();
    m_worker->start();
    connect(this, SIGNAL(forwardSegmentImage(QImage*,QString,QString)),
            m_worker, SLOT(segmentImage(QImage*,QString,QString)));
    connect(m_worker, SIGNAL(doneImage()),
            this, SLOT(doneImage()));
    connect(m_worker, SIGNAL(workerStatus(QString)),
            this, SLOT(workerStatus(QString)));

    // start the event loop
    exec();
}

void ProxyThread::segmentImage(QImage* image, const QString imagepath, const QString segtype)
{
    emit forwardSegmentImage(image, imagepath, segtype);
}

void ProxyThread::workerStatus(const QString &status)
{
    emit forwardWorkerStatus(status);
}

void ProxyThread::doneImage()
{
    emit forwardDoneImage();
}
