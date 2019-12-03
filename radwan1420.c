
   unsigned int counter=0, counter2=0;

//Timer 0 initiallisations
void InitTimer0()
{
  //OPTION Register
  OPTION_REG.T0CS = 0; //Internal instruction cycle clock (CLKOUT)
  OPTION_REG.PSA = 0;  //Prescaler is assigned to the Timer0 module

  //PS2:PS0: Prescaler Rate Select bits, Prescaler 1:64
  OPTION_REG.PS2 = 1;
  OPTION_REG.PS1 = 0;
  OPTION_REG.PS0 = 1;


  TMR0 = 99; //Timer0 starts counting value

  //INTCON Register
  INTCON.TMR0IE = 1; //1 = Enables the TMR0 Interrupt
  INTCON.PEIE=1;  //Enables all unmasked peripheral interrupts
  INTCON.GIE = 1; //1 = Enables all interrupts

}


//isr
void Interrupt()
{
  if(INTCON.TMR0IF == 1)   //if timer0 interrupt occured
  {
     INTCON.TMR0IF = 0;  //reset timer0 interrupt flag
     TMR0 = 99; //Timer0 starts counting again

     counter++; //counts 1 second

     counter2++; //counts 2 seconds

    /*if(counter == 6000)
     {
       counter=0;
       porte.re0 = ~porte.re0; //toggle led
     }

     if(counter2 == 100)
     {
       counter2=0;
       porte.re1 = ~porte.re1; //toggle led
     }*/

  }
}




// LCD module connections
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;
 // End LCD module connections
unsigned int x = 1;
char RPM[10] ;

void main() {

   TRISE=0B00000001;

   ADCON1=0B00001110;




  Lcd_Init(); // Initialize LCD

  Lcd_Cmd(_LCD_CLEAR); // Clear display

  Lcd_Cmd(_LCD_CURSOR_OFF);// Cursor off


  lcd_out(1,5,"Welcome");
  delay_ms(3000);
  Lcd_Cmd(_LCD_CLEAR); // Clear display
  Lcd_Out(2,5,RPM);  // Write RPM "00660!" at current cursor position
  
  loop:

if (PORTE.RE0 ==0)
{  counter2= 0 ;
while( counter2 <6000)
{
 IntToStr(x, RPM); // RPM is " 0" (one blank here)
  Lcd_Out(2,4,RPM);  // Write RPM "00660!" at current cursor position
if(PORTE.RE0==0)
{
x++;
while (porte.re0==0);
}
}
}

goto loop;



}