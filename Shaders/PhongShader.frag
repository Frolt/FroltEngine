#version 410 core

// Material
struct Material {
    sampler2D diffuseMap1;
    sampler2D diffuseMap2;
    sampler2D diffuseMap3;
    sampler2D specularMap1;
    sampler2D specularMap2;
    sampler2D specularMap3;
    sampler2D emissionMap;
    vec3 diffuseColor;
    vec3 specularColor;
    float shininess;
    bool hasDiffMap;
    bool hasSpecMap;
    bool hasEmissionMap;
    bool isLight;
};
// Directional light
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
};
// Point light
struct PointLight {
    vec3 position;
    vec3 diffuse;
    float constant;
    float linear;
    float quadratic;
};
// Spotlight
struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 diffuse;
    float innerCone;
    float outerCone;
    float constant;
    float linear;
    float quadratic;
};

// Number of lights supported
const int numOfPointLights = 5;
const int numOfspotlights = 5;
const int numOfMaps = 3;
// Uniforms
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[numOfPointLights];
uniform SpotLight spotLights[numOfspotlights];
uniform vec3 camPos;

// From vertex shader
in vec3 Pos;
in vec3 Normal;
in vec2 UV;
in vec3 FragPos;

// Fragment color
out vec4 FragColor;

// Function declarations
vec3 calcDirLight(DirLight light, vec3 normal, vec3 camDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 camDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 camDir);
vec3 calcEmission();

void main()
{
    vec3 fragColor = vec3(0.0);
    if (material.isLight) {
        fragColor = material.diffuseColor;
    } else {
        vec3 normal = normalize(Normal);
        vec3 camDir = normalize(camPos - FragPos);
        fragColor += calcDirLight(dirLight, normal, camDir);
        for (int i = 0; i < numOfPointLights; i++)
            fragColor += calcPointLight(pointLights[i], normal, camDir);
        for (int i = 0; i < numOfspotlights; i++)
            fragColor += calcSpotLight(spotLights[i], normal, camDir);
        fragColor += calcEmission();
    }

    // Final fragment color
    FragColor = vec4(fragColor, 1.0);
//    float near = 0.1f;
//    float far = 1000.0f;
//    float depth = gl_FragCoord.z * 2.0 - 1.0;
//    float linearDepth =
//    FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}

//---------------------------------------------------------------------------------
// Function definitions
//---------------------------------------------------------------------------------

vec3 calcDirLight(DirLight light, vec3 normal, vec3 camDir)
{
    vec3 lightDir = normalize(-light.direction);
    // Diffuse
    float diffStr = max(dot(normal, lightDir), 0.0);
    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float specStr = pow(max(dot(camDir, reflectDir), 0.0), material.shininess);
    // Result
    vec3 amb, diff, spec;
    if (material.hasDiffMap) {
        amb = light.ambient * texture(material.diffuseMap1, UV).rgb * texture(material.diffuseMap2, UV).rgb * texture(material.diffuseMap3, UV).rgb;
        diff = light.diffuse * diffStr * texture(material.diffuseMap1, UV).rgb * texture(material.diffuseMap2, UV).rgb * texture(material.diffuseMap3, UV).rgb;
    } else {
        amb = light.ambient * material.diffuseColor;
        diff = light.diffuse * diffStr * material.diffuseColor;
    }
    if (material.hasSpecMap) {
        spec = light.diffuse * specStr * texture(material.specularMap1, UV).rgb * texture(material.specularMap2, UV).rgb * texture(material.specularMap3, UV).rgb;
    } else {
        spec = light.diffuse * specStr * material.specularColor;
    }
    return (amb + diff + spec);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 camDir)
{
    vec3 lightDir = normalize(light.position - FragPos);
    // Diffuse
    float diffStr = max(dot(normal, lightDir), 0.0);
    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float specStr = pow(max(dot(reflectDir, camDir), 0.0), material.shininess);
    // Attenuation
    float distance = length(light.position - FragPos);
    light.constant = 1.0;
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Result
    vec3 diff, spec;
    if (material.hasDiffMap) {
        diff = light.diffuse * diffStr * texture(material.diffuseMap1, UV).rgb;
    } else {
        diff = light.diffuse * diffStr * material.diffuseColor;
    }
    if (material.hasSpecMap) {
        spec = light.diffuse * specStr * texture(material.specularMap1, UV).rgb;
    } else {
        spec = light.diffuse * specStr * material.specularColor;
    }
    diff *= attenuation;
    spec *= attenuation;
    return (diff + spec);
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 camDir)
{
    vec3 lightDir = normalize(light.position - FragPos);
    // Diffuse
    float diffStr = max(dot(normal, lightDir), 0.0);
    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float specStr = pow(max(dot(reflectDir, camDir), 0.0) , material.shininess);
    // Attenuation
    float distance = length(light.position - FragPos);
    light.constant = 1.0;
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float intensity = clamp((theta - light.outerCone) / (light.innerCone - light.outerCone), 0.0, 1.0);
    // Result
    vec3 diff, spec;
    if (material.hasDiffMap) {
        diff = light.diffuse * diffStr * texture(material.diffuseMap1, UV).rgb;
    } else {
        diff = light.diffuse * diffStr * material.diffuseColor;
    }
    if (material.hasSpecMap) {
        spec = light.diffuse * specStr * texture(material.specularMap1, UV).rgb;
    } else {
        spec = light.diffuse * specStr * material.specularColor;
    }
    diff *= attenuation * intensity;
    spec *= attenuation * intensity;
    return (diff + spec);
}

vec3 calcEmission()
{
    if (material.hasEmissionMap)
        return texture(material.emissionMap, UV).rgb;
    else
        return vec3(0);
}
