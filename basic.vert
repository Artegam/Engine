#version 430
in vec4 vp;
in vec3 vn;

//uniform vec3 Ld; //Light source intensity - voir setuniform(name, values);
in vec4 Kd; //Diffuse reflectivity

out vec3 LightIntensity;
 
void main() {
	vec4 v = gl_ModelViewMatrix * vp;	//eye coordinates
	vec3 s = normalize(gl_LightSource[0].position.xyz - v.xyz); //vector s (light - surface)
	
  vec3 norm = normalize(gl_NormalMatrix * vn); //vector normal
	
	
	vec3 v2 = normalize(-v.xyz);
	vec3 r = reflect( -s, norm); // vecteur de reflechissement
//	vec3 ambient = gl_LightSource[0].ambient * Ka.xyz;
	vec3 ambient = gl_LightSource[0].ambient.xyz * vec3(0.1, 0.1, 0.1);
	
	float sDotN = max( dot(s, norm), 0.0);
	
	//the diffuse shading equation
//	LightIntensity = Ld * Kd * max( dot(s, norm), 0.0); // max elimine les valeurs negatives
//	LightIntensity = gl_LightSource[0].diffuse.xyz * vec3(0.8, 0.0, 0.0) * max( dot(s, norm), 0.0); // max elimine les valeurs negatives
//	LightIntensity = gl_LightSource[0].diffuse.xyz * Kd.xyz * max( dot(s, norm), 0.0); // max elimine les valeurs negatives
	vec3 diffuse = gl_LightSource[0].diffuse.xyz * Kd.xyz * sDotN; // max elimine les valeurs negatives
	vec3 spec = vec3(0.0);
	if (sDotN > 0.0)
		spec = gl_LightSource[0].specular.xyz * vec3(0.2, 0.2, 0.2) * pow( max( dot(r, v2), 0.0), 0.5);
		//spec = gl_LightSource[0].specular * Ks * pow( max( dot(r,v), 0.0), Shininess);
		
	LightIntensity = ambient + diffuse + spec;
  
	gl_Position = gl_ModelViewProjectionMatrix * vp;
};