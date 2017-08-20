#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


//define value of pi
#define M_PI           3.14159265358979323846

//Starting values of newton method
#define Z_START_IM           2.0
#define Z_START_RE          -2.0

//Mutex definition and declare currentRow
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;
int currentRow=0;

//newton thread data
struct thread_data{
    
    int  line_count; 
    char * attrData;
    char * convData;
    
};

//output thread data 
struct output_thread_data{
        
    int   line_count;
    int   degree;
    char* attrData;
    char* convData;
    
};

//special newton thread data
struct special_thread_data{
    
    int  line_count; 
    char ** attrData;
    char ** convData;
    int  * finished;
    
};

//special output thread data 
struct special_output_thread_data{
        
    int   line_count;
    int   degree;
    char ** attrData;
    char ** convData;
    int*  finished;
    
};

//Declare functions
void *newton_d1(void* );
void *newton_d2(void* );
void *newton_d4(void* );
void *newton_d5(void* );
void *newton_d7(void* );
void *printRountine(void* );

/*****************************************************************************
                    NEWTON ROUTINE 1
*****************************************************************************/

//newton method for degree 1
void *newton_d1(void *threadarg)
{
    struct thread_data *arguments = (struct thread_data *) threadarg;
    //initialise variables needed for later
    int line_count  = arguments->line_count;
    char * attrData = arguments->attrData;
    char * convData = arguments->convData; 
    
//Row we should now work on
    int row;
    
//Get currentRow to be processed
    while(1){
        pthread_mutex_lock( &mutex1 );
        if (currentRow == line_count) row = currentRow;
        else { row = currentRow ; currentRow++;}
        pthread_mutex_unlock( &mutex1 );
        
//Break while loop if row is line_count
        if (row == line_count) break;
        
//Process newton iteration
        int ix; 
        double z_im;
        double z_re;
        double step = 4./(line_count-1);
        char * attrCurrent = attrData + 6*line_count*row;
        char * convCurrent = convData + 6*line_count*row;
        
        for (ix =0; ix < line_count; ix++){
//Initial value
            z_im = Z_START_IM - row*step;
            z_re = Z_START_RE + ix*step;
            
//check abort criteria:             

            int iterCounter=0;

            while(1){
                z_re -= z_re -1.;
                z_im -= z_im;
                iterCounter++;
                
//check if z is close to root
                double diff_re = 1.0 - z_re;
                double diff_im = z_im;
                double diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    const char iterChar = iterCounter%10 + 48;
//Write color into Data array
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to the origin
                if ( (z_re*z_re + z_im *z_im)<0.000001){
                    
                    const char iterChar = iterCounter%10 + 48;
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                        
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is divergent  
                if ( (z_re>10000000000)||(z_im>10000000000) ){
                    
                    const char iterChar = iterCounter%10 + 48;
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                        
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    
                    break;                    
                }
            }
        }
    }pthread_exit(NULL);
}

/*****************************************************************************
                    NEWTON ROUTINE DEGREE 2
*****************************************************************************/

//newton method for degree 2
void *newton_d2(void *threadarg)
{
    struct thread_data *arguments = (struct thread_data *) threadarg;
    //initialise variables needed for later
    int line_count  = arguments->line_count;
    char * attrData = arguments->attrData;
    char * convData = arguments->convData; 
    
//Row we should now work on
    int row;
    
//Get currentRow to be processed
    while(1){
        pthread_mutex_lock( &mutex1 );
        if (currentRow == line_count) row = currentRow;
        else { row = currentRow ; currentRow++;}
        pthread_mutex_unlock( &mutex1 );
        
//Break while loop if row is line_count
        if (row == line_count) break;
        
//Process newton iteration
        int ix; 
        double z_im;
        double z_re;
        double step = 4./(line_count-1);
        char * attrCurrent = attrData + 6*line_count*row;
        char * convCurrent = convData + 6*line_count*row;
        
        for (ix =0; ix < line_count; ix++){
//Initial value
            z_im = Z_START_IM - row*step;
            z_re = Z_START_RE + ix*step;
            
//check abort criteria:             
            int iterCounter=0;

            while(1){
                
                double a2 = z_re*z_re;
                double b2 = z_im*z_im;
                double sum = a2+b2;
                double fac1 = 0.5 *z_re /sum;
                double fac2 = 0.5 *z_im /sum;

                z_re -= (b2 -1. +a2)*fac1;
                z_im -= (a2 +1. +b2)*fac2;
                iterCounter++;
                
//check if z is close to root1
                double diff_re = 1.000000 - z_re;
                double diff_im = z_im;
                double diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = '0';
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root2
                diff_re = -1.000000 - z_re;
                diff_im = z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = '0';
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to the origin
                if ( (z_re*z_re + z_im *z_im)<0.000001){
                    
                    char iterChar = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                        
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = '0';
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is divergent  
                if ( (z_re>10000000000)||(z_im>10000000000) ){
                    
                    char iterChar = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                        
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = '0';
                    *(convCurrent)++ = ' ';
                    
                    break;                    
                }
            }
        }
    }pthread_exit(NULL);
}
/*****************************************************************************
                    NEWTON ROUTINE 4
*****************************************************************************/

//newton method for degree 4
void *newton_d4(void *threadarg)
{
    struct thread_data *arguments = (struct thread_data *) threadarg;
    //initialise variables needed for later
    int line_count  = arguments->line_count;
    char * attrData = arguments->attrData;
    char * convData = arguments->convData; 
    
//Row we should now work on
    int row;
    
//Get currentRow to be processed
    while(1){
        pthread_mutex_lock( &mutex1 );
        if (currentRow == line_count) row = currentRow;
        else { row = currentRow ; currentRow++;}
        pthread_mutex_unlock( &mutex1 );
        
//Break while loop if row is line_count
        if (row == line_count) break;
        
//Process newton iteration
        int ix; 
        double z_im;
        double z_re;
        double step = 4./(line_count-1);
        char * attrCurrent = attrData + 6*line_count*row;
        char * convCurrent = convData + 6*line_count*row;
        
        for (ix =0; ix < line_count; ix++){
//Initial value
            z_im = Z_START_IM - row*step;
            z_re = Z_START_RE + ix*step;
            
//check abort criteria:             
            int iterCounter=0;

            while(1){
                
            double rpw=z_re;
		    double ipw=z_im;
		    double k1, k2, k3;
		    int g;
		    
		    for (g=0; g<2; g++)
		        {
		
			            k1=rpw*(z_re+z_im);
                        k2=z_im*(rpw+ipw);
                        k3=z_re*(ipw-rpw);
                        rpw=k1-k2;
                        ipw=k1+k3;
	        	}
		    z_re -= (z_re-rpw/(rpw*rpw+ipw*ipw))/4.;
		    z_im -= (z_im+ipw/(rpw*rpw+ipw*ipw))/4.;
   
                

                iterCounter++;

                
//check if z is close to root1
                double diff_re = 1.000000 - z_re;
                double diff_im = z_im;
                double diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;}
//Write color into Data array
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root2
                diff_re = -1.000000 - z_re;
                diff_im = z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;}
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root3
                diff_re = z_re;
                diff_im = 1.00000 - z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;}
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root4
                diff_re = z_re;
                diff_im = -1.00000 - z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;}
//Write color into Data array
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }

//check if z is close to the origin
                if ( (z_re*z_re + z_im *z_im)<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;}
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                        
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is divergent  
                if ( (z_re>10000000000)||(z_im>10000000000) ){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                        
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;                    
                }
            }
        }
    }pthread_exit(NULL);
}

