/*
  Blink
  Continuously turns on an LED for one second and then off for one second.
  This example is to be used with the chipKIT Uno32, Max32, Cerebot MX3ck, Cerebot MX4ck, and Cerebot MX7ck.
  This example code is in the public domain.
*/

#include <SPI.h>
#include <SD.h>
#include "TouchScreen.h"
#include <DisplayCore.h>
#include <DSPI.h>

// Declare Variables
byte RXByte;
int  cnt  = 0;
int  cnt2  = 0;
byte testbyte = 0;
int  checkcnt = 0;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(230400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  /*
    Serial.println("Welcome to Bonneville Power Administration.");
    Serial.println("This window will display data incoming through a fiber C37.94 interface to the FPGA.");
    Serial.println(" ");
    //Serial.println("        Header                                     Operation Codes                                                                                                             FRAME DATA  ");
    //Serial.println("=======================   =============================================================== ==================================================================================================================================================================================");
  */
  // Displaying the BPA Logo

  Serial.println(":######+               +#######.             '###    '#+            ####    +#;            ######.            ###+    ;#;           '###            +###               `###                ######`    ");
  Serial.println(".### ###,            ###.    `###             #####`  #:            .#####  :#.            ###.                ###+  `#;            ;###            '##+                ###                ###,       ");
  Serial.println(".######,             ###`     ###:            #+####  #:            .#;#### :#.            #####+              ,###  '#`            ;###            '##+                ###                #####+     ");
  Serial.println(".#######,           `###`     ###;            #+.###+ #:            .#:;###':#.            #####+               ###  ##             ;###            '##+                ###                #####+     ");
  Serial.println(".###  ###            ###.     ###:            #+ '###,#:            `#: +###;#.            ###. ,               +##+`#'             ;###            '##+                ###                ###, ,     ");
  Serial.println(":#######`              ########              .##    '##:            ;#+    +##.            #######,               ###`              '###            '######:           `#######            #######,   ");

  /*
    Serial.println(" ");
    Serial.println(" ");
    Serial.println(" ");
    Serial.println("    +###:     ####+     ## ;#  #:    ###`    ####.           ##:      ####'     ,#+  ##     ##    ,#'  #`    ##    '###    '####    +###;      :##      ####;    #'     #####     +#` `#          ");
    Serial.println("    +# ##    ##  '#:    ## :#; #     #'      ## ##           ###      ## ;#,    :## ;##     ##     ##, #     ##    ##        ##     +# ##      +##     ` ## `    #:    ##  ,#+    '## `+          ");
    Serial.println("    +# ##   .#'  `#+    ,#.+## #     #+'     ##`#;          ,++#      ##  ##    '+#.###     ##     ### #     ##    ###:      #+     +# #'      #,#:      ##      #:    #+   ##    '###`+          ");
    Serial.println("    +#''    .#'   ##    `#;#'#.'     #+'     ####           +;'#;     ##  ##    #.###'#     ##     +,###     ##     +##:     ##     +###      ,+:##      ##      #:    ##   ##    '.##;+          ");
    Serial.println("    +#       ##  `#;     ##+`##`     #'      ##'#.          #::##     ## .#'    #`+##:#.    ##     + +##     ##       ##     ##     +#;#:     #;:+#      ##      #:    ##   ##    '. ##+          ");
    Serial.println("    +#       ;##,##      ;#, ##      ##:+    ## ##         .+  +#     ##'##     # ,#..#:    ##     +  ##     ##    #:'#;     #+     +# ##     #  ,#'     +#      #;    `##.##`    '. .#+          ");
  */

  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");

  cnt  = 0;
  cnt2 = 0;
}

unsigned int c; // c accumulates the total bits set in v
unsigned int v; // count the number of bits set in v

