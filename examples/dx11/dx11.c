#define RGFW_IMPLEMENTATION
#define RGFW_DIRECTX
#define RGFW_DEBUG
#include "RGFW.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#if _MSC_VER
#pragma comment(lib, "uuid")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "windowscodecs.lib")
#endif

typedef struct {
	IDXGIFactory* pFactory;
	IDXGIAdapter* pAdapter;
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pDeviceContext;

    IDXGISwapChain* swapchain;
    ID3D11RenderTargetView* renderTargetView;
    ID3D11DepthStencilView* pDepthStencilView;
} directXinfo;

#define MULTILINE_STR(...) #__VA_ARGS__

const char* shaderString = MULTILINE_STR(
    struct VOut
    {
        float4 position : SV_POSITION;
    };

    VOut VS(float3 position : POSITION)
    {
        VOut output;
        output.position = float4(position, 1.0);

        return output;
    }


    float4 PS(VOut input) : SV_TARGET
    {
        float z = (input.position.y * 0.095) +  (input.position.x  *  0.09);

        return float4(input.position.y / 255, input.position.x / 255, z / 255, 1.0);
    }
);

int directXInit(RGFW_window* win, directXinfo* info);
void directXClose(RGFW_window* win, directXinfo* dxInfo);

int main(void) {
    RGFW_window* win = RGFW_createWindow("name", 0, 0, 500, 500, RGFW_windowCenter);
    RGFW_window_setExitKey(win, RGFW_escape);

    directXinfo dxInfo;
    if (directXInit(win, &dxInfo) == 0) {
        printf("failed to create a directX context\n");
        return 1;
    }

    dxInfo.pDeviceContext->lpVtbl->OMSetRenderTargets(dxInfo.pDeviceContext, 1, &dxInfo.renderTargetView, NULL);

    // Set viewport
    D3D11_VIEWPORT viewport;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = win->w;
    viewport.Height = win->h;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    dxInfo.pDeviceContext->lpVtbl->RSSetViewports(dxInfo.pDeviceContext, 1, &viewport);

    float vertices[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    ID3D11Buffer* pVertexBuffer;
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = sizeof(vertices);
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    dxInfo.pDevice->lpVtbl->CreateBuffer(dxInfo.pDevice, &bd, NULL, &pVertexBuffer);

    // Copy vertex data into vertex buffer
    D3D11_MAPPED_SUBRESOURCE ms;
    dxInfo.pDeviceContext->lpVtbl->Map(dxInfo.pDeviceContext, (ID3D11Resource*)pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
    memcpy(ms.pData, vertices, sizeof(vertices));
    dxInfo.pDeviceContext->lpVtbl->Unmap(dxInfo.pDeviceContext, (ID3D11Resource*)pVertexBuffer, 0);

    // Compile shaders
    ID3D10Blob* pVertexShaderBlob = NULL;
    ID3D10Blob* pPixelShaderBlob = NULL;
    ID3D10Blob* pErrorBlob = NULL;

    D3DCompile(shaderString, strlen(shaderString), NULL, NULL, NULL, "VS", "vs_5_0", 0, 0, &pVertexShaderBlob, &pErrorBlob);
    D3DCompile(shaderString, strlen(shaderString), NULL, NULL, NULL, "PS", "ps_5_0", 0, 0, &pPixelShaderBlob, &pErrorBlob);

    // Create shaders
    ID3D11VertexShader* pVertexShader;
    ID3D11PixelShader* pPixelShader;
    dxInfo.pDevice->lpVtbl->CreateVertexShader(dxInfo.pDevice, pVertexShaderBlob->lpVtbl->GetBufferPointer(pVertexShaderBlob), pVertexShaderBlob->lpVtbl->GetBufferSize(pVertexShaderBlob), NULL, &pVertexShader);
    dxInfo.pDevice->lpVtbl->CreatePixelShader(dxInfo.pDevice, pPixelShaderBlob->lpVtbl->GetBufferPointer(pPixelShaderBlob), pPixelShaderBlob->lpVtbl->GetBufferSize(pPixelShaderBlob), NULL, &pPixelShader);

    dxInfo.pDeviceContext->lpVtbl->VSSetShader(dxInfo.pDeviceContext, pVertexShader, 0, 0);
    dxInfo.pDeviceContext->lpVtbl->PSSetShader(dxInfo.pDeviceContext, pPixelShader, 0, 0);

    // Set input layout
    ID3D11InputLayout* pInputLayout;
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    dxInfo.pDevice->lpVtbl->CreateInputLayout(dxInfo.pDevice, layout, 1, pVertexShaderBlob->lpVtbl->GetBufferPointer(pVertexShaderBlob), pVertexShaderBlob->lpVtbl->GetBufferSize(pVertexShaderBlob), &pInputLayout);
    dxInfo.pDeviceContext->lpVtbl->IASetInputLayout(dxInfo.pDeviceContext, pInputLayout);

    for (;;) {
        RGFW_pollEvents();

        if (RGFW_window_shouldClose(win))
            break;

        float clearColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
        dxInfo.pDeviceContext->lpVtbl->ClearRenderTargetView(dxInfo.pDeviceContext, dxInfo.renderTargetView, clearColor);

        UINT stride = sizeof(float) * 3;
        UINT offset = 0;
        dxInfo.pDeviceContext->lpVtbl->IASetVertexBuffers(dxInfo.pDeviceContext, 0, 1, &pVertexBuffer, &stride, &offset);

        dxInfo.pDeviceContext->lpVtbl->IASetPrimitiveTopology(dxInfo.pDeviceContext, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        dxInfo.pDeviceContext->lpVtbl->IASetInputLayout(dxInfo.pDeviceContext, pInputLayout);

        dxInfo.pDeviceContext->lpVtbl->VSSetShader(dxInfo.pDeviceContext, pVertexShader, NULL, 0);
        dxInfo.pDeviceContext->lpVtbl->PSSetShader(dxInfo.pDeviceContext, pPixelShader, NULL, 0);
        dxInfo.pDeviceContext->lpVtbl->Draw(dxInfo.pDeviceContext, 3, 0);

        dxInfo.swapchain->lpVtbl->Present(dxInfo.swapchain, 0, 0);
    }

    directXClose(win, &dxInfo);

    RGFW_window_close(win);
}

int directXInit(RGFW_window* win, directXinfo* info) {
	RGFW_ASSERT(FAILED(CreateDXGIFactory(&__uuidof(IDXGIFactory), (void**) &info->pFactory)) == 0);

	if (FAILED(info->pFactory->lpVtbl->EnumAdapters(info->pFactory, 0, &info->pAdapter))) {
		#ifdef RGFW_DEBUG
			fprintf(stderr, "Failed to enumerate DXGI adapters\n");
		#endif
		info->pFactory->lpVtbl->Release(info->pFactory);
		return 0;
	}

	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

	if (FAILED(D3D11CreateDevice(info->pAdapter, D3D_DRIVER_TYPE_UNKNOWN, NULL, 0, featureLevels, 1, D3D11_SDK_VERSION, &info->pDevice, NULL, &info->pDeviceContext))) {
		#ifdef RGFW_DEBUG
			fprintf(stderr, "Failed to create Direct3D device\n");
		#endif
		info->pAdapter->lpVtbl->Release(info->pAdapter);
		info->pFactory->lpVtbl->Release(info->pFactory);
		return 0;
	}

	RGFW_window_createSwapChain_DirectX(win, info->pFactory, (IUnknown*)info->pDevice, &info->swapchain);

	ID3D11Texture2D* pBackBuffer;
	info->swapchain->lpVtbl->GetBuffer(info->swapchain, 0, &__uuidof(ID3D11Texture2D), (LPVOID*) &pBackBuffer);
	info->pDevice->lpVtbl->CreateRenderTargetView(info->pDevice, (ID3D11Resource*) pBackBuffer, NULL, &info->renderTargetView);
	pBackBuffer->lpVtbl->Release(pBackBuffer);

	D3D11_TEXTURE2D_DESC depthStencilDesc = { 0 };
	depthStencilDesc.Width = win->w;
	depthStencilDesc.Height = win->h;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	ID3D11Texture2D* pDepthStencilTexture = NULL;
	info->pDevice->lpVtbl->CreateTexture2D(info->pDevice, &depthStencilDesc, NULL, &pDepthStencilTexture);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = { 0 };
	depthStencilViewDesc.Format = depthStencilDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	info->pDevice->lpVtbl->CreateDepthStencilView(info->pDevice, (ID3D11Resource*) pDepthStencilTexture, &depthStencilViewDesc, &info->pDepthStencilView);

	pDepthStencilTexture->lpVtbl->Release(pDepthStencilTexture);

	info->pDeviceContext->lpVtbl->OMSetRenderTargets(info->pDeviceContext, 1, &info->renderTargetView, info->pDepthStencilView);

	return 1;
}

void directXClose(RGFW_window* win, directXinfo* dxInfo) {
    dxInfo->swapchain->lpVtbl->Release(dxInfo->swapchain);
    dxInfo->renderTargetView->lpVtbl->Release(dxInfo->renderTargetView);
    dxInfo->pDepthStencilView->lpVtbl->Release(dxInfo->pDepthStencilView);

    dxInfo->pDeviceContext->lpVtbl->Release(dxInfo->pDeviceContext);
    dxInfo->pDevice->lpVtbl->Release(dxInfo->pDevice);
    dxInfo->pAdapter->lpVtbl->Release(dxInfo->pAdapter);
    dxInfo->pFactory->lpVtbl->Release(dxInfo->pFactory);
}
