#ifndef FILTER_H
#define FILTER_H

#include <QGroupBox>

/**
 * @brief Filters base class.
 */
class Filter : public QGroupBox
{
    Q_OBJECT
public:
    Filter(const QString& title, int column, QWidget* parent = nullptr);

    ~Filter() override = default;

    Filter& operator=(const Filter& other) = delete;
    Filter(const Filter& other) = delete;

    Filter& operator=(Filter&& other) = delete;
    Filter(Filter&& other) = delete;

public Q_SLOTS:
    virtual void setChecked(bool checked);

protected:
    int64_t column_;
};

#endif // FILTER_H
