// ピクセルシェーダーの入力
struct PS_INPUT {
	float4 DiffuseColor       : COLOR0;
	float4 SpecularColor      : COLOR1;
	float2 TextureCoord0      : TEXCOORD0;
	float2 TextureCoord1      : TEXCOORD1;
};

// ピクセルシェーダーの出力
struct PS_OUTPUT {
	float4 Output             : COLOR0;
};

// 描画するテクスチャ
sampler mapTexture   : register(s0);
sampler lightTexture : register(s1);

PS_OUTPUT main(PS_INPUT PSInput) {
	PS_OUTPUT PSOutput;
	float4 outTextureColor;
	float4 lightTextureColor;

	outTextureColor   = tex2D(mapTexture, PSInput.TextureCoord0);
	lightTextureColor = tex2D(lightTexture, PSInput.TextureCoord0);

	outTextureColor.r = outTextureColor.r + (-outTextureColor.r) * (1.0 - lightTextureColor.r);
	outTextureColor.g = outTextureColor.g + (-outTextureColor.g) * (1.0 - lightTextureColor.g);
	outTextureColor.b = outTextureColor.b + (-outTextureColor.b) * (1.0 - lightTextureColor.b);

	PSOutput.Output = outTextureColor;
	return PSOutput;
}