#include "OBJ.hlsli"

VSOutput main(float4 pos : POSITION, float2 uv : TEXCOORD, float3 normal : NORMAL)
{
	//�@���Ƀ��[���h�s��ɂ��X�P�[�����O�E��]��K�p
	float4 wnormal = normalize(mul(world, float4(normal, 0)));
	float4 wpos = mul(world, pos);

	//�����ˌ�
	float3 ambient = m_ambient;
	//�g�U���ˌ�
	float3 diffuse = dot(lightVec,wnormal.xyz) * m_diffuse;

	//����x
	const float shininess = 4.0f;
	//���[���h���W�n�ł̕����x�N�g��
	float3 eyedir = normalize(cameraPos - wpos.xyz);
	//���ˌ��x�N�g��
	float3 reflect = normalize(-lightVec + 2 * dot(lightVec, wnormal.xyz) * wnormal.xyz);
	//���ʔ��ˌ�
	float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

	//�s�N�Z���V�F�[�_�[�ɓn���l
	VSOutput output;
	output.svpos = mul(mul(viewproj,world),pos);
	//Lambert���˂̌v�Z
	output.color.rgb = dot(-lightVec, normal) * m_diffuse * lightColor;
	//�S�ĉ��Z����
	output.color.rgb = (ambient + diffuse + specular) * lightColor;
	output.color.a = m_alpha;
	output.uv = uv;

	return output;
}