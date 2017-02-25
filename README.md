# GFXApiDll / Banana Splitter
GFX Api , used in Banana Splitter, is the first in-game splitter available! ( that I know ;) ) !!!!!!!!
Now, you dont need to play the game in windowed mode and have the splitter next to you, you can play in fullscreen, YES IN FULLSCREEN!!!
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
