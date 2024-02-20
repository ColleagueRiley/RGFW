struct VOut
{
    float4 position : SV_POSITION;
};

VOut VS(float4 position : POSITION)
{
    VOut output;

    output.position = position;

    return output;
}


float4 PS(float4 position : SV_POSITION) : SV_TARGET
{
    return float4(1.0, 0.0, 0.0, 1.0);
}