#!/usr/bin/env python3

# NOTE: this example requires PyAudio because it uses the Microphone class

import speech_recognition as sr
import serial, time

arduino = serial.Serial('COM3', 9600, timeout = 1)
time.sleep(1)

def write(text):
    arduino.write(bytes(text, "UTF-8"))

def main():
    # obtain audio from the microphone
    r = sr.Recognizer()
    with sr.Microphone() as source:
        print("Say something!")
        audio = r.listen(source)

    # recognize speech using Sphinx
    try:
        text = r.recognize_sphinx(audio)
        print(text)
        good = input("Is this what you wanted to input? (Y/N)")
        if good.lower() == "y":
            write(text)
            input("Press enter to try again")
        elif good.lower() == "n":
            tipe = input("Would you like to manually enter text (Y) or try again (N)?")
            if tipe.lower() == 'y':
                text = input()
                write(text)
                input("Press enter to try again")
        main()
    except sr.UnknownValueError:
        print("Sphinx could not understand audio")
    except sr.RequestError as e:
        print("Sphinx error; {0}".format(e))
main()
