#  EclipseCardReader Project

This project is designed to read data from an SD card and display it on an ESP8266-based device. It supports various file types and formats, including text, binary files, and image files in XBM and BIN formats. It also supports Cyrillic text display. More features will be added in the future.

## Features
- Reads and displays text files (`.txt`, `.log`, `.csv`, `.ini`).
- Supports binary files (`.bin`).
- Supports image formats (`.xbm` and `.bin` for images in binary format).
- Cyrillic text support for better language compatibility.
- Open-source project — feel free to contribute with pull requests.
- You can even play monocrome video in binary format on it

## Requirements
- ESP8266 platform
- Arduino IDE or PlatformIO
- SD Card module
- Display (e.g., OLED, TFT)
- External libraries: `U8g2`, `SD`, `SPI`, and other required dependencies for your display.

## Installation

1. **Set up your ESP8266**:
   - Install the [ESP8266 board package](https://github.com/esp8266/Arduino) in the Arduino IDE or PlatformIO.
   
2. **Install necessary libraries**:
   - Install the `U8g2` library for handling displays.
   - Install `SD` library for reading from the SD card.
   
3. **Connect the SD card and display**:
   - Ensure your SD card module is connected to the ESP8266.
   - Connect your display module (OLED or TFT) to the ESP8266.

4. **Upload the code**:
   - Open the Arduino IDE, load the project files, and upload the sketch to your ESP8266.

## Usage

Once the project is set up, the device will read files from the SD card and display them on the connected display. You can navigate through text files, view binary files, and render images.

### Supported File Formats:
- **Text files**: `.txt`, `.log`, `.csv`, `.ini`
- **Binary files**: `.bin`
- **Image files**: `.xbm`, `.bin` (binary image format)
- BETA **BMP files** not work as well

### Future Features:
- More file format support.
- Enhanced navigation and file management features.
- Optimization for large files and better performance.
- Comunicating with phone program by wifi
- Hacking tools
- Games
- Usefull aplications

## Contributing

This project is open-source! Feel free to fork the repository, submit issues, or create pull requests with improvements and new features.

## License

This project is licensed under the GPU License - see the [LICENSE](LICENSE) file for details.
