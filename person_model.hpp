/**
 * @file
 * @brief Enthält die Deklaration des Personen-Modells.
 * @author Björn Schäpers
 */

#ifndef PERSON_MODEL_HPP
#define PERSON_MODEL_HPP

#include <QAbstractItemModel>

#include <vector>

class PersonModel final : public QAbstractItemModel {
    Q_OBJECT
    public:
    explicit PersonModel(QObject* parent = nullptr) noexcept;
    ~PersonModel(void) noexcept;

    void populateWithTestData(void) noexcept;

    QModelIndex   index(int row, int column, const QModelIndex& parent) const noexcept override;
    QModelIndex   parent(const QModelIndex& child) const noexcept override;
    int           rowCount(const QModelIndex& parent) const noexcept override;
    int           columnCount(const QModelIndex& parent) const noexcept override;
    QVariant      data(const QModelIndex& index, int role) const noexcept override;
    Qt::ItemFlags flags(const QModelIndex& index) const noexcept override;

    private:
    struct PersonData;

    std::vector<PersonData> Data;
};

#endif //PERSON_MODEL_HPP
