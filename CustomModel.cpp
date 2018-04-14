#include "CustomModel.hpp"

CustomModel::CustomModel(QObject *parent) : QAbstractTableModel(parent){
	insertColumns(0, 4);
	insertRows(0, 4);

}


int CustomModel::rowCount(const QModelIndex &parent ) const {
	return 4;
}
int CustomModel::columnCount(const QModelIndex &parent ) const{
	return 4;
}
QVariant CustomModel::data(const QModelIndex &index, int role ) const{
	if(role == Qt::DisplayRole)
		return QVariant(index.column());
	else
		return QVariant();
}
