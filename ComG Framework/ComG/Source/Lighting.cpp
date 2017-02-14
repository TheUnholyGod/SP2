#include "Lighting.h"
#include "GL\glew.h"


//void Lighting::LightUpdate(double dt)
//{
//	if (!reset)
//	{
//		suntimer = 1;
//	}
//	lightrotate = (dt * suntimer) * 2;
//	sunrotate += lightrotate;
//	LightPos.SetToRotation(lightrotate, 0, 0, 1);
//	lighting = LightPos * lighting;
//	if (sunup == false)
//	{
//		light[0].power = 0;
//		glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
//		if (lighting.y >= 0)
//		{
//			sunup = true;
//			reset = false;
//		}
//	}
//	else
//	{
//		light[0].type = Light::LIGHT_DIRECTIONAL;
//		light[0].position.Set(lighting.x, lighting.y, lighting.z);
//		light[0].power = 1;
//		glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
//		if (lighting.y <= 0)
//		{
//			sunup = false;
//		}
//	}
//}
//
//void Lighting::LightReset(double dt)
//{
//	suntimer = 20;
//	reset = true;
//}