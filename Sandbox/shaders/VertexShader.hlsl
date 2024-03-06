struct VSIn {
	float3 pos : Position;
	float2 tex : TexCoord;
	float3 norm : NormalVS;
};

struct VSOut{
    float3 norm : Normal;
    float4 pos : SV_POSITION;
};

cbuffer Object : register(b0) {
	matrix transform;
};

cbuffer Scene : register(b1) {
    matrix cam;
};

//program
VSOut main(VSIn In)
{
	VSOut Out;

    float4 worldPos = mul(transform, float4(In.pos, 1.0f));
    Out.pos = mul(cam, worldPos);
	
    Out.norm = In.norm;

	return Out;
}