/*****************************************************************************
                    NEWTON ROUTINE 5
*****************************************************************************/

//newton method for degree 5
void *newton_d5(void *threadarg)
{
    struct thread_data *arguments = (struct thread_data *) threadarg;
    //initialise variables needed for later
    int line_count  = arguments->line_count;
    char * attrData = arguments->attrData;
    char * convData = arguments->convData; 
    
//Row we should now work on
    int row;
    
//Get currentRow to be processed
    while(1){
        pthread_mutex_lock( &mutex1 );
        if (currentRow == line_count) row = currentRow;
        else { row = currentRow ; currentRow++;}
        pthread_mutex_unlock( &mutex1 );
        
//Break while loop if row is line_count
        if (row == line_count) break;
        
//Process newton iteration
        int ix; 
        double z_im;
        double z_re;
        double step = 4./(line_count-1);
        char * attrCurrent = attrData + 6*line_count*row;
        char * convCurrent = convData + 6*line_count*row;
        
        for (ix =0; ix < line_count; ix++){
//Initial value
            z_im = Z_START_IM - row*step;
            z_re = Z_START_RE + ix*step;
            
//check abort criteria:             
            int iterCounter=0;

            while(1){
                
            double rpw=z_re;
		    double ipw=z_im;
		    double k1, k2, k3;
		    int g;
		    
		    for (g=0; g<3; g++)
		        {
		
			            k1=rpw*(z_re+z_im);
                        k2=z_im*(rpw+ipw);
                        k3=z_re*(ipw-rpw);
                        rpw=k1-k2;
                        ipw=k1+k3;
	        	}
		    z_re -= (z_re-rpw/(rpw*rpw+ipw*ipw))/5.;
		    z_im -= (z_im+ipw/(rpw*rpw+ipw*ipw))/5.;
   
                

                iterCounter++;

                
//check if z is close to root1
                double diff_re = 1.000000 - z_re;
                double diff_im = z_im;
                double diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;}
//Write color into Data array
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root2
                diff_re = 0.30901699 - z_re;
                diff_im = 0.95105652 - z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;}
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root3
                diff_re = -0.80901699 - z_re;
                diff_im = 0.58778525 - z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;}
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root4
                diff_re = -0.80901699 - z_re;
                diff_im = -0.58778525  - z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;}
