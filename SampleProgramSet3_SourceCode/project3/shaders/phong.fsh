#version 410 core

// phong.fsh - a fragment shader that implements a Phong Lighting model.

in PVA
{
	vec3 ecPosition;
	vec3 ecUnitNormal;
	vec3 OVHat;
} pvaIn;

out vec4 fragmentColor;

const int MAX_LIGHTS = 3;

// Phong lighting model values
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform vec3 globalAmbient;
uniform int totalLights;
uniform int projEnum;
uniform float opacity;
uniform float shininess;
uniform vec3 brightness[MAX_LIGHTS];
uniform vec4 lightPos[MAX_LIGHTS];

vec3 snapToOne(vec3 totalLight)
{
	float snap = 1.0;
	if(totalLight.x>snap)
	{
		snap=totalLight.x;
	}
	if(totalLight.y>snap)
	{
		snap = totalLight.y;
	}
	if(totalLight.z>snap)
	{
		snap = totalLight.z;
	}
	totalLight =(totalLight)/snap;
	return totalLight;

}

float attenuation(vec3 curPos, vec3 lightPos)
{
		return 1 / (distance(curPos, lightPos)/2);
}

vec4 evaluateLightingModel()
{
	int attenuationConstant = 10;
	int directionalConstant = 3;
	vec3 vHat;
	vec3 q = pvaIn.ecPosition;
	vec3 normal = pvaIn.ecUnitNormal;
	vec3 result = vec3(0.0,0.0,0.0);

	result += ka * globalAmbient;//add ambient



	if(projEnum == 1)//perspective
	{
		vHat = normalize(-q);
	}
	else if(projEnum==2)//orthogonal
	{
		vHat = pvaIn.OVHat;
	}
	else //if(projEnum == 2)-oblique
	{
		vHat = vec3(0.0, 0.0, 1.0);
	}

	if(dot(vHat,normal) < 0) //flip normal if its on the wrong side
	{
		normal = -normal;
	}

 	for(int i = 0; i<totalLights; i++)
	{
	 	vec4 currentLightPos = lightPos[i];
		vec3 liHat;

		if(currentLightPos.w == 1.0)
		{
			liHat = normalize(currentLightPos.xyz - q);
		}
		else
		{
			liHat = normalize(currentLightPos.xyz);
		}

		float totalAttenuation = attenuation(currentLightPos.xyz, q) * attenuationConstant;

		vec3 riHat = normalize(reflect(-liHat, normal));
		if(dot(riHat, vHat) > 0)
		{
			float rdotv = dot(riHat, vHat);

			if(currentLightPos.w == 0.0)//directional
			{
				result += directionalConstant * ks * brightness[i] * pow(rdotv, shininess);// add specular
			}
			else
			{
				result += totalAttenuation * ks * brightness[i] * pow(rdotv, shininess);//add specular
			}
		}
		if(dot(liHat, normal) > 0)
		{
			if(currentLightPos.w == 1.0)
			{
				result += totalAttenuation * kd * brightness[i] * dot(liHat, normal);// add diffuse
			}
			else
			{
				result += directionalConstant * kd * brightness[i] * dot(liHat, normal);//add diffuse
			}
		}
	}

	result = snapToOne(result);

	return vec4(result, opacity);
}

void main ()
{
	fragmentColor = evaluateLightingModel();
}
