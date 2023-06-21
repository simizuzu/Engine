// �}�e���A��
cbuffer ConstBufferDataMaterial : register(b0)
{
    //float4 color; // �F(RGBA)
    float3 m_ambient  : packoffset(c0); // �A���r�G���g�W��
	float3 m_diffuse  : packoffset(c1); // �f�B�t���[�Y�W��
	float3 m_specular : packoffset(c2); // �X�y�L�����[�W��
	float m_alpha : packoffset(c2.w);	// �A���t�@
};

// 3D�ϊ��s��
cbuffer ConstBufferDataTransform : register(b1)
{
   // matrix mat; // 3D�ϊ��s��
    matrix viewproj;    //�r���[�v���W�F�N�V�����s��
    matrix world;       //���[���h�s��
    float3 cameraPos;   //�J�������W�i���[���h���W�j
}

cbuffer cbuff2 : register(b2)
{
    float3 lightVec;
    float3 lightColor;
}


// ���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����\����
struct VSOutput
{
    float4 svpos : SV_POSITION; // �V�X�e���p���_���W
    //float3 normal : NORMAL; // �@���x�N�g��
    float4 color : COLOR;
    float2 uv : TEXCOORD; // uv�l
};
