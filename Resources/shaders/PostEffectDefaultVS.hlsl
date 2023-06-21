#include "PostEffectDefault.hlsli"

VSOutput main(float4 pos : POSITION, float2 uv : SV_POSITION)
{
    VSOutput output;
    output.svpos = pos;
    output.uv = uv;
    return output;
}