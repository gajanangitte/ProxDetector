String get_html_top() {
  String FORM_PAGE_TOP = "<!DOCTYPE html>";
  FORM_PAGE_TOP += "<html>";
  FORM_PAGE_TOP += "<body>";
  FORM_PAGE_TOP += "<center>";
  FORM_PAGE_TOP += "<h2> Proximity Detection Registration <h2>";
  FORM_PAGE_TOP += "<h3> Details Form </h3>";
  FORM_PAGE_TOP += "<br><hr>";
  FORM_PAGE_TOP += "<form action=\"/action_page\">";
  FORM_PAGE_TOP += "Name: &emsp; &emsp; &emsp; &nbsp;";
  FORM_PAGE_TOP += "<input type=\"text\" name=\"name\">";
  FORM_PAGE_TOP += "<br><br>";

  return FORM_PAGE_TOP;
}

String get_hmtl_down() {
    String FORM_PAGE_DOWN = "<input type=\"submit\" value=\"Submit\">";
    FORM_PAGE_DOWN += "</form><br><br> <hr>";
    FORM_PAGE_DOWN += "<form action=\"/stop_webserver\">";
    FORM_PAGE_DOWN += "<input type=\"submit\" value=\"Start Sniffing\">";   
    FORM_PAGE_DOWN += "</center></body></html>";
    return FORM_PAGE_DOWN;
}