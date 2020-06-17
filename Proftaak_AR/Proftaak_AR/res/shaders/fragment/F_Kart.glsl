#version 330 core

layout(location = 0) out vec4 color;

in vec3 FragPos;
in vec3 Normal;
in vec3 ViewPos;
in vec2 TexCoord;

uniform vec3 lightDir;
uniform vec3 lightColor;

uniform vec3 kartColor;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform sampler2D diffuseMask;

uniform bool useDiffuseMap;
uniform bool useSpecularMap;
uniform bool useDiffuseMask;

uniform bool useLighting;

void main()
{
	vec3 objectColor = vec3(0.5f, 0.5f, 0.5f);
	
	if(useDiffuseMap && useDiffuseMask)
	{
		float maskValue = vec3(texture(diffuseMask, TexCoord)).x;
		if(maskValue > 0)
			objectColor = kartColor * maskValue;
		else
			objectColor = vec3(texture(diffuseMap, TexCoord));
	}
	else if(useDiffuseMap)
		objectColor = vec3(texture(diffuseMap, TexCoord));

	if(useLighting)
	{
		//Ambient Light
		float ambientStrength = 0.2;
		vec3 ambient = ambientStrength * lightColor;

		//Diffused Light
		vec3 norm = normalize(Normal);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lightColor;
	
		//Specular Light
		float specularStrength = 0.5;
		vec3 viewDir = normalize(ViewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

		vec3 specular = specularStrength * spec * lightColor;  
		if(useSpecularMap)
			specular *= vec3(texture(specularMap, TexCoord));

		vec3 result = (ambient + diffuse + specular) * objectColor;

		color = vec4(result, 1.0f);
	}
	else
		color = vec4(objectColor, 1.0f);
};