void loop()
{


  if (Serial.available())
  {
    testbyte = Serial.read();


    cnt = cnt + 1;


    if (cnt >= 32)
    {
      cnt2 = cnt2 + 1;
      Serial.println();
      Serial.println();
      Serial.print("Frame #");
      Serial.print(cnt2, DEC);
      Serial.print(":");
      cnt = 0;
    }

    // Determine number of 0s to pad with
    if (testbyte == 0)
    {
      Serial.print("0000000");
    }

    else if (testbyte < 2)
    {
      Serial.print("0000000");
    }

    else if (testbyte < 4)
    {
      Serial.print("000000");
    }

    else if (testbyte < 8)
    {
      Serial.print("00000");
    }

    else if (testbyte < 16)
    {
      Serial.print("0000");
    }

    else if (testbyte < 32)
    {
      Serial.print("000");
    }

    else if (testbyte < 64)
    {
      Serial.print("00");
    }

    else if (testbyte < 128)
    {
      Serial.print("0");
    }

    Serial.print(testbyte, BIN);


    testbyte = 0;
  }
}

#include <Adafruit_GFX.h>    // Core graphics library
//#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>
#include "TouchScreen.h"

// These are the four touchscreen analog pins
#define YP A4  // must be an analog pin, use "An" notation!
#define XM A5  // must be an analog pin, use "An" notation!
#define YM 6   // can be a digital pin
#define XP 7   // can be a digital pin

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 110
#define TS_MINY 80
#define TS_MAXX 900
#define TS_MAXY 940

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// The display uses hardware SPI, plus #9 & #10
#define TFT_RST -1  // dont use a reset pin, tie to arduino RST if you like
#define TFT_DC 9
#define TFT_CS 10

Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define SD_CS 4

//--------------- STATE DECLARATIONS --------------
#define Idle            0
#define Menu1           1
#define SendMirrorBits  2
#define StartRecording  3
#define WaitToRecord    4
#define DisplayStatus   5
#define SendData        6
//-------------- MAIN STATE VARIABLE -------------
// Jaguar control interface will be implemented
// as a software state machine. It will begin in
// an idle state.
//------------------------------------------------
byte STATE = Idle;

void setup()
{
  Serial.begin(250000);


  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS))
  {
    Serial.println("failed!");
  }
  Serial.println("OK!");

  tft.begin(HX8357D);
  tft.fillScreen(HX8357_BLACK);
  tft.setRotation(0);

  bmpDraw("JD.bmp", 0, 0);

  // Initial state set to Idle
  STATE = Idle;

}

// FPGA Variables
#define FPGAMode 8     // FPGA mode set will be digital pin 8  (0 = fiber optics analysis, 1 = mirrored bit control)

