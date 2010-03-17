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

#ifndef PROXYTHREAD_H
#define PROXYTHREAD_H

#include <QThread>
#include <QImage>

#include <ocropusthread.h>


class ProxyThread : public QThread
{
Q_OBJECT
public:
    explicit ProxyThread(QObject *parent = 0);
    ~ProxyThread();

protected:
    void run();

public slots:
    void segmentImage(QImage* image, const QString imagepath, const QString segtype);
    void workerStatus(const QString& status);
    void doneImage();

signals:    
    void forwardSegmentImage(QImage* image, const QString imagepath, const QString segtype);
    void forwardWorkerStatus(const QString& status);
    void forwardDoneImage();

private:
    OcropusThread* m_worker;

};

#endif // PROXYTHREAD_H
