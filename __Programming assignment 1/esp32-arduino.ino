// Include libraries 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHTesp.h>
#include <WiFi.h>

// Define OLED parameters
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// Pin Configurations for Components
#define BUZZER 5
#define LED_1 15 // Alert the medicine time (RED LED)
#define LED_2 2 // Warn the temperature & humidity (YELLOW LED)
#define PB_CANCEL 34 
#define PB_OK 32 
#define PB_UP 35
#define PB_DOWN 33
#define DHTPIN 12

// Time parameters
#define NTP_SERVER     "pool.ntp.org"
// Time initializing to +5.30
#define UTC_OFFSET     19800  // (5 hours * 3600 seconds/hour) + (30 minutes * 60 seconds/minute)
#define UTC_OFFSET_DST 0      // Sri Lanka does not have the DST effect 

// Delay times
#define MESSAGE_DELAY 1000
#define DELAY 200

// Display & sensor parameters
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHTesp dhtSensor;

// Time parameters
int hours = 0;
int minutes = 0;

// UTC Offset parameter in seconds
long utc_offset_sec = 19800 ;

// Alarm parameters
struct alarm {
  int hours;
  int minutes;
  bool triggered;
};

bool alarm_enabled = false;
int n_alarms = 3;

struct alarm alarms[] = {
  {0, 0, true},
  {0, 0, true},
  {0, 0, true}
};

// Default temperature and humidity parameters 
int temp_high = 32;
int temp_low = 26;
int humidity_high = 80;
int humidity_low = 60;

// Buzzer tone parameters (Let's play the pirates of the caribbean!)
const float songSpeed = 1.0;

// Defining frequency of each music note
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_G5 784
#define NOTE_A5 880
#define NOTE_B5 988

// Music notes of the song, 0 is a rest/pulse
int notes[] = {
    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_D5, NOTE_E5, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
    NOTE_C5, NOTE_A4, NOTE_B4, 0,

    NOTE_A4, NOTE_A4,
    // Repeat of first part
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_D5, NOTE_E5, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
    NOTE_C5, NOTE_A4, NOTE_B4, 0,
    // End of Repeat

    NOTE_E5, 0, 0, NOTE_F5, 0, 0,
    NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
    NOTE_D5, 0, 0, NOTE_C5, 0, 0,
    NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

    NOTE_E5, 0, 0, NOTE_F5, 0, 0,
    NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
    NOTE_D5, 0, 0, NOTE_C5, 0, 0,
    NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4};


// Durations (in ms) of each music note of the song
int durations[] = {
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 125, 250, 125,

    125, 125, 250, 125, 125,
    250, 125, 250, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 375,

    250, 125,
    // Repeat of First Part
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 125, 250, 125,

    125, 125, 250, 125, 125,
    250, 125, 250, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 375,
    // End of Repeat

    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 125, 125, 125, 375,
    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 500,

    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 125, 125, 125, 375,
    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 500};


// Menu parameters
int current_mode = 0;
int max_modes = 6;
String modes[] = {
  "1 - Set Timezone ",
  "2 - Set Alarm 1 ",
  "3 - Set Alarm 2 ",
  "4 - Set Alarm 3 ",   
  "5 - Disable Alarms ", 
  "6 - Temperature and Humidity boundaries "  // My additional parameter to change humidity and temp: boundaries
};


void setup() {
  Serial.begin(9600);

  // Pin configurations
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(PB_CANCEL, INPUT);
  pinMode(PB_OK, INPUT);
  pinMode(PB_UP, INPUT);
  pinMode(PB_DOWN, INPUT);

  // Initializing Temp & Humidity sensor
  dhtSensor.setup(DHTPIN, DHTesp::DHT22);

  // Initializing the OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { 
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }

  display.display();
  delay(MESSAGE_DELAY);
  print_line("Welcome to Medibox!", 10, 20, 2, true);
  delay(MESSAGE_DELAY);

  // Initializing the WIFI
  WiFi.begin("Wokwi-GUEST", "", 6);          // Wokwi-GUEST: The SSID (Service Set Identifier)
  while (WiFi.status() != WL_CONNECTED) {
    delay(DELAY);
    print_line("Connecting to WIFI", 0, 0, 2, true);
  }

  print_line("Connected to WIFI", 0, 0, 2, true);

  // Configuring Initial Time using WIFI network for +5.30
  configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);
}