void loop()
{

  byte FPGAByte = 0;     // byte of data coming in from the fpga
  byte FPGASendByte = 0;     // byte of data to send to the FPGA indicating mirror bit value desired (or other data)
  byte cnt  = 0;
  byte cnt2 = 0;
  //-------
  // IDLE
  //-------

  while (STATE == Idle)
  {
    // Retrieve a point
    TSPoint p = ts.getPoint();


    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z < MINPRESSURE || p.z > MAXPRESSURE)
    {
      return;
    }


    // Scale from ~0->1000 to tft.width using the calibration #'s
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    // If a spot greater than p.x 10 was touched,
    // clear and proceed to menu

    // If anywhere was pressed to start...
    if (p.x > 10)
    {
      tft.setRotation(1);
      tft.fillScreen(HX8357_BLACK);
      tft.setCursor(0, 0);
      tft.setTextColor(HX8357_WHITE);
      tft.setTextSize(3);
      tft.println("     SELECT OPERATION ");
      tft.println("");
      tft.println("");
      tft.println("");
      tft.println("");
      tft.setTextSize(2);
      tft.setTextColor(HX8357_GREEN);
      tft.println(" ---------- ------------- ------------");
      tft.println(" | View   | | View      | | Start    |");
      tft.println(" | Payload| | Trip&Line | | Transfer |");
      tft.println(" | Data   | | Status    | | Trip     |");
      tft.println(" ---------- ------------- ------------");

      STATE = Menu1;
    }
    else
    {
      //STATE = STATE;
      return;
    }
  }

  //-------
  // MENU 1
  //-------
  while (STATE == Menu1)
  {


    // Retrieve a point
    TSPoint p = ts.getPoint();


    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z < MINPRESSURE || p.z > MAXPRESSURE)
    {
      return;
    }

    // Scale from ~0->1000 to tft.width using the calibration #'s
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, tft.height());    // Because of set rotation, the max value of p.y is now 300



    if (p.x > 10)
    {


      if (p.y > 210)
      {
        // tft.setRotation(1);
        tft.fillScreen(HX8357_BLACK);
        tft.setCursor(0, 0);
        tft.setTextSize(3);
        tft.setTextColor(HX8357_YELLOW);
        tft.println(" CURRENT TIMESLOT 1 DATA ");
        tft.setTextSize(2);
        tft.println("");

        STATE = SendMirrorBits;
        break;
      }
      else if (p.y <= 210 && p.y > 110)
      {
        tft.setRotation(1);
        tft.fillScreen(HX8357_BLACK);
        tft.setCursor(0, 0);
        tft.setTextSize(3);
        tft.println("  DATA RECORDING STARTED ");

        digitalWrite(FPGAMode, LOW);              // set fpga mode to fiber optic comm
        STATE = StartRecording;
        break;
      }
      else if (p.y <= 110)
      {
        //        tft.println(" To observe data, connect to Jaguar's");
        //        tft.println(" front RS232 or USB port and setup");
        //        tft.println(" a serial terminal. "); 
        //        tft.println(" ");
        //        tft.println(" Set data bits to 8 ");
        //        tft.println(" Set parity to 0 ");
        //        tft.println(" Set stop bits to 1");
        //        tft.setTextColor(HX8357_CYAN);
        //        tft.println(" Set baud rate to 250000");
        //        tft.setTextColor(HX8357_WHITE);
        //        tft.println(" The data stored in the Jaguar's ");
        //        tft.println(" data buffer will be displayed, ");
        //        tft.println(" as well as an IRIG-B timestamp. ");

        tft.setRotation(1);
        tft.fillScreen(HX8357_BLACK);
        tft.setCursor(0, 0);
        tft.setTextColor(HX8357_WHITE);
        tft.setTextSize(4);
        tft.println(" AWAITING TRANSFER TRIP ");
        tft.setTextSize(2);
        tft.println("under construction* ");
        tft.println("press anywhere to return to menu.");

        STATE = WaitToRecord;
        break;
      }
      else
      {
        STATE = STATE;
        return;
      }
    }
    else
    {
      STATE = STATE;
      return;
    }
  }

  //---------------
  // DATA DUMP TO SCREEN
  //---------------
  while (STATE == SendMirrorBits)
  {

    // If the actions in this state exceed 48, wait for touch, then clear screen
    if (cnt >= 48)
    {

      // Retrieve a point
      TSPoint p = ts.getPoint();

          // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z < MINPRESSURE || p.z > MAXPRESSURE)
    {
      return;
    }


      // Scale from ~0->1000 to tft.width using the calibration #'s
      p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
      p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

      // Check if back button is pressed
      if (p.y < 100 && p.x < 360 && p.x < 100)
      {
        STATE = Idle;
        // Send the selected mirror bit data to the FPGA
        // Send 0s to indicate that it should now deenergize all mirrored bits

        FPGASendByte = 0x00;
        return;
      }

      // If anywhere else was pressed, clear and repeat
      else if (p.x > 10)
      {
        tft.fillScreen(HX8357_BLACK);
        tft.setCursor(0, 0);
        tft.setTextSize(3);
        tft.setTextColor(HX8357_WHITE);
        tft.println(" CURRENT TIMESLOT 1 DATA ");
        tft.setTextColor(HX8357_YELLOW);
        tft.setTextSize(2);
        tft.println("");
        cnt = 0;
        cnt2 = 0;
        return;
      }
      else
      {
        return;
      }
      return;
    }

    //-----------------------------------------------
    //              BYTE RECEIVE PROCESS:
    //
    // 1. Immediately receive the byte if available
    // 2. Increment counter
    // 3. Check if count is 4.
    // 4. If count is 4, make a new line
    // 5. If count is 48, display end of data message
    // 6. Repeat until back button is pressed
    //-----------------------------------------------

    if (Serial.available())
    {
      FPGAByte = Serial.read();


      tft.print("#");
      tft.print(cnt);
      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      // MAKE SURE TO ACCOUNT FOR AN EXTRA SPACE NEEDED IF CNT IS ONLY 1 DIGIT
      // OR ELSE EVERYTHING WILL LOOK LIKE SHIT
      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      if (cnt < 10)
      {
        tft.print(" ");
      }

      tft.print(": ");

      if (FPGAByte < 0x10)
      {
        tft.print("0");
      }
      tft.print(FPGAByte, HEX); // display contents in hex

      tft.print(" "); // make a space
      cnt  = cnt  + 1;
      cnt2 = cnt2 + 1;

      if (cnt2 == 4)
      {
        tft.println(); // new line
        cnt2 = 0; // reset cnt2
      }

      if (cnt >= 48)
      {
        tft.println();
        tft.println("End of current DS0 slot 1 report. ");
        tft.println("Press lower right corner of screen ");
        tft.print("to return to menu or,");
        tft.setTextColor(HX8357_CYAN);
        tft.println("Press anywhere to Continue.");
      }

      // testing
      //      Serial.print("Read# ");
      //      Serial.print(cnt);
      //      Serial.print(":");
      //     Serial.println(FPGAByte, BIN);
    }



    // Don't display anything new if the back button was pressed

    STATE = SendMirrorBits;
  }

  //---------------
  // StartRecording
  //---------------

  while (STATE == StartRecording)
  {

    // Retrieve a point
    TSPoint p = ts.getPoint();


    // Scale from ~0->1000 to tft.width using the calibration #'s
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, tft.height());    // Because of set rotation, the max value of p.y is now 300



    // Check if back button is pressed
    if (p.y < 100 && p.x < 360 && p.x < 100)
    {
      STATE = Idle;
      return;
    }

    // Receive a byte from the FPGA
    if (Serial.available())
    {
      FPGAByte = Serial.read();
      tft.fillScreen(HX8357_BLACK);
    }

    // Check if FPGA detected an error
    if (FPGAByte == 0x00)               // Nothing is being received
    {
      tft.setCursor(0, 0);
      tft.setTextColor(HX8357_WHITE);
      tft.setTextSize(2);
      tft.println("");
      tft.println("");
      tft.println("");
      tft.println("");

      tft.print(" \r ");
      tft.print("STATUS: ");
      tft.setTextColor(HX8357_RED);
      tft.println("LOSS OF SIGNAL   ");

    }
    else if (FPGAByte == 0x05)          // Code for yellow alarm in header
    {
      tft.setCursor(0, 0);
      tft.setTextColor(HX8357_WHITE);
      tft.setTextSize(2);
      tft.println("");
      tft.println("");
      tft.println("");
      tft.println("");

      tft.print(" \r ");
      tft.print("STATUS: ");
      tft.setTextColor(HX8357_YELLOW);
      tft.println("YELLOW ALARM     ");
    }
    else                                // Else, there is not an issue
    {
      tft.setCursor(0, 0);
      tft.setTextColor(HX8357_WHITE);
      tft.setTextSize(2);
      tft.println("");
      tft.println("");
      tft.println("");
      tft.println("");

      tft.print(" \r ");
      tft.print("STATUS: ");
      tft.setTextColor(HX8357_GREEN);
      tft.println("ROK              ");
    }

    // Display current data from spot DS0
    tft.println("");
    tft.setTextColor(HX8357_WHITE);
    tft.print(" \r ");
    tft.print("Current DS0 Byte:  ");
    tft.println(FPGAByte, BIN);
    //Serial.println(FPGAByte, BIN);

    STATE = StartRecording;
    return;
  }

  //---------------
  // WaitforTrip
  //---------------
  while (STATE == WaitToRecord)
  {

    // Retrieve a point
    TSPoint p = ts.getPoint();


    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z < MINPRESSURE || p.z > MAXPRESSURE)
    {
      return;
    }

    // Scale from ~0->1000 to tft.width using the calibration #'s
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, tft.height());    // Because of set rotation, the max value of p.y is now 300



    if (p.x > 10)
    {
      STATE = Idle;
      return;
    };

    STATE = WaitToRecord;
  }

}

