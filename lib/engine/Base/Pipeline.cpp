#include "Pipeline.h"

void Pipeline::CreateSpritePipeline()
{
	HRESULT result;
	// 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> vsBlob;
	// ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> psBlob;
	// ルートシグネチャのシリアライズ
	ComPtr<ID3DBlob> rootSigBlob;
	// エラーオブジェクト
	ComPtr<ID3DBlob> errorBlob;
	// シングルトン呼び出し
	dxCommon_->GetInstance();

	// 頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{ // xyz座標
			"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
		},
		{ // uv座標
			"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
		},
		{ // カラー
			"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
		},
	};
	// グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	// 頂点シェーダ、ピクセルシェーダをパイプラインに設定
	pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();
	// サンプルマスクの設定
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定
	// ラスタライザの設定
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;	// カリングしない
	//pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_FRONT;	// 前面カリング
	//pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;	// 背面カリング
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;	// ポリゴン内塗りつぶし
	pipelineDesc.RasterizerState.DepthClipEnable = true;			// 深度クリッピングを有効に
	// ブレンドステート
	pipelineDesc.BlendState.RenderTarget[0];
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;	// RGBA全てのチャンネルを描画
	// 共通設定
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;	//加算
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;		//ソースの値を100%使う
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;	//デストの値を0%使う

	// 頂点レイアウトの設定
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
	pipelineDesc.InputLayout.NumElements = _countof(inputLayout);
	// 図形の形状設定
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE; // 三角形
	// その他の設定
	pipelineDesc.NumRenderTargets = 1; // 描画対象は1つ
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255指定のRGBA
	pipelineDesc.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	// ルートパラメータの設定
	D3D12_ROOT_PARAMETER rootParams[2] = {};
	// ルートパラメータの設定
	rootParams[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;	// 定数バッファビュー
	rootParams[0].Descriptor.ShaderRegister = 0;					// 定数バッファ番号
	rootParams[0].Descriptor.RegisterSpace = 0;						// デフォルト値
	rootParams[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;	// 全てのシェーダから見える

	// デスクリプタレンジの設定
	D3D12_DESCRIPTOR_RANGE descritorRange{};
	descritorRange.NumDescriptors = 1;
	descritorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descritorRange.BaseShaderRegister = 0;
	descritorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	// テクスチャレジスタ0番
	rootParams[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParams[1].DescriptorTable.pDescriptorRanges = &descritorRange;
	rootParams[1].DescriptorTable.NumDescriptorRanges = 1;
	rootParams[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	// テクスチャサンプラーの設定
	D3D12_STATIC_SAMPLER_DESC sampleDesc{};
	sampleDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;					// 横繰り返し(タイリング)
	sampleDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;					// 縦繰り返し(タイリング)
	sampleDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;					// 奥行繰り返し(タイリング)
	sampleDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;	// ボーダーの時は黒
	sampleDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;					// 全てリニア補間
	sampleDesc.MaxLOD = D3D12_FLOAT32_MAX;									// ミップマップ最大値
	sampleDesc.MinLOD = 0.0f;												// ミップマップ最小値
	sampleDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	sampleDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;			// ピクセルシェーダ殻のみ使用可能

	// ルートシグネチャの設定
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_STREAM_OUTPUT;
	rootSignatureDesc.pParameters = rootParams;
	rootSignatureDesc.NumParameters = _countof(rootParams);
	rootSignatureDesc.pStaticSamplers = &sampleDesc;
	rootSignatureDesc.NumStaticSamplers = 1;
	// ルートシグネチャのシリアライズ
	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	assert(SUCCEEDED(result));
	result = dxCommon_->GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootsignature));
	assert(SUCCEEDED(result));

	rootSigBlob->Release();
	// パイプラインにルートシグネチャをセット
	pipelineDesc.pRootSignature = rootsignature.Get();

	// パイプラインステートの生成
	result = dxCommon_->GetDevice()->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
	assert(SUCCEEDED(result));
}

//void Pipeline::CreateModelPipeline()
//{
//	HRESULT result;
//	dxCommon_->GetInstance();
//
//	// 頂点レイアウト
//	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
//		{ // xyz座標
//			"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
//		},
//		{ // 法線
//			"NORMAL",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
//		},
//		{ // カラー
//			"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
//		},
//	};
//	// グラフィックスパイプライン設定
//	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
//
//	// 頂点シェーダ、ピクセルシェーダをパイプラインに設定
//	pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
//	pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
//	pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
//	pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();
//	// サンプルマスクの設定
//	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定
//	// ラスタライザの設定
//	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;	// カリングしない
//	//pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_FRONT;	// 前面カリング
//	//pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;	// 背面カリング
//	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;	// ポリゴン内塗りつぶし
//	pipelineDesc.RasterizerState.DepthClipEnable = true;			// 深度クリッピングを有効に
//	// ブレンドステート
//	pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask
//		= D3D12_COLOR_WRITE_ENABLE_ALL;		// RGBA全てのチャンネルを描画
//	// 頂点レイアウトの設定
//	pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
//	pipelineDesc.InputLayout.NumElements = _countof(inputLayout);
//	// 図形の形状設定
//	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE; // 三角形
//	// その他の設定
//	pipelineDesc.NumRenderTargets = 1; // 描画対象は1つ
//	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255指定のRGBA
//	pipelineDesc.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング
//
//	// ルートシグネチャの設定
//	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
//	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_STREAM_OUTPUT;
//	// ルートシグネチャのシリアライズ
//	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
//		&rootSigBlob, &errorBlob);
//	assert(SUCCEEDED(result));
//	result = dxCommon_->GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
//		IID_PPV_ARGS(&rootsignature));
//	assert(SUCCEEDED(result));
//	rootSigBlob->Release();
//	// パイプラインにルートシグネチャをセット
//	pipelineDesc.pRootSignature = rootsignature.Get();
//
//	// パイプラインステートの生成
//	result = dxCommon_->GetDevice()->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
//	assert(SUCCEEDED(result));
//}
