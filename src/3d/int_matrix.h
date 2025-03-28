#pragma once

struct DBM;

struct Matrix 
{
	int  a[9];

	Matrix(){}
	Matrix(const DBM& m);
};
