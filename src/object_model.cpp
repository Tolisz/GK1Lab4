#include "object_model.h"

OModel::OModel(const char* path):
	m_model(path), m_camera(nullptr)
{

}

//void OModel::cammeraAttach(OCamera* cam)
//{
//	m_camera = cam;
//}