# This project requires PyBluez
from time import sleep

from tkinter import Frame, Button, Label, Listbox, Variable, SINGLE

NODES_MAP:dict = {
    "N6": 4,
    "N8": 5,
    "M8": 6,
    "M10": 7,
    "M11": 8,
    "P1": 9,
    "P2": 10,
    "P3": 11
}

# Window ---------------------------------------------------

class Auto(Frame):
    """
    ...
    """
    def __init__(self, parent, controller):
        self.take_nodes = Variable(
            value=["N6", "N8", "M8", "M10", "M11"]
        )
        self.leave_nodes = Variable(
            value=["P1", "P2", "P3"]
        )
        Frame.__init__(self, parent)
        self.controller = controller

        # send state confirmation
        self.controller.send_signal(2)

        self.create_widgets()

    def create_widgets(self):
        """
        ...
        """
        self.__btn_return = Button(
            self,
            text = "return",
            command = lambda: self.controller.show_frame("Index"),
            font=("Arial", 18)
        ).grid(row=0, column=0, padx=10, pady=10)

        Label(
            self,
            text = "Automatic",
            font=("Arial", 22)
        ).grid(row=0, column=1, padx=5, pady=5)
        # label.pack(side = "top", fill = "x", pady = 10)

        ## LIST
        Label(
            self,
            text = "take plane Node: ",
            font=("Arial", 22)
        ).grid(row=1, column=0, padx=5, pady=5)
        self.__listbox_takeplane = Listbox(
            self,
            height=10,
            listvariable=self.take_nodes,
            selectmode=SINGLE,
            exportselection=0
        )
        self.__listbox_takeplane.grid(row=1, column=1, padx=10, pady=10)
        ## BTN
        self.__btn_send_takeplane = Button(
            self,
            text = "✓",
            command = self.send_takeplane,
            font=("Arial", 20)
        ).grid(row=1, column=2, padx=10, pady=10)
        ## LIST
        Label(
            self,
            text = "leave plane Node: ",
            font=("Arial", 22)
        ).grid(row=2, column=0, padx=5, pady=5)
        self.__listbox_leaveplane = Listbox(
            self,
            height=10,
            listvariable=self.leave_nodes,
            selectmode=SINGLE,
            exportselection=0,
        )
        self.__listbox_leaveplane.grid(row=2, column=1, padx=10, pady=10)
        ## BTN
        self.__btn_send_leaveplane = Button(
            self,
            text = "✓",
            command = self.send_leaveplane,
            font=("Arial", 20)
        ).grid(row=2, column=2, padx=10, pady=10)
        ##
        self.__btn_clear = Button(
            self,
            text = "clear",
            command = lambda: self.controller.send_signal(1),
            font=("Arial", 25)
        ).grid(row=3, column=0, padx=10, pady=10)
        ##
        self.__btn_launch = Button(
            self,
            text = "launch",
            command = self.launch_auto,
            font=("Arial", 25)
        ).grid(row=3, column=1, padx=10, pady=10)
        ##
        self.__btn_stop = Button(
            self,
            text = "stop",
            command = lambda: self.controller.send_signal(3),
            font=("Arial", 25)
        ).grid(row=4, column=1, padx=10, pady=10)
        ##
        self.__btn_manual = Button(
            self,
            text = "manual",
            command = lambda: self.controller.send_signal(12),
            font=("Arial", 25)
        ).grid(row=5, column=1, padx=10, pady=10)

    def send_takeplane(self):
        """
        ...
        """
        for i in self.__listbox_takeplane.curselection():
            takeplane_node = self.__listbox_takeplane.get(i)
            break
        self.controller.send_signal(
            NODES_MAP.get(takeplane_node)
        )

    def send_leaveplane(self):
        """
        ...
        """
        for i in self.__listbox_leaveplane.curselection():
            leaveplane_node = self.__listbox_leaveplane.get(i)
            break
        self.controller.send_signal(
            NODES_MAP.get(leaveplane_node)
        )

    def launch_auto(self):
        """
        ...
        """
        self.controller.send_signal(2)