//Write color into Data array
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root5
                diff_re = 0.30901699 - z_re;
                diff_im = -0.95105651  - z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;}
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to the origin
                if ( (z_re*z_re + z_im *z_im)<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;}
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                        
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is divergent  
                if ( (z_re>10000000000)||(z_im>10000000000) ){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                        
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;                    
                }
            }
        }
    }pthread_exit(NULL);
}

/*****************************************************************************
                    NEWTON ROUTINE 7
*****************************************************************************/

//newton method for degree 7
void *newton_d7(void *threadarg)
{
    struct thread_data *arguments = (struct thread_data *) threadarg;
    //initialise variables needed for later
    int line_count  = arguments->line_count;
    char * attrData = arguments->attrData;
    char * convData = arguments->convData; 
    
//Row we should now work on
    int row;
    
//Get currentRow to be processed
    while(1){
        pthread_mutex_lock( &mutex1 );
        if (currentRow == line_count) row = currentRow;
        else { row = currentRow ; currentRow++;}
        pthread_mutex_unlock( &mutex1 );
        
//Break while loop if row is line_count
        if (row == line_count) break;
        
//Process newton iteration
        int ix; 
        double z_im;
        double z_re;
        double step = 4./(line_count-1);
        char * attrCurrent = attrData + 6*line_count*row;
        char * convCurrent = convData + 6*line_count*row;
        
        for (ix =0; ix < line_count; ix++){
//Initial value
            z_im = Z_START_IM - row*step;
            z_re = Z_START_RE + ix*step;
            
//check abort criteria:             
            int iterCounter=0;

            while(1){
                
            double rpw=z_re;
		    double ipw=z_im;
		    double k1, k2, k3;
		    int g;
		    
		    for (g=0; g<5; g++)
		        {
		
			            k1=rpw*(z_re+z_im);
                        k2=z_im*(rpw+ipw);
                        k3=z_re*(ipw-rpw);
                        rpw=k1-k2;
                        ipw=k1+k3;
	        	}
		    z_re -= (z_re-rpw/(rpw*rpw+ipw*ipw))/7.;
		    z_im -= (z_im+ipw/(rpw*rpw+ipw*ipw))/7.;

                iterCounter++;
                
//check if z is close to root1
                double diff_re = 1.000000 - z_re;
                double diff_im = z_im;
                double diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;}
 
//Write color into Data array
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root2
                diff_re = -0.9009688679 - z_re;
                diff_im = -0.4338837391 - z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root3
                diff_re =-0.22252093 - z_re;
                diff_im = 0.97492791218 - z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root4
                diff_re = -0.9009688679- z_re;
                diff_im = 0.4338837391 - z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root5
                diff_re =0.62348980 - z_re;
                diff_im = 0.781831482- z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root6
                diff_re =-0.22252093  -z_re;
                diff_im = -0.974927912 -z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
                
//check if z is close to root7
                diff_re =0.6234898 - z_re;
                diff_im =-0.781831482 - z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }

//check if z is close to the origin
                if ( (z_re*z_re + z_im *z_im)<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                        
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is divergent  
                if ( (z_re>10000000000)||(z_im>10000000000) ){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                        
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;                    
                }
            }
        }
    }pthread_exit(NULL);
}

