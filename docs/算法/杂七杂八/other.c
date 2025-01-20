void DoorCheck(void)
{

    if(!bErrorRelease)
    {
        cFilterDoorNo++;
        if(cFilterDoorNo>20)    //200~300ms
        {
            cFilterDoorNo=0x00;
            if(cError.allBit==0x00)
            {
                if(bBegin)
                {
                    if(bSubSpining)
                    {
                        bErrorOpenDoor=1;
                    }
                    else if(bSubInertiaing)
                    {
                        bPauseDoor=1;
                        filterno=1;
                    }
                }
            }
            bErrorRelease=1;
        }
    }
    else
    {
        cFilterDoorNo=0x00;
        if(bErrorRelease)           //彻底解除报警
        {
            if(!bErrorWtLeSen&&(cError.allBit!=0x00))
            {
                cCountBuzz=0x00;
            }
            cError.allBit&=0x20;
        }
        bErrorRelease=0;
        bPauseDoor=0;
    }

    if(filterno)
    {
    SpiningCheck();

    }
    else

    UnBalanceCheck();


}

case 1.1:
bErrorRelease:0
cFilterDoorNo : 21
cError.allBit: 0
bBegin: 1
bSubSpining :1
bSubInertiaing :0

case 1.2:
bErrorRelease:0
cFilterDoorNo : 21
cError.allBit: 0
bBegin: 1
bSubSpining :0
bSubInertiaing :1

case 1.3
bErrorRelease:0
cFilterDoorNo : 21
cError.allBit: 0
bBegin: 0

case 1.4:
bErrorRelease:0
cFilterDoorNo : 21
cError.allBit: 1

case 1.5:
bErrorRelease:0
cFilterDoorNo:19
cError.allBit: 1

case 2.1
filterno:1

case 2.2
filterno:0

cTimer100msLoad：0
cFilterUnBalanNo：11
cUnBalanceNo：0
cUnBalanCount：10
bFulling=0
void UnBalanceCheck(void)
{
    
     cSetFullCount=1;
    if(cTimer100msLoad&&(cPauseControl.allBit==0x00))//!bErrorUnBalan)
    {
        cFilterUnBalanNo++;
        if(cFilterUnBalanNo>1)  //10~20ms
        {
            cFilterUnBalanNo=0x00;
            cUnBalanceNo++;
            if(cUnBalanceNo<=cUnBalanCount)
            {
                cUnBalaControl.allBit=0x07;
                if(bFulling)
                {
                    if(bInFallFullWash)//喷淋漂洗标志位
                    {
                        iTimer1secStep=cntInFallFullTM;//带喷淋漂洗的漂洗过程时间
                        cFullControl.allBit=0x5f;//为何不对进水标志置1
                        bInFallFullWashing=0;//喷淋漂洗标志位
                    }
                    else
                    {

                        cFullControl.allBit=cntFullPR[cProcess];
                    }
                    iTimer1secStep+=180;
                }
                else
                {
                    bFull=1;    //脱水中的不平衡修正按漂洗控制
                    bFulling=1;
                    cFullControl.allBit=0x00;
                    bSpining=0;
                /*  iTimer1secStep=cntCoeSpinTM[cProcess];
                    /*iTimer1secStep=180;
                    cSpinControl.allBit=cntSpinPR[cProcess];*/

                }
                bGoing=0;
                iTimer1secEnd=0x0000;
            }
            else
            {
                cUnBalaControl.allBit=0x00;
                bErrorUnBalan=1;
                cUnBalanceNo=0x00;
            }
        }
    }
    else
    {
        cFilterUnBalanNo=0x00;
    }
             // cSetFullCount=cntFullPR[cProcess];        //数组中有可能达到0，，当cprocess为6和5时系统就崩溃
    iTimer1secStep=(cSetFullCount-cFullCountNo)*(cntCoeFullTM[cProcess]/cSetFullCount);                  //除数为零系统崩溃
}

UnBalanceCheck
case 1.1:
cTimer100msLoad:1
cPauseControl.allBit:0
cFilterUnBalanNo:10
cUnBalanCount:10
cUnBalanceNo:5
bFulling:1
bInFallFullWash:1

case 1.2:
cTimer100msLoad:1
cPauseControl.allBit:1
cUnBalanCount:0
cUnBalanceNo:5

case 1.3:
cTimer100msLoad:0
cPauseControl.allBit:0
cUnBalanCount:10
cUnBalanceNo:5
bFulling:0

