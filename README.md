# Automatic-OTA-Updates-ESP32
Recently, I received a request to make it easy for ME to update the firmware on MY ESP32. So, I thought about it and created a cool system. Now, when MY ESP32 turns on, it checks if there's a newer version of the software on the server. If there is, it updates itself and then gets back to work. No stress, no fuss!
🧙 # What I Needed:
To make this magic happen, I wanted to compare the times when files were made on the server. But guess what? I couldn't find a ready-made solution! So, I crafted a little tool in PHP to do the job.

📚 # Library Friends:
Before I dive in, I need to make sure I have some helpful tools (libraries) ready. I can get them easily through the Arduino IDE menu. I've left clues in the source file to help me find them.

💻 # PHP Helper:
I also made a tiny PHP file that helps MY ESP32 find out when a file was made on the server. I'll upload this file alongside MY new software, and I'm good to go!

2. How to Get Started:
Before I get my hands dirty, I'll make a few changes:

OTA.ino:

WIFI_CONNECT_SSID: Tell MY ESP32 the name of MY Wi-Fi.
WIFI_CONNECT_PSWD: Share the secret password.
otaDirURL: Let it know where to find MY new software.
otaBinFilename: What's the name of MY new software?
otaCheck.php:

filename: 
What's the name of MY new software? (Same as otaBinFilename.)
3. Let the Magic Begin:
Now, I'll do some simple coding magic and create a special file. I'll upload this file and MY new software to the server. That's it!
