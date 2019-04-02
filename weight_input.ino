
void setupscale() {
  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
  scale.begin(DOUT, CLK, 128);
  scale.set_scale(adjustment);                // this value is obtained by calibrating the scale with known weights;
  scale.tare();                           // reset the scale to 0
}

void startcalibration() {
  scale.set_scale();
  scale.tare();
}

void calibratescale() {
  // Place the known weight on  scale
  // Divide the result by known weight.
  adjustment = scale.get_units(20) / knownweight;
  scale.set_scale(adjustment);
  Blynk.virtualWrite(adjpin, adjustment);
}

float readscale() {
  if (scale.wait_ready_timeout(1000)) {
  float weightreading;
  weightreading = scale.get_units(15);
  return weightreading;
  } else return 9999;
}
