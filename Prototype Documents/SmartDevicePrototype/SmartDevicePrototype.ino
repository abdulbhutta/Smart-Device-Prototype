#include "DHT.h"

//Define sensor type and what pin its connected to
#define DHTTYPE DHT11
#define DHTPIN 2
//Delay is measured in ms, 5000 = 5 seconds
#define SamplingRate = 5000  

//Initialize sensor
DHT dht (DHTPIN, DHTTYPE)

//Initialize variables
double temperature=0;
double humidity=0;
int image = 1;

void setup() {
  //Start the usb port and DHT11 sensor
  Serial.begin(115200)
  dht.begin();

  //initialize Camera and SD Card
  esp_err_t err = esp_camera_init(&config);
  SD_MMC.begin();

   //Create new file data.txt to save the captured data  
   File data = SD.open("/data.txt");
   writeFile(data, "/data.txt", "Reading Temperature, Humidity, and image every 5 seconds!\n\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(SamplingRate); //Wait for 5 seconds
  readSensor();
  capture();
  saveData();
}

void readSensor() {
  //Read the temperature and humidity
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
}

void capture(){
  //If SD card is not full then capture the image and save it!
  if (SDCard != FULL){
    //Take picture with camera
    camera *picture = NULL;
    picture = esp_camera_fb_get();   

    //save picture to SD Card
    String Path = "/Picture" + image + ".jpg"; //Path to save the image in picture folder

    //Save the image to SD Card
    fs::FS &fs = SD_MMC; 
    File image = fs.open(path.c_str(), FILE_WRITE);

    //Increment the image counter (next image)
    image++;
  }

  else {
    //If SD Card is full then exit the application!
    Serial.println("SD CARD FULL ... EXITING!");
    exit();
  }
}

void saveData() {
   output = String(temperature) + String(humidity) + String(image);
   //add the current data to the file
   appendFile(data, "/data.txt", output.toString());
}
