cbuffer Object : register(b0) {
	matrix transform;
};

cbuffer Camera : register(b1) {
	matrix cam;
};

cbuffer Lights : register(b2) {
	float3 dirLight;

	struct PointLights {
		float3 light;
	} pointLights[4];
};

struct VSOut{
	float2 tex: TexCoord;
	float3 norm: Normal;
	float3 toLight[5] : toLight;
	float4 pos: SV_POSITION;
};

VSOut main(float3 pos : Position, float2 tex : TexCoord, float3 norm : NormalVS)
{
	VSOut Out;

	float4 worldPos = mul(transform, float4(pos, 1.0f));

	Out.pos = mul(cam, worldPos);
	Out.tex = tex;
	Out.norm = (float3)mul(transform, float4(norm, 0.0f));
	
	//directional Light
	Out.toLight[0] = dirLight;// -worldPos;

	return Out;
}