#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include "../2d/Sprite.h"
#include "../Engine/WindowsApp.h"
#include <d3dcompiler.h>
#include "../Engine/Input.h"

using namespace DirectX;
using namespace Microsoft::WRL;

#pragma comment(lib, "d3dcompiler.lib")

class TransEffect :public Sprite
{
private: // エイリアス
// Microsoft::WRL::を省略
    template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
    // DirectX::を省略
    using XMFLOAT2 = DirectX::XMFLOAT2;
    using XMFLOAT3 = DirectX::XMFLOAT3;
    using XMFLOAT4 = DirectX::XMFLOAT4;
    using XMMATRIX = DirectX::XMMATRIX;

public:

    //コンストラクタ
   /* PostEffect();*/

    static TransEffect* Create(SpriteCommon* spriteCommon, UINT texNumber, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);
    void Initialize(SpriteCommon* spriteCommon, UINT texNumber, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);
    
    //描画
    void Draw(ID3D12GraphicsCommandList* cmdList);

    //シーン描画前処理
    void PreDrawScene(ID3D12GraphicsCommandList* cmdList);
    //シーン描画後処理
    void PostDrawScene(ID3D12GraphicsCommandList* cmdList);
    //パイプライン生成
    void CreateGraphicsPipelineState();

    struct ConstBufferDatat {
        XMFLOAT4 color; // 色 (RGBA)
        XMMATRIX mat;   // ３Ｄ変換行列
        float time;
        float alpha;//アルファ
        float Move;//ブロックノイズの大きさ
    };


private:
    //テクスチャバッファ
    ComPtr<ID3D12Resource> texBuff[2];
    //SRV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap> descHeapSRV;
    //深度バッファ
    ComPtr<ID3D12Resource> depthBuff;
    //RTV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap> descHeapRTV;
    //DSV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap> descHeapDSV;
    //グラフィックスパイプライン
    ComPtr<ID3D12PipelineState> pipelineState;
    //ルートシグネチャ
    ComPtr<ID3D12RootSignature> rootSignature;


private:
    //画面クリアカラー
    static const float clearColor[4];
};

