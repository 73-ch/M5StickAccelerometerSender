#ifndef _UDPSENDER_H
#define _UDPSENDER_H

class UDPSender {
 private:
  int status = WL_IDLE_STATUS;
  WiFiUDP Udp;

 public:
  UDPSender(std::string ssid, std::string pass);
  ~UDPSender();

  template <class T>
  void send(std::string path, T data);
};

UDPSender::UDPSender(std::string ssid, std::string pass, const int port) {
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid.c_str(), pass.c_str());

    // wait 10 seconds for connection:
    delay(10000);
  }

  Udp.begin(port);
}

UDPSender::~UDPSender() {}

template <class T>
void UDPSender::send(std::string path, T data) {
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
}

#endif