#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <vector>
#include <cfloat> // FLT_MAX
#include <iostream>
#include <limits>
#include <cstddef>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
using namespace std;

#include "object3d.h"
#include "scene_parser.h"

#include "image.h"
#include "vectors.h"
#include "sphere.h"
#include "camera.h"
#include "ray.h"
#include "hit.h"
#include "group.h"
#include "matrix.h"
#include "light.h"

#include "normal.h"
#include "shader.h"
#include "diffuse.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

float clamp(float a)
{
    if(a > 1.0f)
        return 1.0f;
    else if(a < 0.0f)
        return 0.0f;
    else
        return a;
}

float specularExponent(Ray r, Hit h, Vec3f dir)
{
    // (h.n)^e -- h=halfway vector (direction+view)/|(direction+view)|, n = normal
    Vec3f view = r.getDirection(); view.Negate(); 
    Vec3f half = (dir+view); half.Normalize(); // Halfway vector
    float t = half.Dot3(h.getNormal()); t = max(0.0f,t);
    return t;
}
int main(int argc, char** argv) {
	
char *input_file = NULL;
int width = 100;
int height = 100;
char *output_file = NULL;
float depth_min = 0;
float depth_max = 1;
char *normal_file = NULL;
char *depth_file = NULL;
// sample command lines:
// raycast -input scene.txt -size 100 100 -output output.tga
//raycast -input scene.txt -size 100 100 -normal normal.tga


	for (int i = 1; i < argc; i++) {
  if (!strcmp(argv[i],"-input")) {
    i++; assert (i < argc); 
    input_file = argv[i];
   
  } else if (!strcmp(argv[i],"-size")) {
    i++; assert (i < argc); 
    width = atoi(argv[i]);
    i++; assert (i < argc); 
    height = atoi(argv[i]);
  } else if (!strcmp(argv[i],"-output")) {
    i++; assert (i < argc); 
    output_file = argv[i];
  } else if (!strcmp(argv[i],"-depth")) {
    i++; assert (i < argc); 
    depth_min = atof(argv[i]);
    i++; assert (i < argc); 
    depth_max = atof(argv[i]);
    i++; assert (i < argc); 
    depth_file = argv[i];
  }else if(!strcmp(argv[i],"-normal")){
            i++; assert(i<argc);
            normal_file = argv[i];
        }else {
    printf ("whoops error with command line argument %d: '%s'\n",i,argv[i]);
    assert(0);
  }
}

 // Define Image Files
    Image *output_image = new Image(width, height);
    Image *normal_image = new Image(width, height);
    Image *depth_image = new Image(width, height);
    // Read input file
    SceneParser *s = new SceneParser(input_file);
    Camera *c = s->getCamera();
    Group *g = s->getGroup();
   
Vec3f background = s->getBackgroundColor();
output_image->SetAllPixels(background);
normal_image->SetAllPixels(background);
depth_image->SetAllPixels(background);


 // Set output files
    bool out=false, normout=false, depthout=false;
    if(output_file != NULL)
        out = true;
    if(normal_file != NULL)
        normout = true;
   if(depth_file != NULL)
        depthout = true;

    /*vector<std::function<void()> > tasks(height);*/

  for(int i=0;i<width;i+=1){
		
			for(int j=0;j<height;j+=1) {
				Ray ray = c->generateRay(Vec2f(i*1.0f/width,j*1.0f/height));
	         	int tmin=FLT_MIN; 
				Hit hit=Hit(FLT_MAX,Vec3f(1,0,0),Vec3f(0,0,0));
				bool isNear=g->intersect(ray,hit,tmin);
			
				
				if(out==false && isNear== true) {
				NormalShader normal;
				Vec3f color = hit.getColor();
				Vec3f currentcolor=normal.shading(color, &hit, s);
                normal_image->SetPixel(i,j,currentcolor);
                 }
              
                    
				if(normout==false && isNear==true){
				  DiffuseShader diffuse;
				  Vec3f color = hit.getColor();
				  Vec3f currentcolor=diffuse.shading(color, &hit, s);
			      output_image->SetPixel(i,j,currentcolor);
			      
			        }
		
			
	 	        }  
	 	
       }

	 //save tga   
			if(normal_file != NULL)
			{
			normal_image->SaveTGA(normal_file);
     	 	cout<<normal_file<<endl;
			}
 			if(output_file != NULL)   	
			{
	 		output_image->SaveTGA(output_file);
   			cout<<output_file<<endl;	
		    }
         	if(depth_file != NULL)
         	{
         	depth_image->SaveTGA(output_file);
   			cout<<depth_image<<endl;
		 	}
}

