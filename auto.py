# This project requires PyBluez
from tkinter import Frame, Button, Label, Listbox, Variable, SINGLE

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
        self.create_widgets()

    def send_signal(direction:str) -> None:
        """
        ...
        """
        print("Direction: ", direction)

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

        ##
        Label(
            self,
            text = "take plane Node: ",
            font=("Arial", 22)
        ).grid(row=1, column=0, padx=5, pady=5)
        self.__listbox_takeplane = Listbox(
            self,
            height=10,
            listvariable=self.take_nodes,
            selectmode=SINGLE
        ).grid(row=1, column=1, padx=10, pady=10)
        ##
        Label(
            self,
            text = "leave plane Node: ",
            font=("Arial", 22)
        ).grid(row=2, column=0, padx=5, pady=5)
        self.__listbox_leaveplane = Listbox(
            self,
            height=10,
            listvariable=self.leave_nodes,
            selectmode=SINGLE
        ).grid(row=2, column=1, padx=10, pady=10)

        ##
        self.__btn_clear = Button(
            self,
            text = "clear",
            command = lambda: self.send_signal("e"),
            font=("Arial", 25)
        ).grid(row=3, column=0, padx=10, pady=10)
        ##
        self.__btn_launch = Button(
            self,
            text = "launch",
            command = lambda: self.send_signal("l"),
            font=("Arial", 25)
        ).grid(row=3, column=1, padx=10, pady=10)
        ##
        self.__btn_stop = Button(
            self,
            text = "stop",
            command = lambda: self.send_signal("s"),
            font=("Arial", 25)
        ).grid(row=4, column=1, padx=10, pady=10)