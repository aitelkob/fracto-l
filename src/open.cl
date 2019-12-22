# define WIN_X 1000
# define WIN_Y 1000
# define inde(x,y,width) 4*width*y +x*4;

double maps(double y, double Immin, double Immax)
{
  return y*(Immax - Immin) + Immin;
}
int     get_color(int   maxitration,int n)
{
    double t;
    int     r,g,b;

    t = (double)n / (double)maxitration;
    r = (int)(9*(1-t)*t*t*t*255);
    g = (int)(15*(1-t)*(1-t)*t*t*255);
    b = (int)(8.5*(1-t)*(1-t)*(1-t)*t*255);
    return (((r&0x0ff)<<16)|((g&0x0ff)<<8)|(b&0x0ff));
}

__kernel void fractals(__global char *ouput,
					__global double *buffer)
{	
		int n;
		int res;
		double  a;
		double  b;
		double  AA;
		double  BB;
		double  ab;
		double	bb;
		double	SQR;
		double	SQI;
		double	zoom_rn = buffer[0];
        double  zoom_rx = buffer[1];
		double	zoom_in = buffer[2];
		double	zoom_ix = buffer[3];
		double  mouse_x =(double) buffer[4];
		double  mouse_y = (double) buffer[6];
		int maxitration	= buffer[5];
		int	shape = buffer[7];

		int	color = 0;
		n = 0;
		res = 0;
		int	x_dim = get_global_id(0);
		int y_dim = get_global_id(1);
		int idx = inde(x_dim, y_dim, WIN_X);
		a = maps((double)x_dim /WIN_X,zoom_rx,zoom_rn);
		b = maps((double)y_dim /WIN_Y,zoom_ix,zoom_in);
		AA = a;
		BB = b;
		if (shape == 1)
		{
			  while (n < maxitration)
 				  {
     				ab = a * a - b * b ;
  				    bb = 2 * a * b;
          		    a = ab + AA;
                    b = bb + BB;
                    if (a * a + b * b > 4)
							 break;
         			 n++;
				  }
		}
		if (shape == 2)
		{
 			 while (n < maxitration)
			  {
      			ab = a * a - b * b ;
      			bb = 2 * a * b;
				a = ab + mouse_x ;
				b = bb + mouse_y;
  				 if (a * a + b * b > 4)
    			   break;
     				 n++;
			  }
		}
		if (shape == 3)
		{
			while (n < maxitration)
			{
				SQR = a*a;
 				SQI = b*b;
				ab = ((SQR * 3.0) - SQI) * b;
				bb = (SQR - (SQI * 3.0)) * a;
				a = ab + AA;
				b = bb + BB;
					 if (a * a + b * b > 4)
   						break;
    					 n++;
			}
		}
	    if (shape == 4)
 		{
     		while (n < maxitration)
     		{
         		SQR = a*a;
       		    SQI = b*b;
                ab = -4 * a * b * (SQR - SQI);
                bb = SQR * SQR + (SQI * SQI) -6 *  (SQR * SQI);
                 a = ab + AA;
                 b = bb + BB;
                 if (a * a + b * b > 4)
                     break;
                  n++;
            }   
         }
		 if (shape == 5)
 		 {
     		while (n < maxitration)
     		{
     		    SQR = a*a;
        	    SQI = b*b;
				 bb = ((SQR * 3.0) - SQI) * b;
				 ab = (SQR - (SQI * 3.0)) * a;
          		 a = ab + AA;
         		 b = bb + BB;
      		    if (a * a + b * b > 4)
            		  break;
          		 n++;
     		}
  		}
          if (shape == 6)
          {
             while (n < maxitration)
             {
                 SQR = a*a;
                 SQI = b*b;
                  bb = ((SQR * 3.0) - SQI) * b;
                  ab = fabs((SQR - (SQI * 3.0)) * a);
                  a = ab + AA;
                  b = bb + BB;
                 if (a * a + b * b > 4)
                       break;
                  n++;    
			 }
		 }
			color  = get_color(maxitration,n);
		if (n == maxitration)
		{
				ouput[idx] = 0;
				ouput[idx+1] = 0;
				ouput[idx+2] = 0;
				ouput[idx+3] = 0;
		}
		else
		{
			 ouput[idx] = 	color;
 			 ouput[++idx] = color >> 8;
			 ouput[++idx] = color >> 16;
			 ouput[++idx] = 0;
		}
}

