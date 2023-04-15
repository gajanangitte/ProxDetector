/****************************************
 * Include Libraries
 ****************************************/
#include "./ubidots_manager.h"
#include "./prox_detection.h"
#include "./esppl_functions.h"

void setup() { 
  
  delay(500);
  pinMode(D5, OUTPUT); // sets the pins to output mode
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  Serial.begin(115200);

  blue();
  load_webpage();
  turnoff();
    
  esppl_init(cb);
}

/* You cannot use a time delay here to keep the LED on, so will need to use ratio of 
detected packets to overall packets to keep LED on for longer. If you try to use a 
delay to keep the light on for long enough to be useful, the watchdog timer kills the 
process and it dies */
int cooldown_timer = 0; /* This variable will be a cooldown timer to keep the LED on for longer, we'll set it to 1000 if we
detect a packet from a device with a MAC address on the list, and then keep the LED on till we get 1000 packets that 
are NOT from any device on the list. */

/* end exparimental variable package */

bool maccmp(uint8_t *mac1, uint8_t *mac2) {
  for (int i=0; i < ESPPL_MAC_LEN; i++) {
    if (mac1[i] != mac2[i]) {
      return false;
    }
  }
  return true;
}

void cb(esppl_frame_info *info) {
  for (int i=0; i<SAVED_CONNECTIONS; i++) {
    if ((maccmp(info->sourceaddr, umac_addr[i]) || maccmp(info->receiveraddr, umac_addr[i])) && (uname[i]!=NULL) ) {
        Serial.println(uname[i] + " is here!");
        Serial.println(umac_addr[i][0] + " is here!");
        Serial.println(info->rssi);
        if(info->rssi > -75 ) {
          uavailable[i] = true;
        }
        else
          uavailable[i] = false;
        
        urssi[i] = info->rssi;
        }
    } 
  
  
  }


void loop() { // I didn't write this part but it sure looks fancy.
  
  while (true) {
    esppl_sniffing_start();
    turnoff();
    Serial.println("Sniffing Mode Started");
    for(int i=0;i<SAVED_CONNECTIONS;i++){
      uavailable[i] = false;
      urssi[i] = 0;
    }
    int32_t start_time = millis();
    int32_t end_time = millis();

        
    while(end_time - start_time <= 10*1000) { 
      for (int i = ESPPL_CHANNEL_MIN; i <= ESPPL_CHANNEL_MAX; i++ ) {
        esppl_set_channel(i);
        while (esppl_process_frames()) {
          //
        }
      }
      end_time = millis();
    }
    
    esppl_sniffing_stop();
    display_status();
    update_location(uname, urssi, uavailable, SAVED_CONNECTIONS);
  }  
}