/*****************************************************************************
                    PRINT ROUTINE
*****************************************************************************/

void* printRountine(void* threadarg){
    
//Initialise thread arguments    
    struct output_thread_data* arguments= (struct output_thread_data *)threadarg;
    int  line_count = arguments->line_count;
    int  degree     = arguments->degree;
    char *attrData  = arguments->attrData;
    char *convData  = arguments->convData;
    
//Maximum Color Value defined   
    const int maxColor  = 10;
    
//define the correct filenames
    char filename_attractor[30];
    char filename_convergence[30];
    sprintf(filename_attractor  ,  "newton_attractors_x%d.ppm" , degree);
    sprintf(filename_convergence,  "newton_convergence_x%d.ppm", degree);

//open file
    FILE * attrPF;
    FILE * convPF;
    attrPF  = fopen(filename_attractor,   "w");
    convPF  = fopen(filename_convergence, "w");

//print P3 header
    fprintf(attrPF, "P3\n%d %d\n%d\n", line_count, line_count, maxColor);
    fprintf(convPF, "P3\n%d %d\n%d\n", line_count, line_count, maxColor);


//print color buffer to file
    fwrite(attrData, line_count*line_count*6 , 1, attrPF);
    fwrite(convData, line_count*line_count*6 , 1, convPF);
    
//close files
    fclose(attrPF);
    fclose(convPF);
    
    pthread_exit(NULL);
}

/*****************************************************************************
                    SPECIAL PRINT
*****************************************************************************/

void* specialprintRountine(void* threadarg){
    
//Initialise thread arguments    
    struct special_output_thread_data* arguments= (struct special_output_thread_data *)threadarg;
    int  line_count = arguments->line_count;
    int  degree     = arguments->degree;
    char **attrData = arguments->attrData;
    char **convData = arguments->convData;
    int *finished   = arguments->finished;
    
//Maximum Color Value defined   
    const int maxColor  = 10;
    
//define the correct filenames
    char filename_attractor[30];
    char filename_convergence[30];
    sprintf(filename_attractor  ,  "newton_attractors_x%d.ppm" , degree);
    sprintf(filename_convergence,  "newton_convergence_x%d.ppm", degree);

//open file
    FILE * attrPF;
    FILE * convPF;
    attrPF  = fopen(filename_attractor,   "w");
    convPF  = fopen(filename_convergence, "w");

//print P3 header
    fprintf(attrPF, "P3\n%d %d\n%d\n", line_count, line_count, maxColor);
    fprintf(convPF, "P3\n%d %d\n%d\n", line_count, line_count, maxColor);

    int waitingforRow;
    
    for(waitingforRow=0; waitingforRow < line_count; waitingforRow++){
        
//wait for new calculated row
        while(1){
            int proceed = 0;
            pthread_mutex_lock( &mutex2 ); 
            if(finished[waitingforRow]==1) proceed =1;
            pthread_mutex_unlock( &mutex2);
            if(proceed == 1) break;
            }
        
//get Data pointer for current Row
        fwrite(attrData[waitingforRow], line_count*6 , 1, attrPF);
        fwrite(convData[waitingforRow], line_count*6 , 1, convPF);
        
        
        
            pthread_mutex_lock ( &mutex3);
            free(attrData[waitingforRow]);
            free(convData[waitingforRow]);
            attrData[waitingforRow]=NULL;
            convData[waitingforRow]=NULL;
            pthread_mutex_unlock( &mutex3);
            
            
            
    }

//close files
    fclose(attrPF);
    fclose(convPF);
    
    pthread_exit(NULL);
}
/*****************************************************************************
                    SPECIAL NEWTON ROUTINE 7
*****************************************************************************/

//newton method for degree 7
void *special_newton_d7(void *threadarg)
{
    struct special_thread_data *arguments = (struct special_thread_data *) threadarg;
    //initialise variables needed for later
    int line_count  = arguments->line_count;
    char ** attrData = arguments->attrData;
    char ** convData = arguments->convData; 
    int * finished = arguments->finished;
    
//Row we should now work on
    int row;
    
//Get currentRow to be processed
    while(1){
        pthread_mutex_lock( &mutex1 );
        if (currentRow == line_count) row = currentRow;
        else { row = currentRow ; currentRow++;}
        pthread_mutex_unlock( &mutex1 );
        
//Break while loop if row is line_count
        if (row == line_count) break;
        
        
        
//allocate memory for storing current row
        
        char* pt1 = (char*) malloc(6*50000);
        char* pt2 = (char*) malloc(6*50000);
        
        if(pt1!=NULL && pt2!=NULL){
        pthread_mutex_lock (&mutex3);
        *(attrData+row) = pt1;
        *(convData+row) = pt2;
        pthread_mutex_unlock (&mutex3);}
        else {printf("attrData = %p \t convData = %p \n", (void*)pt1, (void*)pt2);}
        
        //printf("Allocated memory for row: %d \n", row);

//Process newton iteration
        int ix; 
        double z_im;
        double z_re;
        double step = 4./(line_count-1);
        char * attrCurrent = attrData[row];
        char * convCurrent = convData[row];
        
        for (ix =0; ix < line_count; ix++){
//Initial value
            z_im = Z_START_IM - row*step;
            z_re = Z_START_RE + ix*step;
            
//check abort criteria:             
            int iterCounter=0;

            while(1){
                
            double rpw=z_re;
		    double ipw=z_im;
		    double k1, k2, k3;
		    int g;
		    
		    for (g=0; g<5; g++)
		        {
		
			            k1=rpw*(z_re+z_im);
                        k2=z_im*(rpw+ipw);
                        k3=z_re*(ipw-rpw);
                        rpw=k1-k2;
                        ipw=k1+k3;
	        	}
		    z_re -= (z_re-rpw/(rpw*rpw+ipw*ipw))/7.;
		    z_im -= (z_im+ipw/(rpw*rpw+ipw*ipw))/7.;

                iterCounter++;
                
//check if z is close to root1
                double diff_re = 1.000000 - z_re;
                double diff_im = z_im;
                double diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;}
 
//Write color into Data array
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root2
                diff_re = -0.9009688679 - z_re;
                diff_im = -0.4338837391 - z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root3
                diff_re =-0.22252093 - z_re;
                diff_im = 0.97492791218 - z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root4
                diff_re = -0.9009688679- z_re;
                diff_im = 0.4338837391 - z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root5
                diff_re =0.62348980 - z_re;
                diff_im = 0.781831482- z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is close to root6
                diff_re =-0.22252093  -z_re;
                diff_im = -0.974927912 -z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
                
//check if z is close to root7
                diff_re =0.6234898 - z_re;
                diff_im =-0.781831482 - z_im;
                diff = diff_re*diff_re + diff_im*diff_im;
                if (diff<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '9';
                    *(attrCurrent)++ = ' ';
                    
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }

//check if z is close to the origin
                if ( (z_re*z_re + z_im *z_im)<0.000001){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                        
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;
                }
//check if z is divergent  
                if ( (z_re>10000000000)||(z_im>10000000000) ||iterCounter>1000 ){
                    
                    char iterChar  = iterCounter%10 + 48;
                    char iterChar2 = iterCounter/10 %10 + 48;
                    char iterChar3 = iterCounter/100 % 10 + 48;
                    if(iterCounter/10 %10 != 0){iterChar = 57;} 
                    if(iterCounter/100 %10 != 0){iterChar2 = 57;} 
//Write color into Data array
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                    *(attrCurrent)++ = '0';
                    *(attrCurrent)++ = ' ';
                        
                    *(convCurrent)++ = iterChar;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar2;
                    *(convCurrent)++ = ' ';
                    *(convCurrent)++ = iterChar3;
                    *(convCurrent)++ = ' ';
                    
                    break;                    
                }
            }
        }
        
//tell print thread that row is finished
        pthread_mutex_lock( &mutex2 );
        finished[row] = 1;
        pthread_mutex_unlock( &mutex2 );
        
    }pthread_exit(NULL);
}
/*****************************************************************************
                    MAIN FUNCTION
*****************************************************************************/

