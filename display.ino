
// utility function for digital clock display: prints leading 0
String twoDigits(int digits) {
  if (digits < 10) {
    String i = '0' + String(digits);
    return i;
  }
  else {
    return String(digits);
  }
}


void displayweight(float weight){
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  displayClock();                                                           // display the selected clock to the OLED
  display.setFont(ArialMT_Plain_24);
  display.drawString(displayCenterX, displayCenterY + 4,  String(weight,2));    // outpot the weight to the OLED
  display.display();
}

void timeanddate() {
  String timenow = String(hour()) + ":" + twoDigits(minute()) + ":" + twoDigits(second());
  display.setFont(ArialMT_Plain_10);
  display.drawString(displayCenterX, displayCenterY - 24, timenow + " " + currentDay + " " + currentMonth + " " + currentDate + " " + String( year())); // display time. day, month date and year
}

void timeandday() {
  getCurrentTime();
  display.setFont(ArialMT_Plain_10);
  display.drawString(displayCenterX, displayCenterY - 24, currentDay + " " + currentTime );     // display day and time
}


void timeonly() {
  getCurrentTime();
  display.setFont(ArialMT_Plain_24);
  display.drawString(displayCenterX, displayCenterY - 24, currentTime );                        // display only the time
}


void displayClock() {                                                                       // call the selected display for the clock
  switch (whatclock)
  {
    case 1: { // Item 1
        timeandday();
        break;
      }
    case 2: { // Item 2
        timeanddate();
        break;
      }
    case 3: { // Item 3
        timeonly();
        break;
      }
  }
}

/*
 * setup the OLED
 */
void setupdisplay() {
  display.init();
  display.setI2cAutoInit(true);
}

// get the time and the day
void getCurrentTime() {
  currentTime = String(hour()) + ":" + twoDigits(minute());
  currentMonth = monthstrings[month() - 1];
  currentDate = String(day());
  currentDay = daystrings[weekday() - 1];
}
