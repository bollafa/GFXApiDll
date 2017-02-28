# GFXApiDll / Banana Splitter
GFX Api , used in Banana Splitter, is the first in-game splitter available! ( that I know ;) ) !!!!!!!!
Now, you dont need to play the game in windowed mode and have the splitter next to you, you can play in fullscreen, YES IN FULLSCREEN!!!
![](https://puu.sh/unGqi/8e90c59d81.jpg)

![](https://puu.sh/um2kR/ed09b55d58.jpg)

# How to use ?
Banana splitter is not the regular .exe you are used to , it's a dll - and as I dont know if my target readers know about this topic, I will assume you don't - . It is a dll because it needs to live within the target process - kinda like a parasite - and then it is able to hook the drawing functions of the game and it's able to draw text!.

Dlls can't be started like a regular executable, you need to inject into the target process.

How to do this you ask? Well it is really easy in practice, use an injector that you like - eventually I will make my own injector just for BananaSplitter, but I wanted to release Banana splitter earlier so you can enjoy it now ! :) - Anyhow, like I was saying, use an injector that you like , personally I recommend Extreme Injector v3.3 by master131 , it's the one I use and I love it, it is fast , clean, small , and you dont need to select the process everytime you restart it. 

# Games / Graphics Library supported
As of now, Banana Splitter supports:
- DirectX 9.0
- Directx 11.0

# HOW TO CONTROL

When you inject the dll, you'll see at your left a timer set at 0 , 00:00:0 .
And the Dll will create a folder at Documents, called BananaSplitter. ( My Documents \ BananaSplitter )
Inside it, there will be 2 files, (if everything went OK ) :
**GameTimer.txt** : Here you can put the name of each checkpoint that you want to see ingame for example

```
First Boss
Second Boss
Gwyn ( Last Boss )
```


(etc. , you get the idea)

and another file:

**Config.txt** : There will be 3 comments, put the RGBA color in the order specified below each comment, ranging from 0-255

######Hint Color
**_R,G,B,A_**
######LapColor
**_R,G,B,A_**
######Current time color
**_R,G,B,A_**

The **controls** in game are as follows: 
- space : pause / start
- Numpad 0 : add split (when you get to your checkpoint press this key)
- Numpad 7 : Save ( saves the run in `Documents\BananaSplitter\Game _GameName_ _Numberofmilliseconds_ .txt ` )
- Numpad 4:  Move timer leftways.
- Numpad 6 : Moves timer rightways.
- Numpad 8 : moves timer upways.
- Numpad 2 : moves timer down.
- Numpad 3 : Reload GameTimer.txt

# TODOS

Support  OpenGL , DirectX 10 and earlier versions of DirectX9 , Vulkan and Mantle.

Custom loader/injector with more customizable options :)

# KNOWN ISSUES

Darksouls 1 for some reason is a special snowflake, so for DarkSouls 1 and **other special snowflake games that use DirectX9** use the BananaSplitterAlternative.dll (doesnt matter wheter it is x64 , or x86 , just make sure the target process is the same architecture)

# Checked Games

**Games that I have checked under _windows 7_ that work ** 
- Darksouls III
- Darksouls II : Scholar of the first sin
- Darksouls I  : ( with the alternative Dll)
- Supremme Commander I : ( Supremme commander speedrun?? :D it works tho :D )

I really dont have any other game that I can check, so , if it doesnt work in your game PLEASE LET ME KNOW.

# DISCLAIMER
I dont take the responsibility of you getting banned for using this in online games, if you want to speed run in Steam **_remember to play in offline mode_** . Just remember to play in offline mode.
# Credits

The most important section, yet I dont know why everybody leaves this at the end, or doesnt read it at all.
Firstly , I want to say a HUUUUUUUUUUUUUUUUUUGE thanks to **Tsuda Kageyu** the original autor of **MinHook - The Minimalistic API Hooking Library for x64/x86** , it's what makes this program work, without it, this wouldn't even exist.

Then, StackOverflow and every user on it as they have helped a lot, a LOT.
FW1FontWrapper for the amazing font api!! :D

Lastly but now in any way worse: **Unknowncheats.me** the greatest forum and community I've ever seen, I want to thank specially  **evolution536** for his tutorials on x64 hooking and Direct3d11 hooking.

I almost forgot, the humongously great MSDN Documentation, holy damn, it has helped. 


Thanks for taking your time to read this!



