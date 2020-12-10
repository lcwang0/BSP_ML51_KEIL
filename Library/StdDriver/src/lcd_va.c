/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//***********************************************************************************************************

#include "ML51.h"

/**
 *  @brief LCD Initialization routine.
 *  @param[in]  u8LCDPowerType  LCD Power type: \ref TYPE_A (Standard) / \ref TYPE_B (LowPower)
 *  @param[in]  u8LCDVSource    LCD VLCD source: \ref AVDD_PIN / \ref VLCD_PIN / \ref Internal_VCP
 *  @param[in]  u8DrivingVol    LCD driving voltage: \ref LCD_CPVOL_5_2V / \ref LCD_CPVOL_5_0V / \ref LCD_CPVOL_4_8V / \ref LCD_CPVOL_4_6V /
 *                                                  \ref LCD_CPVOL_4_4V / \ref LCD_CPVOL_4_2V / \ref LCD_CPVOL_4_0V / \ref LCD_CPVOL_3_8V /
 *                                                  \ref LCD_CPVOL_3_6V / \ref LCD_CPVOL_3_4V / \ref LCD_CPVOL_3_2V / \ref LCD_CPVOL_3_0V /
 *                                                  \ref LCD_CPVOL_2_8V
 *  @param[in]  u8BiasLevel     LCD bias level: \ref BIAS_1_2 (1/2 bias) / \ref BIAS_1_3 (1/3 bias) / \ref BIAS_1_4 (1/4 bias)
 *  @param[in]  u8ComNum        LCD Com number: \ref LCD_4COM (1/4 Duty)/ \ref LCD_6COM (1/6 Duty)/ \ref LCD_8COM ((1/8 Duty)
 *  @return None.
 *  @example LCD_Open(TYPE_A, Internal_VCP, LCD_CPVOL_3_6V, BIAS_1_4, LCD_8COM );
 */
void LCD_Open_va(unsigned char u8LCDPowerType, unsigned char u8LCDVSource, unsigned char u8DrivingVol, unsigned char u8BiasLevel, unsigned char u8ComNum)
{
    LCD_Disable();
    /* Turn all segments off */
    LCD_SetAllPixels(Disable);

    switch(u8LCDPowerType)
    {
      case TYPE_A: clr_LCDCON0_TYPE; break;
      case TYPE_B: set_LCDCON0_TYPE; break;
    }

      LCDCON0&=0xC0; LCDCON0|=u8BiasLevel;    //Setting bias 
      LCDCON0&=0xF3; LCDCON0|=u8ComNum;       //Setting com
      LCDCPUMP = u8DrivingVol;                //Setting charge pump voltage
      LCDRMODE = u8LCDVSource;                // VLCD source select

}


/**
 *  @brief LCD Current Mode Select.
 *  @param[in]  u8LCDCurrentSel   LCD Current type: \ref Resistor_Enhance_Mode/
 *                                                  \ref Resistor_PowerSave_Mode /
 *                                                  \ref Buffer_PowerSave_Mode /
 *                                                  \ref Resistor_Mode /
 *                                                  \ref Buffer_Mode /
 *  @param[in]  u8LCDPSSel        LCD Power Saving Select\: \ref TurnOn_All / \ref TurnOn_1_4 / \ref TurnOn_2_4 / \ref TurnOn_3_4 /
 *  @Note    (Resistor_Enhance_Mode + TurnOn_All), (Buffer_Mode + TurnOn_All), (PowerSave_Mode + TurnOn_x_4)
 *  @example LCD_Current_Mode(Buffer_Mode, TurnOn_All);
 */
void LCD_Current_Mode_va(unsigned char u8LCDCurrentSel, unsigned char u8LCDPSSel)
{
    SFRS=3;
    LCDRMODE |= (u8LCDCurrentSel&0xc0);               // lcd Driving type
    switch (u8LCDCurrentSel)
    {
      case Buffer_PowerSave_Mode: 
      case Resistor_PowerSave_Mode: 
        LCDPWR = u8LCDPSSel; break;
      case Resistor_Enhance_Mode:
        LCDRMODE|=Resistor_Mode;
        set_LCDCON1_RE_MODE;
      case Buffer_Mode: 
      case Resistor_Mode: 
        LCDPWR=0; break;
    }
}

