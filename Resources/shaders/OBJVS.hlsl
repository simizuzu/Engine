#include "OBJ.hlsli"

VSOutput main(float4 pos : POSITION, float2 uv : TEXCOORD, float3 normal : NORMAL)
{
	//法線にワールド行列によるスケーリング・回転を適用
	float4 wnormal = normalize(mul(world, float4(normal, 0)));
	float4 wpos = mul(world, pos);

	//環境反射光
	float3 ambient = m_ambient;
	//拡散反射光
	float3 diffuse = dot(lightVec,wnormal.xyz) * m_diffuse;

	//光沢度
	const float shininess = 4.0f;
	//ワールド座標系での方向ベクトル
	float3 eyedir = normalize(cameraPos - wpos.xyz);
	//反射光ベクトル
	float3 reflect = normalize(-lightVec + 2 * dot(lightVec, wnormal.xyz) * wnormal.xyz);
	//鏡面反射光
	float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

	//ピクセルシェーダーに渡す値
	VSOutput output;
	output.svpos = mul(mul(viewproj,world),pos);
	//Lambert反射の計算
	output.color.rgb = dot(-lightVec, normal) * m_diffuse * lightColor;
	//全て加算する
	output.color.rgb = (ambient + diffuse + specular) * lightColor;
	output.color.a = m_alpha;
	output.uv = uv;

	return output;
}