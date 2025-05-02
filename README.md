#  EclipseCardReader Project

EclipseCardReader project is a small pocket fully functional an ESP8266-based computer device with tiny OS on it.Its designed for operations with files on sd card and displaying file content on OLED screen it also have WiFI communication.This device is open sourse.If you want you can write your own programs limited only by your imagination.This is a great raw developing patform for developers with already written functions for communicating with modules, which allows you to develop programs at a slightly higher level without worrying about working at the lowest level if it is not necessary.The project is not standing still, but is developing steadily. If anyone wants to join, I will be happy to work in the team.

![0-02-05-5fd539d9425924827cf47028db6f424b4b42caf41aeed0ffb1b3eefbe7a31d5c_31db0134bd097097](https://github.com/user-attachments/assets/81c51f07-5d4b-47d2-854c-d72074957494)
![0-02-05-d872321e6d63a7388ff39bb39ee99e843fac06e999c48f0906c3f88082a3570d_bbbf8c074acce483](https://github.com/user-attachments/assets/e18a5ed0-fe7d-48be-8c45-bbc47d4c5efe)
![0-02-05-3826e74b619d82baf90581f9ee3a56a675f34acf9ef2267ad8d33f180e28e14c_2d0e194ab1a64e67](https://github.com/user-attachments/assets/8308cdc7-9933-41d4-b34f-4c88234f5241)

## Features
- Reads and displays text files (`.txt`, `.log`, `.csv`, `.ini`).![0-02-05-d29b04aa1d99147aa4999640226d7b2c21c310e76e2e2fae6d00f9fa9fff6592_d1c26bf3d6b69a05](https://github.com/user-attachments/assets/e3a959da-ce05-483e-8483-9c32a80c7fba)
- Supports binary files (`.bin`).
- Supports image formats (`.xbm` and `.bin` for images in binary format).- ![0-02-05-b0772b1091d2bf9108df944e561c37386b4e36b3ba7a9b9846b4bb034653ab1f_48ca4d19e0e4e435](https://github.com/user-attachments/assets/08d6afa6-c2d9-4acf-96dd-6ab32423abb7)
- Cyrillic text support for better language compatibility.

- Open-source project — feel free to contribute with pull requests.

- You can even play monocrome video in binary format on it
  https://github.com/user-attachments/assets/6ab3960a-5d0c-4b49-a16e-c42f48a2fc2a




## Requirements
- ESP8266 platform
- Arduino IDE or PlatformIO
- SD Card module
- Display (e.g., OLED, TFT)
- External libraries: `U8g2`, `SD`, `SPI`, and other required dependencies for your display.

## Installation

   
1. **Install necessary libraries**:
   - Install the `U8g2` library for handling displays. [Instalation](https://github.com/olikraus/u8g2/wiki)
   - Install `SDfat` library for reading from the SD card.[Instalation](https://github.com/greiman/SdFat)
   - Install `GyverBTN` library for button initialization.[Instalation](https://github.com/GyverLibs/GyverButton?tab=readme-ov-file#install)
   - Install `NTPClient` library for UTC real time sync.
   - 
   
2. **Connect the SD card and display**:
   - Ensure your SD card module is connected to the ESP8266.
   - Connect your display module (OLED or TFT) to the ESP8266.

3. **Upload the code**:
   - Open the Platformio VsCode, load the project files, and upload the code to your ESP8266.

## Usage

Once the project is set up, the device will read files from the SD card and display them on the connected display. You can navigate through text files, view binary files, and render images.

### Supported File Formats:
- **Text files**: `.txt`, `.log`, `.csv`, `.ini`
- **Binary files**: `.bin`
- **Image files**: `.xbm`, `.bin` (binary image format)
- BETA **BMP files** not work as well
  
### Supported Operations With Files
- **Change file attribute**:
- **Delete file**:
- **Rename file**:
  

### Future Features:
- More file format support.
- Enhanced navigation and file management features.
- Optimization for large files and better performance.
- Wifi communication
- Hacking tools
- Games
- Usefull applications

## Contributing

This project is open-source! Feel free to fork the repository, submit issues, or create pull requests with improvements and new features.

## License

This project is licensed under the GPU License - see the [LICENSE](LICENSE) file for details.
