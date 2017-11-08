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
uniform int totalLights;
uniform int projEnum;
uniform vec4 lightPos[MAX_LIGHTS];
uniform vec3 brightness[MAX_LIGHTS];
uniform vec3 globalAmbient;
uniform float shininess;
uniform float opacity;

float attenuation(vec3 curPos, vec3 lightPos)
{
		return 1 / (distance(curPos, lightPos)/2);
}

vec4 evaluateLightingModel()
{
	int attenuationConstant = 10;
	vec3 normal = pvaIn.ecUnitNormal; // unit normal vector to Q
	vec3 Q = pvaIn.ecPosition; //point of evaluation

	vec3 ambient = ka * globalAmbient;
	vec3 diffuse = vec3(0.0, 0.0, 0.0);
	vec3 specular = vec3(0.0, 0.0, 0.0);

	vec3 v_hat; // unit vector towards eye

	if(projEnum == 1)//perspective
		v_hat = normalize(-Q);
	else if(projEnum==2)//orthogonal
		v_hat = pvaIn.OVHat;
	else //if(projEnum == 2)-oblique
		v_hat = vec3(0.0, 0.0, 1.0);

	if(dot(normal, v_hat) < 0) //check if normal in right direction
		normal = -normal;

	bool isPositional = false;

	 for(int i = 0; i<totalLights; i++) //for each light source
	 {
		 	vec4 currentLightPos = lightPos[i];
			vec3 li_hat;

			if(currentLightPos.w == 0.0) //directional light
			{
				li_hat = normalize(currentLightPos.xyz);
			}
			else //positional light
			{
				li_hat = normalize(currentLightPos.xyz - Q);
				isPositional = true;
			}

			float atten = attenuation(currentLightPos.xyz, Q) * attenuationConstant;

			if(dot(li_hat, normal) > 0)
			{
				if(!isPositional)
				{
					diffuse += kd * brightness[i] * dot(li_hat, normal);
				}
				else
				{
					diffuse += atten * kd * brightness[i] * dot(li_hat, normal);
				}
			}

			vec3 ri_hat = normalize(reflect(-li_hat, normal));
			if(dot(ri_hat, v_hat) > 0)
			{
				float rdotv = dot(ri_hat, v_hat);

				if(!isPositional)
				{
					specular += ks * brightness[i] * pow(rdotv, shininess);
				}
				else
				{
					specular += atten * ks * brightness[i] * pow(rdotv, shininess);
				}
			}
	 }

	vec3 totalLight = ambient + diffuse + specular;

	for(int i=0; i<3; i++)
		if(totalLight[i] >= 1.0)
			totalLight[i] = 1.0;

	//return vec4(ambient + (factor * kd * liStrength), opacity);
	return vec4(totalLight, opacity);
}

void main ()
{
	fragmentColor = evaluateLightingModel();
}
// #version 410 core
//
// // phong.fsh - a fragment shader that implements a Phong Lighting model.
//
// in PVA
// {
// 	vec3 ecPosition;
// 	vec3 ecUnitNormal;
// } pvaIn;
//
// out vec4 fragmentColor;
//
// // Phong material properties (just kd for now; you will add the rest later):
// // uniform vec3 ka = vec3(0.0,0.8,0.0);
// // uniform vec3 kd = vec3(0.8,0.0,0.0);
// // uniform vec3 ks = vec3(0.0,0.0,0.8);
// // uniform vec3 globalAmbient;
// // uniform int totalLights;
// // uniform vec4 ecLightPositions;
// // uniform vec3 lightIntensity;
// // uniform int projection;
// // uniform float shininess;
// // uniform float opacity;
//
// // float atteunation(vec3 pos, vec3 lightPos)
// // {
// // 	return ((1)/distance(lightPos,pos));
// // }
// //
// // vec3 divideByMax(vec3 ambient, vec3 diffuse, vec3 specular)
// // {
// // 	vec3 total = ambient+diffuse+specular;
// // 	float maximum = total.x;
// // 	if(maximum<total.y)
// // 	{
// // 		maximum = total.y;
// // 	}
// // 	if(maximum<total.z)
// // 	{
// // 		maximum = total.z;
// // 	}
// // 	if(maximum>1)
// // 	{
// // 		total.x = total.x/maximum;
// // 		total.y = total.y/maximum;
// // 		total.z = total.z/maximum;
// // 	}
// // 	return total;
// // }
//
// vec4 evaluateLightingModel()
// {
// 	// int brightness = 8;
// 	// vec3 ambient = ka*globalAmbient;
// 	// vec3 diffuse = {0.0,0.0,0.0};
// 	// vec3 specular = {0.0,0.0,0.0};
// 	// vec3 q = pvaIn.ecPosition;
// 	// vec3 normal = pvaIn.ecUnitNormal;
// 	//
// 	// vec3 vHat=normalize(-q);
// 	//
// 	// if(dot(normal,v_hat)<0)
// 	// {
// 	// 	normal = -normal;
// 	// }
// 	//
// 	// vec4 lightPos;
// 	// vec3 liHat;
// 	// vec3 riHat;
// 	// float curAttenuation
// 	// for(int i=0; i< totalLights; i++)
// 	// {
// 	// 	curAttenuation = attenuation(ecLightPositions[i].xyz)*brightness;
// 	//
// 	//
// 	//
// 	// 	if(ecLightPositions[i].w==1.0)//positional
// 	// 	{
// 	// 		liHat = normalize(ecLightPositions[i].xyz);
// 	// 	}
// 	// 	else//directional
// 	// 	{
// 	// 		liHat = normalize(ecLightPositions[i].xyz-q);
// 	// 	}
// 	//
// 	// 	//calculate specular
// 	// 	riHat = normalize(reflect(liHat, normal));
// 	// 	if(dot(riHat,vHat)>0)
// 	// 	{
// 	// 		if(ecLightPositions[i].w==1)//positional
// 	// 		{
// 	// 			specular += curAttenuation*ks*lightIntensity[i]*pow(dot(riHat,vHat),shininess);
// 	// 		}
// 	// 		else{
// 	// 			specular += ks*lightIntensity[i]*pow(dot(riHat,vHat),shininess);
// 	// 		}
// 	// 	}
// 	//
// 	// 	//calculate diffuse
// 	// 	if(dot(normal,liHat)>0)
// 	// 	{
// 	// 		if(ecLightPositions[i].w==1)//positional-use attenuation
// 	// 		{
// 	// 			diffuse+=curAttenuation*kd*lightIntensity[i]*dot(normal,liHat);
// 	// 		}
// 	// 		else
// 	// 		{
// 	// 			diffuse+=kd*lightIntensity[i]*dot(normal,liHat);
// 	// 		}
// 	// 	}
// 	// }
//
// 	vec3 liHat = vec3(0.0, 0.0, 1.0);
// 	vec3 liStrength = vec3(1.0, 1.0, 1.0);
// 	float factor = abs(dot(liHat, pvaIn.ecUnitNormal));
//
// //	return vec4(divideByMax(ambient,diffuse,specular),1)
// 	return vec4(factor * kd * liStrength, 1.0);
// }
//
// void main ()
// {
// 	fragmentColor = evaluateLightingModel();
// }
