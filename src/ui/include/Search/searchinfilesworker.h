#ifndef SEARCHINFILESWORKER_H
#define SEARCHINFILESWORKER_H

#include <QObject>
#include <QMutex>
#include "include/Search/filesearchresult.h"
#include "include/Search/searchhelpers.h"

class SearchInFilesWorker : public QObject
{
    Q_OBJECT
public:
    explicit SearchInFilesWorker(const QString &string, const QString &path, const QStringList &filters, const SearchHelpers::SearchMode &searchMode, const SearchHelpers::SearchOptions &searchOptions);
    ~SearchInFilesWorker();

    FileSearchResult::SearchResult getResult();

signals:
    void finished(bool stopped);
    void error(QString string);
    void progress(QString file);

public slots:
    void run();
    void stop();

private:
    QString m_string;
    QString m_path;
    QStringList m_filters;
    SearchHelpers::SearchMode m_searchMode;
    SearchHelpers::SearchOptions m_searchOptions;
    FileSearchResult::SearchResult m_result;
    QMutex m_resultMutex;
    bool m_stop = false;
    QMutex m_stopMutex;
    FileSearchResult::Result buildResult(const QRegularExpressionMatch &match, QString *content);
};

#endif // SEARCHINFILESWORKER_H
