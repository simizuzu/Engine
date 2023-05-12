#include "OBJ.hlsli"

VSOutput main(float4 pos : POSITION, float2 uv : TEXCOORD, float3 normal : NORMAL)
{

	//�E�A���A���̕��������������C�g
	float3 lightdir = float3(1, -1, 1);
	lightdir = normalize(lightdir);
	//���C�g�̐F
	float3 lightcolor = float3(1.0f, 0.5f, 0.5f);
	//�����ˌ�
	float3 ambient = m_ambient;
	//�g�U���ˌ�
	float3 diffuse = dot(-lightdir, normal) * m_diffuse;

	//���_���W
	const float3 eye = float3(0, 0, -20);
	//����x
	const float shininess = 4.0f;
	//���_���王�_�ւ̕����x�N�g��
	float3 eyedir = normalize(eye - pos.xyz);
	//���ˌ��x�N�g��
	float3 reflect = normalize(lightdir + 2 * dot(-lightdir, normal) * normal);
	//���ʔ��ˌ�
	float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

	//�s�N�Z���V�F�[�_�[�ɓn���l
	VSOutput output;
	output.svpos = mul(mat, pos);
	//Lambert���˂̌v�Z
	output.color.rgb = dot(-lightdir, normal) * m_diffuse * lightcolor;
	//�S�ĉ��Z����
	output.color.rgb = (ambient + diffuse + specular) * lightcolor;
	output.color.a = m_alpha;
	output.uv = uv;

	return output;
}