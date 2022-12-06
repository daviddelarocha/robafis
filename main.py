"""
...
"""
# packages
from typing import Any
from tkinter import Tk, Frame, Button, Label

# modules
from conne_bt import BluetoothConnector
from manual import Manual
from auto import Auto


BTCONN = BluetoothConnector()

# Windows ---------------------------------------------------

#Create the GUI
class Index(Frame):
    """
    ...
    """
    def __init__(self, parent, controller):
        Frame.__init__(self, parent)
        self.controller = controller

        # send state confirmation
        self.controller.send_signal(0)

        label = Label(
            self,
            text="Select modality:",
            font=("Arial", 16)
        )
        label.pack(side="top", fill="x", pady=15)

        button1 = Button(
            self,
            text="Manual Control",
            command=lambda: controller.show_frame("Manual"),
            font=("Arial", 18)
        )
        button1.pack(padx=10, pady=5)
        button2 = Button(
            self,
            text="Automatic: Operational research",
            command=lambda: controller.show_frame("Auto"),
            font=("Arial", 18)
        )
        button2.pack(padx=10, pady=15)

# Root Window ---------------------------------------------------

class SampleApp(Tk):
    """
    ...
    """
    def __init__(self, *args, **kwargs):
        Tk.__init__(self, *args, **kwargs)

        self.btconnector = BTCONN
        # the container is where we'll pack the current page
        self.container = Frame(self)
        self.container.pack(side="top", fill="both", expand=True)
        self.current_frame = None

        self.show_frame("Index")

    def show_frame(self, page_name):
        '''Show a frame for the given page name'''

        # destroy the old page, if there is one
        if self.current_frame is not None:
            self.current_frame.destroy()

        # create the new page and pack it in the container
        cls = globals()[page_name]
        self.current_frame = cls(self.container, self)
        self.current_frame.pack(fill="both", expand=True)

    def send_signal(self, msg:Any) -> Any:
        """
        ...
        """
        self.btconnector.write(msg)
        print("send message: ", msg)

# Begin the GUI processing ---------------------------------------------------

root = SampleApp()
root.title("RobAFIS")
root.mainloop()
root.destroy()