#include "d3d11.h"
#include <DirectXMath.h>
#include <dxgi.h>
#include <fstream>
#include <vector>

using namespace DirectX;

class DirectRenderer
{
public:
    struct Vertex {
        XMFLOAT3 position;
        XMFLOAT4 color;
        // Add texture coordinates if needed: XMFLOAT2 texCoord;
    };



    // Define indices


    // Create the swap chain
    IDXGISwapChain* pSwapChain = nullptr;
    ID3D11DeviceContext* pDeviceContext = nullptr;
    ID3D11Device* pDevice = nullptr;
    ID3D11RenderTargetView* renderTargetView;
    ID3D11Buffer* vertexBuffer;
    ID3D11Buffer* indexBuffer;

    // After initializing DirectX
    ID3D11VertexShader* vertexShader = nullptr;
    ID3D11PixelShader* pixelShader = nullptr;
    ID3D11InputLayout* inputLayout = nullptr;

    void InitRenderer(HWND handler);
    void InitSwapChainAndRenderer(HWND handler);
    void CreateBuffers();
    void CreateShaders();
    void CreateTriangle();
    void SetShaders();
    void RenderTriangle();
    void Draw();
    void CleanUp();
};