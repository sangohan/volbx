#ifndef FILTERNUMBERS_H
#define FILTERNUMBERS_H

#include <QWidget>

#include "Filter.h"

class DoubleSlider;

namespace Ui
{
class FilterNumbers;
} // namespace Ui

/**
 * @brief Numbers filter for value type columns in model.
 */
class FilterNumbers : public Filter
{
    Q_OBJECT
public:
    FilterNumbers(const QString& name,
                  int column,
                  double min,
                  double max,
                  QWidget* parent = nullptr);

    ~FilterNumbers() override;

    FilterNumbers& operator=(const FilterNumbers& other) = delete;
    FilterNumbers(const FilterNumbers& other) = delete;

    FilterNumbers& operator=(FilterNumbers&& other) = delete;
    FilterNumbers(FilterNumbers&& other) = delete;

private:
    ///Double slider.
    DoubleSlider* slider_;

    ///Minimum set on filter creation.
    double minOnInit_;

    ///Maximum set on filter creation.
    double maxOnInit_;

    ///Numbers are doubles.
    bool doubleMode_;

    Ui::FilterNumbers* ui;

    static const int factor_;

private Q_SLOTS:
    /**
     * Trigerred on change of left handle on slider.
     * @param newValue new value.
     */
    void sliderMinChanged(int newValue);

    /**
     * Trigerred on change of right handle on slider.
     * @param newValue new value.
     */
    void sliderMaxChanged(int newValue);

    /**
     * Trigerred on change of left LineEdit (from).
     */
    void fromEditingFinished();

    /**
     * Trigerred on change of right LineEdit (to).
     */
    void toEditingFinished();

Q_SIGNALS:
    void newNumericFilter(int column, double from, double to);
};

#endif // FILTERNUMBERS_H
