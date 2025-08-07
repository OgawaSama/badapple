# Bad Apple!! on the Terminal with C

Very simple program to run [Bad Apple!!](https://www.youtube.com/watch?v=9lNZ_Rnr7Jc) on your terminal!  

Before running, you may choose your own resolution to display on the terminal, but be careful as high resolutions (equals or bigger than the original 920x760px) may not be displayed perfectly (because they occupy a lot of the terminal per line).  
If supported on your terminal emulator, zoom out and you may see the images correctly!  

## Requirements

* Some **Linux OS** (sorry, people, I didn't bother to port this elsewhere);
* **yt-dlp**, available on https://github.com/yt-dlp/yt-dlp;
* **ffmpeg**, available on https://ffmpeg.org/;
* **mpg123**, available on https://www.mpg123.de/;
* **C** and **gcc**.

## How to run

After pulling this repo, edit the Makefile to have your desired resolution (default is 114x88px) and run it with
```shell
Make
```
It will flood your terminal, but do not worry, it is only downloading and formatting the files needed for this. After they're downloaded, they'll be deleted, so no mess here either!  

It should create a file `badapple.mp3` with the audio and a folder `/imgs` with the needed video frames.  
Simply execute the generated `badapple` file and have fun!
```shell
./badapple
```

