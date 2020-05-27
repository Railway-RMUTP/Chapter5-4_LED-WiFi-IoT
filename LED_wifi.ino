
#include <WiFi.h>
const char* ssid     = "vivo123";
const char* password = "123456789";
#define ledPINRed 2
#define ledPINGrn 16
WiFiServer server(80);
void setup()
{
    Serial.begin(115200);
    pinMode(ledPINRed, OUTPUT);      // set the LED pin mode
    pinMode(ledPINGrn, OUTPUT);      // set the LED pin mode
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();
}
int value = 0;
void loop(){
 WiFiClient client = server.available();   // listen for incoming clients
  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<html>");
            client.println("<head>");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
            client.println("<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css\">");
            client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js\"></script>");
            client.println("<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/js/bootstrap.min.js\"></script>");
            client.println("</head>");
            client.println("<body>");

          
            client.println();
            // the content of the HTTP response follows the header:
            
            client.print("<div class=\"container\">");
            client.print("<div class=\"row text-center\">");
            client.print("<div class=\"col-12\">");
            client.print("<a class=\"btn btn-lg btn-danger\" href=\"/HR\" style=\"margin-top:0.5em;margin-right:0.5em;padding-right:2em;margin-left:0.5em;padding-left: 2em;\">on</a>");
            client.print("<a class=\"btn btn-lg btn-danger\" href=\"/LR\" style=\"margin-top:0.5em;margin-right:0.5em;padding-right:2em;margin-left:0.5em;padding-left: 2em;\">off</a>");
            client.print("</div>");
                
            client.print("<div class=\"col-12\">");
            client.print("<a class=\"btn btn-lg btn-success\" href=\"/HG\" style=\"margin-top:0.5em;margin-right:0.5em;padding-right:2em;margin-left:0.5em;padding-left: 2em;\">on</a>");
            client.print("<a class=\"btn btn-lg btn-success\" href=\"/LG\" style=\"margin-top:0.5em;margin-right:0.5em;padding-right:2em;margin-left:0.5em;padding-left: 2em;\">off</a>"); 
            client.print("</div>");
            client.print("</div>");
            client.print("</div>");
  
            client.print("</body>");
            client.print("</html>");

            
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
     

         // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /HR")) {
          digitalWrite(ledPINRed, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /LR")) {
          digitalWrite(ledPINRed, LOW);                // GET /L turns the LED off
        }

         // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /HG")) {
          digitalWrite(ledPINGrn, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /LG")) {
          digitalWrite(ledPINGrn, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
