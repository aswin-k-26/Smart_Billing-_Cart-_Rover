🛒 Smart Billing Cart Rover (Smart Trolley)
📌 Project Overview

Smart Billing Cart Rover is an automated smart shopping trolley system that helps customers do product billing while shopping itself.
The cart uses RFID-based product scanning to detect items added/removed from the trolley and automatically updates the bill.

The rover is also capable of movement control using Start/Stop RFID cards and can alert the user if obstacles are detected during motion using a buzzer.

Additionally, the system provides a live web interface where users can view:

Product list

Total bill amount

And a dynamic payable QR code for instant payment

This project reduces billing time, avoids long queues, and improves customer shopping experience.

✨ Key Features

✅ RFID Product Billing

Products are tagged with RFID cards

When scanned, the product gets added to the cart bill automatically

Bill gets updated instantly

✅ Start / Stop Rover Control

Special RFID cards:

Start Card → rover starts moving

Stop Card → rover stops

✅ Remove Last Scanned Item

A dedicated push button is used to remove the last scanned product

Total updates automatically

✅ Obstacle Detection + Alert

Rover checks for obstacles while moving

If an obstacle is detected:

Movement stops / warning triggered

Buzzer alerts customer

✅ Webpage Billing Dashboard

Rover hosts a webpage through Wi-Fi

Shows:

Live product list

Total payable amount

Payment section

✅ Dynamic Payable QR Code

Total amount changes dynamically based on products scanned

QR code gets updated automatically based on current bill amount

Helps user pay instantly using UPI QR

🧠 System Workflow

User scans Start Card → Rover starts

Products are scanned using RFID → Added to bill

LCD shows product name + updated total

If user clicks remove button → last item removed

Web dashboard updates bill live

Dynamic QR is generated based on current amount

User scans QR and completes payment

User scans Stop Card → Rover stops

🧩 Hardware Components Used

ESP32 Development Board (Wi-Fi enabled microcontroller)

RFID Reader Module (RC522)

RFID Tags / Cards (Product cards + Start/Stop cards)

Motor Driver (L298N / L293D)

DC Motors + Wheels + Chassis

Ultrasonic Sensor (Obstacle detection)

Buzzer

I2C 16x2 LCD Display

Push Button (Remove product)

Battery / Power Supply

Jumper wires + breadboard/PCB

💻 Software / Tools Used

Arduino IDE (for programming)

Embedded C / Arduino C

HTML + CSS + JavaScript (webpage dashboard)

Wi-Fi Web Server (hosted by rover)

🌐 Web Dashboard Features

The rover provides a live webpage interface that displays:

Current scanned product list

Total amount

Dynamic payment section

QR code updates based on payable amount

This helps the customer complete billing without needing a separate cashier counter.

📷 Output Display

📌 LCD shows:

WELCOME TO THE STORE

Product name + price

Total amount

Rover status messages like ROVER STOPS

📌 Webpage shows:

Items list

Total bill

Dynamic payable QR for payment

🚀 Future Enhancements

Auto-follow cart using RSSI / phone tracking

User login & unique cart assignment

Database integration for product inventory

Payment verification + invoice generation

App interface for improved UI
