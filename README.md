# Multi-audio
this is a server on Raspberry pi who allow a client to call via RAW socket to send a sound via a json

i use 4 simples soundcards, 4amp, 8 speaker and a RPI 4.

this project use [RTaudio](https://github.com/thestk/rtaudio/tree/57c2c9d7598a783a5167422cd744f4d3797141bb), [json](https://github.com/nlohmann/json) and [AudioFile](https://github.com/mpruett/audiofile)

to compile it do : 

> g++ -Wall -D__LINUX_ALSA__ -o multiaudio3 multispk.cpp spk.cpp engine.cpp Vecteur3d.cpp AudioFile.o RtAudio.o -lasound -lpthread -Wno-psabi


multispk.cpp is the main file

spk.cpp control the speaker

engine.cpp controle the process for 3D sound and the client ask



you can clone the git and do :

use to config.conf file to add sound (wav 44,100 16bit) like this :

> audio=foo.wav;bar.wav; (many.wav) .....

each sound take respectivly an id foo.wav will be the 0 bar.the 1 etc ... 

> ./multiaudio3

it start a server 


to try it use putty in a RAW channel 

for launch a sound tape [ispos,idbuffer,command,loop,[posx,posy,posz]]

ispos : if ispos = 255 the sound will be launch everywhere 
        else  use posx, posy, and posz as double.

idbuffer : the buffer of the sound.

command  : P for play or S to stop.

loop : if loop is 0 the sound will loop.

[posx,posy,posz] : the postion of the sound

exemple : 
> [255,0,"P",1]  //Play the sound

> [255,0,"S",1]  //Stop the sound

> [0,0,"P",1,[1,1.4,1.2]]  //Play the sound in a position define by [posx,posy,posz]

> [255,0,"S",1] //Stop the sound again