void loop() {
  if (digitalRead(PB_OK) == LOW) {
    delay(DELAY);
    go_to_menu();
  }

  update_time();
  check_alarm();
  check_temperature_humidity();
}

/*
Function to print a line on the OLED display
*/
void print_line(String text, int column, int row, int text_size, bool clear) {
  if (clear) {
    display.clearDisplay();
  }
  display.setTextSize(text_size);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(column, row);
  display.println(text);

  display.display();
}

/*
Function to update the current time on the OLED display
*/
void update_time() {
  struct tm timeinfo;
  getLocalTime(&timeinfo);

  char time_hour[3];
  char time_minute[3];
  char full_time[9];

  strftime(time_hour, 3, "%H", &timeinfo);
  strftime(time_minute, 3, "%M", &timeinfo);
  strftime(full_time, 9, "%T", &timeinfo);

  print_line(String(full_time), 15, 0, 2, true);

  hours = atoi(time_hour);                 // atoi : str-->int 
  minutes = atoi(time_minute);
}

/*
Function to check if any alarm 
*/
void check_alarm() {
  if (!alarm_enabled) {
    return;
  }

  for (int i = 0; i < n_alarms; i++) {
    if (!alarms[i].triggered && alarms[i].hours == hours && alarms[i].minutes == minutes) {
      ring_alarm();
      alarms[i].triggered = true;
    }
  }
}

/*
Function to ring the alarm with music and LED
*/
void ring_alarm() {
  print_line("Medicine Time!", 0, 0, 2, true);

  digitalWrite(LED_1, HIGH);

  bool canceled = false;   // This helps to stop alarm imediately after pushing CANCEL (not run the full tone) 

  while (!canceled && digitalRead(PB_CANCEL) == HIGH) {
    const int totalNotes = sizeof(notes) / sizeof(int);
    for (int i = 0; i < totalNotes; i++) {
      if (digitalRead(PB_CANCEL) == LOW) {
        delay(DELAY);
        canceled = true;
        break;
      }

      const int currentNote = notes[i];
      float wait = durations[i] / songSpeed;
      
      if (currentNote != 0)
      {
        tone(BUZZER, notes[i], wait); 
      }
      else
      {
        noTone(BUZZER);
      }
      
      delay(wait);
    }
  }

  digitalWrite(LED_1, LOW);
  display.clearDisplay();
}

/*
Function to check temperature and humidity levels and provide warnings
*/
void check_temperature_humidity() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();

  bool warning = false;
  if (data.temperature > temp_high) {
    warning = true;
    print_line("Temperature HIGH", 0, 40, 1, false);
  }

  else if (data.temperature < temp_low) {
    warning = true;
    print_line("Temperature LOW", 0, 40, 1, false);
  }

  if (data.humidity > humidity_high) {
    warning = true;
    print_line("Humidity HIGH", 0, 50, 1, false);
  }

  else if (data.humidity < humidity_low) {
    warning = true;
    print_line("Humidity LOW", 0, 50, 1, false);
  }

  // Additional feature for YELLOW LED alert
  if (warning) {
    digitalWrite(LED_2, HIGH);
    delay(DELAY);
    digitalWrite(LED_2, LOW);
  }
}

/*
Function to navigate the user to different modes using the buttons
*/ 
void go_to_menu() {
  while (digitalRead(PB_CANCEL) == HIGH) {
    print_line(modes[current_mode], 0, 0, 2, true);

    int pressed = wait_for_button_press();

    if (pressed == PB_UP) {
      delay(DELAY);
      current_mode += 1;
      current_mode = current_mode % max_modes;   // To limit 0 to 5
    }

    else if (pressed == PB_DOWN) {
      delay(DELAY);
      current_mode -= 1;
      if (current_mode < 0) {
        current_mode = max_modes - 1;          // -1 --> 5
      }
    }

    else if (pressed == PB_OK) {
      delay(DELAY);
      run_mode(current_mode);
    }

    else if (pressed == PB_CANCEL) {
      delay(DELAY);
      break;
    }
  }
}

