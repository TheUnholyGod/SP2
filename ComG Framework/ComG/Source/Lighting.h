#ifndef _LIGHTING_H
#define _LIGHTING_H

#include "MatrixStack.h"
#include "Light.h"
#include "Vector3.h"
#include "Utility.h"

class Lighting : public Light 
{
	enum UNIFORM_TYPE
	{
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_NUMLIGHTS,
		U_TOTAL,
	};

	unsigned m_parameters[U_TOTAL];
	unsigned program;

public:
	void LightInit(unsigned int &m_pogramID);
	void LightInit1(unsigned int &m_pogramID);
	void LightUpdate(double dt);
	void LightReset(double dt);
	void LightRender(MS viewStack);
	int Lightgetsunup();
	float getsuntimer();

	bool start;
	int Day;

private:
	double lightrotate, sunrotate;
	Mtx44 LightPos;
	int sunup;
	float suntimer;
	Vector3 lighting;
	
	bool reset;
};

#endif