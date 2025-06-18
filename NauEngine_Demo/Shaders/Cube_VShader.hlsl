/*
cbuffer MatrixBuffer : register(b0)
{
    float4x4 world;
    float4x4 view;
    float4x4 proj;
};
*/

struct VSInput
{
    float3 position : POSITION;
    float4 color : COLOR;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD0;
};

cbuffer TransformCBuf : register(b0)
{
    row_major float4x4 wMat;
    row_major float4x4 wInvTransposeMat;
}

cbuffer CameraCBuf : register(b1)
{
    row_major float4x4 viewProjMat;
}

VSOutput main(VSInput input)
{
    VSOutput output;
    /*
    float4 worldPos = mul(float4(input.position, 1.0f), world);
    worldPos = mul(worldPos, view);
    worldPos = mul(worldPos, proj);
    output.normal = mul(float4(input.normal, 0.0f), world).xyz;
    output.texcoord = input.texcoord;
    output.position = worldPos;
    */
    output.normal = input.normal;
    output.texcoord = input.texcoord;
    float4 worldPos = mul(float4(input.position, 1.0f), wMat);
    //float4 worldPos = float4(input.position * 0.1, 1) * float4(0.9, 1.6, 1, 1) + float4(0.5, 0.5, 0.5, 0);
    worldPos = mul(worldPos, viewProjMat);
    output.position = worldPos;
    
    return output;
}
