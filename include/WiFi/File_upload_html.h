#ifndef file_upload_html_h
#define file_upload_html_h
#include <Arduino.h>

const char uploadPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Upload to EclipseCardReader</title>
  <style>
    :root {
      --bg-color: #1e1e1e;
      --panel-bg: #252526;
      --text-color: #d4d4d4;
      --accent: #0a84ff;
      --border-radius: 8px;
      --font-family: "Segoe UI", Consolas, monospace;
    }

    body {
      background-color: var(--bg-color);
      color: var(--text-color);
      font-family: var(--font-family);
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: flex-start;
      padding-top: 60px;
      margin: 0;
    }

    h2 {
      color: #ffffff;
      margin-bottom: 20px;
      font-weight: normal;
      font-size: 28px;
    }

    form {
      background-color: var(--panel-bg);
      padding: 30px;
      border-radius: var(--border-radius);
      box-shadow: 0 8px 24px rgba(0, 0, 0, 0.3);
      display: flex;
      flex-direction: column;
      align-items: center;
      width: 90%;
      max-width: 420px;
    }

    input[type="file"] {
      background: #2a2a2a;
      color: #d4d4d4;
      border: 1px solid #3c3c3c;
      padding: 8px;
      width: 100%;
      margin-bottom: 15px;
      border-radius: var(--border-radius);
    }

    input[type="submit"] {
      background-color: var(--accent);
      color: white;
      padding: 10px 20px;
      border: none;
      border-radius: var(--border-radius);
      cursor: pointer;
      font-size: 14px;
      transition: background-color 0.2s;
      width: 100%;
    }

    input[type="submit"]:hover {
      background-color: #0074e8;
    }

    #fileName {
      margin-bottom: 10px;
      font-size: 13px;
      color: #bbbbbb;
      font-style: italic;
      text-align: center;
    }

    #loadingMessage {
      margin-top: 15px;
      font-size: 14px;
      color: #cccccc;
      display: none;
    }

    #progressBarContainer {
      width: 100%;
      background: #3c3c3c;
      border-radius: var(--border-radius);
      margin-top: 10px;
      display: none;
      position: relative;
      height: 12px;
      overflow: hidden;
    }

    #progressBar {
      width: 0%;
      height: 100%;
      background: var(--accent);
      transition: width 0.3s ease;
    }

    #progressPercent {
      position: absolute;
      left: 50%;
      top: 0;
      transform: translateX(-50%);
      font-size: 12px;
      color: #ffffff;
      height: 100%;
      display: flex;
      align-items: center;
      justify-content: center;
      pointer-events: none;
    }

    footer {
      margin-top: 40px;
      font-size: 14px;
      color: #888;
    }

    footer a {
      color: var(--accent);
      text-decoration: none;
    }

    footer a:hover {
      text-decoration: underline;
    }
  </style>
</head>
<body>
  <h2>⬆ Upload File to EclipseCardReader</h2>
  <form id="uploadForm">
    <div id="fileName">No file selected</div>
    <input type="file" name="upload" id="fileInput" required>
    <input type="submit" value="Upload">
    <div id="loadingMessage">⏳ Uploading...</div>
    <div id="progressBarContainer">
      <div id="progressBar"></div>
      <div id="progressPercent">0%</div>
    </div>
  </form>

  <footer>
    <p>🔗 <a href="https://github.com/qqeOSAS/EclipseCardReader" target="_blank">View on GitHub</a></p>
  </footer>

  <script>
    document.getElementById("uploadForm").addEventListener("submit", function(e) {
      e.preventDefault();
      const fileInput = document.getElementById("fileInput");
      const file = fileInput.files[0];
      if (!file) return;

      document.getElementById("loadingMessage").style.display = "block";
      document.getElementById("progressBarContainer").style.display = "block";
      document.getElementById("progressBar").style.width = "0%";
      document.getElementById("progressPercent").textContent = "0%";

      const formData = new FormData();
      formData.append("upload", file);
      formData.append("size", file.size);

      const xhr = new XMLHttpRequest();
      xhr.open("POST", "/upload", true);

      xhr.upload.onprogress = function(e) {
        if (e.lengthComputable) {
          var percent = Math.round((e.loaded / e.total) * 100);
          document.getElementById("progressBar").style.width = percent + "%";
          document.getElementById("progressPercent").textContent = percent + "%";
        }
      };

      xhr.onload = function() {
        document.getElementById("loadingMessage").style.display = "none";
        document.getElementById("progressBarContainer").style.display = "none";
        alert("✅ Upload complete!");
        fileInput.value = "";
        document.getElementById("fileName").textContent = "No file selected";
      };

      xhr.onerror = function() {
        document.getElementById("loadingMessage").style.display = "none";
        document.getElementById("progressBarContainer").style.display = "none";
        alert("❌ Error during upload");
      };

      xhr.send(formData);
    });

    document.getElementById("fileInput").addEventListener("change", function () {
      const file = this.files[0];
      if (file) {
        document.getElementById("fileName").textContent = "File: " + file.name + " (" + file.size + " bytes)";
      } else {
        document.getElementById("fileName").textContent = "No file selected";
      }
    });
  </script>
</body>
</html>
)rawliteral";


#endif