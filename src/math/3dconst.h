#pragma once

/* Axises for DBM constructor */
enum AXIS_3D
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS,
};

enum MATRIX_CONSTRUCT_MODE
{
    // Creation of diagonal matrix
    DIAGONAL,
    // Rotation by Euler-angles: Rz(psi)*Ry(tetta)[*Rz(phi)]:
    EULER,
    // Inversion of rotation by Euler-angles: [Rz(-phi)*]Ry(-tetta)*Rz(-psi):
    EULER_INV,
    // Rotation around vector defined by spherical coord. (psi,tetta):
    // Rz(psi)*Ry(tetta)*Rz(phi)*Ry(-tetta)*Rz(-psi):
    AROUND_EULER,
    // Rotation around vector defined by descart coord. (x,y,z):
    // Rz(psi)*Ry(tetta)*Rz(vabs())*Ry(-tetta)*Rz(psi):
    AROUND_VECTOR,
};
