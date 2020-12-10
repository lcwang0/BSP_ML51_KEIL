/**
 * @brief This function config PWM1 generator 
 * @param[in] u8PWM1ChannelNum PWM1 channel number. Valid values are between 0~5
 * @param[in] u8PWM1OPMode PWM1 run mode select from Independent, Complementary or Synchronized mode.
 * @param[in] u8PWM1PwmType select Edge-Aligned Type or Center-Aligned Type
 * @param[in] u32PWM1Frequency Target generator frequency, note the actually PWM period is 16bit value. from 0x0000 ~ 0xFFFF
 * @param[in] u16PWM1DutyCycle Target generator duty cycle percentage of PWM1. Valid range are between 0 ~ 100. 10 means 10%, 20 means 20%...
 * @return none
 * @note        
 * @example PWM1_ConfigOutputChannel(0,Synchronized,EdgeAligned,0x6FF,10);
  */
void PWM1_ConfigOutputChannel(unsigned char u8PWM1ChannelNum,
                                unsigned char u8PWM1OPMode,
                                unsigned char u8PWM1PwmType,
                                unsigned long u32PWM1Frequency,
                                unsigned int u16PWM1DutyCycle)
{
    SFRS = 2;
    switch (u8PWM1OPMode)
    {
        case Independent:    PWM1CON1&=0x3F;break;
        case Complementary:  PWM1CON1&=0x3F;PWM1CON1|=0x40;break;
        case Synchronous:    PWM1CON1&=0x3F;PWM1CON1|=0x80;break;
    }
    switch (u8PWM1PwmType)
    {
        case EdgeAligned:    PWM1CON1&=0xEF;break;
        case CenterAligned:  PWM1CON1|=0x10;break;
    }
    switch (u8PWM1ChannelNum)
    {
        case 0:  PWM1C0H=(u32PWM1Frequency*u16PWM1DutyCycle/100)>>8;PWM1C0L=(u32PWM1Frequency*u16PWM1DutyCycle/100);break;
        case 1:  PWM1C1H=(u32PWM1Frequency*u16PWM1DutyCycle/100)>>8;PWM1C1L=(u32PWM1Frequency*u16PWM1DutyCycle/100);break;
    }
    PWM1PH = u32PWM1Frequency>>8;
    PWM1PL = u32PWM1Frequency;
}


/**
* @brief This function action all PWM run
* @param[in] none
* @return none
* @note        
* @example PWM0_RUN();
*/
void PWM1_RUN(void)
{
    set_PWM1CON0_PWMRUN;
}

/**
* @brief This function action all PWM stop run
* @param[in] none
* @return none
* @note        
* @example PWM0_RUN();
*/
void PWM1_STOP(void)
{
  clr_PWM1CON0_PWMRUN;
}