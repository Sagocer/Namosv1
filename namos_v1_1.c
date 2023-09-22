#include <namos_v1_1.h>

int btn_push_ok_value=25;
short channel_state[8];
short btn_lock[8];
int btn_push_counter[8];
int analog_in[8] = {7, 4, 5, 6, 0, 1, 2, 3};
int16 channel_emty_value[8];
int16 channel_active_value[8];
short channel_alarm_bit[8];
int alarm_high_counter=0;
int alarm_low_counter=0;
short alarm_led_up=0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int16 read_adc_value(int channel)
{   
   set_adc_channel(channel);
   delay_us(20);
   return read_adc();    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void light_out_control(int channel, short state)
{
   if(state == 1)
      switch(channel) 
      {
         case 0: output_high(out1); break;
         case 1: output_high(out2); break;
         case 2: output_high(out3); break;
         case 3: output_high(out4); break;
         case 4: output_high(out5); break;
         case 5: output_high(out6); break;
         case 6: output_high(out7); break;
         case 7: output_high(out8); break;
      }
   else
      switch(channel) 
      {
         case 0: output_low(out1); break;
         case 1: output_low(out2); break;
         case 2: output_low(out3); break;
         case 3: output_low(out4); break;
         case 4: output_low(out5); break;
         case 5: output_low(out6); break;
         case 6: output_low(out7); break;
         case 7: output_low(out8); break;
      }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void state_out_control(int channel, short state)
{
   if(state == 1)
      switch(channel) 
      {
         case 0: output_high(state1); break;
         case 1: output_high(state2); break;
         case 2: output_high(state3); break;
         case 3: output_high(state4); break;
         case 4: output_high(state5); break;
         case 5: output_high(state6); break;
         case 6: output_high(state7); break;
         case 7: output_high(state8); break;
      }
    else
      switch(channel) 
      {
         case 0: output_low(state1); break;
         case 1: output_low(state2); break;
         case 2: output_low(state3); break;
         case 3: output_low(state4); break;
         case 4: output_low(state5); break;
         case 5: output_low(state6); break;
         case 6: output_low(state7); break;
         case 7: output_low(state8); break;
      }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void start_meas(int channel)
{
   channel_emty_value[channel] = read_adc_value(analog_in[channel]);
   
   light_out_control(channel, 1);
   state_out_control(channel, 1);
   
   delay_ms(500);
   
   channel_active_value[channel] = read_adc_value(analog_in[channel]);
   
   channel_state[channel] = 1; 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void btn_events(int channel)
{
   if(channel_state[channel] == 0) 
   {  
      start_meas(channel);      
   }
   else
   {  
      light_out_control(channel, 0);
      state_out_control(channel, 0);
      channel_state[channel] = 0;
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void alarm_dedect()
{
   int16 xx=0;
   for(int ch=0; ch<8; ch++)
      if(channel_state[ch] == 1)
      {        
         xx = read_adc_value(analog_in[ch]);
         
         if(xx > 550 || xx < 497)
         {
            light_out_control(ch, 0);
            channel_state[ch] = 0;
            channel_alarm_bit[ch] = 1;
         }      
      }
         
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void alarm_led_pulse()
{
   if(alarm_led_up==1) for(int m=0; m<8; m++) if(channel_alarm_bit[m]==1) state_out_control(m, 1);
   else                for(int n=0; n<8; n++) if(channel_alarm_bit[n]==1) state_out_control(n, 0);
}

void main()
{  
  
  // float okunan;
   setup_adc_ports(sAN0|sAN1|sAN2|sAN3|sAN4|sAN5|sAN6);
   setup_adc(ADC_CLOCK_INTERNAL);
   
   set_tris_b(0xff);
   set_tris_c(0x00);
   set_tris_d(0x00);
   set_tris_e(0x00);
   
   output_low(state1);
   output_low(state2);
   output_low(state3);
   output_low(state4);
   output_low(state5);
   output_low(state6);
   output_low(state7);
   output_low(state8);
   
   output_low(out1);
   output_low(out2);
   output_low(out3);
   output_low(out4);
   output_low(out5);
   output_low(out6);
   output_low(out7);
   output_low(out8);
   
   output_low(PIN_E2);
   
   for(int a=0; a<8; a++) channel_alarm_bit[a]=0;
   
   delay_ms(1000);

   while(TRUE)
   { /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
      if(input(btn1)) {if(btn_lock[0] == 0) btn_push_counter[0]++;} else btn_lock[0] = 0; 
      if(input(btn2)) {if(btn_lock[1] == 0) btn_push_counter[1]++;} else btn_lock[1] = 0;
      if(input(btn3)) {if(btn_lock[2] == 0) btn_push_counter[2]++;} else btn_lock[2] = 0;
      if(input(btn4)) {if(btn_lock[3] == 0) btn_push_counter[3]++;} else btn_lock[3] = 0;
      if(input(btn5)) {if(btn_lock[4] == 0) btn_push_counter[4]++;} else btn_lock[4] = 0;
      if(input(btn6)) {if(btn_lock[5] == 0) btn_push_counter[5]++;} else btn_lock[5] = 0;
      if(input(btn7)) {if(btn_lock[6] == 0) btn_push_counter[6]++;} else btn_lock[6] = 0;
      if(input(btn8)) {if(btn_lock[7] == 0) btn_push_counter[7]++;} else btn_lock[7] = 0;
   
      if(btn_push_counter[0] == btn_push_ok_value) {btn_lock[0] = 1; btn_push_counter[0] = 0; for(int c=0; c<8; c++) channel_alarm_bit[c]=0; output_low(PIN_E2);}
      if(btn_push_counter[1] == btn_push_ok_value) {btn_lock[1] = 1; btn_push_counter[1] = 0; btn_events(1);}
      if(btn_push_counter[2] == btn_push_ok_value) {btn_lock[2] = 1; btn_push_counter[2] = 0; btn_events(2);}
      if(btn_push_counter[3] == btn_push_ok_value) {btn_lock[3] = 1; btn_push_counter[3] = 0; btn_events(3);}
      if(btn_push_counter[4] == btn_push_ok_value) {btn_lock[4] = 1; btn_push_counter[4] = 0; btn_events(4);}
      if(btn_push_counter[5] == btn_push_ok_value) {btn_lock[5] = 1; btn_push_counter[5] = 0; btn_events(5);}
      if(btn_push_counter[6] == btn_push_ok_value) {btn_lock[6] = 1; btn_push_counter[6] = 0; btn_events(6);}
      if(btn_push_counter[7] == btn_push_ok_value) {btn_lock[7] = 1; btn_push_counter[7] = 0; btn_events(7);}
      
      alarm_dedect();
      
      delay_ms(1);
      
      if(alarm_led_up == 0) { alarm_low_counter++; alarm_high_counter=0;}
      else                  { alarm_low_counter=0; alarm_high_counter++;}
      
      if(alarm_low_counter  == 2000) alarm_led_up = 1;
      if(alarm_high_counter == 2000) alarm_led_up = 0;
      
      alarm_led_pulse();
      
      for(int b=0; b<8; b++) if(channel_alarm_bit[b] == 1) output_high(PIN_E2);
   } /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
