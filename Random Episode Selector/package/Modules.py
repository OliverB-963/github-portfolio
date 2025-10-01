import random

import tkinter as tk
import ttkbootstrap as ttk

from .Page import Page
from .BooleanPopUp import BooleanPopUp


def error_message_grid(parent, _text, _width, row_col, sticky_='', columnspan_=1, error=True, bg_colour='#222222', timedelay=4000):
    if error:
        message_temp = tk.Message(parent, text=_text, width=_width, fg="red", background=bg_colour)
    else:
        message_temp = tk.Message(parent, text=_text, width=_width, fg='white', background=bg_colour)
    message_temp.grid(row=row_col[0], column=row_col[1], columnspan=columnspan_, sticky=sticky_)
    parent.after(timedelay, message_temp.destroy)

def validate_entry(combobox: ttk.Combobox, associated_var: ttk.Variable):
    if type(associated_var) == ttk.StringVar:
        if associated_var.get() not in combobox["values"]:
            associated_var.set("")
    else:
        try:
            if str(associated_var.get()) not in combobox["values"]:
                associated_var.set(0)
        except tk.TclError:
            associated_var.set(0)


class Randomizer(Page):
    def __init__(self, parent):
        super().__init__(parent)

        self.create_widgets()
        self.create_page_buttons()

    def update(self):
        self.show_title_combo['values'] = self.data.get_show_names()

    def create_widgets(self):
        def load_show():
            current_show = self.show_title_string.get()
            if not self.data.show_exists(current_show):
                return

            self.season_total_label["text"] = "Seasons - " + str(self.data.get_shows_seasons_num(current_show))
            self.episode_total_label["text"] = "Total Episodes - " + str(self.data.get_shows_seasons_total(current_show))
            self.data.change_current_show(current_show)

        def randomise_generator():
            current_show = self.show_title_string.get()

            if not self.data.show_exists(current_show):
                error_message_grid(self, "No show currently loaded", 200,
                                        [5, 1], sticky_='s', columnspan_=2)
                return
            
            self.random_episode = self.randomise(current_show)
            if self.random_episode is None:
                error_message_grid(self, "No episodes available", 200,
                                    [5, 1], sticky_='s', columnspan_=2)
                return

            season_num_label["text"] = "Season " + str(self.random_episode[0])
            epsiode_num_label["text"] = "Episode " + str(self.random_episode[1])

        def mark_as_watched():
            if self.random_episode is None:
                error_message_grid(self, "No episode currently loaded", 200,
                                    [5, 1], sticky_='s', columnspan_=2)
            else:
                error_message_grid(self, "Episode marked as watched", 200,
                                    [5, 1], sticky_='s', columnspan_=2, error=False)
                
                self.data.change_episode_watched(
                    self.show_title_string.get(),
                    self.random_episode[0] - 1,
                    self.random_episode[1] - 1,
                    1
                )

        self.rowconfigure((0, 1, 2, 3, 4, 5), weight=1, uniform='x')
        self.columnconfigure((0, 1, 2, 3), weight=1, uniform='y')

        self.random_episode = None
        self.show_title_string = tk.StringVar(value=self.data.get_current_show())

        self.title_label = ttk.Label(self, text="Randomiser", font="calibri 25")
        self.show_title_combo = ttk.Combobox(self, values=self.data.get_show_names(), textvariable=self.show_title_string)
        self.show_title_combo.bind("<<ComboboxSelected>>", lambda e: load_show())
        self.show_title_combo.bind("<FocusOut>", lambda e: validate_entry(self.show_title_combo, self.show_title_string))

        self.season_total_label = ttk.Label(self, text="Seasons")
        self.episode_total_label = ttk.Label(self, text="Total Episodes")

        randomize_button = ttk.Button(self, text="Randomize!", command=randomise_generator)

        season_num_label = ttk.Label(self, text="Season")
        epsiode_num_label = ttk.Label(self, text="Episode")
        confirm_watched_button = ttk.Button(self, text="Watched", command=mark_as_watched)

        self.title_label.grid(row=0, column=0, columnspan=4)
        self.show_title_combo.grid(row=1, column=1, columnspan=2)
        randomize_button.grid(row=3, column=1, columnspan=2)

        self.season_total_label.grid(row=2, column=1)
        self.episode_total_label.grid(row=2, column=2)
        season_num_label.grid(row=4, column=1, padx=[0, 10])
        epsiode_num_label.grid(row=4, column=2, padx=[10, 0])
        confirm_watched_button.grid(row=4, column=1, columnspan=2)

        self.load_show_info()

        watermark_label = ttk.Label(self, text="\u00A9 2025 Oliver Bailey", padding=5)
        watermark_label.grid(row=5, column=3, sticky='se')

    def create_page_buttons(self):
        file_button = ttk.Button(self, text="Files", command= lambda: self.app.show_frame(FileManagement))
        file_button.grid(row=5, column=0, columnspan=2, sticky='sw')

    def load_show_info(self):
        current_show = self.show_title_string.get()
        if not self.data.show_exists(current_show):
            return
        
        self.season_total_label["text"] = "Seasons - " + str(self.data.get_shows_seasons_num(current_show))
        self.episode_total_label["text"] = "Total Episodes - " + str(self.data.get_shows_seasons_total(current_show))

    def randomise(self, current_show):        
        seasons = self.data.get_seen_shows_seasons(current_show)
        available_episodes = []

        for i in range(len(seasons)):
            if len(seasons[i]) > 0:
                for j in range(len(seasons[i])):
                    if seasons[i][j] == 0:
                        available_episodes.append([i + 1, j + 1])

        if len(available_episodes) == 0:
            return None

        rand_num = random.randint(0, len(available_episodes) - 1)

        return available_episodes[rand_num]


