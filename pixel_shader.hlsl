// Input structure from the vertex shader
struct PSInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

// Output structure to the render target
struct PSOutput
{
    float4 color : SV_TARGET;
};

// Main pixel shader function
PSOutput main(PSInput input)
{
    PSOutput output;
    
    // Output the color directly to the render target
    output.color = input.color;

    return output;
}