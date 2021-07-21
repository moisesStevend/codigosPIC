#include "mcc_generated_files/mcc.h"
#include <string.h>
#include "mcc_generated_files/interrupt_manager.h"

void Serial_println(char *m);
double get_lon(char *t);
double get_lat(char *t);
int isGNRMC(char *t);
void Serial_print3(char *m);
int get_data(float d);
float get_coord(float xx);

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();

    double longitud, latitud;
    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    char data_w[80];
    char buff[100];
    char data_ufox[80];
    
    union {
		float a;
		unsigned char bytes[4];
	} thing, thing2;
	
            
    while (1)
    {
        strcpy(data_w,msg);
        
        Serial_println(data_w);
        
        if(isGNRMC(data_w)){
            longitud = get_coord(get_lon(data_w));
            latitud= get_coord(get_lat(data_w));
            
            printf("long: %.6f, lat: %.6f\n", longitud, latitud);
            
            Serial_print3("AT \n");
            __delay_ms(1000);
            
            Serial_print3("AT$RC \n");
            __delay_ms(1000);
            
            thing.a = longitud;
            thing2.a= latitud;
            
            
            //sprintf(buff, "AT$SF=%d%d \n",get_data(longitud),get_data(latitud));
            //Serial_print3("AT$SF=01 \n");
            //Serial_print3(buff);
            //sprintf(data_ufox,"AT$SL=%02x%02x%02x%02x%02x%02x%02x%02x \n",thing.bytes[0],thing.bytes[1],thing.bytes[2],thing.bytes[3],thing2.bytes[0],thing2.bytes[1],thing2.bytes[2],thing2.bytes[3]); 
            sprintf(data_ufox,"AT$SF=%02x%02x%02x%02x%02x%02x%02x%02x \n",thing.bytes[0],thing.bytes[1],thing.bytes[2],thing.bytes[3],thing2.bytes[0],thing2.bytes[1],thing2.bytes[2],thing2.bytes[3]); 
            //snprintf(data_ufox, 50, "AT$SF=%s%s \n",float_buffer(longitud),float_buffer(latitud));
            Serial_print3(data_ufox);
            
            printf("%s",data_ufox); 
             __delay_ms(1000);
        }
        //Serial_println(isGNRMC(data_w) ? "GNRMC\n":"");
        //printf("data gps: %s\n",msg);
        __delay_ms(1000);
    }
}

int get_data(float d){
	float l = 1205.088256;
	
	int l_g = (int)l/100;//12
	
	//float l_m = (l - l_g*100)/60; //1205.088256 - 1200
	
	//printf("grados: %d, minutos: %f", l_g, l_m);
	
	return l_g;
	
}


void Serial_print3(char *m){
    while(*m!='\0'){
        if(UART3_is_tx_ready()){ 
            UART3_Write(*(m++));
        }
    }
}

void Serial_println(char *m){
    while(*m!='\0'){
        if(UART5_is_tx_ready()){ 
            UART5_Write(*(m++));
        }
    }
    if(UART5_is_tx_ready()){
        UART5_Write('\n');
    }
}

int isGNRMC(char *t){
    char nmea_id[5]="GNRMC";
    //char nmea_id[5]="ASGNRMA";  
    int i=-1;
    int count=0;
    
    while(*t!=','){
		//printf("%c",*t);
   
        if(i>=0){
			//printf("%c",*t);
            if(nmea_id[i]==*t){
				//printf("%c",*t);
                count++;
            }
            i++;
        }
        
        if(*t=='$'){
            i=0;//1
            
            //printf("%c",*t);
        }    
        
        t++;
    }
    //printf("%d",count);
    if(count==5){
        return 1;
    }else{
        return 0;
    }
    //return 
}


double get_lon(char *t){
	char mm[80];
	char *p=mm;
	double ll;
	
	while(*t!='\0'){
		*p=*t;
		p++;
		t++;
	}
    
   char * token = strtok(mm, ",");
   int j=0;
   // loop through the string to extract all other tokens
   while( token != NULL ) {
	  //printf( " %s\n", token ); //printing each token
	  
	  if(j==3){
			//sscanf(token,"%f", &ll);
            ll = atof(token);
			return(ll);
		}
	  token = strtok(NULL, ",");
	  j++;
	   
   }
   
   return 0.0;
}

double get_lat(char *t){
	char mm[80];
	char *p=mm;
	double ll;
	
	while(*t!='\0'){
		*p=*t;
		p++;
		t++;
	}
    
   char * token = strtok(mm, ",");
   int j=0;
   // loop through the string to extract all other tokens
   while( token != NULL ) {
	  //printf( " %s\n", token ); //printing each token
	  
	  if(j==5){
			//sscanf(token,"%f", &ll);
             ll = atof(token);
			return(ll);
		}
	  token = strtok(NULL, ",");
	  j++;
	   
   }
   
   return 0.0;
}


float get_coord(float xx)
{	//7707.923339
	//double x=7707.923339, data_final;
    float x=xx, data_final;
		
	int deg=(int)x;//7707
	float resto = (x -(int)(deg/100)*100)/60; //7700
	deg =(int)(deg/100); //7700
				//7707.923339	
	
	data_final = deg+resto;
	
	//printf("dato flotante %.6f\n", x);
	//printf("dato entero %d\n", (int)x);
	//printf("dato del degree %d\n", deg);
	//printf("dato del minutos %.6f\n", resto);
	//printf("dato enc oordenadas %.6f\n", data_final);
	
	return (-1*data_final);
}