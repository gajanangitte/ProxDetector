#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "./prox_detection_util.h"
#include "./server_page.h"

const char *connect_ssid = "Prox_Connector";
const char* password = "admin12345";

bool web_helper = true;

IPAddress connect_ip(192, 169, 69, 69);
IPAddress connect_gateway(192, 169, 69, 69);
IPAddress connect_subnet(255, 255, 255, 0);

ESP8266WebServer server(80);


String sendFormHTML() {
  Serial.println(0001);  
  String html = get_html_top();
  html += show_connected_devices(); 
  html += get_hmtl_down();  
  Serial.println(0002);   

return html;
}

std::vector<String> ma_tokenisation(String ma) {
  std::vector<String> result;
  ma = ma+":";
  String temp = "";
  for(char i: ma ) {
    if(i==':') {
      result.push_back(temp);
      temp = "";
    }
    else
      temp+=i;
  }
  
  if(result.size()!=6){
     server.send(404, "text/plain", "Form Format Not Supported");
  }

  return result;
}

void handle_onConnect() {
    server.send(200, "text/html", sendFormHTML());  
}

void handle_error(){
  server.send(404, "text/plain", "Page Does Not Exist");
}

void handle_stopWebNiggering() {
   web_helper = false;
   server.send(200, "text/plain", "Web Server Stopped");  
}

void handle_onSubmit() {
    String mac_addr = server.arg("mac_addr");
    mac_addr = remove_spaces(mac_addr);
    Serial.println(mac_addr);
    std::vector<String> tokenised_mac_addr = ma_tokenisation(mac_addr);
    String name = server.arg("name");

    Serial.println(name);
    // for(String s: tokenised_mac_addr)
    //   Serial.println(s);
    Serial.println("Meet ^^^");
    add_device(name, tokenised_mac_addr); 

    server.send(200, "text/plain", "Successfully added a device");
}

void load_webpage() {
    
    WiFi.softAP(connect_ssid, password);
    WiFi.softAPConfig(connect_ip, connect_gateway, connect_subnet);
    delay(100);

    server.on("/", handle_onConnect);
    server.on("/action_page", handle_onSubmit);
    server.on("/stop_webserver", handle_stopWebNiggering);
    server.onNotFound(handle_error);

    server.begin();
    Serial.println("HTTP Server Started");


    int start_time = millis();
    int end_time = millis();

    while( web_helper ) {
      server.handleClient();
      end_time = millis();
    }


}