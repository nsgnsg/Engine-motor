#define MAX_LIGHTS 8
varying vec2 ftex;
uniform bool isTexturized;
uniform sampler2D texSampler;

uniform int numLights;
uniform int shininess;
uniform vec3 ambient;


uniform vec4 materialColor;

varying vec3 fnormal;
varying vec3 fpos;

uniform bool isDirectional[MAX_LIGHTS];
uniform vec4 posLight[MAX_LIGHTS];
uniform vec3 colorLight[MAX_LIGHTS];
uniform float linearAtt[MAX_LIGHTS];



void main() {

	vec3 finalDiffuse = numLights > 0? ambient: vec3(1, 1, 1);
	float finalSpecular = 0.0;

	
	vec3 N = normalize(fnormal);
	vec3 L,H;
	float att,NdotH, cos_eta;
	
	//if(lighting){
		for(int i = 0; i < numLights; i++) {
			
			cos_eta = 0.0;
			att = 1.0;
			L = posLight[i].xyz;
			
			if (!isDirectional[i]) {
				L = L - fpos;
				att = 1.0 / (1.0 + linearAtt[i] * length(L));
			}
			
			L = normalize(L);
			cos_eta = max(0, dot(N, L));
			
			finalDiffuse = finalDiffuse + (cos_eta * att) * colorLight[i];
			
			if (shininess > 0 && cos_eta > 0.0) {
				H = normalize(L - normalize(fpos));
				NdotH = max(0, dot(N,H));
				if(NdotH > 0){
					finalSpecular += (pow(NdotH, shininess) * att); 
				}
				
			}
		}
	//}
	
	vec4 finalColor = vec4(1,1,1,1);
	if(isTexturized)
		finalColor *= texture2D(texSampler, ftex);
	
	
	finalColor = finalColor * materialColor;
	
	if(numLights > 0)
		finalColor *= vec4(finalDiffuse, 1);
	
	
	vec4 specularVec = vec4 (finalSpecular,finalSpecular,finalSpecular,0);
	finalColor += specularVec; 
	
	gl_FragColor = finalColor;
	
	
	
	
	
}