struct PSInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD0;
};

float4 main(PSInput input) : SV_Target
{
    float r = sin(input.texcoord.x * 40) * sin(input.texcoord.y * 30);
    
    r = r * 0.5 + 0.5;
    
    float4 color = float4(r, 0, 1 - r, 1);
    return color;
}
