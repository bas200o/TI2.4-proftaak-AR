#version 330 core

layout(location = 0) out vec4 color;

in vec3 FragPos;
in vec3 Normal;
in vec3 ViewPos;
in vec2 TexCoord;

uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{
	vec3 objectColor = vec3(0.5f, 0.5f, 0.5f);
	
	//Ambient Light
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	//Diffused Light
	vec3 norm = normalize(Normal);
	vec3 lightdir = normalize(lightPos-FragPos);
	float diff = max(dot(norm, lightdir), 0.0);
	vec3 diffuse = diff * lightColor;

	//Specular Light
	float specularStrength = 0.8;
    vec3 viewDir = normalize(ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightdir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * lightColor;  

	vec3 result = (ambient + diffuse + specular) * objectColor;


	color = vec4(result, 1.0f);
};