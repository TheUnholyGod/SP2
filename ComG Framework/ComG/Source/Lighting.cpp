#include "Lighting.h"
#include "GL\glew.h"

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
	sunup = true;
}

void Lighting::LightInit1(unsigned int &m_pogramID)
{

	light[0].type = Lighting::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 100, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1.f;
	light[0].kC = 100.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	suntimer = 1;
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
		light[0].power = 0;
		glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
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
		light[0].type = Lighting::LIGHT_DIRECTIONAL;
		light[0].position.Set(lighting.x, lighting.y, lighting.z);
		light[0].power = 1;
		glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);

		if (lighting.y >= 0 && lighting.y < 0.5)
		{
			sunup = 3;
		}
		else if (lighting.y > 0.5)
		{
			sunup = 1;
		}
	}

	std::cout << "Lighting Level: " << lighting.y << std::endl;
}

void Lighting::LightRender(MS viewStack)
{
	if (light[0].type == Lighting::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Lighting::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
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