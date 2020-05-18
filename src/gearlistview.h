/*
	Copyright (C) 2010 C-41 Bytes <contact@c41bytes.com>

	This file is part of AnalogExif.

    AnalogExif is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AnalogExif is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with AnalogExif.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GEARLISTVIEW_H
#define GEARLISTVIEW_H

#include <QListView>
#include <QMouseEvent>

class GearListView : public QListView
{
	Q_OBJECT

public:
	GearListView(QWidget *parent): QListView(parent) { }

signals:
	void focused();

protected:
	virtual void mousePressEvent(QMouseEvent * event)
	{
		QModelIndex clickIndex = indexAt(event->pos());

		QListView::mousePressEvent(event);		

		if(!clickIndex.isValid() && (event->button() != Qt::RightButton))
			clearSelection();
	}
	
	virtual void focusInEvent(QFocusEvent * event)
	{
		QListView::focusInEvent(event);

		emit focused();
	}
};

#endif // GEARLISTVIEW_H
