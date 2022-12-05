# This project requires PyBluez
from tkinter import Tk, Frame, Button, Label

# Window ---------------------------------------------------

class Manual(Frame):
    """
    ...
    """
    def __init__(self, parent, controller):
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

        label = Label(
            self,
            text = "Manual Control",
            font=("Arial", 22)
        ).grid(row=0, column=1, padx=5, pady=5)
        # label.pack(side = "top", fill = "x", pady = 10)

        ##
        self.__btn_avance = Button(
            self,
            text = "⬆",
            command = lambda: self.send_signal("w"),
            font=("Arial", 25)
        ).grid(row=2, column=1, padx=10, pady=10)
        # self.__btn_avance.pack()
        ##
        self.__btn_left = Button(
            self,
            text = "⬅",
            command = lambda: self.send_signal("a"),
            font=("Arial", 25)
        ).grid(row=3, column=0, padx=10, pady=10)
        # self.__btn_left.pack()
        ##
        self.__btn_right = Button(
            self,
            text = "➡",
            command = lambda: self.send_signal("d"),
            font=("Arial", 25)
        ).grid(row=3, column=2, padx=10, pady=10)
        # self.__btn_right.pack()
        ##
        self.__btn_reverse = Button(
            self,
            text = "⬇",
            command = lambda: self.send_signal("r"),
            font=("Arial", 25)
        ).grid(row=4, column=1, padx=10, pady=10)
        # self.__btn_reverse.pack()
        ##
        self.__btn_stop = Button(
            self,
            text = "stop",
            command = lambda: self.send_signal("s"),
            font=("Arial", 25)
        ).grid(row=5, column=1, padx=10, pady=10)
        # self.__btn_stop.pack()
        ##
        self.__btn_openp = Button(
            self,
            text = "open P",
            command = lambda: self.send_signal("p"),
            font=("Arial", 25)
        ).grid(row=6, column=0, padx=10, pady=10)
        # self.__btn_stop.pack()
        ##
        self.__btn_openp = Button(
            self,
            text = "close P",
            command = lambda: self.send_signal("c"),
            font=("Arial", 25)
        ).grid(row=6, column=2, padx=10, pady=10)
        # self.__btn_stop.pack()