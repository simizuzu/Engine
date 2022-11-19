#include "Material.h"
#include <d3dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")

void Material::Initialize()
{
	HRESULT result;
	Microsoft::WRL::ComPtr<ID3D12Device> device = DirectXCommon::GetInstance()->GetDevice();

	Microsoft::WRL::ComPtr<ID3DBlob> vsBlob; // 頂点シェーダオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob> psBlob; // ピクセルシェーダオブジェクト

	bool vsflag = false;
	bool psflag = false;

	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob; // エラーオブジェクト

#pragma region 頂点シェーダー

	//頂点シェーダー
	if (vsFiledata.pFileName.size() > 4)
	{
		// 頂点シェーダの読み込みとコンパイル
		result = D3DCompileFromFile(
			vsFiledata.pFileName.c_str(), // シェーダファイル名
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
			vsFiledata.pEntrypoint.c_str(), vsFiledata.pTarget.c_str(), // エントリーポイント名、シェーダーモデル指定
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
			0,
			&vsBlob, &errorBlob);

		// エラーなら
		if (FAILED(result))
		{
			// errorBlobからエラー内容をstring型にコピー
			std::string error;
			error.resize(errorBlob->GetBufferSize());
			std::copy_n((char*)errorBlob->GetBufferPointer(),
				errorBlob->GetBufferSize(),
				error.begin());
			error += "\n";
			// エラー内容を出力ウィンドウに表示
			OutputDebugStringA(error.c_str());
			assert(0);
		}

		vsflag = true;
	}

#pragma endregion

#pragma region ピクセルシェーダー

	//ピクセルシェーダ－
	if (psFiledata.pFileName.size() > 4)
	{
		// ピクセルシェーダの読み込みとコンパイル
		result = D3DCompileFromFile(
			psFiledata.pFileName.c_str(), // シェーダファイル名
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
			psFiledata.pEntrypoint.c_str(), psFiledata.pTarget.c_str(), // エントリーポイント名、シェーダーモデル指定
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
			0,
			&psBlob, &errorBlob);

		// エラーなら
		if (FAILED(result))
		{
			// errorBlobからエラー内容をstring型にコピー
			std::string error;
			error.resize(errorBlob->GetBufferSize());
			std::copy_n((char*)errorBlob->GetBufferPointer(),
				errorBlob->GetBufferSize(),
				error.begin());
			error += "\n";
			// エラー内容を出力ウィンドウに表示
			OutputDebugStringA(error.c_str());
			assert(0);
		};

		psflag = true;
	}

#pragma endregion
}