/**
 * @file
 * @brief Enthält die Definition des Personen-Modells.
 * @author Björn Schäpers
 */

#include "person_model.hpp"

enum class Column {
    Image,
    FirstName,
    LastName,
    DateOfBirth,
    Mail,
    VIP,
    Count,
};

/**
 * @class PersonModel
 * @brief Ein einfaches Modell für Personen-Daten.
 * @author Björn Schäpers
 * @since V0.1 - 14.02.2025
 *
 * @property PersonModel::Data
 * @brief Die Daten im Modell.
 */

struct PersonModel::PersonData {};

/**
 * @brief Konstruktor.
 * @author Björn Schäpers
 * @param[in] parent Qt-Parent.
 */
PersonModel::PersonModel(QObject* parent) noexcept : QAbstractItemModel{parent} {
    return;
}

/**
 * @brief Destruktor.
 * @author Björn Schäpers
 */
PersonModel::~PersonModel(void) noexcept = default;

/**
 * @brief Fügt Testdaten in das Modell ein.
 * @author Björn Schäpers
 */
void PersonModel::populateWithTestData(void) noexcept {
    beginResetModel();

    endResetModel();
    return;
}

/**
 * @brief Generiert den Index für einen Modell-Eintrag.
 * @author Björn Schäpers
 * @param[in] row Die gefragte Zeile.
 * @param[in] column Die gefragte Spalte.
 * @param[in] parent Der Eltern-Index, dessen Kinder gesucht werden.
 * @return Der Index.
 */
QModelIndex PersonModel::index(int row, int column, const QModelIndex& parent) const noexcept {
    if ( parent.isValid() ) {
        return {};
    } //if ( parent.isValid() )

    if ( row >= std::ssize(Data) || column >= static_cast<int>(Column::Count) ) {
        return {};
    } //if ( row >= std::ssize(Data) || column >= static_cast<int>(Column::Count) )

    return createIndex(row, column);
}

/**
 * @brief Liefert den Eltern-Index zu einem Index.
 * @author Björn Schäpers
 * @param[in] child Der Index zu dem gefragt wird.
 * @return Der Eltern-Indx.
 */
QModelIndex PersonModel::parent(const QModelIndex& /*child*/) const noexcept {
    //Wir sind nur eine Liste, d.h. alle gültigen Indices haben den Default-Index als Elter.
    return {};
}

/**
 * @brief Liefert die Anzahl der Zeilen unter einem Index.
 * @author Björn Schäpers
 * @param[in] parent Der Index nach dessen Unterzeilen gefragt wird.
 * @return Die Anzahl der Zeilen.
 */
int PersonModel::rowCount(const QModelIndex& parent) const noexcept {
    return parent.isValid() ? 0 : static_cast<int>(Data.size());
}

/**
 * @brief Liefert die Anzahl der Spalten unter einem Index.
 * @author Björn Schäpers
 * @param[in] parent Der Index nach dessen Unterspalten gefragt wird.
 * @return Die Anzahl der Spalten.
 */
int PersonModel::columnCount(const QModelIndex& /*parent*/) const noexcept {
    return static_cast<int>(Column::Count);
}

/**
 * @brief Setzt die Daten.
 * @author Björn Schäpers
 * @param[in] index Der Index des zu ändernden Eintrags.
 * @param[in] value Der neue Wert.
 * @param[in] role Die Rolle die bearbeitet wird.
 * @return Ob das Editieren erfolgt ist.
 */
bool PersonModel::setData(const QModelIndex& index, const QVariant& value, int role) noexcept {
    return false;
}

/**
 * @brief Liefert die Daten.
 * @author Björn Schäpers
 * @param[in] index Der Index des gefragten Eintrags.
 * @param[in] role Die gefragte Rolle.
 * @return Der Wert.
 */
QVariant PersonModel::data(const QModelIndex& index, int role) const noexcept {
    return {};
}

/**
 * @brief Liefert die Flags zu einem Index.
 * @author Björn Schäpers
 * @param[in] index Der Index.
 * @return Die Flags dazu.
 */
Qt::ItemFlags PersonModel::flags(const QModelIndex& index) const noexcept {
    const auto baseFlags = QAbstractItemModel::flags(index);

    if ( !index.isValid() ) {
        return baseFlags;
    } //if ( !index.isValid() )

    auto flags = baseFlags | Qt::ItemFlag::ItemNeverHasChildren;

    if ( index.column() == static_cast<int>(Column::VIP) ) {
        flags |= Qt::ItemFlag::ItemIsEditable;
    } //if ( index.column() == static_cast<int>(Column::VIP) )

    return flags;
}

#include "moc_person_model.cpp"
