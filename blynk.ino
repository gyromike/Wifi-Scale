BLYNK_WRITE(V9)
{
  if (param.asInt()) {
    Blynk.virtualWrite(V1, float(readscale()));
    displayweight(readscale());
  }

}

BLYNK_WRITE(V5)
{
  if (param.asInt()) {
    // adding 1 row to table
    String timestamp = currentTime + " " + currentDay + " " + currentMonth + " " + currentDate;
    Blynk.virtualWrite(V20, "add", rowIndex, timestamp, readscale());

    //highlighting latest added row in table
    Blynk.virtualWrite(V20, "pick", rowIndex++);
    Blynk.virtualWrite(indexpin, rowIndex);
  }
}

BLYNK_WRITE(V6) {
  if (param.asInt()) {
    scale.tare();                           // reset the scale to 0
  }
}

BLYNK_WRITE(V7) {
  if (param.asInt()) {
    calibrating = 1;
    startcalibration();
  }
}

BLYNK_WRITE(V8) {
  if (param.asInt()) {
    calibratescale();
    calibrating = 0;
  }
}

BLYNK_CONNECTED() {
  rtc.begin();                              // Synchronize time on connection
  //  bridge_master.setAuthToken(reader_token); // Token of reader
  Blynk.syncVirtual(adjpin, indexpin, knownweightpin);
}

BLYNK_WRITE(adjpin) {
  adjustment =  param.asFloat();
  scale.set_scale(adjustment);
}

BLYNK_WRITE(knownweightpin) {
  knownweight =  param.asInt();
}


BLYNK_WRITE(indexpin) {
  rowIndex =  param.asInt();
}



