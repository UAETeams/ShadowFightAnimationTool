#include "AnimatedTransformCompressed.h"

AnimatedTransformCompressed::AnimatedTransformCompressed(uint16_t _px, uint16_t _py, uint16_t _pz, uint16_t _ux, uint16_t _uy, uint16_t _uz)
{
	this->_p = CompressedVector3(_px, _py, _pz);
	this->_r = CompressedQuaternion(_ux, _uy, _uz);
}