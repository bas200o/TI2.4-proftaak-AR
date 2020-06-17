#version 330 core

layout(location = 0) out vec4 color;

in vec3 FragPos;
in vec3 Normal;
in vec3 ViewPos;
in vec2 TexCoord;

uniform vec3 lightDir;
uniform vec3 lightColor;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;

uniform bool useDiffuseMap;
uniform bool useSpecularMap;

uniform bool useLighting;

void main()
{
	if(useDiffuseMap)
	{
		if(texture(diffuseMap, TexCoord).a < 0.5f)
			discard;
	}

	if(useLighting)
	{
		vec3 objectColor = (!useDiffuseMap) ? vec3(0.5f, 0.5f, 0.5f) : vec3(texture(diffuseMap, TexCoord));

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
	{
		vec3 objectColor = (!useDiffuseMap) ? vec3(0.5f, 0.5f, 0.5f) : vec3(texture(diffuseMap, TexCoord));
		color = vec4(objectColor, 1.0f);
	}
};