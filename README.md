# Fire-Detection-System
## View:
- ### Video:
https://github.com/user-attachments/assets/0f9d3453-867f-4003-9136-f18d3f20d32b

- ### Photos:
<img src="https://github.com/user-attachments/assets/6488e4da-5b37-48d6-8eae-b4324ced96be" width="15%"></img> 
<img src="https://github.com/user-attachments/assets/c5e0d2e0-fb81-4a64-8487-79a001bb3218" width="15%"></img> 
<img src="https://github.com/user-attachments/assets/a5b16994-3098-41de-a762-2e83be8e2247" width="15%"></img> 
<img src="https://github.com/user-attachments/assets/45ecedb3-f161-4676-9b5b-75babf77064a" width="15%"></img>
<img src="https://github.com/user-attachments/assets/7e94e1fc-8e90-4af9-aafb-625ea394c0aa" width="15%"></img> 

## Description:
In the project, I used the **ESP8288 Processor** which receives a signal from an **LM393 flame detection sensor**. 
<br>
The system functions as follows:

**1. Fire detected**:
<br>
Several **operations occur simultaneously**:
 -	**Red LED** flashes.
 -	Alarm is activated via a **Buzzer**.
 -	**FAN** powered through an **N-MOS current pusher** (MOSFET) in order to control the fan effectively.
  
**2. No fire detected:**
<br>
**Green LED** is on.

Independently of the **LM393 fire detection sensor**, the system **simultaneously** performs continuous **temperature** and **humidity** measurements using the **DHT11 sensor** and displays the values in two ways:

 - **Phone/Computer**– Communication is established through a **GUI** via a **WIFI module** that allows connection through the **TCP/IP protocol** allowing for the wireless display of information.

 - **16X2 LCD**– Communication via the **I2C protocol** allows for  serial communication between the various components to display the information.


## Electrical diagram:
<img width="902" alt="Electrical diagram" src="https://github.com/user-attachments/assets/1880fa60-6480-4ad0-aa2c-f4179d125edc">