//Main function
int main ( int argc, char *argv[] ){
    
//Check if number of arguments is correct
    if ( argc != 4){
        printf("Please provide 3 arguments : -t[num_threads] -l[lineCount] [degree] \n.");
        abort() ;
    }
    
//Passing Arguments: -t5 -l1000 7
// [thread count] [line count] [d=degree]
    
    int num_threads;
    int line_count;
    int degree;
    
    if (sscanf(argv[1], "-l%d", &line_count) == EOF ){
        fprintf(stderr, "Please format input as -l[line_count]\n");
        exit(EOF);
    }
    if (sscanf(argv[2], "-t%d", &num_threads) == EOF ){
        fprintf(stderr, "Please format input as -l[num_threads]\n");
        exit(EOF);
    }
    if (sscanf(argv[3], "%d", &degree) == EOF ){
        fprintf(stderr, "Please format input as [degree]\n");
        exit(EOF);
    }

    if(line_count != 50000) {
// Memory Allocation for attrData, convData:
// size is line_count * line_count * 6 Bytes
    
    char * attrData = (char*) malloc (6*line_count*line_count*sizeof(char));
    char * convData = (char*) malloc (6*line_count*line_count*sizeof(char));
    

//initialising thread rountine arguments to pass through pthread_creat()
    struct thread_data Data;
    struct thread_data *ptrData = &Data;
    Data.line_count = line_count;
    Data.attrData   = attrData;
    Data.convData   = convData;
    
//Create threads for Newton Method calculation for different threads


    pthread_t newton_thread[num_threads];
    int ctr;
    int rc;
    switch(degree){
        case 1:
            for (ctr = 0 ; ctr < num_threads ; ctr++){
                rc = pthread_create( &newton_thread[ctr], NULL, newton_d1, ptrData);
                if (rc) {
                    printf("ERROR; return code from pthread_create() is %d\n", rc);
                    exit(-1);
                        }
            } break;
        case 2:
            for (ctr = 0 ; ctr < num_threads ; ctr++){
                rc = pthread_create( &newton_thread[ctr] , NULL, newton_d2, ptrData);
                if (rc) {
                    printf("ERROR; return code from pthread_create() is %d\n", rc);
                    exit(-1);
                        }
            } break;
	case 4:
            for (ctr = 0 ; ctr < num_threads ; ctr++){
                rc = pthread_create( &newton_thread[ctr] , NULL, newton_d4, ptrData);
                if (rc) {
                    printf("ERROR; return code from pthread_create() is %d\n", rc);
                    exit(-1);
                        }
            } break;
        case 5:
            for (ctr = 0 ; ctr < num_threads ; ctr++){
                rc = pthread_create( &newton_thread[ctr] , NULL, newton_d5, ptrData);
                if (rc) {
                    printf("ERROR; return code from pthread_create() is %d\n", rc);
                    exit(-1);
                        }
            } break;
        case 7:
            for (ctr = 0 ; ctr < num_threads ; ctr++){
                rc = pthread_create( &newton_thread[ctr] , NULL, newton_d7, ptrData);
                if (rc) {
                    printf("ERROR; return code from pthread_create() is %d\n", rc);
                    exit(-1);
                        }
            } break;
    }
    
//wait for all the newton threads to finish
    
    for (ctr =0 ; ctr < num_threads ; ctr ++){
        pthread_join( newton_thread[ctr], NULL);
    }
    
//print ppm files
    struct output_thread_data outData;
    struct output_thread_data * ptroutData =&outData;
    outData.degree      = degree;
    outData.line_count  = line_count;
    outData.attrData    = attrData;
    outData.convData    = convData;

    pthread_t output_thread;
    rc = pthread_create(&output_thread, NULL, printRountine, ptroutData);
    if (rc) { printf("ERROR; return code from pthread_create() is %d\n", rc);
              exit(-1);}
    pthread_join(output_thread, NULL);


//destroy pthreads and mutex
    
    pthread_mutex_destroy( &mutex1 );
    pthread_mutex_destroy( &mutex2 );
    pthread_mutex_destroy( &mutex3 );
    free(attrData);
    free(convData);
    }
    
//for -l50000
    else{
        
        int looper;
        
        char** attrData = (char **) malloc(50000*sizeof(char*));
        char** attrlooper = attrData;
        for (looper=0; looper< line_count ; looper++ ){
            attrlooper[looper] = NULL;}
        
        char** convData = (char **) malloc(50000*sizeof(char*));
        char** convlooper = convData;
        for (looper=0; looper< line_count ; looper++ ){
            convlooper[looper] = NULL;}
            
        int * finished  = (int*) calloc(50000,sizeof(int));
            
        struct special_thread_data Data;
        struct special_thread_data* ptrData = &Data;
        Data.line_count = line_count;
        Data.attrData   = attrData;
        Data.convData   = convData;
        Data.finished   = finished;
        
        struct special_output_thread_data outData;
        struct special_output_thread_data * ptroutData =&outData;
        outData.degree      = degree;
        outData.line_count  = line_count;
        outData.attrData    = attrData;
        outData.convData    = convData;
        outData.finished    = finished;
        
        pthread_t output_thread;
        int rc;
        rc = pthread_create(&output_thread, NULL, specialprintRountine, ptroutData);
        if (rc) { printf("ERROR; return code from pthread_create() is %d\n", rc);
                    exit(-1);}
                    
        pthread_t newton_thread[num_threads];
        int ctr;
        for (ctr = 0 ; ctr < num_threads ; ctr++){
            rc = pthread_create( &newton_thread[ctr] , NULL, special_newton_d7, ptrData);
            if (rc) {
                printf("ERROR; return code from pthread_create() is %d\n", rc);
                exit(-1);
                    }
        }            

        for (ctr =0 ; ctr < num_threads ; ctr ++){
        pthread_join( newton_thread[ctr], NULL);
        }
        pthread_join( output_thread, NULL);
        
        pthread_mutex_destroy( &mutex1 );
        pthread_mutex_destroy( &mutex2 );
        pthread_mutex_destroy( &mutex3 );
        free(attrData);
        free(convData);
    }

    pthread_exit (NULL);
    
}
