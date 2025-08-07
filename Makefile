default:
	yt-dlp -f mp4 https://www.youtube.com/watch?v=9lNZ_Rnr7Jc -o original_badapple.mp4
	ffmpeg -i original_badapple.mp4 badapple.mp3

	# change the scale HERE for other resolutions VVV
	ffmpeg -i original_badapple.mp4 -vf "scale=114:88" -c:a copy mini_badapple.mp4

	ffmpeg -i mini_badapple.mp4 -vf "lutyuv='u=128:v=128:y=if(gte(val,128),255,0)'" badapple.mp4
	mkdir imgs
	ffmpeg -i badapple.mp4 "imgs/frame_%d.png"
	rm -f original_badapple.mp4 badapple.mp4 mini_badapple.mp4
	cc main.c -o badapple -lpng

clean:
	rm -f badapple