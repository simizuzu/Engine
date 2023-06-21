cbuffer cbuff : register(b0)
{
    
};

struct VSOutput
{
    float4 svpos : SV_Position;
    float2 uv : TEXCOORD;
};