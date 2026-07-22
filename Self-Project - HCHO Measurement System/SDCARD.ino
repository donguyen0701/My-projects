void writeSD(float analog, float humid, float temp){
    myFile = SD.open("/log.csv", FILE_APPEND);
    if (myFile) {
        Serial.println(F("Writing log to SD Card"));

        // Write timestamp
        DateTime now = rtc.now();
        myFile.print(now.year(), DEC);
        myFile.print('-');
        myFile.print(now.month(), DEC);
        myFile.print('-');
        myFile.print(now.day(), DEC);
        myFile.print(' ');
        myFile.print(now.hour(), DEC);
        myFile.print(':');
        myFile.print(now.minute(), DEC);
        myFile.print(':');
        myFile.print(now.second(), DEC);
        myFile.print(", ");
        myFile.print(analog);
        myFile.print(", ");
        myFile.print(humid);
        myFile.print(", ");
        myFile.println(temp);
        myFile.close();
        } else {
        Serial.println(F("SD Card: Issue attempting to open the file."));
        SD.begin(PIN_SPI_CS);
    }
}
