#pragma once

/******************************************************************************
			 3D MATHEMATICS FUNCTION. 		(Splitted into /src/math/*, db vec, int vec, db mat, int mat, quaternion and other files.)
			 KD_Lab::Alexander "Sicher" Kotliar (C) 1995 - 1997
******************************************************************************/

#include "../math/int_math.h"

#include "int_vector.h"
#include "db_vector.h"
#include "int_matrix.h"
#include "db_matrix.h"
#include "quaternion.h"

// Note: These inlines are implemented in the independent files because used externally (e.g. 3d/inline/db_vector.h: DBV::spherical2descart()),
// while internally used inlines should be placed directly in the struct declarations (e.g. 3d/db_vector.h: DBV::psi()).
#include "inline/int_vector.h"
#include "inline/db_vector.h"
#include "inline/db_matrix.h"