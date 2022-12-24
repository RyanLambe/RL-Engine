#define MaxLights 4

//constant buffers
cbuffer material : register(b0) {
	float4 colour;
	float smoothness;
	float reflectivity;
};

cbuffer lightData : register(b1) {
	float3 dirColour;

	struct PointData {
		float3 colour;
		float power;
		float range;
	} pointData[MaxLights];
}

//resouces
Texture2D tex;
SamplerState Sampler;

//input
struct PSIn {
	float2 tc : TexCoord;
	float3 norm : Normal;
	float3 toCam: toCamera;
	float3 toLight[1 + MaxLights] : toLight;
};

float4 getPointDiffuse(PSIn In, float4 albedo, int index) {

	//cut off anything beyond range
	float distance = length(In.toLight[index + 1]);
	if (distance > pointData[index].range)
		return float4(0, 0, 0, 0);

	//diffuse
	float diffuse = dot(normalize(In.norm), normalize(In.toLight[index + 1]));
	
	//attinuation
	float range = (cos(distance * 3.14159 / pointData[index].range) + 1) / 2;
	range *= pointData[index].power;
	range = min(range, 1);

	//return
	float4 Out = albedo;
	Out *= float4(pointData[index].colour, 1);
	Out *= diffuse;
	Out *= range;
	return Out;
}

float4 getPointSpecular(PSIn In, float4 specularTint, int index) {

	//calculate
	float3 halfDir = normalize(In.toLight[index + 1] + In.toCam);
	float specAngle = saturate(dot(halfDir, normalize(In.norm)));
	float specular = pow(specAngle, smoothness * 100);

	float distance = length(In.toLight[index + 1]);


	//return
	float4 Out = specularTint;
	Out *= float4(pointData[index].colour, 1);
	Out *= specular;
	Out *= pointData[index].power;
	Out /= distance;
	return Out;
}

float4 main(PSIn In) : SV_TARGET
{
	//get values
	float4 albedo = colour * tex.Sample(Sampler, In.tc);
	float4 specularTint = albedo * reflectivity;
	albedo *= 1 - reflectivity;

	//directional light
	float diffuse = dot(normalize(In.norm), normalize(In.toLight[0]));
	diffuse = saturate(diffuse);

	float3 halfDir = normalize(In.toLight[0] + In.toCam);
	float specAngle = saturate(dot(halfDir, normalize(In.norm)));
	float specular = pow(specAngle, smoothness * 100);

	//Create Diffuse/Specular
	float4 DiffuseFinal =  albedo * float4(dirColour, 1) * diffuse;
	float4 specFinal = specularTint * float4(dirColour, 1) * specular;

	//point lights
	for (int i = 0; i < MaxLights; i++) {
		DiffuseFinal += getPointDiffuse(In, albedo, i);
		specFinal += getPointSpecular(In, specularTint, i);
	}

	return DiffuseFinal + specFinal;
}