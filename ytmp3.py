from pytube import YouTube
from moviepy.editor import *
import os

def download_and_convert_to_mp3(url, output_path):
    try:
        # Descargar el video de YouTube
        yt = YouTube(url)
        video = yt.streams.filter(only_audio=True).first()
        video.download(output_path=output_path, filename="temp_video.mp4")

        # Convertir el video a MP3
        video_path = output_path + "temp_video.mp4"
        audio_path = output_path + yt.title + ".mp3"
        video_clip = AudioFileClip(video_path)
        video_clip.write_audiofile(audio_path)

        # Eliminar el archivo de video temporal
        os.remove(video_path)

    except Exception as e:
        input(f"An error occured: {e}\n\nPress enter to exit... ")

if __name__ == "__main__":
    url = input("YouTube URL: ")
    output_path = "C:/Users/pey/Documents/ytmp3_output/"
    download_and_convert_to_mp3(url, output_path)
    os.startfile(output_path)

