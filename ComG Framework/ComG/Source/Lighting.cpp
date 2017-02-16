#include "Lighting.h"
#include "GL\glew.h"
#include "MyMath.h"

void Lighting::LightInit(unsigned int &m_pogramID)
{
	sunup = 1;

	program = m_pogramID;
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(program, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(program, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(program, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(program, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(program, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(program, "lights[0].kQ");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(program, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(program, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(program, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(program, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(program, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(program, "lights[0].exponent");

	glUseProgram(program);

	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	lighting.y = 1.f;
	reset = false;
	start = true;
	Day = 0;
	sunrotate = 0;
}

void Lighting::LightInit1(unsigned int &m_pogramID)
{
	 type = Lighting::LIGHT_DIRECTIONAL;
	 position.Set(0, 1, 0);
	 color.Set(1, 1, 1);
	 power = 0.f; 
	 kC = 100.f;
	 kL = 0.01f;
	 kQ = 0.001f;
	 cosCutoff = cos(Math::DegreeToRadian(45));
	 cosInner = cos(Math::DegreeToRadian(30));
	 exponent = 3.f;
	 spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT0_TYPE],  type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, & color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER],  power);
	glUniform1f(m_parameters[U_LIGHT0_KC],  kC);
	glUniform1f(m_parameters[U_LIGHT0_KL],  kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ],  kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF],  cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER],  cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT],  exponent);
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	suntimer = 0;
}

void Lighting::LightUpdate(double dt)
{
	if (!reset)
	{
		suntimer = 1;
	}
	lightrotate = (dt * suntimer) * 2;
	sunrotate += lightrotate;
	LightPos.SetToRotation(lightrotate, 0, 0, 1);
	lighting = LightPos * lighting;
	if (lighting.y <= 0)
	{
		 power = 0;
		glUniform1f(m_parameters[U_LIGHT0_POWER],  power);
		if (lighting.y >= 0 && lighting.y <= 0.5)
		{
			sunup = 3;
			reset = false;
		}
		else if (lighting.y <= -0.5)
		{
			sunup = 2;
			reset = false;
		}
	}
	else
	{
		 type = Lighting::LIGHT_DIRECTIONAL;
		 position.Set(lighting.x, lighting.y, lighting.z);
		 power = 1;
		glUniform1f(m_parameters[U_LIGHT0_POWER],  power);

		if (lighting.y >= 0 && lighting.y < 0.5)
		{
			sunup = 3;
		}
		else if (lighting.y > 0.5)
		{
			sunup = 1;
		}
	}
	if (sunrotate >= 390)
	{
		sunrotate -= 390;
		Day++;
	}
}

void Lighting::LightRender(MS viewStack)
{
	if ( type == Lighting::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir( position.x,  position.y,  position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if ( type == Lighting::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() *  position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() *  spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() *  position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}
}
void Lighting::LightReset(double dt)
{
	suntimer = 20;
	reset = true;
}

int Lighting::Lightgetsunup()
{
	int sun;
	sun = sunup;
	return sun;
}

float Lighting::getsuntimer()
{
	float suntime;
	suntime = suntimer;
	return suntime;
}