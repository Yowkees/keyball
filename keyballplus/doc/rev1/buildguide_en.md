<!--
  This build guide is a DRAFT written by adapting the Keyball39 build guide
  (keyball39/doc/rev1/buildguide_en.md) for Keyball+.
  - The kit contents list (chapter 1) reflects the Keyball+ instruction sheet.
  - The images under images/ are provisional copies of Keyball39's photos.
    Replace them in place (same file names) with Keyball+ photos once available.
  - The remaining "TODO" comments are all placeholders waiting for real Keyball+ photos.
-->

# Build Guide for Keyball+

This guide provides detailed instructions for assembling the Keyball+.

Keyball+ is a split keyboard kit with a thumb trackball (39 keys). Based on Keyball39, it supports
**both** MX switches and low-profile (Kailh Choc) switches; the kit includes PCB sockets and spacers
for each. You can build it with either type (or mix them per key). The key count and key layout are
identical to Keyball39, and most of the assembly procedure is shared with Keyball39.
You can also separate one right-hand thumb key and build it as a **38-key** board (see [Chapter 6](#anchor6)).

**日本語版のKeyball+ビルドガイドは[こちら](buildguide_jp.md)です。**


<!-- TODO: replace with a photo of Keyball+ -->
![01](images/kbp_001.jpg)

## 【Table of Contents】

> **Preparation**
 - [1. Parts Check](#anchor1)
   - [1-1. Kit Contents](#anchor1-1)
   - [1-2. Parts You Need to Prepare Yourself Before Assembly](#anchor1-2)
   - [1-3. Parts and Options That Can Be Installed After Assembly](#anchor1-3)
 - [2. Preparation](#anchor2)
   - [2-1. Required Tools](#anchor2-1)
   - [2-2. Firmware](#anchor2-2)

> **Implementation**
 - [3. Implementation](#anchor3)
   - [3-1. Before Soldering](#anchor3-1)
   - [3-2. Installing Diodes](#anchor3-2)
   - [3-3. Soldering Key Sockets](#anchor3-3)
   - [3-4. Soldering LEDs (Optional)](#anchor3-4)
   - [3-5. Soldering Jumpers](#anchor3-5)
   - [3-6. TRRS Socket, Tactile Switch, and 4-pin Socket](#anchor3-6)
   - [3-7. Soldering ProMicro](#anchor3-7)
 - [4. Assembling the Trackball Reading Board](#anchor4)
   - [4-1. Soldering the Sensor](#anchor4-1)
   - [4-2. Soldering the L-shaped Connector](#anchor4-2)
 - [5. Soldering the Left-Right Detection Jumper on the Left Side](#anchor5)
 - [6. Cutting the Top Plate (Optional)](#anchor6)

> **Assembly**
 - [7. Assembly](#anchor7)
   - [7-1. Installing the Protection Plate](#anchor7-1)
   - [7-2. Assembling the Top Plate](#anchor7-2)
   - [7-3. Writing the Firmware and Checking Operation](#anchor7-3)
   - [7-4. Assembling the Bottom Plate](#anchor7-4)
 - [8. Installing the Trackball](#anchor8)
   - [8-1. Inserting the Ball Reading Board](#anchor8-1)
   - [8-2. Assembling the Trackball Case](#anchor8-2)
   - [8-3. Installing the Trackball Case](#anchor8-3)

> **Finishing**
 - [9. Final Assembly](#anchor9)
 - [10. Changing the Keymap / Updating the Firmware](#anchor10)
 - [11. How to Use Keyball+♪](#anchor11)

<a id="anchor1"></a>
## 1. Parts Check

Please check that all kit contents are included when your kit arrives.

<a id="anchor1-1"></a>
### 1-1. Kit Contents

The standard set can accommodate one thumb trackball on either the left or right side.

<!-- Single-hand kits are also available for dual-ball specifications with trackballs on both sides, or for assembly without trackballs on either side. -->

<!-- If you purchased a single-hand set or dual-ball set, please check the included parts list in your kit for the contents. -->

**Keyball+ Kit Contents**
| Part Name | Quantity | Notes |
|:-------|:----:|:-----|
| Middle PCB (Left/Right) | 1 set | Main board |
| Top PCB (Left/Right) | 1 set | For key switch mounting |
| Middle Acrylic Plate (Left/Right) | 1 set | Includes the thumb section |
| Bottom Acrylic Plate (Left/Right) | 1 set | Bottom cover |
| ProMicro Protection Plate | 2 pieces | For board protection |
| 34mm Trackball Holding Case (Top/Bottom) | 1 set | For ball mounting |
| Trackball Reading Board | 1 piece | Sensor board |
| L-shaped Connector Pin (7-pin) | 1 piece | For sensor connection |
| Trackball Reading IC + Lens | 1 set | PMW3360 + optical lens |
| Flat Head Screw M1.7 | 2 pieces | For trackball case mounting |
| Small Head Screw M1.7 | 2 pieces | For trackball case assembly |
| TRRS Jack | 2 pieces | For TRRS cable connection |
| Tactile Switch | 2 pieces | For ProMicro reset |
| Connector Pin (12-pin) | 4 pieces | For ProMicro connection |
| Diode (chip type) | 48 pieces | For key matrix error prevention (21 mounted on the trackball side + 24 on the non-trackball side = 45; the rest are spares) |
| OLED Module | 2 pieces | Display |
| OLED Pin Socket + Pin Header | 2 sets | For OLED connection |
| PCB Socket for MX switches | 40 pieces | Use when building with MX switches (39 mounted + 1 spare) |
| PCB Socket for Choc switches | 40 pieces | Use when building with low-profile switches (39 mounted + 1 spare) |
| Spacer M2 9mm | 4 pieces | For the ProMicro protection plate |
| Spacer M2 7mm | 12 pieces | For the top plate in the MX build |
| Spacer M2 4mm | 12 pieces | For the top plate in the low-profile build |
| Screw M2 3.5mm | 32 pieces | For plate mounting |
| Cushion Rubber | 8 pieces | For bottom anti-slip |

> You only use one of the two socket types (MX or Choc); they can also be mixed per key. Likewise, use the 7mm spacers for an MX build and the 4mm spacers for a low-profile build.

<!-- TODO: replace with a photo of the Keyball+ kit contents -->
![02](images/kbp_007.jpg)

<a id="anchor1-2"></a>
### 1-2. Parts You Need to Prepare Yourself Before Assembly

The following parts are not included in the kit and need to be purchased separately.

| Part Name | Quantity | Notes |
|:-------|:----:|:-----|
| ProMicro | 2 pieces | You can choose inexpensive ones or USB Type-C compatible ones |
| Key Switches | 39 pieces | MX compatible or low-profile (Kailh Choc). See [Chapter 3-3](#anchor3-3) for how MX/Choc are used. 38 pieces if you separate one right-hand thumb key ([Chapter 6](#anchor6)) |
| Keycaps | 39 pieces | 1u. Match the switch type you use (MX / Choc). 38 pieces if you separate the right-hand thumb key |
| 34mm Diameter Trackball | 1 piece | Required when using trackball |
| TRS Cable | 1 piece | For left/right connection. TRRS (4-pole) cable is also acceptable |
| USB Cable | 1 piece | For connecting to a PC. Compatible with the ProMicro you purchased |

<!-- TODO: replace with a photo for Keyball+ -->
![03](images/kbp_003.jpg)

<a id="anchor1-3"></a>
### 1-3. Parts and Options That Can Be Installed After Assembly

The following parts are optional and can be installed even after assembly.

| Part Name | Quantity | Notes |
|:-------|:----:|:-----|
| Full-color LED (YS-SK6812MINI-E) | 55 pieces | Under each key + underglow. 29 on the left / 26 on the right. 54 pieces if you separate the right-hand thumb key ([Chapter 6](#anchor6)) ※SK6812MINI cannot be used |

<!-- TODO: replace with a photo for Keyball+ -->
![04](images/kbp_004.jpg)

<a id="anchor2"></a>
## 2. Preparation

<a id="anchor2-1"></a>
### 2-1. Required Tools

The following tools are required for assembling Keyball+. Please check that you have all of them.

| Tool Name | Purpose |
|:-------|:-----|
| Soldering Iron (Temperature adjustable if implementing LEDs) | Soldering work |
| Solder (Low melting point is effective if implementing LEDs) | For connections |
| #0 + Precision Driver | For screw tightening |
| Tweezers | For handling parts |
| 150 grit sandpaper | For polishing when cutting plates |

![05](images/kbp_005.jpg)

<a id="anchor2-2"></a>
### 2-2. Firmware

To operate Keyball+, firmware needs to be written to the ProMicro you purchased.

Keyball+ firmware is written using **[Keyball Link](https://keyball-link.shiroganelab.com/)**, a web tool that lets you edit keymaps and flash firmware directly from your browser. No special software installation is required (a WebHID/WebSerial capable browser such as Google Chrome is needed).

<a id="anchor3"></a>
## 3. Implementation

Now we begin soldering work.

The PCB is reversible, so first decide which side will be left/right hand.
When operating the trackball with your right thumb, the trackball will be attached to the area where the PCB is cut, as shown in the red circle in the photo below.

<!-- TODO: replace with a photo of the Keyball+ PCB -->
![20](images/kbp_010.jpg)

When operating the trackball with your left thumb, the layout is as shown in the photo below.

![21](images/kbp_011.jpg)

This build guide explains the specification with the trackball on the right hand.
>**⚡️ Warning**: If you solder the wrong side, rework will be very difficult.
>Please mark the front side with masking tape or similar as shown in the photo below to prevent mistakes.

![22](images/kbp_012.jpg)

<a id="anchor3-1"></a>
### 3-1. Before Soldering
The soldering iron tip should be shaped like a bamboo spear tip, which makes it easier to place solder on flat surfaces and "scoop up" excess solder.

![27](images/kbp_027.jpg)

<a id="anchor3-2"></a>
### 3-2. Installing Diodes
Now let's solder the diodes in order.
All diodes are soldered on the **back side**.

The diode silk marks are the marks shown by the arrows in the photo below: **21 on the trackball side and 24 on the non-trackball side (45 pieces total for both sides)**.
> **⚡️Warning**: Diodes have polarity, so please install them in the correct orientation.
The orientation is where the straight line on the component matches the straight line at the tip of the arrow in the silk mark.
> Please check the orientation carefully by looking at the photo below.
> All diodes on the same board are arranged in the same orientation.
Please check that the orientation matches the surrounding diodes as you proceed with soldering.

![25](images/kbp_014.jpg)

The diode silk has black dots as shown in red in the photo below, so you can verify polarity after soldering the diodes.

![26](images/kbp_015.jpg)

Let's start soldering.
First, apply solder to one side of the diode pad.

![28](images/kbp_020.jpg)

Grab the diode with tweezers and fix it while melting the pre-applied solder.

![30](images/kbp_028.jpg)

Rotate the board 180 degrees and flow solder to the other leg of the diode.
Finally, touch both legs with the iron tip, and if the diode doesn't fall off, both legs are soldered.

![Solder the other leg](images/kbp_029.jpg)

Install 21 diodes on the trackball side and 24 on the non-trackball side, for a total of 45 on both sides.

![37](images/kbp_030.jpg)

<a id="anchor3-3"></a>
### 3-3. Soldering Key Sockets
Key sockets are soldered on the **back side** like diodes.
The kit includes both **MX switch sockets** and **Choc switch sockets**.

For each key position, choose **one of the three combinations** below and solder that (you can choose per key).

**This build guide proceeds with the Choc + LED combination.**

| Combination | Usable switches | LED at this position |
|:--|:--|:--:|
| **MX socket + Choc socket** | Both MX and Choc (swap the switch to change type) | Not possible |
| **MX socket + LED** | MX only | Possible |
| **Choc socket + LED** | Choc only | Possible |

> A position where you want to swap between MX and Choc gets no LED; a position where you want an LED is fixed to either MX or Choc. LED soldering is done in [Chapter 3-4](#anchor3-4).

![85](images/kbp_077-3.jpg)

![85](images/kbp_077-1.jpg)

![85](images/kbp_077-2.jpg)

The number of sockets you solder depends on the combinations you chose: a position with both MX and Choc uses 2 sockets (MX + Choc), a position with an LED uses 1.
If you separate one right-hand thumb key to make a 38-key board (see [Chapter 6](#anchor6)), the socket at that position can be omitted.
Set them to match the silk mark and shape for soldering.

>**⚡️Warning**: If they protrude from the silk, the orientation is wrong.
>Please check the correct orientation in the photo below.

**For MX switch sockets**

![85](images/kbp_077.jpg)

**For Choc switch sockets**
Choc sockets also have an orientation. As shown in the photo below, place the terminal with the black resin part in an octagonal shape near the center of the switch.

![85](images/kbp_075.jpg)

Bend both tabs at the ends of the socket with tweezers or similar, as shown in the photo, before soldering.

![85](images/kbp_075-1.jpg)

For soldering, apply solder to one side of the socket pad as shown in the blue circle.

![86](images/kbp_078.jpg)

Fit the socket and press down with tweezers from above, then touch the iron tip with a little solder from the side of the terminal, and the solder will melt and the socket will sink.
Based on experience, this method is least likely to cause "tempura" (poor connection).

Choc sockets tend to shift position when soldered, so adjust the position as you attach it.

![87](images/kbp_079.jpg)

![87](images/kbp_079-1.jpg)

Rotate the board 180 degrees and solder the other terminal.

Solder the chosen socket(s) at all 39 key positions (38 if you separated the right-hand thumb key).

![89](images/kbp_081.jpg)

<a id="anchor3-4"></a>
### 3-4. Soldering LEDs (Optional)
LEDs (YS-SK6812MINI-E) are optional.
On Keyball+, LEDs are placed under each key plus underglow: **29 on the left side and 26 on the right side (55 total)**. Note that the count differs between left and right (the side with the trackball has 26, the side without has 29).
If you separate the right-hand thumb key to make a 38-key board (see [Chapter 6](#anchor6)), the LED at that position is also removed, so the trackball side has 25 and the total is 54.

>**⚡️Warning**: A per-key (under-key) LED can only be fitted at a position where the key socket in [Chapter 3-3](#anchor3-3) is **MX only or Choc only**. A position with both MX and Choc sockets cannot have its under-key LED (underglow LEDs are unaffected).
However, LEDs are very sensitive to heat, so please adjust the iron tip temperature to **220°C to 280°C**.
Since the iron tip temperature is low, heat may not transfer to the pad, making it easy for solder to become "tempura" (poor connection).
The keyboard can be used without LEDs, and lighting all LEDs is quite difficult.
We recommend completing it without LEDs first. LEDs can be added later.

All LEDs are soldered on the **back side**.

Match the leg with the notch on the YS-SK6812MINI-E 4-pin with the marked pad and place the LED for soldering.

LEDs are mixed with upward and downward facing ones, but if you match the pin notch with the marking as shown in the photo below, the up/down orientation will automatically match.

Soldering all 4 pins at once can cause the component temperature to rise and damage it, so please solder 2 pins at a time with intervals.
For this reason, place about 10 LEDs at once, and move to the next LED soldering after applying solder once.
This prevents continuously heating one LED.

<!-- TODO: replace with a photo of the Keyball+ LED layout (asymmetric, 55 total) -->
![80](images/kbp_070.jpg)

After all LED soldering is complete, proceed to the next step.
The LED lighting check is done after the key switches are mounted, in [Chapter 7-3](#anchor7-3).

<a id="anchor3-5"></a>
### 3-5. Soldering Jumpers
Jumpers need to be shorted to operate the OLED module.

>**⚡️Warning**: Jumper soldering is done **only on the back side**.
There are "Back Side Only" markings, with [4 pieces each] on the left and right boards.
Warm the pad with the iron tip, then melt solder to create a bridge.

![41](images/kbp_036.jpg)

If you're not confident in soldering or not good at bridge work, try applying solder to the 8 pads first as shown in the photo below.

![40b](images/kbp_037.jpg)

Adding solder here should make bridging easier.

![40b](images/kbp_038.jpg)

If the solder freshness deteriorates (heated multiple times), surface tension decreases and bridging becomes difficult.
Scrape off the solder once and add solder or flux to try again.
When bridging is successful, it should look like the photo below.
Bridge a total of 8 locations on both sides.

There are other jumpers, but these will be explained later, so please solder only 4 locations each on the left and right for now.

<a id="anchor3-6"></a>
### 3-6. TRRS Socket, Tactile Switch, and 4-pin Socket
Solder the parts shown in the photo below.
>**⚡️Warning**: This time all are installed **only on the front side**, so please be careful.

![51](images/kbp_040.jpg)

If you're worried about parts floating, fix them with masking tape or similar for soldering.

![52](images/kbp_041.jpg)

When all are installed, it should look like the photo below.

![53](images/kbp_042.jpg)


<a id="anchor3-7"></a>
### 3-7. Soldering ProMicro
ProMicro is soldered using the connector pins shown in the photo below, which makes replacement easier when ProMicro fails.
Connector pins have installation direction, so please look at the photo carefully for the work.

![60](images/kbp_050.jpg)

First, insert the connector pin into the board [front side] loosely. (It does not need to be fully seated yet.)

Insert the connector to match the **square silk frame**.
If the black silk frame is misaligned with the connector, the insertion hole is wrong.

![61](images/kbp_055.jpg)

Rest ProMicro loosely on the inserted connector pin, then press ProMicro down — this also seats the connector pin firmly.

![63](images/kbp_057.jpg)

Solder **only the ProMicro side** in a state where it's firmly inserted to the end.
Soldering while inserted into the board prevents the connector pin from being installed at an angle.
>**⚡️Warning**: If you solder the connector pin to the middle PCB side as well, replacement will be very difficult when ProMicro fails.

![63](images/kbp_057-1.jpg)

OLED can be installed on both left and right boards as standard.
Insert a 4-pin header into the 4-pin socket and place the OLED module.
Then solder **only one** of the 4 pins.

While melting the solder of the single soldered pin, press the OLED module from above to prevent it from floating.
Also, adjusting it to be parallel with ProMicro will look better.

Once the position is determined, solder the remaining 3 pins.

![70](images/kbp_062.jpg)

The main-board soldering is done here (the trackball reading board follows in [Chapter 4](#anchor4), and the left-right detection jumper in [Chapter 5](#anchor5)).
Firmware writing and the key-input / LED operation check are done after the key switches are mounted, in [Chapter 7-3](#anchor7-3).

<a id="anchor4"></a>
## 4. Assembling the Trackball Reading Board
Prepare the board shown in the photo below (hereinafter, ball board) and optical sensor.

※For quality confirmation of sensors and boards, pre-soldered ball boards may arrive.
In that case, skip this step and proceed to L-shaped connector soldering in [Chapter 4-2](#anchor4-2).

![90](images/kbp_090.jpg)

<a id="anchor4-1"></a>
### 4-1. Soldering the Sensor

The sensor IC is inserted from the back side where no components are mounted on the ball board.
>**⚡️Warning**: If the sensor polarity is wrong, repair will be very difficult!
Please carefully confirm that it's inserted in the correct orientation and from the correct direction before soldering!
Match the notch indicating pin 1 of the IC with the [1pin] silk on the board.

![91](images/kbp_091.jpg)

The IC looks like this from the back.
Solder all pins from the front side where SMD components are mounted (the side without the Keyball logo).

![92](images/kbp_092.jpg)

Use tweezers to peel off the protective seals [2 pieces].

![93](images/kbp_093.jpg)

Attach the sensor lens to the side where the protective seals were peeled off.
The lens has direction, and if the direction is wrong, the two thin pins of the lens may break, so please check the direction carefully.
There's a protrusion like the arrow in the photo below at the front of the lens, and this should be on the top side when mounting.

![95](images/kbp_095.jpg)

If the lens and IC directions match, the two pins of the lens should insert into the IC without force. Please insert slowly.

![94](images/kbp_094.jpg)

<a id="anchor4-2"></a>
### 4-2. Soldering the L-shaped Connector
Next, install the L-shaped connector pin on the **front side** of the board where the trackball will be mounted.
The L-shaped connector also has direction.
Insert the side where the pins are not U-shaped into the middle board for soldering.

![96](images/kbp_083.jpg)

Apply masking tape or similar to prevent parts from floating and solder from the back side.

![97](images/kbp_084.jpg)

Next, solder the 4 jumpers for optical sensor signal lines.
>**⚡️Warning**: There are jumpers near the soldered connector, so apply solder to **only the back side** and short them as shown in the photo below.

![97](images/kbp_085.jpg)

<a id="anchor5"></a>
## 5. Soldering the Left-Right Detection Jumper on the Left Side

>**⚡️Warning**: The standard Keyball+ firmware has a function to automatically detect the left/right of the keyboard.
For detection, solder a jumper at **one location only on the left side board**.

When looking at the left side board from the back, there's a **LEFT** silk as shown in the red circle in the photo below.
Please solder the jumper next to this to short it.

![140](images/kbp_086.jpg)

If mounting the trackball on the left side, the position is slightly different, and the LEFT jumper will be at the position shown in the photo below.

>**⚡️Warning**: Be sure to jumper **only the left side board**.

![141](images/kbp_087.jpg)

The soldering work is now complete.

As a side note, before turning off the soldering iron, apply plenty of solder to the tip. When you use it next time, if you remove this solder, you can resume work with a shiny tip!

![100](images/kbp_096.jpg)

<a id="anchor6"></a>
## 6. Cutting the Top Plate (Optional)

The top plate has sections that can be separated along a perforation only if you need to.
If you are combining MX and Choc switches, cut along the perforation.
When cutting, use a cutter to score the perforation on both the front and back sides, then fold to separate, and polish the cut edge with about 150 grit sandpaper.

### ① Remove one right-hand thumb key (make it a 38-key board)

<!-- TODO: add a Keyball+ photo showing where the right-hand thumb key is separated -->
You can separate the **thumb key closest to the trackball**, on the trackball side.
This is an option for people whose thumb hits this key while operating the trackball.
After separating it, the board has **38 keys**. The LED at that position is separated together with the key, so if you install LEDs the trackball side has one fewer, for **54 in total**.
In that case you only need **38** key switches and **38** keycaps. The key socket at that position is unused even if soldered, so you may skip it.

### ② Choc thumb section with MX everywhere else

You can build the thumb section with Choc switches and the rest with MX switches (the reverse combination is also possible, but this is the only practical switch mix).
In that case the thumb section (Choc = 4mm spacer) and the rest (MX = 7mm spacer) end up at different top-plate heights, so separate the thumb section along the perforation.
**If you build with all MX or all Choc switches, this cut is not needed.**

Since every key position has a fixed switch type in this build, you can use **"Choc + LED" for the thumb keys and "MX + LED" for the rest** to fit an under-key LED at every position (55 total; see the combinations in [Chapter 3-3](#anchor3-3)).

![101](images/kbp_100.jpg)

Polish the cut surface with about 150 grit sandpaper.

![102](images/kbp_102.jpg)

<a id="anchor7"></a>
## 7. Assembly

<a id="anchor7-1"></a>
### 7-1. Installing the Protection Plate

Install the ProMicro protection plate on the middle board.

First screw the 9mm spacer, then screw the acrylic protection plate to it.

The protection plate shape is common for both trackball and non-trackball sides. There's no front/back.

![111](images/kbp_104.jpg)

<a id="anchor7-2"></a>
### 7-2. Assembling the Top Plate

Screw the spacer to the **back side** of the top plate.
Use the **7mm** spacers for an MX build, or the **4mm** spacers for a low-profile (Choc) build (12 pieces total for both sides).

![112](images/kbp_107.jpg)

First, insert key switches into the four corners of the top plate. This improves the positioning accuracy between plates.

For an MX build, match the screw holes of the top plate and middle acrylic plate, and stack the plates.

![113](images/kbp_108.jpg)

Next, also match the screw holes of the soldered middle board, and stack while confirming that the key switch terminals fit firmly into the key sockets.

![114](images/kbp_112.jpg)

Once the plates are stacked, **install all the remaining key switches** (38 for a 38-key build). Push each switch straight down from the top-plate side, checking that the terminals don't bend, and confirm on the back of the middle board that both terminals came out of the socket. You need every switch installed at this stage so you can check key input in [Chapter 7-3](#anchor7-3).

<a id="anchor7-3"></a>
### 7-3. Writing the Firmware and Checking Operation

Now that the key switches are installed, write the firmware and check key input and LED operation.
**Once the bottom plate is attached you can no longer reach the ProMicro, LEDs, or the back of the boards, so check at this stage.**

Keyball+ has no test-only firmware like Keyball39. You write the production firmware from [Keyball Link](https://keyball-link.shiroganelab.com/).
There are two versions, a **standard version** and an **LED version**: choose the **LED version if you installed LEDs, or the standard version if you did not** (the standard version does not light LEDs but lets you use more features).
Keyball+ firmware is common regardless of which side the trackball is mounted on.

Open Keyball Link, connect Keyball+ to your PC with a USB cable, and follow the on-screen instructions to write (FLASH) the firmware.
If the keyboard is not recognized even with the USB cable connected, try pressing the soldered RESET switch quickly twice.
※Be sure to write the same firmware version to both left and right Pro Micros.

When writing is done, open a text editor and **press every key one by one to confirm it registers correctly**.
If left and right are reversed, re-check the left-right detection jumper in [Chapter 5](#anchor5). If a key does not respond, redo the soldering of that key's socket and diode.

![82](images/kbp_073.jpg)

If you installed LEDs, also check that they light up.
LEDs are wired in series, so it's easy to identify a problem area if only some light up.
For example, if LEDs up to number 12 light up but number 13 onward do not, the soldering of [LED 12 or 13] is likely at fault, so redo those. If that does not help, replace LED 13.
Repeat the lighting check and soldering correction until all LEDs light up.

If you want to directly edit Keyball+ firmware and build it yourself, use the [keyball-plus-firmware repository](https://github.com/ineno771/keyball-plus-firmware) (see [Chapter 10](#anchor10)).

<a id="anchor7-4"></a>
### 7-4. Assembling the Bottom Plate

Once the operation check is done, peel off the protective sheet of the acrylic bottom plate, place it on the back of the main body, and screw it.
Next, attach cushion rubber to the four corners of the keyboard back.

<a id="anchor8"></a>
## 8. Installing the Trackball

<a id="anchor8-1"></a>
### 8-1. Inserting the Ball Reading Board

Insert the assembled trackball reading board into the 7-pin connector.
Insert the board vertically.

![120](images/kbp_114.jpg)

<a id="anchor8-2"></a>
### 8-2. Assembling the Trackball Case

The trackball case has 3 ceramic balls pre-fixed.
If ceramic balls happen to fall off, please fix the spare ceramic ball with appropriate bond.
Please keep the spare ceramic ball for future use in case you lose the ball.

Shake the case to check that the ceramic balls don't fall off.

![122](images/kbp_122.jpg)

The two pins on the case top can be inserted into the hole in the case bottom.
Apply force slowly from top and bottom to combine. (It doesn't need to fit perfectly as it will stick together with the subsequent screw tightening.)

![123](images/kbp_123.jpg)

Attach M1.7 tapping screws.
The kit includes **small head screws** and **flat head screws**, but use the **small head screws**.

![124](images/kbp_124.jpg)

From the back of the case, screw these 2 locations.
>**⚡️Warning**: Be careful not to overtighten.

![125](images/kbp_125.jpg)

<a id="anchor8-3"></a>
### 8-3. Installing the Trackball Case

Install the completed case to the main body.
The ball board goes into the sensor storage area on the back of the case.
While making sure the ball board shown by the arrow is around the center of the case, slowly fit it from above.
If there's resistance, don't force it in, but pull it out once and try inserting again.

It should go all the way in without much force.

![126](images/kbp_127.jpg)

When checking from the back of the main body, there may be a gap as shown by the arrow between the main board and ball board.

![128](images/kbp_129.jpg)

In that case, gently push from the front of the case (in the direction of the finger mark).
Applying too much force may damage the L-shaped connector, so push gently.
When the gap disappears as shown in the photo below, the screw holes in the blue circle should match.

![129](images/kbp_130.jpg)

Tighten the **flat head screws** 2 pieces of M1.7 torx screws included in the kit from the back of the main body.
At this time, hold the ball holding case with your finger to prevent it from rotating while tightening the screws.

<a id="anchor9"></a>
## 9. Final Assembly

Almost complete! Finish by pushing in the 34mm trackball and fitting your keycaps!
Thank you for your hard work.

![132](images/kbp_135.jpg)

<!-- TODO: replace with a photo of the completed Keyball+ -->
![Keyball+ completed](images/kbp_136.jpg)

<a id="anchor10"></a>
## 10. Changing the Keymap / Updating the Firmware

The firmware was already written in [Chapter 7-3](#anchor7-3). This chapter is for reference when you later change the keymap or re-flash the firmware to a newer version.

The Keyball+ keymap can be changed and flashed from your browser with the dedicated web tool **[Keyball Link](https://keyball-link.shiroganelab.com/)**. No special software installation is required.

If you re-flash the firmware, mind the **standard version** vs **LED version**.
Choose the **LED version if you soldered the LEDs, or the standard version if you did not** (if you flash the LED version without any LEDs installed, capacity is spent on unused LED control and some features available in the standard version are dropped).

>**⚡️Warning**: Be sure to write the same firmware version to both left and right Pro Micros. The keymap is written to the ProMicro on the side where the USB cable is connected.

**If you want to build firmware yourself**
The latest Keyball+ firmware is published in the [keyball-plus-firmware repository](https://github.com/ineno771/keyball-plus-firmware).
Copy the `keyboards/keyball` folder from the repository to your QMK Firmware `keyboards` directory and freely edit keymaps etc. to build.

<a id="anchor11"></a>
## 11. How to Use Keyball+♪
   - The trackball changes to up/down/left/right scroll while switched to the scroll layer.

   - [Keyball Link](https://keyball-link.shiroganelab.com/) allows easy keymap checking, changing, and writing.

   - USB cable can be inserted into either left or right side.
   However, keymaps are written to the ProMicro on the side where the USB cable is inserted, so please review the keymap when switching for the first time.

   - Specially prepared keycodes for the Keyball series are available.
   They can be used to change the trackball to scroll, or change cursor speed and scroll speed.

   >**⚡️Warning**: Disconnecting the TRS cable while Keyball is connected to PC (powered on) can cause malfunction.
   When disconnecting/connecting the TRS cable, always disconnect the USB cable first.

This concludes the Keyball+ build guide.
For questions or issues about Keyball+, please post to the [Yowkees/keyball Discussions](https://github.com/Yowkees/keyball/discussions).
We will respond as quickly as possible.

―Acknowledgments―
The Keyball+ firmware is based on the Keyball39 firmware. Thanks to the tremendous cooperation of [KoRoN@Kaoriya](https://www.kaoriya.net/), the Keyball39 firmware has significantly improved trackball operation smoothness, and the substantial memory reduction allows enjoyment of many LED actions. I would like to express my deep gratitude here. Thank you very much.
　@Yowkees
