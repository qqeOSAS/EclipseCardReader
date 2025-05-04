#  EclipseCardReader Project

EclipseCardReader project is a small pocket fully functional an ESP8266-based computer device with tiny OS on it.Its designed for operations with files on sd card and displaying file content on OLED screen it also have WiFI communication.This device is open sourse.If you want you can write your own programs limited only by your imagination.This is a great raw developing patform for developers with already written functions for communicating with modules, which allows you to develop programs at a slightly higher level without worrying about working at the lowest level if it is not necessary.The project is not standing still, but is developing steadily. If anyone wants to join, I will be happy to work in the team.
![0-02-05-81ced817665f4ce3c59f07f0adb623bc67a3b109435accd9a80c7ed6d6a0eb41_dfdb2f54c31eacaf](https://github.com/user-attachments/assets/b83e6f41-9c5b-4898-8949-2413b774c677)
![0-02-05-8b87a7f2afa34dd0704f77e2857fa58b321f4e5b16c01d5ba58faf21007d29b1_ce7ce5612225cffe](https://github.com/user-attachments/assets/3b3c489f-63b0-4d00-8103-c56ab60cc9b6)
![0-02-05-5fd539d9425924827cf47028db6f424b4b42caf41aeed0ffb1b3eefbe7a31d5c_31db0134bd097097](https://github.com/user-attachments/assets/81c51f07-5d4b-47d2-854c-d72074957494)
![0-02-05-d872321e6d63a7388ff39bb39ee99e843fac06e999c48f0906c3f88082a3570d_bbbf8c074acce483](https://github.com/user-attachments/assets/e18a5ed0-fe7d-48be-8c45-bbc47d4c5efe)
![0-02-05-3826e74b619d82baf90581f9ee3a56a675f34acf9ef2267ad8d33f180e28e14c_2d0e194ab1a64e67](https://github.com/user-attachments/assets/8308cdc7-9933-41d4-b34f-4c88234f5241)





## Features
- Reads and displays text files (`.txt`, `.log`, `.csv`, `.ini`).![0-02-05-57966a308527ca4d877a0d213d45f27d6344672aed144472e5d52d66e2b2863b_8df05fa3feaaefbe](https://github.com/user-attachments/assets/a48163cb-db07-4bc4-89e2-75223d3d0ab2) it  also supports cyrylic text and enters in txt documment
- Supports binary files (`.bin`). It cam open specially prepared images in binary format.Read about file preparations below.
- Supports image formats (`.xbm` and `.bin` for images in binary format).- ![0-02-05-b0772b1091d2bf9108df944e561c37386b4e36b3ba7a9b9846b4bb034653ab1f_48ca4d19e0e4e435](https://github.com/user-attachments/assets/08d6afa6-c2d9-4acf-96dd-6ab32423abb7)
- Future plan to write correct  bmp file opening.
  

- Open-source project — feel free to contribute with pull requests.

- You can even play monocrome video in binary format on it
  https://github.com/user-attachments/assets/6ab3960a-5d0c-4b49-a16e-c42f48a2fc2a
  
  ### Supported File Formats:
- **Text files**: `.txt`, `.log`, `.csv`, `.ini`
- **Binary files**: `.bin`
- **Image files**: `.xbm`, `.bin` (binary image format)
- BETA **BMP files** not work as well
  
### Supported Operations With Files
![0-02-05-bae46946ae255d08176e60823efb4ac6ec23788cdc6a406802d3ca0c8fff4d8a_49c47cf587ff6226](https://github.com/user-attachments/assets/1b9189ff-51bf-43a9-b386-a7446ecbd6d1)
- **Change file attribute**:  like changing file visybility
- **Delete file**: removing file frm sd card
- **Rename file**: You can enter file name using keabord and save

## Required components
- Any `ESP8266` based board like generic esp8266 or in my case ESP8266 Wemos D1 board whinch is compatible with current PCB. [AliExpress link](https://a.aliexpress.com/_EIIKsc6)
- SD Card module.Can be any `SPI MicroSD card reader`. This one is compatible with PCB. [AliExpress link](https://a.aliexpress.com/_EHWfQvc)
- Display:  `IIC 128x64 0,96 OLED display` ssd1306 based or ssh1306 compatible with PCB [AliExoress link](https://a.aliexpress.com/_EuybAvG)
- 5 tactile buttons with 4 contacts [AliExpress link](https://a.aliexpress.com/_EGV2sc6)
-  1 rezistor 10k
-  PCB. You can find shematic and gerber file of the project here [files](Shematic%20&&%20gerber%20files/Gerber_PCB_Eclipse%20prototype_2025-02-15.zip)


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
