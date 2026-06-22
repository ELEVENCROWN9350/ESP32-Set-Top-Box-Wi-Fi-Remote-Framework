#include <IRrecv.h>
#include <IRutils.h>

IRrecv irrecv(4);
decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {

    Serial.println(resultToHumanReadableBasic(&results));

    Serial.print("rawlen = ");
    Serial.println(results.rawlen);

    for (uint16_t i = 0; i < results.rawlen; i++) {
      Serial.print(results.rawbuf[i] * kRawTick);
      Serial.print(", ");
    }

    Serial.println();
    Serial.println();

    irrecv.resume();
  }
}