import customtkinter

class BooleanPopUp(customtkinter.CTkToplevel):
    def __init__(self, parent, title, message):
        super().__init__(parent)
        self.__create_screen_size([300, 150])
        self.title(title)
        self.resizable(False, False)

        self.rowconfigure((0, 1), weight=1)
        self.columnconfigure((0, 1), weight=1, uniform='y')

        self.confirmed = None

        message_label = customtkinter.CTkLabel(self, text=message, wraplength=200)
        yes_button = customtkinter.CTkButton(self, text="Yes", command=self.on_yes)
        no_button = customtkinter.CTkButton(self, text="No", command=self.on_no)

        message_label.grid(row=0, column=0, columnspan=2)
        yes_button.grid(row=1, column=0)
        no_button.grid(row=1, column=1)

        # Make the popup modal
        self.grab_set()
        self.focus_set()
        self.wait_window()

    def on_yes(self):
        self.confirmed = True
        self.destroy()

    def on_no(self):
        self.confirmed = False
        self.destroy()

    def __create_screen_size(self, geometry):
        '''Sets geometry of window and centers on screen'''
        dy = (self.winfo_screenheight() - geometry[1]-80)//2
        dx = (self.winfo_screenwidth() - geometry[0])//2

        self.geometry(f'{geometry[0]}x{geometry[1]}+{dx}+{dy}')