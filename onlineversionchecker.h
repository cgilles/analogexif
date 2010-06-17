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

#ifndef ONLINEVERSIONCHECKER_H
#define ONLINEVERSIONCHECKER_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDateTime>

#include "expat.h"

class VersionFileParser : public QObject
{
	Q_OBJECT

public:
	VersionFileParser(QObject *parent = 0);
	~VersionFileParser();

	bool parse(const QString& xmlData);
	bool parse(const QString& ver, const QString& xmlData);

	QString getVersion() const
	{
		return version;
	}

	QString getPlatform() const
	{
		return platform;
	}

	QDateTime getDate() const
	{
		return QDateTime::fromString(date.simplified(), "hh:mm dd.MM.yyyy");
	}

	QString getDetails() const
	{
		return details;
	}

private:
	// Expat handlers
	static void __cdecl xmlStartElementHandler(void* userData, const XML_Char *name, const XML_Char **atts);
	static void __cdecl xmlEndElementHandler(void* userData, const XML_Char *name);
	static void __cdecl xmlCharacterDataHandler(void *userData, const XML_Char *s, int len);

	XML_Parser xmlParser;
	QString curTag;
	QString lookupPlatform;
	bool found;

	QString version;
	QString platform;
	QString details;
	QString date;
};

class OnlineVersionChecker : public QObject
{
	Q_OBJECT

public:
	OnlineVersionChecker(QObject *parent);

	void checkForNewVersion();

private:
	static const QUrl versionCheckUrl;

	QNetworkAccessManager manager;

	VersionFileParser parser;

	QString selfVersion, selfPlatform;
	QDateTime selfDate;

private slots:
	void downloadFinished(QNetworkReply *reply);

signals:
	void newVersionAvailable(QString newTag, QDateTime newTime, QString newSummary);
};

#endif // ONLINEVERSIONCHECKER_H
