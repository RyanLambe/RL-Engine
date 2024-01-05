struct VSIn {
	float3 pos : Position;
	float2 tex : TexCoord;
	float3 norm : NormalVS;
};

struct VSOut{
	float4 pos: SV_POSITION;
};

//program
VSOut main(VSIn In)
{
	VSOut Out;

	Out.pos = float4(In.pos.xy, 0, 1.0f);

	return Out;
}