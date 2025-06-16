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
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD0;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD0;
};

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
    output.position = float4(input.position, 1) * 0.1 + float4(0.5, 0.5, 2, 0);
    
    return output;
}
