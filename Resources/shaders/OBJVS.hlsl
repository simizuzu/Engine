#include "OBJ.hlsli"

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{
    //VSOutput output; // ピクセルシェーダーに渡す値
    //output.svpos = mul(mat, pos);
    //output.normal = normal;
    //output.uv = uv;

    //右、下、億の方向を向いたライト
    float3 lightdir = float3(1, -1, 1);
    lightdir = normalize(lightdir);
    //ライトの色
    float3 lightcolor = float3(1, 1, 1);
    //ピクセルシェーダに渡す値
    VSOutput output;
    output.svpos = mul(mat, pos);
    //Lambert反射の計算
    output.color.rgb = dot(-lightdir, normal) * m_diffuse * lightcolor;
    output.color.a = m_alpha;
    output.uv = uv;

    return output;
}