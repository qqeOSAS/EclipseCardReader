#  EclipseCardReader Project

This project is designed to read data from an SD card and display it on an ESP8266-based device. It supports various file types and formats, including text, binary files, and image files in XBM and BIN formats. It also supports Cyrillic text display. More features will be added in the future.
![0-02-05-7d27540fc13b7ccfe05d305e92de7660659ca910c8436d646dc3c32b854821ba_5e46d6799baead9d](https://github.com/user-attachments/assets/ad814d22-9d8b-40bb-a98c-fd0620cec6de)
![0-02-05-235390ea414d3b16d32e517033a4c7a39a03cbfd7492ff033648bcea15bd4963_a6bbaa052ea283f2](https://github.com/user-attachments/assets/27f47024-83cf-47c9-b5b5-764fdef4376a)
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
