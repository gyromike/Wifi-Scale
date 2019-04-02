
//  Global data

#define SDA_PIN     2             // I2C SDA pin
#define SLC_PIN     14            // I2C SCL pin

int knownweight = 33;

// Define our data and clock pins for the scale
#define DOUT 4 // D2 maps to GPIO4
#define CLK 5  // D1 maps to GPIO5

#define BLYNKSIZE 34
#define MODULENAMESIZE 128

#define getweight       V0
#define docalibration   V1
#define weightpin       V2 
#define terminaldisplay V10
#define adjpin V25
#define indexpin V26
#define knownweightpin V27

//define your default values here, if there are different values in config.json, they are overwritten.
// if you are using BLYNK you may not need the mqtt items
char mqtt_server[40] = "your mqtt server";    // <======= this is the default data 
char mqtt_port[6] = "8080";                   // <========= this also
char blynk_token[BLYNKSIZE] = "YOUR_BLYNK_TOKEN";    //<======== and this
char modulename[MODULENAMESIZE] = "Thin K scale";   //<===== this is the name for the OTA updates using the arduino IDE


//flag for saving data
bool shouldSaveConfig = true;
float adjustment = 2280.0;
int   calibrating = 0;

// screen information
#define screenW  128
#define screenH  64
#define displayCenterX  screenW/2
#define displayCenterY  (screenH/2)   

int rowIndex;
int whatclock = 1;

//days and months information
const char*  daystrings[7]  =  {"Sun", "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat"};
const char*   monthstrings[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
int days[7]; 
int today;

String  currentTime;
String  currentDate;
String  currentMonth;
String  currentDay;

