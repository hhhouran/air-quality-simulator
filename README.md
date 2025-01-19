## Getting Started

This simulation requires the Wokwi Extension, which is available in Visual Studio Code.

1. Download the [Wokwi Extension](https://marketplace.visualstudio.com/items?itemName=wokwi.wokwi-vscode).

2. The Wokwi Extension requires you to create an account on Wokwi's website to obtain a license:
    - Open the command palette and select "Wokwi: Start Simulator".
    - Click on "Get License", create an account, and obtain your license from the browser.

3. Download [PlatformIO Extension](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) in Visual Studio Code
    - PlatformIO is an extension that will build/compile our script and provide us a build file
    - The build file contains the .hex and .elf file that wokwi needs to execute the program in the simulation

4. Build the project using PlatformIO

5. Open `diagram.json` folder and run the program
    - I have already configured the `wokwi.toml` file to reference the .hex and .elf file within the build folder. If .hex and .elf file are not found when running the program, you will need to debug why the path is not working



## Understanding the diagram

The diagram.json folder house's the ardiuno, lcd, and dht11 sensor. The board and components cannot be edited directly from the diagram because we have the free version of wokwi. We can however, modify the the diagram within their website. 

in this [Wokwi Diagram Project](https://wokwi.com/projects/420454532427376641) you will find the diagram where we can make changes. 

When making changes, you will notice the `diagram.json` beside it also changes. This json file house's the diagram in json. 

After making any changes, copy the `diagram.json` and paste it to this projects `diagram.json`

NOTE: We could have technically just created our scripts in wokwi's project in the UI. However, we use platformIO instead to build/compile because it also allows us to have a way to upload this right away to a physical device if we wanted to.

Also, PlatformIO has plenty of useful libraries for components we can utilize