/**
 * @file
 * @brief Enthält die Deklaration des List-Views.
 * @author Björn Schäpers
 */

#ifndef LIST_VIEW_HPP
#define LIST_VIEW_HPP

#include <QWidget>

class QAbstractItemModel;
class QTreeView;

class ListView : public QWidget {
    Q_OBJECT
    public:
    explicit ListView(QWidget* parent = nullptr) noexcept;

    void setModel(QAbstractItemModel* model) noexcept;

    private:
    QTreeView* TheView;
};

#endif //LIST_VIEW_HPP
