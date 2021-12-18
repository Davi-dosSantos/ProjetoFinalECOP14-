#include "config.h"
#include "bits.h"
#include "lcd.h"
#include "keypad.h"
#include "ssd.h"
#include "led.h"
#include "rgb.h"
#include <proc/pic18f4520.h>
#include "adc.h"
#include "pwm.h"
#include "timer.h"
#include "bits.h"


void main(void){
    unsigned long int cont = 1800000, round=1, i=0, nled=0;
    unsigned int tecla = 16, win = 0;
    unsigned char stoped = 0, op = 0;
    
    lcdInit();
    ssdInit();
    adcInit();
    kpInit();
    pwmInit();
    timerInit();
    
    for(;;){
        ssdUpdate();
        switch(op){
            case 0:
                for(i=0;i<100;i++){
                    if(stoped == 1){
                        cont--;
                    }
                }
                rgbColor(WHITE);
                lcdPosition(0, 0);
                lcdChar((((cont / 360000) % 24) / 10) + 48);
                lcdChar((((cont / 360000) % 24) % 10) + 48);
                lcdChar(':');
                lcdChar((cont / 60000) % 6 + 48);
                lcdChar((cont / 6000) % 10 + 48);
                lcdChar(':');
                lcdChar((cont / 1000) % 6 + 48);
                lcdChar((cont / 100) % 10 + 48);
                
                if(cont == 0){
                    win = 1;
                    stoped = 0;
                    lcdPosition(0, 9);
                    lcdChar(' ');
                    lcdChar(' ');
                    lcdChar(' ');
                    lcdChar(' ');
                    lcdChar(' ');
                    lcdChar(' ');
                    lcdChar(' ');
                    lcdChar(' ');        
                    
                 
                    lcdPosition(1, 0);
                    lcdChar('F');
                    lcdChar('I');
                    lcdChar('N');
                    lcdChar('I');
                    lcdChar('S');
                    lcdChar('H');
                    lcdChar(' ');
                    lcdChar('R');
                    lcdChar('O');
                    lcdChar('U');
                    lcdChar('N');
                    lcdChar('D');
                    lcdChar(' ');
                    lcdChar('!');
                    lcdChar('!');
                    lcdChar('!');
                        
                }
                
                if (win == 1){
                    pwmSet(100);
                    rgbColor(RED); 

                
                }
                
                
                
            case 1:
                kpDebounce();
                op = 2;
                break;
            case 2:
                if (kpRead()!=tecla){
                    tecla = kpRead();
                    if(bitTst(tecla,0)){//pausa contador
                        pwmSet(0);
                        win = 0;
                        if(stoped == 0){
                            stoped = 1;
                        }else{
                            stoped = 0;
                        }
                    }
                    if(bitTst(tecla,1)){//reset contador
                        rgbColor(WHITE);
                        pwmSet(0);
                        win = 0;
                        cont = 50000;
                        stoped = 0;
                        lcdPosition(1, 0);
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdPosition(0, 9);
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                        lcdChar(' ');
                     
                    }
                    if(bitTst(tecla,2)){// K.O
                        if(cont!=0){
                            stoped = 0;
                            lcdPosition(0, 9);
                            lcdChar('K');
                            lcdChar('.');
                            lcdChar('O');
                            lcdChar('!');
                            lcdChar('!');
                            lcdChar(' ');
                            lcdChar(' ');
                            lcdChar(' ');
                            lcdPosition(1, 0);
                            lcdChar('E');
                            lcdChar('N');
                            lcdChar('D');
                            lcdChar(' ');
                            lcdChar('O');
                            lcdChar('F');
                            lcdChar(' ');
                            lcdChar('F');
                            lcdChar('I');
                            lcdChar('G');
                            lcdChar('H');
                            lcdChar('T');
                            lcdChar(' ');
                            lcdChar('!');
                            lcdChar('!');
                            lcdChar('!');
                            
                            
                            
                            win = 1;
                         
                           
                        }
                    }
                    if(bitTst(tecla,3)){// seta round atual
                        if (round < 5)
                            round ++;
                        else round = 1;
                    }
                    
                }
                op = 3;
                break;
                case 3:
                //Mostra round atual no no display
                ssdDigit(0, 0);
                ssdDigit(0, 1);
                ssdDigit(0, 2);
                ssdDigit(round, 3);
                op = 0;  
                for(char i=0; i<50; i++)
                break;
            
            default:
            op = 0;
            break;
        }
        //ssdUpdate();
    }
}