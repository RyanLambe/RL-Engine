#define MaxLights 4

//constant buffers
cbuffer Object : register(b0) {
	matrix transform;
};

cbuffer Scene : register(b1) {
	matrix cam;
	float3 lightPos[1 + MaxLights];
};

//input output
struct VSIn {
	float3 pos : Position;
	float2 tex : TexCoord;
	float3 norm : NormalVS;
};

struct VSOut{
	float2 tex: TexCoord;
	float3 norm: Normal;
	float3 toCam: toCamera;
	float3 toLight[1 + MaxLights] : toLight;
	float4 pos: SV_POSITION;
};

//program
VSOut main(VSIn In)
{
	VSOut Out;

	float4 worldPos = mul(transform, float4(In.pos, 1.0f));

	Out.pos = mul(cam, worldPos);
	Out.tex = In.tex;
	Out.toCam = normalize(-Out.pos);
	Out.norm = (float3)mul(transform, float4(In.norm, 0.0f));
	
	//directional Light
	Out.toLight[0] = lightPos[0];

	//point lights
	for (int i = 1; i <= MaxLights; i++) {
		Out.toLight[i] = lightPos[i] - worldPos;
	}

	return Out;
}