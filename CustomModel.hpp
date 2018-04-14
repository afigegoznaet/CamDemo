#ifndef CUSTOMMODEL_HPP
#define CUSTOMMODEL_HPP

#include <QObject>
#include <QAbstractTableModel>

class CustomModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit CustomModel(QObject *parent = Q_NULLPTR);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // CUSTOMMODEL_HPP
