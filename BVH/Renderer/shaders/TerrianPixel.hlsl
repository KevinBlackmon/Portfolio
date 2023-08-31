#include "mvp.hlsli"

struct PSIn
{
    float4 pos : SV_POSITION;
    float3 nrm : NORMAL;
    float2 uv : UV;
};


float4 main(PSIn inputVert) : SV_Target
{
    float4 sunDirect = normalize(float4(0, -15, 0, 1));
    inputVert.nrm = normalize(inputVert.nrm);
    float dotprod = dot(-sunDirect.xyz, inputVert.nrm);
    float4 diffuse = float4(.75f, .90f, .75f, 1);
    
    return saturate(dotprod * diffuse);
}