class FileManagement(Page):
    def __init__(self, parent):
        super().__init__(parent)  

        self.create_widgets()
        self.create_page_buttons()

    def update(self):
        self.shows_combobox["values"] = self.data.get_show_names()

    def create_page_buttons(self):
        randomizer_button = ttk.Button(self, text="Return to Randomizer", command= lambda: self.app.show_frame(Randomizer))
        randomizer_button.grid(row=4, column=0, columnspan=2, sticky='sw')

    def create_widgets(self):
        self.rowconfigure((0, 1, 2), weight=1, uniform='x')
        self.rowconfigure(3, weight=2, uniform='x')
        self.rowconfigure(4, weight=3, uniform='x')
        self.columnconfigure((0, 1), weight=1, uniform='y')

        self.current_show_string = tk.StringVar()
        self.season_num_int = tk.IntVar()
        self.season_selection_int = tk.IntVar()
        self.episodes_num_int = tk.IntVar()
        self.added_show_string = tk.StringVar()
        self.changing_watched_boolean = tk.BooleanVar(value=False)

        title_label = ttk.Label(self, text="Tv Show Management", font='calibri 25 underline')

        selection_frame = self.create_show_selection_frame()      

        add_frame = self.create_add_show_frame()  

        edit_frame = self.create_edit_frame()

        title_label.grid(row=0, column=0, columnspan=2)
        selection_frame.grid(row=1, column=0, rowspan=2, sticky='ns')
        add_frame.grid(row=1, column=1, rowspan=2, sticky='nsew')
        edit_frame.grid(row=3, column=0, columnspan=2, sticky='nsew')

        watermark_label = ttk.Label(self, text="\u00A9 2025 Oliver Bailey", padding=5)
        watermark_label.grid(row=4, column=1, sticky='se')

    def create_show_selection_frame(self) -> ttk.Frame:
        def load_show():
            season_num = self.data.get_shows_seasons_num(self.current_show_string.get())
            self.season_num_int.set(season_num)

            self.update_seasons_selection()

        def change_season_num_pressed(event):
            if event.x < 180:
                return 
            
            change_season_num_entered()

        def change_season_num_entered():
            current_show = self.current_show_string.get()
            old_season_num = self.data.get_shows_seasons_num(self.current_show_string.get())

            try:
                self.season_num_int.get()
            except tk.TclError:
                self.season_num_int.set(old_season_num)

                error_message_grid(self, "Invalid entry!", 200,
                                    [4, 0], sticky_='s', columnspan_=2)
                return
            
            if self.season_num_int.get() < 0:
                self.season_num_int.set(old_season_num)

                error_message_grid(self, "Invalid entry!", 200,
                                    [4, 0], sticky_='s', columnspan_=2)
                return

            if current_show == '':
                error_message_grid(self, "No show currently selected", 200,
                                    [4, 0], sticky_='s', columnspan_=2)
                return
            
            self.data.set_seasons(self.current_show_string.get(), self.season_num_int.get())
            
            self.update_seasons_selection()

            message = f"The show {current_show} now has {self.data.get_shows_seasons_num(current_show)} seasons"
            error_message_grid(self, message, 200,
                                [4, 0], sticky_='s', columnspan_=2, error=False)

        selection_frame = ttk.Frame(self)
        selection_frame.rowconfigure((0, 1, 2, 3), weight=1, uniform='x')

        shows_label = ttk.Label(selection_frame, text="Select Show")
        self.shows_combobox = ttk.Combobox(selection_frame, values=self.data.get_show_names(), textvariable=self.current_show_string)
        self.shows_combobox.bind("<<ComboboxSelected>>", lambda e: load_show())
        self.shows_combobox.bind("<FocusOut>", lambda e: validate_entry(self.shows_combobox, self.current_show_string))


        seasons_label = ttk.Label(selection_frame, text="Set number of seasons")
        self.seasons_spinbox = ttk.Spinbox(selection_frame, from_=0, to=50, textvariable=self.season_num_int)
        self.seasons_spinbox.bind("<Return>", lambda e: change_season_num_entered())
        self.seasons_spinbox.bind("<ButtonRelease>", change_season_num_pressed)

        shows_label.grid(row=0)
        self.shows_combobox.grid(row=1)
        seasons_label.grid(row=2)
        self.seasons_spinbox.grid(row=3)

        return selection_frame
    
    def create_add_show_frame(self) -> ttk.Frame:
        def add_show():
            show_name = self.added_show_string.get()

            if show_name not in self.data.get_show_names():
                self.data.add_show(show_name)
                error_message_grid(self, "Show added to database", 200,
                                    [4, 0], sticky_='s', columnspan_=2, error=False)
                self.update()
            else:
                error_message_grid(self, "Show already found in database", 200,
                                    [4, 0], sticky_='s', columnspan_=2)
                
        def delete_show():
            show_name = self.added_show_string.get()

            if show_name not in self.data.get_show_names():
                error_message_grid(self, "Show not found in database", 200,
                                    [4, 0], sticky_='s', columnspan_=2)
                return
                
            confirmation_popup = BooleanPopUp(self, "Confirmation Popup", 
                "Are you sure you want to delete the show? All information will be permanently deleted!")
            
            if confirmation_popup.confirmed:
                self.data.delete_show(show_name)
                error_message_grid(self, "Show deleted from database", 200,
                                    [4, 0], sticky_='s', columnspan_=2, error=False)
            
            self.added_show_string.set("")

        add_frame = ttk.Frame(self)
        add_frame.rowconfigure((0, 1, 2), weight=1)
        add_frame.columnconfigure((0, 1), weight=1, uniform='y')

        title_label = ttk.Label(add_frame, text="Add/Delete Shows")
        show_name_entry = ttk.Entry(add_frame, textvariable=self.added_show_string)
        add_button = ttk.Button(add_frame, text="add", command=add_show)
        delete_button = ttk.Button(add_frame, text="delete", command=delete_show)

        title_label.grid(row=0, column=0, columnspan=2)
        show_name_entry.grid(row=1, column=0, columnspan=2)
        add_button.grid(row=2, column=0)
        delete_button.grid(row=2, column=1)

        return add_frame

    def create_edit_frame(self) -> ttk.Frame:
        def change_episode_num():
            try:
                episode_value = self.episodes_num_int.get()    
            except tk.TclError:
                self.episodes_num_int.set(0)

                error_message_grid(self, "Invalid entry!!", 200,
                                    [4, 0], sticky_='s', columnspan_=2)
                episode_value = 2
                return
            
            if 0 > episode_value > 200:
                error_message_grid(self, "Invalid entry!!", 200,
                                    [4, 0], sticky_='s', columnspan_=2)
                return

            current_show = self.current_show_string.get()
            current_season = self.season_selection_int.get()

            if current_show == "":
                error_message_grid(self, "No show currently selected", 200,
                                    [4, 0], sticky_='s', columnspan_=2)
                return

            if current_season == 0:
                error_message_grid(self, "No season currently selected", 200,
                                    [4, 0], sticky_='s', columnspan_=2)
                return
                
            self.data.change_episode_value(current_show, current_season - 1, episode_value)

            message = f"Number of episodes in {current_show} season {current_season} now set to {episode_value}"
            error_message_grid(self, message, 200,
                                    [4, 0], sticky_='s', columnspan_=2, error=False)

        def mark_as_watched():
            if (self.current_show_string.get() == '' or self.season_selection_int.get() == 0
                or episode_selection_int.get() == 0):
                error_message_grid(self, "No episode currently selected", 200,
                                    [4, 0], sticky_='s', columnspan_=2)
            else:
                current_episode_value = self.data.get_episode_watched(
                    self.current_show_string.get(),
                    self.season_selection_int.get() - 1,
                    episode_selection_int.get() - 1
                )
                if current_episode_value:
                    message_addition = "not watched"
                else:
                    message_addition = "watched"
                error_message_grid(self, "Episode marked as " + message_addition, 200,
                                    [4, 0], sticky_='s', columnspan_=2, error=False)
                self.data.change_episode_watched(
                    self.current_show_string.get(),
                    self.season_selection_int.get() - 1,
                    episode_selection_int.get() - 1,
                    0 if current_episode_value else 1
                )

        def toggle_setting_watched():
            if self.changing_watched_boolean.get():
                confirm_button.grid_forget()
                episodes_num_spinbox.grid_forget()
                change_watched_button.grid(row=4, column=0, columnspan=2, sticky='n')

                update_episodes_combobox()
                episode_select_combobox.grid(row=1, column=1)  
            else:
                change_watched_button.grid_forget()
                episode_select_combobox.grid_forget()
                confirm_button.grid(row=1, column=0, columnspan=2)
                episodes_num_spinbox.grid(row=1, column=1)

        def update_episodes_combobox():
            if self.changing_watched_boolean.get() and self.current_show_string.get() != '':
                if self.season_selection_int.get() == 0:
                    return
                
                seasons_episodes = self.data.get_shows_seasons_episodes_num(self.current_show_string.get(),
                    self.season_selection_int.get() - 1) 

                episode_select_combobox["values"] = list(range(1, seasons_episodes + 1))

        edit_frame = ttk.Frame(self)
        edit_frame.columnconfigure((0, 1), weight=1)
        edit_frame.rowconfigure((0, 1), weight=1)

        episode_selection_int = tk.IntVar()

        title_label = ttk.Label(edit_frame, text="Edit Show", font="calibri 20 underline")
        self.season_select_combobox = ttk.Combobox(edit_frame, values=list(range(self.season_num_int.get())), textvariable=self.season_selection_int)
        self.season_select_combobox.bind("<<ComboboxSelected>>", lambda e: update_episodes_combobox())
        self.season_select_combobox.bind("<FocusOut>", lambda e: validate_entry(self.season_select_combobox, self.season_selection_int))
                
        episodes_num_spinbox = ttk.Spinbox(edit_frame, from_=0, to=100, textvariable=self.episodes_num_int)
        episode_select_combobox = ttk.Combobox(edit_frame, values=[], textvariable=episode_selection_int)
        episode_select_combobox.bind("<FocusOut>", lambda e: validate_entry(episode_select_combobox, episode_selection_int))

        confirm_button = ttk.Button(edit_frame, text="change", command=change_episode_num)
        change_watched_button = ttk.Button(self, text="Mark as Watched", command=mark_as_watched)
        change_to_watch_checkbox = ttk.Checkbutton(edit_frame, variable=self.changing_watched_boolean, command=toggle_setting_watched)

        title_label.grid(row=0, column=0, columnspan=2)
        self.season_select_combobox.grid(row=1, column=0)
        episodes_num_spinbox.grid(row=1, column=1)
        confirm_button.grid(row=1, column=0, columnspan=2)
        change_to_watch_checkbox.grid(row=1, column=0, sticky='w', padx=(15, 0))

        return edit_frame
    
    def create_name_frame(self, parent) -> ttk.Frame:
        frame = ttk.Frame(parent)
        frame.rowconfigure((0, 1), weight=1)

        return frame
    
    def update_seasons_selection(self):
        season_num = self.data.get_shows_seasons_num(self.current_show_string.get())
        self.season_select_combobox["values"] = list(range(1, season_num + 1))