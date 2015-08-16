/**
 * @author  Tilen Majerle
 * @email   tilen@majerle.eu
 * @website http://stm32f4-discovery.com
 * @link    http://stm32f4-discovery.com/2015/08/hal-library-23-touch-for-stm32fxxx/
 * @version v1.0
 * @ide     Keil uVision
 * @license GNU GPL v3
 * @brief   Touch library for all touch screen controllers
 *	
\verbatim
   ----------------------------------------------------------------------
    Copyright (C) Tilen Majerle, 2015
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
\endverbatim
 */
#ifndef TM_TOUCH_H
#define TM_TOUCH_H 100

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup TM_STM32Fxxx_HAL_Libraries
 * @{
 */

/**
 * @defgroup TM_TOUCH
 * @brief    Touch library for touch screen controllers - http://stm32f4-discovery.com/2015/08/hal-library-23-touch-for-stm32fxxx/
 * @{
 *
 * This library is a "high" level library for working with touch screens.
 * It needs low level drivers (read/write functions) specially for your touch controller.
 *
 * When you have your driver written, 2 functions are needed:
 *  - Function for touch initialization
 *  - Function for touch read coordinates
 * 
 * When you call @ref TM_TOUCH_Init function, you also have to specify some parameters for low level functions.
 *
 * \par Set built-in driver
 *
 * @note  If you follow my description in @ref TM_DISCO library on how to select your used board, then this library will automatically select your "target".
 * 
\code
//Use touch driver on STM32F7-Discovery, FT5336 controller
#define TOUCH_USE_STM32F7_DISCOVERY
	
//Use touch driver on STM32F439-Eval board, TS3510 controller
#define TOUCH_USE_STM32F439_EVAL
\endcode
 *
 * @note  When selecting "built-in" drivers, you also have to include some libs.
 *           - @ref TM_TOUCH_TS3510 library for STM32F439-Eval
 *           - @ref TM_TOUCH_FT5336_H for STM32F7-Discovery
 *
 * \par Set custom driver
 *
 * Setting custom driver needs special structure @TM_TOUCH_DRIVER_t where you pass pointers to your low level driver functions.
 * 
 * You can see example on how to do that.
 *
\code
//Create variable with structure
TM_TOUCH_DRIVER_t MyDriver;

//Working touch screen structure
TM_TOUCH_t TS;

//Create functions for custom TOUCH driver
//Init function
uint8_t MYDRIVER_Init(TM_TOUCH_t* TS) {
  //Initialize your custom driver here.
  
  //Set max X and Y location for touch
  TS->MaxX = MAX_X_VALUE;
  TS->MaxY = MAX_Y_VALUE;
}

//Read function
uint8_t MYDRIVER_Read(TM_TOUCH_t* TS) {
  //Read coordinates and check if pressed here
}

//In main function for example:
int main() { 
  //Pass init and read functions
  MyDriver.Init = MYDRIVER_Init;
  MyDriver.Read = MYDRIVER_Read;

  //Init touch library
  TM_TOUCH_Init(&MyDriver, &TS);

  while (1) {
    //Read touch and process
    TM_TOUCH_Read(&TS);
  }
}
\endcode
 *
 * \par Changelog
 *
\verbatim
 Version 1.0
  - First release
\endverbatim
 *
 * \par Dependencies
 *
\verbatim
 - STM32Fxxx HAL
 - defines.h
 - TM TOUCH TS3510
 - TM TOUCH FT5336
 - TM I2C
 - TM GPIO
\endverbatim
 */

#include "stm32fxxx_hal.h"
#include "defines.h"

/**
 * @defgroup TM_TOUCH_Macros
 * @brief    Library defines
 * @{
 */
/* Macros here */
/**
 * @}
 */
 
/**
 * @defgroup TM_TOUCH_Typedefs
 * @brief    Library Typedefs
 * @{
 */

/**
 * @brief  Touch working structure
 */
typedef struct {
	uint8_t NumPresses;   /*!< Number of touches (fingers) detected */
	uint16_t X[10];       /*!< X positions for touches */
	uint16_t Y[10];       /*!< Y positions for touches */
	uint8_t Events;       /*!< Events, if any. For example, touch has detected "zoom" with fingers or similar */
	uint8_t Orientation;  /*!< Touch orientation to match LCD orientation if needed */
	uint16_t MaxX;        /*!< Touch MAX X value. Maximal value for touch X coordinate */
	uint16_t MaxY;        /*!< Touch MAX Y value. Maximal value for touch Y coordinate */
} TM_TOUCH_t;

/**
 * @brief  TOUCH Driver structure
 */
typedef struct {
	uint8_t (*Init)(TM_TOUCH_t*); /*!< Pointer to init function for touch controller */
	uint8_t (*Read)(TM_TOUCH_t*); /*!< Pointer to read function for touch controller */
} TM_TOUCH_DRIVER_t;

/**
 * @brief  TOUCH result enumeration
 */
typedef enum {
	TM_TOUCH_Result_Ok = 0x00, /*!< Everything OK */
	TM_TOUCH_Result_Error      /*!< An error occurred */
} TM_TOUCH_Result_t;

/**
 * @}
 */

/**
 * @defgroup TM_TOUCH_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Initializes touch controller 
 * @param  *Driver: Pointer to filled @ref TM_TOUCH_DRIVER_t to be used for touch. Set parameter to NULL if you want to use default drivers which lib supports
 * @param  *TS: Pointer to empty @ref TM_TOUCH_t structure
 * @retval Member of @ref TM_TOUCH_Result_t enumeration
 */
TM_TOUCH_Result_t TM_TOUCH_Init(TM_TOUCH_DRIVER_t* Driver, TM_TOUCH_t* TS);

/**
 * @brief  Reads touch data from sensor 
 * @param  *TouchData: Poiter to @ref TM_TOUCH_t structure where data will be stored
 * @retval Touch status:
 *            - 0: OK
 *            - > 0: Error
 */
uint8_t TM_TOUCH_Read(TM_TOUCH_t* TouchData);

/**
 * @}
 */
 
/**
 * @}
 */
 
/**
 * @}
 */

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif
