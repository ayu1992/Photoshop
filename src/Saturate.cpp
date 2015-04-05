#include "Saturate.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

Saturate::Saturate(int size){};
Saturate::~Saturate(){};

void Saturate::applySaturate(PixelBuffer * canvas, float level){
	float r,g,b,min,max,h,s,v,delta;
	float f, p, q, t;
	long quad;
	for(int x = 0; x < canvas->getWidth(); x++){
		for(int y = 0; y < canvas->getHeight(); y++){
			ColorData c = canvas->getPixel(x,y);
			r = c.getRed();
			g = c.getGreen();
			b = c.getBlue();
			// convert to HSV color space
			
        	max = std::max(std::max(r, g), b);
        	delta = (max - min);

			if( max <= 0.0 ){		// r = g = b = 0        // s = 0, v is undefined
				s = 0.0;
            	h = -1;
            	v = 0;		 
            
			}else{
				min = std::min(std::min(r, g), b);
				//set up v
        		v = max;
        		//set up s	
				s = level;
				//set up h
				
            	if (r >= max) h = (g-b)/delta;
            	if (g >= max) h = 2.0 + ( b - r ) / delta;
            	if (b >= max) h = 4.0 + ( r - g ) / delta;
 		    	h *= 60;	//convert to degrees
 		    	if (h < 0)	h += 360;	
			}
			
 		    // convert back to rgb
 		    if (s == 0)	{
 		    	canvas->setPixel(x,y,ColorData(v,v,v).clampedColor());
 		    	continue;
 		    }
			if(h >= 360.0) h = 0.0;
 		    h /= 60;			// sector 0 to 5
			quad = (long) h ;
			f = h - quad;			// factorial part of h
			p = v * ( 1.0 - s );
			q = v * ( 1.0 - s * f );
			t = v * ( 1.0 - s * ( 1.0 - f ) );
			
			switch(quad){
				case 0:
					canvas->setPixel(x,y,ColorData(v,t,p).clampedColor());
 		    		break;
 		    	case 1:
 		    		canvas->setPixel(x,y,ColorData(q,v,p).clampedColor());
 		    		break;
 		    	case 2:
 		    		canvas->setPixel(x,y,ColorData(p,v,t).clampedColor());
 		    		break;
 		    	case 3:
 		    		canvas->setPixel(x,y,ColorData(p,q,v).clampedColor());
 		    		break;
 		    	case 4:
 		    		canvas->setPixel(x,y,ColorData(t,p,v).clampedColor());
 		    		break;
 		    	default:
 		    		canvas->setPixel(x,y,ColorData(v,p,q).clampedColor());
 		    		break;
			}
		}
	}
}
