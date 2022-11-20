from pyautogui import *
import pyautogui
import time
import keyboard
import random
import win32api, win32con

time.sleep(2)

def click(x,y):
    win32api.SetCursorPos((x,y))
    win32api.mouse_event(win32api.MOUSEEVENTF_LEFTDOWN,0,0)
    win32api.mouse_event(win32api.MOUSEEVENTF_LEFTUP,0,0)

while keyboard.is_pressed('q') == False:
    pic = pyautogui.screenshot(region=(394,288,603,423))

    width, height = pic.size

    for x in range(0,width,5):
        for y in range (0, height, 5):
            #Cores do centro: (255, 219, 195)
            r,g,b = pic.getpixel((x,y))

            if b == 195 and r == 255 and g == 219:
                if b == 195:
                    click(x+394,y+288)
                    time.sleep(0.05)
                    break