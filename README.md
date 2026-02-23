# Smart Temperature Control – ESP32 + Blynk

Proyek ini merupakan sistem monitoring dan kontrol suhu berbasis ESP32 yang terintegrasi dengan platform IoT Blynk. Sensor DS18B20 membaca suhu secara real-time, lalu sistem secara otomatis mengendalikan lampu dan kipas melalui relay berdasarkan ambang temperatur yang telah ditentukan.

Logika kontrol:

* Suhu < 32°C → Lampu ON, Kipas OFF
* 32–35°C → Lampu OFF, Kipas OFF
* Suhu > 35°C → Lampu OFF, Kipas ON

Data suhu dikirim ke dashboard Blynk setiap 3 detik untuk pemantauan jarak jauh. Sistem ini merepresentasikan implementasi Internet of Things (IoT) dalam otomasi lingkungan berbasis sensor dan kontrol aktuator secara cerdas, sederhana, dan efisien.

Teknologi: ESP32, DS18B20, Relay Module, WiFi, Blynk IoT.
