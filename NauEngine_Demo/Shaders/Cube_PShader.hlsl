// Texture2D tex : register(t0);
// SamplerState samp : register(s0);

struct PSInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD0;
};

float4 main(PSInput input) : SV_TARGET
{
    // float4 color = tex.Sample(samp, input.texcoord);
    // return color;
    // float4 color = float4(input.texcoord, 0, 1);
    float4 color = float4(sin(input.texcoord.x * 40) * sin(input.texcoord.y * 30), 0, 0, 1);
    color.x = color * 0.5 + 0.5;
    color.z = 1 - color.x;
    return color;
}