// This function opens a Windows Bitmap (BMP) file and
// displays it at the given coordinates.  It's sped up
// by reading many pixels worth of data at a time
// (rather than pixel by pixel).  Increasing the buffer
// size takes more of the Arduino's precious RAM but
// makes loading a little faster.  20 pixels seems a
// good balance.


#define BUFFPIXEL 10

void bmpDraw(char *filename, uint8_t x, uint16_t y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding

  uint8_t  sdbuffer[3 * 10]; // pixel buffer (R+G+B per pixel)

  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();

  if ((x >= tft.width()) || (y >= tft.height())) return;

  //  Serial.println();
  //  Serial.print(F("Loading image '"));
  //  Serial.print(filename);
  //  Serial.println('\'');

  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.print(F("File not found"));
    return;
  }

  // Parse BMP header
  if (read16(bmpFile) == 0x4D42) { // BMP signature
    Serial.print(F("File size: ")); Serial.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    Serial.print(F("Header size: ")); Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if (read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
      //if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

      goodBmp = true; // Supported BMP format -- proceed!
      Serial.print(F("Image size: "));
      Serial.print(bmpWidth);
      Serial.print('x');
      Serial.println(bmpHeight);

      // BMP rows are padded (if needed) to 4-byte boundary
      rowSize = (bmpWidth * 3 + 3) & ~3;

      // If bmpHeight is negative, image is in top-down order.
      // This is not canon but has been observed in the wild.
      if (bmpHeight < 0) {
        bmpHeight = -bmpHeight;
        flip      = false;
      }

      // Crop area to be loaded
      w = bmpWidth;
      h = bmpHeight;
      if ((x + w - 1) >= tft.width())  w = tft.width()  - x;
      if ((y + h - 1) >= tft.height()) h = tft.height() - y;

      // Set TFT address window to clipped image bounds
      tft.setAddrWindow(x, y, x + w - 1, y + h - 1);

      for (row = 0; row < h; row++) { // For each scanline...

        // Seek to start of scan line.  It might seem labor-
        // intensive to be doing this on every line, but this
        // method covers a lot of gritty details like cropping
        // and scanline padding.  Also, the seek only takes
        // place if the file position actually needs to change
        // (avoids a lot of cluster math in SD library).
        if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
          pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
        else     // Bitmap is stored top-to-bottom
          pos = bmpImageoffset + row * rowSize;
        if (bmpFile.position() != pos) { // Need seek?
          bmpFile.seek(pos);
          buffidx = sizeof(sdbuffer); // Force buffer reload
        }

        for (col = 0; col < w; col++) { // For each pixel...
          // Time to read more pixel data?
          if (buffidx >= sizeof(sdbuffer)) { // Indeed
            bmpFile.read(sdbuffer, sizeof(sdbuffer));
            buffidx = 0; // Set index to beginning
          }

          // Convert pixel from BMP to TFT format, push to display
          b = sdbuffer[buffidx++];
          g = sdbuffer[buffidx++];
          r = sdbuffer[buffidx++];
          tft.pushColor(tft.color565(r, g, b));
        } // end pixel
      } // end scanline
      Serial.print(F("Loaded in "));
      Serial.print(millis() - startTime);
      Serial.println(" ms");
      //} // end goodBmp
    }
  }

  bmpFile.close();
  if (!goodBmp) Serial.println(F("BMP format not recognized."));
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File &f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File &f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}
