# EclipseCardReader

**EclipseCardReader** is a pocket-sized ESP8266-based computer with a tiny OS for SD card file operations and display content output to an OLED display. The project is open-source and developer-friendly: you can build your own apps using ready-to-use libraries for display, SD card, buttons, and Wi-Fi.

![device photo](https://github.com/user-attachments/assets/b83e6f41-9c5b-4898-8949-2413b774c677)

---

## Features

- Browse text files with Cyrillic support and line breaks.
- View binary files and images in `.xbm`, `.bin` formats. Experimental support for `.bmp`.
- Play monochrome video in a special binary format directly on the device.
- Change file attributes (visibility, read-only) directly from the device.
- Delete or rename files using the on-screen keyboard.
- Wi-Fi support: connection, auto-login, "Death attack" (experimental), beacon spam (fake network clones), and file transfer.
- Animations and smooth movement of graphics on the display.
- Easily add your own mini-apps and demos!

---

## Interface Examples

![Screenshot 1](https://github.com/user-attachments/assets/e18a5ed0-fe7d-48be-8c45-bbc47d4c5efe)
![Screenshot 2](https://github.com/user-attachments/assets/8308cdc7-9933-41d2-854c-d72074957494)
![Text Viewer Example](https://github.com/user-attachments/assets/a48163cb-db07-4bc4-89e2-75223d3d0ab2)
![Image Viewer Example](https://github.com/user-attachments/assets/08d6afa6-c2d9-4acf-96dd-6ab32423abb7)

---

## Supported File Formats

- **Text**: `.txt`, `.log`, `.csv`, `.ini`, `.md`, `.json`, `.xml`, `.yaml`, `.yml`, `.cfg`, `.conf`, `.lst`, `.dat`, `.gcode`, `.h`, `.c`, `.py`, `.cpp`
- **Binary**: `.bin`
- **Images**: `.xbm`, `.bin` (binary image), partial `.bmp` (beta)

## Supported File Operations

- **Change attributes**: visibility, read-only
- **Delete**: remove file from SD card
- **Rename**: enter new file name using on-screen keyboard

---

## Wi-Fi Features

- Connect to Wi-Fi, save login for future auto-connect
- "Death Attack" (experimental, needs improvement)
- Beacon spam (fake network clones)
- You can transfer files over Wi-Fi in two ways:

- **Access Point Mode:** The device creates its own Wi-Fi network. Connect to this network and open the web interface in your browser to upload/download files.
- **Client Mode (STA):** The device connects to your existing Wi-Fi network. Access the web interface via the device’s local IP address.

> **Note:** File transfer may not work properly with specific file types.

> **WARNING:** Wi-Fi features are for educational and research purposes only. Use responsibly and legally!

---

## Required Components

- Any ESP8266-based board (e.g., Wemos D1 mini)
- SD card module (SPI MicroSD card reader)
- OLED display 128x64 (SSD1306 or compatible)
- 5 tactile buttons (4 contacts)
- 10k resistor
- PCB board — [schematics and gerber files](Shematic%20&&%20gerber%20files/)

---

## Installation

1. **Install required libraries:**
   - [U8g2](https://github.com/olikraus/u8g2/wiki) — display driver
   - [SDfat](https://github.com/greiman/SdFat) — SD card access
   - [GyverBTN](https://github.com/GyverLibs/GyverButton?tab=readme-ov-file#install) — button handling
   - [NTPClient](https://github.com/arduino-libraries/NTPClient) — real-time clock sync

2. **Wiring:**
   - Connect SD card module and OLED display to your ESP8266 according to the schematic.

3. **Upload:**
   - Open the project with PlatformIO (VSCode), connect your board, and upload the firmware.

---

## Creating Your Own App

You can create custom programs using the libraries for display, file system, and Wi-Fi already provided. Add your `.cpp`/`.h` files, register in the main menu, and experiment!

---

## Developer Section

- Core logic for file browsing: `drawSDFilesSystem.h`, `ReadBinary.h`, `drawBinVievOptions.h`, `drawAnimation.h`, `BinImageBrowser.h`
- File attributes: `File properties browser/draw_edit_attributes.h`, `SdCard_utils.h`
- Animation: `drawAnimation.h` (supports acceleration for graphics and text)

---

## Roadmap

- More file format support
- Improved navigation and file management
- Optimization for large files and better performance
- File transfer over Wi-Fi
- Hacking tools, micro-games, and useful applications

---

## License

GNU GENERAL PUBLIC LICENSE v3 — see [LICENSE](LICENSE)

---

## Contributing

This project is open for collaboration! Fork, pull requests, and issues are welcome. Have an idea or found a bug? Let me know!
