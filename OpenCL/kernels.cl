__kernel void upDate(__global const double* heatValue_0, 
			__global double* heatValue_1, 
			 double diffConst,  int width)
{
	int x = get_global_id(0);
	int y = get_global_id(1);
	
	int px = y*(width)+x;
	double tmp= 0.;	

	tmp += heatValue_0[px+1];
        tmp += heatValue_0[px-1];
        tmp += heatValue_0[px+width];
	tmp += heatValue_0[px-width];

	tmp *= diffConst*0.25;
	tmp += (1.0-diffConst)*heatValue_0[px];

	heatValue_1[px] = tmp;

}
