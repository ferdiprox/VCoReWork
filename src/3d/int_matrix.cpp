#include "int_matrix.h"

#include "db_matrix.h"

/******************************************************************************
		  MATRIX Definition
******************************************************************************/
Matrix::Matrix(const DBM& m)
{
	for(int i = 0;i < 9;i++)
		a[i] = round(m.a[i]);
}