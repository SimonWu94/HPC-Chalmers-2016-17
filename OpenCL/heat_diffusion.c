// heat_diffusion.c

#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <CL/cl.h>

#if defined(cl_khr_fp64)  // Khronos extension available?
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#endif

/*******************************************************************************
                FUNCTION DECLARATION
 ******************************************************************************/

void parseCommandLine (int, char **, int *, 
				int *, double *, 
				double *, int *) ;

/*******************************************************************************
               MAIN FUNCTION
 ******************************************************************************/

int main(int argc, char ** argv ){

// Parse command line input

    cl_int input_height, input_width; 
    int input_nIterations;
    cl_double initialValue, diffConst;
   
    parseCommandLine(argc , argv , &input_width , 
    					&input_height , 
    					&initialValue, &diffConst, 
    					&input_nIterations ); 

	cl_double * heatValues;
	cl_double * heatValues00;
	cl_double avgTemp, avgAbsTemp;
	avgTemp = 0.;
	avgAbsTemp = 0.;

// Width and height including the O padded boundary
	cl_uint width;
	cl_uint height;

// OpenCL host variables
	cl_uint num_devs_returned;
	cl_context_properties properties[3];
	cl_device_id device_id;
	cl_int err;
	cl_platform_id platform_id;
	cl_uint num_platforms_returned;
	cl_context context;
	cl_command_queue command_queue;
	cl_program program;
	cl_kernel kernel_upDate;
	cl_mem heatValues_0, heatValues_1;
	size_t global[2];

// Read kernel source file
	FILE *fp;
	long filelen;
	long readlen;
	char *kernel_src;

// Read the kernel
	fp = fopen("kernels.cl", "r");
	fseek(fp, 0L, SEEK_END);
	filelen = ftell(fp);
	rewind(fp);


	kernel_src = malloc(sizeof(char)*(filelen+1));
	readlen = fread(kernel_src, 1, filelen, fp);
	if(readlen != filelen)
	{
		printf("error reading file \n");
		exit(1);
	}

// NULL terminating the string
	kernel_src[filelen]='\0';

// Get platform id
	err = clGetPlatformIDs(1,&platform_id, &num_platforms_returned);

	if (err != CL_SUCCESS)
	{
		printf("Unable to get Platform ID. Error Code= %d\n", err);
		exit(1);
	}

	err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, 
							&device_id, &num_devs_returned);

	if (err != CL_SUCCESS)
	{
		printf("Unable to get Device ID. Error Code= %d\n",err);
		exit(1);
	}

// Context properties terminated with 0

	properties[0]= CL_CONTEXT_PLATFORM;
	properties[1]= (cl_context_properties) platform_id;
	properties[2] = 0;

// Create Context
	context = clCreateContext(properties, 1, &device_id, NULL, NULL, &err);
	if (err != CL_SUCCESS)
	{
		printf("Unable to create Context. Error Code =%d\n", err);
		exit(1);
	}


// Create command queue
	command_queue = clCreateCommandQueue(context, device_id, 0, &err);
	if (err != CL_SUCCESS)
	{
		printf("Unable to create command queue. Error Code =%d\n", err);
		exit(1);
	}


// Create program object from source
	program = clCreateProgramWithSource(context, 1, (const char**) &kernel_src, NULL, &err);

	if (err != CL_SUCCESS)
	{
		printf("Unable to create program object. Error Code =%d\n", err);
		exit(1);
	}

	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		printf("Build failed. Error code =%d \n", err);

		size_t len;
		char buffer[2048];
// Get the build log
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG,
								sizeof(buffer), buffer, &len);
		printf("--- Build Log --- \n %s \n", buffer);
		exit(1);
	}

	kernel_upDate = clCreateKernel(program, "upDate", &err);
	if (err != CL_SUCCESS){
		printf("Unable to create upDate kernel object. Error Code = %d \n", err);
		exit(1);
	}

/* Modify the size of the system w.r.t number of Iterations
   The size of non-trivial core after N iterations is given by:
   N = 1  -----> 3
   N = 2  -----> 5
   N = 3  -----> 7
   N = n  -----> 2*n+3
*/
	if(input_height > 2*input_nIterations+3){ height = 2*input_nIterations+3 +2;}
   	else{ height = input_height + 2;}
   	if(input_width > 2*input_nIterations+3){ width = 2*input_nIterations+3 +2;}
   	else{ width = input_width + 2;}

// Initialize heatValues
	heatValues  = (cl_double*) calloc(width*height, sizeof(cl_double));
	heatValues[width*(height/2)  + width/2]  = initialValue;
	heatValues00 = (cl_double*) calloc(width*height, sizeof(cl_double));

// Create buffer objects
	heatValues_0= clCreateBuffer(context, CL_MEM_READ_WRITE,width*height* sizeof(cl_double), NULL, &err);
	if (err != CL_SUCCESS){
		printf("Unable to create heatValues_0 buffer. Error Code = %d \n", err);
		exit(1);
	}

	heatValues_1= clCreateBuffer(context, CL_MEM_READ_WRITE,width*height* sizeof(cl_double), NULL, &err);
	if (err != CL_SUCCESS){
		printf("Unable to create heatValues_1 buffer. Error Code = %d \n", err);
		exit(1);
	}

// Write from host memory to buffer
	err= clEnqueueWriteBuffer(command_queue, heatValues_0, CL_TRUE, 0, width*height* sizeof(cl_double),(cl_double *) heatValues , 0, NULL, NULL);
	if (err != CL_SUCCESS){
		printf("Unable to enqueue heatValues_0 buffer. Error Code = %d \n", err);
		exit(1);
	}

	err= clEnqueueWriteBuffer(command_queue, heatValues_1, CL_TRUE, 0, width*height* sizeof(cl_double),(cl_double *) heatValues00 , 0, NULL, NULL);
	if (err != CL_SUCCESS){
		printf("Unable to enqueue heatVales_1 buffer. Error Code = %d \n", err);
		exit(1);
	}



