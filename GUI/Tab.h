#pragma once

#include <memory>

#include <QMainWindow>

class Dataset;
class TableModel;
class DataView;
class FilteringProxyModel;
class DataViewDock;

/**
 * @brief Tab containing models, view, dock widgets with data and plot.
 */
class Tab : public QMainWindow
{
    Q_OBJECT
public:
    explicit Tab(std::unique_ptr<Dataset> dataset, QWidget* parent = nullptr);

    ~Tab() override = default;

    FilteringProxyModel* getCurrentProxyModel();

    TableModel* getCurrentTableModel();

    DataView* getCurrentDataView();

private:
    DataViewDock* createDataViewDock(FilteringProxyModel* proxyModel);
};