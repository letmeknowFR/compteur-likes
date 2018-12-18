/*********************************************************************\
 *                                                                   *
 *                         LIKE_COUNTER                              *
 *                                                                   *
 *  Get the fan count of an Facebook, Twitter, Instagram pages.      *
 *                                                                   *
 *  https://developers.facebook.com/docs/graph-api/reference/page    *
 *  https://www.instagram.com/developer                              *
 *                                                                   *
 *  By Benjamin Amory 18/12/2018                                     *
 \********************************************************************/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <string.h>
#include <ArduinoJson.h>
#include <HT1632.h>
#include <font_5x4.h>
#include <font_8x5.h>
#include <images.h>

/****************************************** SETUP ****************************************/
char ssid[] = "";       // your network SSID (name)
char password[] = "";  // your network key (password)

String FACEBOOK_ACCESS_TOKEN = "";
String FACEBOOK_PAGE_ID = "";
String TWITTER_PAGE_ID = "";
String INSTA_ACCESS_TOKEN = "";

char *HOST_FACEBOOK = "graph.facebook.com";
char *HOST_TWITTER = "cdn.syndication.twimg.com";
char HOST_INSTA[] = "api.instagram.com";

const char *likes;
const char *followers_twitter;
const char *followers_insta;
void facebook_get_likes();
void insta_get_followers();
void twitter_get_followers();
void print_twitter(int pos);
void print_facebook(int pos);
void print_insta(int pos);

typedef struct display_funct {
  void (*get)(void);
  void (*display)(int);
} display_funct;

display_funct function[3] = {{facebook_get_likes, print_facebook}, {twitter_get_followers, print_twitter}, {insta_get_followers, print_insta}};

WiFiClientSecure client;
DynamicJsonBuffer jsonBuffer(512);

void setup() {
  Serial.begin(115200);
  HT1632.begin(D2, D3, D4);
  HT1632.clear();
  HT1632.drawText(".", 0, 0, FONT_8X5, FONT_8X5_END, FONT_8X5_HEIGHT, 1);
  HT1632.render();
  while (wifi_connect() != true);
  facebook_get_likes();
  twitter_get_followers();
  insta_get_followers();
}

/************************************ LOOP FUNCTION *************************************/
void loop() {
  int pos = 0;
  if (WiFi.status() == WL_CONNECTED) {
    for (int i = 0; i < 3; i++) {
      HT1632.clear();
      function[i].display(pos);
      HT1632.render();
      function[i].get();
      delay(2000);
      HT1632.clear();
      function[i].display(pos);
      HT1632.render();
      delay(2000);
      while (pos < 9) {
        yield();
        HT1632.clear();
        if (i + 1 == 3)
          function[0].display(pos - 9);
        else
          function[i + 1].display(pos - 9);
        function[i].display(pos);
        HT1632.render();
        delay(100);
        pos++;
      }
      pos = 0;
    }
  } else {
    HT1632.drawText("no wifi", 0, 0, FONT_8X5, FONT_8X5_END, FONT_8X5_HEIGHT, 1);
    delay(2000);
    wifi_connect();
  }
}

/*********************************** DISPLAY FUNCTION ***********************************/
void print_twitter(int pos) {
  HT1632.drawImage(IMG_TWITTER, IMG_FB_WIDTH,  IMG_FB_HEIGHT, 0, 0);
  HT1632.drawText(followers_twitter, 11, pos, FONT_8X5, FONT_8X5_END, FONT_8X5_HEIGHT, 1);
  Serial.println(followers_twitter);
}

void print_insta(int pos) {
  HT1632.drawImage(IMG_INSTA, IMG_FB_WIDTH,  IMG_FB_HEIGHT, 0, 0);
  HT1632.drawText(followers_insta, 13, pos, FONT_8X5, FONT_8X5_END, FONT_8X5_HEIGHT, 1);
  Serial.println(followers_insta);
}

void print_facebook(int pos) {
  HT1632.drawImage(IMG_FB2, IMG_FB_WIDTH,  IMG_FB_HEIGHT, 0, 0);
  HT1632.drawText(likes, 13, pos, FONT_8X5, FONT_8X5_END, FONT_8X5_HEIGHT, 1);
  Serial.println(likes);
}
/******************************************************************************************/

