#define LIST_SIZE 16
#define MAC_LEN 6

/*
 * This is the number of devices we would scan for
 */

int8_t SAVED_CONNECTIONS = 0;
/*
 * This is your friend's MAC address list
 Format it by taking the mac address aa:bb:cc:dd:ee:ff 
 and converting it to 0xaa,0xbb,0xcc,0xdd,0xee,0xff
 */
 // DC-41-A9-65-C6-15
// ac-5f-ea-0b-b2-0c
// {0xdc, 0x41, 0xa9, 0x65, 0xc6, 0x15}
uint8_t umac_addr[LIST_SIZE][MAC_LEN] = { };

bool uavailable[LIST_SIZE] = {};
int8_t urssi[LIST_SIZE] = {};
/*
 * This is your friend's name list
 * put them in the same order as the MAC addresses
 */
String uname[LIST_SIZE] = {};

String remove_spaces(String a) {
    String b = "";
    for(char i: a) {
      if(!isspace(i)) {
          b+=i;
      }
    }
    return b; 
}

void add_device(String name, std::vector<String> tokenised_mac_addr) {
  uname[SAVED_CONNECTIONS] = name;
  // Serial.println(uname[SAVED_CONNECTIONS]);

  for(int idx=0; idx < 6; idx++) {
    char hex[2]; 
    tokenised_mac_addr[idx].toCharArray(hex,3 );
    umac_addr[SAVED_CONNECTIONS][idx] = (uint8_t)strtol(hex, NULL, 16);
    uavailable[SAVED_CONNECTIONS] = 0;
    urssi[SAVED_CONNECTIONS] = 0;
    // Serial.println(umac_addr[SAVED_CONNECTIONS][idx]);
  }
  SAVED_CONNECTIONS++;
}

String show_connected_devices()
{
    
    String available_mac_dropdown = "<select id='mac_addr' name='mac_addr'>\n";
    
         
    auto client_count = wifi_softap_get_station_num();
    Serial.printf("Total devices connected = %d\n", client_count);
    
    auto i = 1;
    struct station_info *station_list = wifi_softap_get_station_info();
    while (station_list != NULL) {
        auto station_ip = IPAddress((&station_list->ip)->addr).toString().c_str();
        char station_mac[18] = {0};
            
        sprintf(station_mac, "%02X:%02X:%02X:%02X:%02X:%02X", MAC2STR(station_list->bssid));
        Serial.printf("%d. %s %s", i++, station_ip, station_mac);
        
        available_mac_dropdown += "<option value=\" ";
        available_mac_dropdown += station_mac; 
        available_mac_dropdown += "\">"; 
        available_mac_dropdown += station_mac;
        available_mac_dropdown += "</option> \n";
        
        station_list = STAILQ_NEXT(station_list, next);
    }
    available_mac_dropdown +="</select>\n";
    wifi_softap_free_station_info();

    return available_mac_dropdown;
}

void red() {
  digitalWrite(D6, HIGH); }  // Turn ON the red LED
void blue() {
  digitalWrite(D5, HIGH); } // Turn ON the blue LED
void green() {
  digitalWrite(D7, HIGH); } // Turn ON the green LED
void turnoff() {
  digitalWrite(D7, LOW), digitalWrite(D5, LOW), digitalWrite(D6, LOW); 
}

void display_status() {
  bool green_led = false;
  for(int idx=0; idx < SAVED_CONNECTIONS; idx++) {
      if(uavailable[idx] == true) {
          green_led = true;
          green();
      }
  }
  if(!green_led) {
    red();
  }

}


