# [Semi-automatic film processor](https://github.com/thetalkingtree/filmprocessor-arduino)

For photographers, who are developing film manually, this machine can save some processing time.
This repo contains the code and schematics for a semi-automated photographic film processor. In this stage of development the processor supports the B&W dev process tested with Foma based films and chemicals. By extending the code it is possible to use any type of film and development process, even Caffenol.

###### Main features : 
Automatic agitation time calculation based on the
- Used chemicals
- Temperature
- Film type
- Time compensation
- Push/Pull processing

###### Film development time calculation
- In case of Foma developers the usable development temperatures (from the technical sheets) are ranging from 16-26 Celsius, but the development times are specified only for the 16, 18, 20, 22, 24 and 26 grade Celsius.
- Simply put the thermometer in to the developer and based on the actual temperature, the development time is automatically calculated within the range of 16-26 grade celsius. For example if the developer temperature is 18,6 grade Celsius, the processor will calculate the accurate development time.

In the project the LCDMenuLib2 is used for the LCD menu. For more information check out the [https://github.com/Jomelo/LCDMenuLib2](https://github.com/Jomelo/LCDMenuLib2 "https://github.com/Jomelo/LCDMenuLib2") page.

Feel free to extend,  modify etc. this project. 

**Schematics**
![Schematics](/Fritzing/semiauto-film-developer_bb.png)

**Secoind prototype**
![Prototype2](/Fritzing/img1.jpg)
![Prototype2](/Fritzing/img2.jpg)

**First prototype**
![Prototype1](/Fritzing/filmprocessor.jpg)
