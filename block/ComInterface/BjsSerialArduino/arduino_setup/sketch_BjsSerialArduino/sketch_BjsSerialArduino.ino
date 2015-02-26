// Copyright 2015 MakingBot
// This file is part of BotJs.
//
// BotJs is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// BotJs is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with BotJs.  If not, see <http://www.gnu.org/licenses/>.

#include <NewPing.h>

//! Mail structure
struct mail
{
  byte device;
  byte propid;
  byte mode;
  byte data[4];
  byte end;
};

#define READ  0
#define WRITE 1

// ========================================================================
// => Loop Parameters

//! 
#define DELAY_LOOP   40

// ========================================================================
// => HC_SR04 Parameters
// 29ms should be the shortest delay between pings.

//! Device id on the communication interface
#define HC_SR04_DEVID     1
//! Property id
#define HC_SR04_PROPID    0

//! Arduino pin tied to trigger pin on the ultrasonic sensor.
#define TRIGGER_PIN  12
//! Arduino pin tied to echo pin on the ultrasonic sensor.
#define ECHO_PIN     11
//! Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define MAX_DISTANCE 200

//! Mail
struct mail HcSr04Mail;
//! NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//!
//! Setup function
//!
void setup()
{
  Serial.begin(115200);
  
  HcSr04Mail.device = HC_SR04_DEVID;
  HcSr04Mail.propid = HC_SR04_PROPID;
  HcSr04Mail.mode   = WRITE;
  int i;
  for(i=0 ; i<4 ; i++)
  {
    HcSr04Mail.data[i]= 0;
  }
}

//!
//! Loop function
//!
void loop()
{
  delay(DELAY_LOOP);
  
  
  unsigned int ping_us = sonar.ping();
  
  byte* buf[0];
  
  Serial.write(HcSr04Mail.device);
  
//  Serial.print("Ping: ");
//  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
//  Serial.println("cm");


}


