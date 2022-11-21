struct VSOut 
{
	float3 color : Color;
	float4 pos : SV_POSITION;
};

VSOut main( float2 pos : Position, float3 color : Color )
{
	VSOut Out;
	Out.pos = float4(pos.x, pos.y, 0.0f, 1.0f);
	Out.color = color;
	return Out;
}