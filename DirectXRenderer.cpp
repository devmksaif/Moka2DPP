#include "DirectXRenderer.h"


WORD indices[] = { 0, 1, 2 ,3 };  // Assuming a triangle with vertices at indices 0, 1, and 2



void DirectRenderer::InitRenderer(HWND handler)
{
    InitSwapChainAndRenderer(handler);
    CreateBuffers();
    CreateShaders();
    CreateTriangle();
}

void DirectRenderer::InitSwapChainAndRenderer(HWND handler)
{
    // Create a DXGI_SWAP_CHAIN_DESC structure
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = 800;                         // Width of the back buffer
    swapChainDesc.BufferDesc.Height = 600;                        // Height of the back buffer
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Pixel format
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;          // Refresh rate numerator
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;         // Refresh rate denominator
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   // How the swap chain will be used
    swapChainDesc.OutputWindow = handler;                             // Handle to the output window
    swapChainDesc.SampleDesc.Count = 1;                            // Number of multisamples per pixel
    swapChainDesc.SampleDesc.Quality = 0;                         // Image quality level
    swapChainDesc.Windowed = TRUE;                                // Windowed mode


    HRESULT result = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
        0, nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc,
        &pSwapChain, &pDevice, nullptr, &pDeviceContext);




   
}

void DirectRenderer::CreateBuffers()
{
    // Create a back buffer (usually index 0)
    ID3D11Texture2D* backBuffer;
    pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));

    // Create render target view
    pDevice->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);

    // Release the back buffer
    backBuffer->Release();

    pDeviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
    D3D11_VIEWPORT viewport = {};
    viewport.Width = static_cast<FLOAT>(1280); // Set your window width
    viewport.Height = static_cast<FLOAT>(720); // Set your window height
    viewport.MaxDepth = 0.2f;
    pDeviceContext->RSSetViewports(1, &viewport);

}

void DirectRenderer::CreateShaders()
{
    // Load compiled shader bytecode from .cso files
    std::ifstream vsFile("vertex_shader.cso", std::ios::binary);
    std::ifstream psFile("pixel_shader.cso", std::ios::binary);

    std::vector<char> vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
    std::vector<char> psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };

    // Create vertex shader
    pDevice->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertexShader);

    // Create pixel shader
    pDevice->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixelShader);

    // Create input layout
    D3D11_INPUT_ELEMENT_DESC inputLayoutDesc[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    pDevice->CreateInputLayout(inputLayoutDesc, 2, vsData.data(), vsData.size(), &inputLayout);
}



void DirectRenderer::CreateTriangle()
{
    Vertex vertices[] = {
         {XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
        {XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
        {XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)}
    };

    D3D11_BUFFER_DESC vertexBufferDesc = {};
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(vertices);
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vertexData = {};
    vertexData.pSysMem = vertices;

    // Create index buffer
    D3D11_BUFFER_DESC indexBufferDesc = {};
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(indices);
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA indexData = {};
    indexData.pSysMem = indices;

    pDevice->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
    pDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
}

void DirectRenderer::SetShaders()
{
    pDeviceContext->IASetInputLayout(inputLayout);
    pDeviceContext->VSSetShader(vertexShader, nullptr, 0);
    pDeviceContext->PSSetShader(pixelShader, nullptr, 0);
}

void DirectRenderer::RenderTriangle()
{
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    // Before drawing the triangle

    // Set vertex and index buffers
    pDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    pDeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);

    // Set the primitive topology
    pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Draw using indices
    pDeviceContext->DrawIndexed(3, 1, 0);
}






void DirectRenderer::Draw()
{
    float clear_Color[] = { 1.f, 1.f , 0.f, 1.0f };
    pDeviceContext->ClearRenderTargetView(renderTargetView, clear_Color);
    SetShaders();

    RenderTriangle();

    // Present the frame
    pSwapChain->Present(1, 0);
}

void DirectRenderer::CleanUp()
{
    renderTargetView->Release();
    pSwapChain->Release();
    pDeviceContext->Release();
    pDevice->Release();
}