/*
Function to wait for a button press and return the pressed button
*/
int wait_for_button_press() {
  while (true) {         //Looping till one push button is pressed 
    if (digitalRead(PB_UP) == LOW) {
      delay(DELAY);
      return PB_UP;
    }

    else if (digitalRead(PB_DOWN) == LOW) {
      delay(DELAY);
      return PB_DOWN;
    }

    else if (digitalRead(PB_OK) == LOW) {
      delay(DELAY);
      return PB_OK;
    }

    else if (digitalRead(PB_CANCEL) == LOW) {
      delay(DELAY);
      return PB_CANCEL;
    }
  }
}

/*
Function to execute different modes based on user input
*/
void run_mode(int mode) {
  if (mode == 0) {
    set_timezone_and_config();
  }

  else if (mode == 1 || mode == 2 || mode == 3) {
    set_alarm(mode - 1);
  }

  else if (mode == 4) {
    disable_alarms();
  }

  else if (mode == 5) {
    set_temperature_humidity_levels();
  }
}

/*
Function to read a value with boundaries and update it based on button presses
*/
int read_value(String text, int init_value, int max_value, int min_value) {
  int temp_value = init_value;
  while (true) {
    print_line(text + String(temp_value), 0, 0, 2, true);

    int pressed = wait_for_button_press();

    if (pressed == PB_UP) {
      delay(DELAY);
      temp_value += 1;
      if (temp_value > max_value) {
        temp_value = min_value;
      }
    }

    else if (pressed == PB_DOWN) {
      delay(DELAY);
      temp_value -= 1;
      if (temp_value < min_value) {
        temp_value = max_value;
      }
    }

    else if (pressed == PB_OK) {
      delay(DELAY);
      return temp_value;
    }

    else if (pressed == PB_CANCEL) {
      delay(DELAY);
      break;
    }
  }

  return init_value;    // If CANCEL is pressed
}

/* 
Function to set the timezone and configuration 
*/
void set_timezone_and_config() {
  int current_offset_hours = utc_offset_sec / 3600;
  int current_offset_minutes = (utc_offset_sec % 3600) / 60;

  int offset_hours = read_value("Enter offset hours: ", current_offset_hours, 14, -12);
  int offset_minutes = read_value("Enter offset minutes: ", current_offset_minutes, 59, 0);

  utc_offset_sec = offset_hours * 3600 + offset_minutes * 60;
  configTime(utc_offset_sec, UTC_OFFSET_DST, NTP_SERVER);
  print_line("Timezone set to " + String(offset_hours) + ":" + String(offset_minutes), 0, 0, 2, true);
  delay(MESSAGE_DELAY);
}

/* 
Function to set the alarm time and enable the alarm 
*/
void set_alarm(int alarm) {
  alarms[alarm].hours = read_value("Enter hour: ", alarms[alarm].hours, 23, 0);
  alarms[alarm].minutes = read_value("Enter minute: ", alarms[alarm].minutes, 59, 0);
  alarms[alarm].triggered = false;   // This will enable the re-using of the same alarm 

  if (!alarm_enabled) {
    alarm_enabled = true;
  }

  print_line("Alarm " + String(alarm) + " is set to " + String(alarms[alarm].hours) + ":" + String(alarms[alarm].minutes), 0, 0, 2, true);
  delay(MESSAGE_DELAY);
}

/* 
Function to disable all alarms 
*/
void disable_alarms() {
  alarm_enabled = false;
  
  for (int i = 0; i < n_alarms; i++) {
    alarms[i] = {0, 0, true};
  }
  print_line("Alarms are disabled", 0, 0, 2, true);
  delay(MESSAGE_DELAY);
}

/* 
Function to set temperature and humidity levels 
*/
void set_temperature_humidity_levels() {
  temp_high = read_value("Enter High Temperature Level: ", 32, 50, 0);
  temp_low = read_value("Enter Low Temperature Level: ", 26, 50, 0);
  humidity_high = read_value("Enter High Humidity Level: ", 80, 100, 0);
  humidity_low = read_value("Enter Low Humidity Level: ", 60, 100, 0);

  print_line("Levels Set: Temp High=" + String(temp_high) + " Temp Low=" + String(temp_low) + " Humidity High=" + String(humidity_high) + " Humidity Low=" + String(humidity_low), 0, 0, 2, true);
  delay(MESSAGE_DELAY);
}