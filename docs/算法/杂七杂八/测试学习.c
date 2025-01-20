
/************************************************
*原型：void SpiningCheck(void)
*功能：脱水过程检测子程序
*说明：无
*参数：无
*返回：无
************************************************/
void SpiningCheck(void)
{
    bSubSpining=0;
    bSubInertiaing=0;
    if(bBegin
        &&(((cProgram==PROGRAM_NOWATER_CHECK)&&(cNoWaterProgram==NOWATERCHECK_C))
            ||((cProgram==PROGRAM_LAB_CYC)&&(cProcess==PROCESS_SGSPIN))))
    {
        bSubSpining=1;
        cUnBalanCount=0;    //不平衡修正次数
    }
    else if(!bPauseKey)
    {
        if(bFulling)
        {                                                   /////////////////////////////////////////////////////////////////////////////////////////
            if(bInFallFullWashing)
            {
                bSubSpining=1;
            }
            if(!bFullOutFall&&(cUnBalaControl.allBit==0x00))
            {
                if(bFullInterva||bFullSpin)
                {
                    bSubSpining=1;
                }
                else if(bFullInertia)
                {
                    bSubInertiaing=1;
                }
            }
        }
        else if(bSpining)
        {
            if(!bSpinOutFall)
            {
                if(bSpinInterva||bSpinSpin)
                {
                    bSubSpining=1;
                }
                else if(bSpinInertia)
                {
                    bSubInertiaing=1;
                }
            }
        }
        cUnBalanCount=2;    //不平衡修正次数
    }
}