case 1.4
cTimer100msLoad:1
cPauseControl.allBit:0
cFilterUnBalanNo:10
cUnBalanCount:10
cUnBalanceNo:5
bFulling:1
bInFallFullWash:0

case2.1:
cTimer100msLoad:0
cPauseControl.allBit:1



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
        &&(((cProgram==4)&&(cNoWaterProgram==3))
            ||((cProgram==6)&&(cProcess==4))))
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







case 4.2:
bBegin:0
cNoWaterProgram:1
cProgram:1
cProcess:1
bPauseKey:1
bFulling 0
bSpining: 1
bSpinOutFall:0

bSpinInterva:0   
bSpinSpin:0 
bSpinInertia:0
(后面三个并列关系)
bSpinInterva:0   
bSpinSpin:0 
bSpinInertia:1

bSpinInterva:0   
bSpinSpin:1
bSpinInertia:0

bSpinInterva:1   
bSpinSpin:1
bSpinInertia:0

bSpinInterva:1   
bSpinSpin:0
bSpinInertia:0

case 4.1:
bBegin:0
cNoWaterProgram:1
cProgram:1
cProcess:1
bPauseKey:1
bFulling 0
bSpining: 1
bSpinOutFall:1


case 3.6
bBegin:0
cNoWaterProgram:1
cProgram:1
cProcess:1
bPauseKey:0
bFulling 1
bSpining: 0
bInFallFullWashing:0
bFullOutFall:1
cUnBalaControl.allBit:0

case 3.5
bBegin:0
cNoWaterProgram:1
cProgram:1
cProcess:1
bPauseKey:0
bFulling 1
bSpining: 0
bInFallFullWashing:1
bFullOutFall:0
cUnBalaControl.allBit:1

case 3.4
bBegin:0
cNoWaterProgram:1
cProgram:1
cProcess:1
bPauseKey:0
bFulling 1
bSpining: 0
bInFallFullWashing:1
bFullOutFall:1
cUnBalaControl.allBit:0

case 3.3
bBegin:0
cNoWaterProgram:1
cProgram:1
cProcess:1
bPauseKey:0
bFulling 1
bSpining: 0
bInFallFullWashing:1
bFullOutFall:1
cUnBalaControl.allBit:1

case 3.2.4
bBegin:0
cNoWaterProgram:1
cProgram:1
cProcess:1
bPauseKey:0
bFulling 1
bSpining: 0
bInFallFullWashing:1
bFullOutFall:0
cUnBalaControl.allBit:0
bFullInterva:0
bFullSpin:0

case 3.2.3
bBegin:0
cNoWaterProgram:1
cProgram:1
cProcess:1
bPauseKey:0
bFulling 1
bSpining: 0
bInFallFullWashing:1
bFullOutFall:0
cUnBalaControl.allBit:0
bFullInterva:1
bFullSpin:0

case 3.2.2
bBegin:0
cNoWaterProgram:1
cProgram:1
cProcess:1
bPauseKey:0
bFulling 1
bSpining: 0
bInFallFullWashing:1
bFullOutFall:0
cUnBalaControl.allBit:0
bFullInterva:0
bFullSpin:1

case 3.2.1
bBegin:0
cNoWaterProgram:1
cProgram:1
cProcess:1
bPauseKey:0
bFulling 1
bSpining: 0
bInFallFullWashing:1
bFullOutFall:0
cUnBalaControl.allBit:0
bFullInterva:0
bFullSpin:0
bFullInertia：1

case 3.2
bBegin:0
cNoWaterProgram:1
cProgram:1
cProcess:1
bPauseKey:0
bFulling 1
bSpining: 0
bInFallFullWashing:1
bFullOutFall:0
cUnBalaControl.allBit:0


case 3.1
bBegin:0
cNoWaterProgram:1
cProgram:1
cProcess:1
bPauseKey:0
bFulling 0
bSpining: 0


case 1.1:
bBegin:1
cProgram:4
cNoWaterProgram:3
cProcess:4

bBegin:1
cProgram:5
cNoWaterProgram:3
cProcess:4

case 1.2:
bBegin:1
cNoWaterProgram:3
cProgram:6
cProcess:4

case 1.3
bBegin:0
cProgram:4
cNoWaterProgram:3
cProcess:4

case 1.4
bBegin:0
cNoWaterProgram:3
cProgram:6
cProcess:4
(没写完)

case 2.1

bBegin:0
cNoWaterProgram:1
cProgram:1
cProcess:1
bPauseKey:1