/*********************************** INSTAGRAM FUNCTION ***********************************/
void insta_get_followers() {
  String line;
  char buff[550];
  int i = 1, y = 1, pos = 0;
  if (client.connect(HOST_INSTA, 443)) {
    Serial.println(String("Connected to ") + HOST_INSTA);
    client.print("GET ");
    client.print("/v1/users/self/?access_token=");
    client.print(INSTA_ACCESS_TOKEN);
    client.println(" HTTP/1.1");
    client.println(String("Host: ") + HOST_INSTA);
    client.println("User-Agent: arduino/1.0.0");
    client.println();
    while(client.connected() && !client.available());
    while (client.available()) {
      line = client.readStringUntil('\r');
      if (line[0] == '\n' && line[1] == '{') {
        buff[0] = '{';
        while (pos < 3) {
          if (line[i] == '{')
            pos++;
          i++;
        }
        while (line[i] != '}') {
          if (line[i] != ' ') {
            buff[y] = line[i];
            y++;
          }
          i++;
        }
      }
    }
    buff[y] = '}';
    buff[y + 1] = '\0';
    client.stop();
    Serial.println(buff);
    JsonObject& root = jsonBuffer.parseObject(buff);
    if (!root.success())
      Serial.println("!!!!Json failed!!!!");
    else
      followers_insta = strdup(root["followed_by"]);
    Serial.println(followers_insta);
  } else {
    Serial.println(String("Connection to ") + HOST_INSTA + String(" failed..."));
  }
}
/****************************************************************************************/

/*********************************** TWITTER FUNCTION ***********************************/
void twitter_get_followers() {
  String line;
  char buff[400];
  int i = 0, y = 2;
  if (client.connect(HOST_TWITTER, 443)) {
    Serial.println("Connected to cdn.syndication.twimg.com");
    client.print("GET ");
    client.print("/widgets/followbutton/info.json?screen_names=");
    client.print(TWITTER_PAGE_ID);
    client.println(" HTTP/1.1");
    client.println("Host: cdn.syndication.twimg.com");
    client.println("User-Agent: arduino/1.0.0");
    client.println();
    while(client.connected() && !client.available());
      while (client.available()) {
        line = client.readStringUntil('\r');
        if (line[0] == '\n' && line[1] == '[')
          while (line[y] != ']') {
            buff[i] = line[y];
            y++;
            i++;
          }
      }
    buff[i] = '\0';
    client.stop();
    Serial.println(buff);
    JsonObject& root = jsonBuffer.parseObject(buff);
    if (!root.success())
      Serial.println("!!!!Json failed!!!!");
    else
      followers_twitter = strdup(root["followers_count"]);
    Serial.println(followers_twitter);
  } else {
    Serial.println("Connection to graph.facebook.com failed...");
  }
}
/*****************************************************************************************/

/*********************************** FACEBOOK FUNCTION ***********************************/
void facebook_get_likes() {
  String line;
  char buff[400];
  int i = 1, y = 0;
  if (client.connect(HOST_FACEBOOK, 443)) {
    Serial.println("Connected to graph.facebook.com");
    client.print("GET /v3.2/");
    client.print(FACEBOOK_PAGE_ID);
    client.print("?fields=access_token%2Cfan_count&access_token=");
    client.print(FACEBOOK_ACCESS_TOKEN);
    client.println(" HTTP/1.1");
    client.println("Host: graph.facebook.com");
    client.println("User-Agent: arduino/1.0.0");
    client.println();
    while(client.connected() && !client.available());
      while (client.available()) {
        line = client.readStringUntil('\r');
        if (line[1] == '{')
          while (line[i - 1] != '}') {
            buff[y] = line[i];
            y++;
            i++;
          }
      }
    buff[y] = '\0';
    client.stop();
    Serial.println(buff);
    JsonObject& root = jsonBuffer.parseObject(buff);
    if (!root.success())
      Serial.println("!!!!Json failed!!!!");
    else
      likes = strdup(root["fan_count"]);
    Serial.println(likes);
  } else {
    Serial.println("Connection to graph.facebook.com failed...");
  }
}
/****************************************************************************************/

/************************************* WIFI FUNCTION ************************************/
bool wifi_connect() {
  int retry = 0;
  int pos = 0;
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    if (retry == 20) {
      HT1632.clear();
      HT1632.drawText("no wifi", 0, 0, FONT_8X5, FONT_8X5_END, FONT_8X5_HEIGHT, 1);
      HT1632.render();
      delay(2000);
      return (false);
    }
    if (pos == 32)
      pos = 0;
    HT1632.drawText(".", pos, 0, FONT_8X5, FONT_8X5_END, FONT_8X5_HEIGHT, 1);
    HT1632.render();
    Serial.print(".");
    delay(500);
    retry++;
    pos++;
  }
  Serial.println("WiFi connected");
  IPAddress ip = WiFi.localIP();
  Serial.println("IP address: ");
  Serial.println(ip);
  return (true);
}
/****************************************************************************************/
