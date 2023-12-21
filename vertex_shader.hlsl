// Input structure from the application
struct VSInput
{
    float3 position : POSITION;
    float4 color : COLOR;
};

// Output structure to the pixel shader
struct VSOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

// Main vertex shader function
VSOutput main(VSInput input)
{
    VSOutput output;
    
    // Transform the vertex position to clip space
    output.position = float4(input.position, 1.0f);
    
    // Pass the color to the pixel shader
    output.color = input.color;

    return output;
}