import tkinter as tk
import ttkbootstrap as ttk

from package import *

class AppConstructor(ttk.Window):
    def __init__(self, title, geometry, data):
        super().__init__(themename="darkly")
        self.title(title)
        self.__create_screen_size(geometry)
        self.minsize(geometry[0], geometry[1])

        self.data = data

        self.frames = {}
        for F in (Randomizer, FileManagement):
            self.frames[F] = F(self)

    def __create_screen_size(self, geometry):
        '''Sets geometry of window and centers on screen'''
        dy = (self.winfo_screenheight() - geometry[1]-80)//2
        dx = (self.winfo_screenwidth() - geometry[0])//2

        self.geometry(f'{geometry[0]}x{geometry[1]}+{dx}+{dy}')

    def show_frame(self, page):
        frame = self.frames[page]
        frame.update()
        frame.tkraise()