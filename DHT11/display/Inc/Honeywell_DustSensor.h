/**
	******************************************************************************
	* File Name          : Honeywell_DustSensor.h
	* Description        : This file contains the common defines of the application
	******************************************************************************
	*
	* COPYRIGHT(c) 2017 Akash kapashia
       * Created by Akash kapashia
	******************************************************************************
*/
 
/* Define to prevent recursive inclusion -------------------------------------*/


 #ifndef __HONEYWELL_DUSTSENSOR_H
 #define __HONEYWELL_DUSTSENSOR_H
	 

 void start_Particle_Measure(void);	
 void Stop_Particle_Measurement(void);
 void Read_Particle_Measuring(void);
 void Enable_Auto_Send(void);
 void Stop_Auto_Send(void);

#endif
