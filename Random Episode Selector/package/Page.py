import ttkbootstrap as ttk

class Page(ttk.Frame):
    def __init__(self, parent):
        super().__init__(parent)
        self.place(x=0, y=0, relheight=1, relwidth=1)
        self.app = parent
        self.data = parent.data
        self.create_page_buttons()
