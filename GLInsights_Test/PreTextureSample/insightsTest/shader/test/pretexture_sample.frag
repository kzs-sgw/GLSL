 #version 440

// pretexture_sample.frag
in vec3 originalPos;
in vec3 originalNorm;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

// 元の値
in vec3 v10; //vu U軸単位ベクトルに対応したベクトル
in vec3 v20; //vv V軸単位ベクトルに対応したベクトル
in vec3 v0c;

// 座標変換後
in vec3 v10x; //vu U軸単位ベクトルに対応したベクトル
in vec3 v20x; //vv V軸単位ベクトルに対応したベクトル
in vec3 v0cx;


//in vec3 spherePos;

uniform sampler2D Tex1;
uniform vec3 camera;
uniform vec3 spherePos;

// for debug //--------------------------------------------------
uniform cameraMat
{
  mat4 ModelViewMatrix;
  mat4 ModelViewProjectionMatrix;
  mat3 NormalMatrix;
  //mat4 ProjectionMatrix;
};

uniform mat4 MVI;

float nRatio = 1.491;


   
//---------------------------------------------------------------

struct LightInfo
{
  vec4 Position;
  vec3 Intensity;
};
uniform LightInfo Light;

struct MaterialInfo
{
  vec3 Ka;
  vec3 Kd;
  vec3 Ks;
  float Shininess;
};
uniform MaterialInfo Material;

layout( location = 0 ) out vec4 FragColor;



void pupilTexture( vec3 pos, vec3 norm, out vec2 alteredTexCoord )
{
  // 角度を２つcos項から求め、正規化する
  // それをテクスチャ座標に変換
}




void phongModel( vec3 pos, vec3 norm, out vec3 ambAndDiff, out vec3 spec )
{
  vec3 s = normalize( vec3( Light.Position ) - pos );
  vec3 v = normalize( -pos.xyz );
  vec3 r = reflect( -s, norm );
  vec3 ambient = Light.Intensity * Material.Ka;
  float sDotN = max( dot(s,norm), 0.0 );
  vec3 diffuse = Light.Intensity * Material.Kd * sDotN;
  spec = vec3(0.0);
  if( sDotN > 0.0 )
    spec = Light.Intensity * Material.Ks *
               pow( max( dot(r,v), 0.0 ), Material.Shininess );
  //spec = Light.Intensity * Material.Ks * pow( max( dot(r,v), 0.0 ), Material.Shininess );

  ambAndDiff = ambient + diffuse;
}

void main()
{
  //vec3 ambAndDiff, spec;
  //phongModel( Position, Normal, ambAndDiff, spec );
  vec2 altTexCoord;
  calcTexCoordForPupil( originalPos, originalNorm, 5.0, altTexCoord ); // radiusの値に気をつける
  //calcTexCoordForPupil_plural( originalPos, originalNorm, 0.5, altTexCoord ); // radiusの値に気をつける
  //calcTexCoordForPupil2( Position, Normal, 5.0, altTexCoord );
  vec4 texColor = texture( Tex1, altTexCoord );
  
  FragColor = 0.7*texColor;
//FragColor = vec4(camera.xyz,1.0);
  //FragColor = (vec4( ambAndDiff, 1.0 ) * texColor) + vec4(spec, 1.0);
}
  
 
 
