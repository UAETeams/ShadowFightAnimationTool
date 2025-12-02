#include "CompressedQuaternion.h"
#include "Quaternion.h"
#include <cmath>

CompressedQuaternion::CompressedQuaternion(uint16_t _ux, uint16_t _uy, uint16_t _uz)
{
	this->_v0 = _ux;
	this->_v1 = _uy;
	this->_v2 = _uz;
}

Quaternion CompressedQuaternion::Rotation()
{
	int v2, v4, v5;
	float v10, v11, v12, v13, v16, v17, v18;

    Quaternion Q = Quaternion();

	v2 = (this->_v1 >> 14) + 4 * (this->_v0 & 0x1FFF);
	v4 = (this->_v2 >> 15) + 2 * (this->_v1 & 0x3FFF);
	v5 = (this->_v2 & 0x7FFF);

	v10 = (float)((float)v2 * staticField()._maxValue / 32767.0f - staticField()._maxValueShift);
	v11 = (float)((float)v4 * staticField()._maxValue / 32767.0f - staticField()._maxValueShift);
	v12 = (float)((float)v5 * staticField()._maxValue / 32767.0f - staticField()._maxValueShift);

	v13 = std::sqrt(1.0f - (v10 * v10) - (v11 * v11) - (v12 * v12));

	char v14 = (char)((this->_v0 >> 13) & 3);

    if (v14 == 1)
    {
        Q.x = 0;
        Q.y = 0;
        Q.z = 0;
        Q.w = 0;

        v16 = v13;
        v17 = v11;
        v18 = v12;
    }
    else
    {
        if (v14 == 2)
        {
            Q.x = 0;
            Q.y = 0;
            Q.z = 0;
            Q.w = 0;

            v18 = v12;
            v17 = v13;
        }
        else
        {
            if (v14 != 3)
            {
                Q.x = v13;
                Q.y = v10;
                Q.z = v11;
                Q.w = v12;

                return Q;
            }
            Q.x = 0;
            Q.y = 0;
            Q.z = 0;
            Q.w = 0;

            v18 = v13;
            v17 = v12;
        }
        v16 = v11;
    }
    Q.x = v10;
    Q.y = v16;
    Q.z = v17;
    Q.w = v18;

    return Q;
}