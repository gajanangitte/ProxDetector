
// API KEY BBFF-129f3f6c0cc0a779f766fcef7ac58b88a39
// token BBFF-YtBpf7m0RwZmyemu2Fx4eJUlbxmpDw
 
#include "Ubidots.h"

// const char* UBIDOTS_TOKEN = "BBFF-rEoHDYRZdxl9A0f9T8zhnOgIzmRFuy";
const char* UBIDOTS_TOKEN = "BBFF-YtBpf7m0RwZmyemu2Fx4eJUlbxmpDw";
const char* WIFI_SSID = "gajanan";
const char* WIFI_PASS = "wallahi7";

String LOCATION = "experimentation base";

Ubidots ubidots(UBIDOTS_TOKEN,  UBI_EDUCATIONAL, UBI_HTTP);

// -8.98871 log(1982.22 x)
double rssi_to_dist(int8_t rssi) {
  if(rssi == 0)
    return 0;  
  Serial.println(rssi);

  double ans = (double)exp((double)rssi/(-8.98871))/(double)1982.22;
  Serial.println(ans);  
  return ans;
}

void update_location(String uname[], int8_t urssi[], bool *uavailable, int8_t connections ) {

  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  ubidots.setDebug(true);
  delay(100);

    

  for(int idx = 0; idx < connections; idx++) {

    // float last_updated_time = ubidots.get()
    char* device_name = (char*)malloc(sizeof(char) * 50);
    char* device_strength = (char*)malloc(sizeof(char) * 50);
    
    String d_strength = uname[idx] + " distance (in m)";
    uname[idx].toCharArray(device_name, uname[idx].length()+1);
    d_strength.toCharArray(device_strength, d_strength.length()+1 );


    ubidots.add(device_name, uavailable[idx]);
    ubidots.add(device_strength, rssi_to_dist(urssi[idx]));

    uavailable[idx] = 0;
  } 

  // Serial.println(001);
  bool bufferSent = false;
  bufferSent = ubidots.send();

  if(bufferSent) {
    Serial.println("Location Updated");
  }
  // free(context);
  delay(5000);
}