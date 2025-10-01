import os
import sys

from ShowData import ShowData
from AppConstructor import AppConstructor
from package import Randomizer

# Creating .exe
# python -m PyInstaller -pyinstaller EpisodeSelector.py --onefile -w

class App(AppConstructor):
    def __init__(self, data):
        super().__init__("Episode Selector", [600, 600], data)

        self.bind_all('<Button>', self.change_focus)

        self.show_frame(Randomizer)

        self.protocol("WM_DELETE_WINDOW", self.close)

        self.mainloop()

    def close(self):
        self.data.save()
        sys.exit()

    def change_focus(*args):
        try:
            if len(args) == 2:
                args[1].widget.focus_set()
        except AttributeError:
            pass


if __name__ == "__main__":
    if not os.path.isdir("Data"):
        os.makedirs("Data")
        open('Data\\show_data.txt', 'w')
        open('Data\\system_data.txt', 'w')
        open('Data\\seen_shows_data.txt', 'w')

    App(ShowData())