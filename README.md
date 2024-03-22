# Conveyor Belt with AI Detection (Prototype)
This repository is about our ELE495 course project. Document the containing the requirements for the project was provided inside [01_Documents]. Its main goal is to create a conveyor belt system that detects both identified and unidentified objects passing through with object detection AI models using NVIDIA's Jetson Nano 2GB Developer Kit.
# Configure NVIDIA Jetson Nano Enviroment
Follow NVIDIA's "Hello AI World" course to setup your Jetson enviroment with NVIDIA JetPack. After your initial boot continue the guide following "Building the Project from Source". We recommend building from source because adding new libraries or drivers directly to your enviroment is less troublesome than configuring the provided Docker enviroment. You can find this course's github repository here: [jetson-inference]

After these initials are done, in order to use the UART on Jetson Nano's GPIO header you can follow this [UART tutorial] video. There is also a github repository called [UARTDemo] provided by [JetsonHacksNano] who is also the video's owner.

You can find tutorials about how to use he GPIO header pins on Jetson Nano inside [jetson-gpio] github repository. Generally "Jetson.GPIO" library already comes pre-installed with the standart version of Jetson Nano Developer Kit Image but if you are missing this library in your enviroment, you can install it with the instructions given inside this repository.

# Re-training AI Model
If you want to retrain your AI model (SSD Mobilenet for ex.) with higher amounts of data and more Epochs we advise you to do this on a diffrent (more powerful) device such as your own computer rather than Jetson Developer Kit. You can recreate training enviroment [pytorch-ssd] provided by [jetson-inference] inside your own device.

There is also an [Issue#879] that has been answered by [dusty-nv] about how you can recreate this enviroment.

We have followed [retraining SSD-Mobilenet] instructions in order to retrain our models (inside [05_AI_Models]) on our own computers' graphics cards for this project.
# How Our Design Works
Our system is being controlled by two devices. First and main one (contains our main FSM) being the NVIDIA Jetson Nano. Second one being an Arduino Uno. You can see the connections between these two devices and other peripherals in the picture below.

<img src="https://github.com/SultanPalamut/Bitirme_Bant/blob/main/07_Pictures/system_diagram.png">

Arduino Uno is being used kind of like a logic converter because TB6600 step motor driver's logic voltage level is 5V. We are using GPIO pins to communicate Jetson Nano with Arduino Uno so our main code inside Jetson Nano can command Arduino to move the conveyor belt. You can see how our system works in more detail on our flow diagram below. 

<img src="https://github.com/SultanPalamut/Bitirme_Bant/blob/main/07_Pictures/flow_diagram.png">

To summarize this diagram, when first powered up Arduino Uno waits Jetson Nano's main FSM to start. When Jetson Nano's main starts it first configures its GPIO pins and UART than activates the two AI models that we are going to use. After all this is done Jetson Nano sends a signal via GPIO to Arduino Uno so it starts to move the conveyor belt. Jetson Nano then waits Arduino Uno until it detects a box and centers (predetermined as we knew the lenght of our box) it. After this task is done Arduino Uno signals Jetson Nano and wait for Jetson Nano to finish. Jetson Nano takes the picture of the box and gives this frame to two AI Models that we have activated. One is trained for the objects that we are expecting (Apple, Lemon, Banana, Orange and Pen) and one is trained for the possible unidentified objects (will be described later). Jetson Nano combines the output data from these two AI to a string and sends it trough UART to HC-05. Then HC-05 sends this information to our app on our cellphone using bluetooth. Jetson Nano then signals Arduino Uno to remove the box out of the way. After Arduino Uno removes the box and signals Jetson Nano the main FSM resets itself for the next loop.
# Imagined Solution For Detecting Unidentified Objects
In order to identify these unidentified objects and give the count of them we would still need our AI to be trained on these possible unknown objects. So we choose to use two AI models.

One is for our main objects and one is for unidentified object as we imagined this conveyor belt would carry specific items and the unwanted object could be a number of things. To give an example you wouldn't expect a computer mouse to be in a conveyor belt that is suppose to have fruits but there could be a pen or a rock that someone might have dropped.

For our project different possiblities of these unidentified objects were endless so we choose to make a demo for our solution. We used the standart SSD-Mobilenet-V2 as our second AI and chose two objects that the "SSD-Mobilenet-V2" would generally notice (not confuse with some other object). Those were a computer mouse and a cellphone. We filtered the output of the "SSD-Mobilenet-V2" and sent it to our app as unidentified object count.

[Issue#879]: <https://github.com/dusty-nv/jetson-inference/issues/879>
[UART tutorial]: <https://www.youtube.com/watch?v=fInhTJhVi5M>
[jetson-gpio]: <https://github.com/NVIDIA/jetson-gpio>
[jetson-inference]: <https://github.com/dusty-nv/jetson-inference/tree/master>
[UARTDemo]: <https://github.com/JetsonHacksNano/UARTDemo>
[JetsonHacksNano]: <https://github.com/JetsonHacksNano>
[pytorch-ssd]: <https://github.com/dusty-nv/pytorch-ssd/tree/6accaa88845ec135a7d6fe25e9a26afd4698639d>
[dusty-nv]: <https://github.com/dusty-nv>
[retraining SSD-Mobilenet]: <https://github.com/dusty-nv/jetson-inference/blob/master/docs/pytorch-ssd.md>
[01_Documents]: <https://github.com/SultanPalamut/AI_Detected_Conveyor_Belt/tree/main/01_Documents>
[05_AI_Models]: <https://github.com/SultanPalamut/AI_Detected_Conveyor_Belt/tree/main/05_AI_Models>


