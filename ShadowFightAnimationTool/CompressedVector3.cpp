#include "CompressedVector3.h"

CompressedVector3::CompressedVector3(uint16_t _px, uint16_t _py, uint16_t _pz)
{
	this->_px = _px;
	this->_py = _py;
	this->_pz = _pz;
}

Vector3 CompressedVector3::Position()
{
	Vector3 vector3 = Vector3(halftofloat(this->_px), halftofloat(this->_py), halftofloat(this->_pz));
	return vector3;
}

float CompressedVector3::halftofloat(uint16_t h)
{
    uint16_t h_exp = (h & 0x7C00u);
    uint16_t h_sig = (h & 0x03FFu);
    uint32_t f_sgn = ((uint32_t)(h & 0x8000u)) << 16;
    uint32_t f_exp, f_sig;

    if (h_exp == 0x0000u) { // zero / subnormal
        if (h_sig == 0) {
            f_exp = 0;
            f_sig = 0;
        }
        else {
            // normalize subnormal
            int e = -1;
            uint16_t sig = h_sig;
            while ((sig & 0x0400u) == 0) { sig <<= 1; e--; }
            sig &= 0x03FFu;
            f_exp = (uint32_t)(127 - 15 + 1 + e) << 23;
            f_sig = (uint32_t)sig << 13;
        }
    }
    else if (h_exp == 0x7C00u) { // Inf or NaN
        f_exp = 0xFFu << 23;
        f_sig = (uint32_t)(h_sig) << 13;
    }
    else { // normalized
        f_exp = (uint32_t)(((h_exp >> 10) - 15 + 127) & 0xFF) << 23;
        f_sig = (uint32_t)h_sig << 13;
    }

    uint32_t f_bits = f_sgn | f_exp | f_sig;
    float result;
    memcpy(&result, &f_bits, sizeof(result));
    return result;
}