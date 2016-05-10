/*
 *  Written By: Grant Hutchinson
 *  License: GPLv3.
 *  h.g.utchinson@gmail.com
 *  Copyright (C) 2012 by Grant Hutchinson
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "detached.h"
#include <QtNetwork>
#include <QWebHistory>

/*
 *  Constructor
 */
detached::detached(QWidget *parent) : Html5ApplicationViewer(parent)
{
    QWebSettings::globalSettings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

    connect(webView()->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), SLOT(addToJavaScript()));
}

/*
 *  Set the webview to a different URL
 */
void detached::remotePage(QString page){
     QUrl pageUrl(QString("file:///") + QDir::currentPath() + page);
      webView()->load(pageUrl);
}

/*
 *  For debugging purpose, when we need to double check navigation
 */
void detached::displayHistory(){
    QWebHistory *web = webView()->history();
    QList<QWebHistoryItem> items = web->items();
    int size = items.length();
     for(int i =0; i< size; i++){
        qDebug() <<   items.at(i).lastVisited();
        qDebug() <<   items.at(i).url();
     }
}

/*
 *  Add our detached slots to the javascript window, class named 'detched'
 */
void detached::addToJavaScript() {
    webView()->page()->mainFrame()->addToJavaScriptWindowObject("detached", this);
}

/*
 *  Emit that our detached window closed, so we know to open it again
 */
void detached::closeEvent(QCloseEvent *event){
    emit detachClose();
}

/*
 * Destructor
 */
detached::~detached(){
}