// Set global work dimension size
 	global[0] = width-2;
 	global[1] = height-2;

// offset for NDRangeKernel
	size_t global_offset[2] = {1,1};

// Set kernel arguments that are fixed


err = clSetKernelArg(kernel_upDate, 2, sizeof(double), &diffConst);
if (err != CL_SUCCESS){
	printf("Unable to clSetKernelArg 2 . Error Code = %d \n", err);
	exit(1);
}
	err = clSetKernelArg(kernel_upDate, 3, sizeof(int), &width);
	if (err != CL_SUCCESS){
	printf("Unable to clSetKernelArg 3 . Error Code = %d \n", err);
	exit(1);
}


	size_t idx = 0;
	const int nit = input_nIterations/2; 
// Enqueue the kernels for nIterations. 
// Swapping the heatValues_0, heatValues_1 periodically
	for(; idx < nit; idx++){

		err = clSetKernelArg(kernel_upDate, 0, sizeof(cl_mem), &heatValues_0);
		err = clSetKernelArg(kernel_upDate, 1, sizeof(cl_mem), &heatValues_1);
		err = clEnqueueNDRangeKernel(command_queue, kernel_upDate, 2, global_offset , global, NULL, 0, NULL, NULL);

		err = clSetKernelArg(kernel_upDate, 1, sizeof(cl_mem), &heatValues_0);
		err = clSetKernelArg(kernel_upDate, 0, sizeof(cl_mem), &heatValues_1);
		err = clEnqueueNDRangeKernel(command_queue, kernel_upDate, 2, global_offset, global, NULL, 0, NULL, NULL);

	}

// Reading buffer to host memory
 	err = clEnqueueReadBuffer(command_queue, heatValues_0, CL_TRUE, 0, sizeof(cl_double)*height*width, heatValues, 0, NULL, NULL);
 	if (err != CL_SUCCESS){
	printf("Unable to clEnqueueReadBuffer 1 . Error Code = %d \n", err);
	exit(1);
	}

// Calculating avgTemp , avgAbsTemp on host CPU
	double* begin_heat_values;
	double* end_heat_values;
	begin_heat_values = heatValues;
	end_heat_values   = heatValues + width*height;
	while(begin_heat_values != end_heat_values){
	avgTemp += *begin_heat_values;
 		begin_heat_values++;
 	}
 	avgTemp /= (input_width*input_height);
 	
	begin_heat_values = heatValues;
	while(begin_heat_values != end_heat_values){
		avgAbsTemp += fabs(avgTemp - *begin_heat_values);
 		begin_heat_values++;
 	}
//Deduct contributions from  artificial boarder cells 
//	avgAbsTemp -= (height*width -input_height*input_width) * avgTemp;


if(height == input_height +2 && width == input_width +2){
	avgAbsTemp -= (height*width -input_height*input_width) * avgTemp;
}


else if(height == input_height+2 && width == 2*input_nIterations+3+2){

	avgAbsTemp -= ((height * width)-(input_height * (width-2)))*avgTemp;
	avgAbsTemp += (input_width - 2*input_nIterations-3)*input_height * avgTemp;
}

else if(height == 2*input_nIterations+3+2 && width == input_width+2){
	avgAbsTemp -= ((height * width)-(input_width * (height-2)))*avgTemp;
	avgAbsTemp += (input_height - 2*input_nIterations-3)*input_width * avgTemp;
}

else { 
	avgAbsTemp -= ((height * width)-((height-2) * (width-2)))*avgTemp;
	avgAbsTemp += (input_height * input_width - (height-2) * (width-2))* avgTemp;
}


	avgAbsTemp /= (input_width*input_height);

// Printing the results 
	printf("average: %f\n", avgTemp);
	printf("average absolute difference: %f\n", avgAbsTemp);

// Clear all cl_objects
	clReleaseMemObject(heatValues_0);
	clReleaseMemObject(heatValues_1);
	clReleaseProgram(program);
	clReleaseKernel(kernel_upDate);
	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);
	free(kernel_src);
	free(heatValues); 


	return 0;

}





/*******************************************************************************
                COMMAND LINE PARSE FUNCTION
 ******************************************************************************/
 
void parseCommandLine (int argc , 
                              char ** argv ,  
                              cl_int * width , 
                              cl_int * height , 
                              cl_double * initialValue , 
                              cl_double * diffConst , 
                              int * nIterations) 
{
// Check if number of arguments provided is correct
    if ( argc != 6){
        printf("Please provide 5 arguments : \n"
                "[width] [height] -i[initial value] "
                "-d[diffusion Constant] -n[number of Iterations] \n.");
        abort() ;
    }
    
// Initialise variables with command line input values
    if (sscanf(argv[1], "%d", width) == EOF ){
        fprintf(stderr, "Please format input as [width]\n");
        exit(EOF);
    }
    
    if (sscanf(argv[2], "%d", height) == EOF ){
        fprintf(stderr, "Please format input as [height]\n");
        exit(EOF);
    }
    
    if (sscanf(argv[3], "-i%lf", initialValue) == EOF ){
        fprintf(stderr, "Please format input as -i[init Value]\n");
        exit(EOF);
    }
    
    if (sscanf(argv[4], "-d%lf", diffConst) == EOF ){
        fprintf(stderr, "Please format input as -d[diffConst]\n");
        exit(EOF);
    }
    
    if (sscanf(argv[5], "-n%d", nIterations) == EOF ){
        fprintf(stderr, "Please format input as -n[nIterations]\n");
        exit(EOF);
    }
    
}


